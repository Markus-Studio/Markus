#![allow(dead_code)]
use super::shared::*;
use std::cell::RefCell;
use tree_sitter::{InputEdit, Language, Parser, Point, Tree};

extern "C" {
    fn tree_sitter_markus() -> Language;
}

pub struct TextEdit {
    /// The range of the text document to be manipulated. To insert
    /// text into a document create a range where start === end.
    pub range: Range,
    /// The string to be inserted. For delete operations use an
    /// empty string.
    pub new_text: String,
}

#[derive(PartialEq, Copy, Clone, Debug)]
pub struct TextEditResult {
    start_byte: usize,
    old_end_byte: usize,
    new_end_byte: usize,
    start_position: Position,
    old_end_position: Position,
    new_end_position: Position,
}

/// The Source is used to store each source file and all of the diagnostics
/// related to them.
pub struct Source {
    /// The file name which this source is derived from.
    pub filename: String,
    /// Source code's content in UTF-16.
    /// We use UTF-16 to have an O(1) mapping from offset to character index.
    /// Also another reason to use a Vector in this situation over a string is
    /// it's so much easier/faster to edit the data.
    pub content: Vec<u16>,
    // Line's offsets.
    line_offsets_cache: RefCell<Option<Vec<usize>>>,
    // The root node of the source code, lazily computed.
    tree: RefCell<Option<Tree>>,
    // The tree-sitter parser instance.
    parser: RefCell<Parser>,
}

impl Source {
    /// Constructs a new Source struct with the given filename and data.
    pub fn new(filename: &str, data: &str) -> Source {
        let language = unsafe { tree_sitter_markus() };
        let mut parser = Parser::new();
        parser
            .set_language(language)
            .expect("Tree-sitter error: cannot set the language on parser.");
        Source {
            filename: String::from(filename),
            content: data.encode_utf16().collect(),
            line_offsets_cache: RefCell::new(None),
            tree: RefCell::new(None),
            parser: RefCell::new(parser),
        }
    }

    /// Returns the content of the source as a string.
    pub fn get_content_utf8(&self) -> String {
        String::from_utf16(&self.content).unwrap()
    }

    /// Recompute the line offsets.
    #[inline]
    fn compute_line_offsets(&self) -> Vec<usize> {
        let data = &self.content;
        let mut result = vec![];
        let mut is_line_start = true;
        let mut skip = false;

        for i in 0..data.len() {
            if skip {
                skip = false;
                continue;
            }

            if is_line_start {
                result.push(i);
            }

            let byte = data[i];

            if byte == '\n' as u16 {
                is_line_start = true;
            } else if byte == '\r' as u16 {
                is_line_start = true;
                if i + 1 < data.len() && data[i + 1] == '\n' as u16 {
                    skip = true;
                }
            } else {
                is_line_start = false;
            }
        }

        if is_line_start {
            result.push(data.len());
        }

        result
    }

    /// Parse the source document, stores the result in the `tree` field.
    #[inline]
    fn parse_source(&self) -> Tree {
        let mut parser = self.parser.borrow_mut();
        // Reset the parser as we're doing a fresh parse.
        parser.reset();
        // Parse the content as UTF-16
        parser.parse_utf16(&self.content, None).unwrap()
    }

    #[inline]
    fn patch_tree(&mut self, edit: &InputEdit) -> Result<(), ()> {
        let old_tree = self.tree.get_mut().as_mut().ok_or(())?;
        old_tree.edit(edit);
        let mut parser = self.parser.borrow_mut();
        let tree = parser.parse_utf16(&self.content, Some(&old_tree)).unwrap();
        self.tree.replace(Some(tree));
        Ok(())
    }

    /// Returns the parse tree of this source document.
    pub fn get_tree(&self) -> Tree {
        self.tree
            .borrow_mut()
            .get_or_insert_with(|| self.parse_source())
            .clone()
    }

    /// Returns the line_offsets of this source.
    pub fn get_line_offsets(&self) -> Vec<usize> {
        self.line_offsets_cache
            .borrow_mut()
            .get_or_insert_with(|| self.compute_line_offsets())
            .clone()
    }

    /// Returns the offset of the given position.
    pub fn offset_at(&mut self, position: Position) -> usize {
        let line_offsets = self.get_line_offsets();

        if position.line >= line_offsets.len() {
            self.content.len()
        } else {
            let line_offset = line_offsets[position.line];
            let next_line_offset = match position.line + 1 < line_offsets.len() {
                true => line_offsets[position.line + 1],
                false => self.content.len(),
            };

            std::cmp::max(
                std::cmp::min(line_offset + position.character, next_line_offset),
                line_offset,
            )
        }
    }

    /// Returns the position at the given offset.
    pub fn position_at(&self, mut offset: usize) -> Position {
        offset = std::cmp::min(offset, self.content.len());

        let line_offsets = self.get_line_offsets();
        let mut low = 0;
        let mut high = line_offsets.len();

        if high == 0 {
            return Position::new(0, offset);
        }

        while low < high {
            let mid = (low + high) / 2;
            if line_offsets[mid] > offset {
                high = mid;
            } else {
                low = mid + 1;
            }
        }

        let line = low - 1;
        Position::new(line, offset - line_offsets[line])
    }

    /// Convert a Span to source Range.
    pub fn span_to_range(&self, span: Span) -> Range {
        // TODO(qti3e) It's possible to optimize this function, `low` in the second call to
        // position_at can be set to the `line` returned by first call to position_at
        Range {
            start: self.position_at(span.offset),
            end: self.position_at(span.offset + span.size),
        }
    }

    /// Apply a set of TextEdits to this source file, returns a range indicating
    /// the region that was effect (offsets are based on the current content)
    pub fn apply_edits(&mut self, edits: &mut Vec<TextEdit>) -> TextEditResult {
        if edits.len() == 0 {
            return TextEditResult::zero();
        }

        edits.sort_by(|a, b| {
            let diff = a.range.start.line.cmp(&b.range.start.line);
            if diff == std::cmp::Ordering::Equal {
                a.range.start.character.cmp(&b.range.end.character)
            } else {
                diff
            }
        });

        let mut last_modified_offset = self.content.len();

        let min_effected_offset = self.offset_at(edits[0].range.start);
        let mut max_effected_offset = 0;
        let mut delta: i32 = 0;

        edits.reverse();
        for e in edits {
            let start_offset = self.offset_at(e.range.start);
            let end_offset = self.offset_at(e.range.end);

            if end_offset > max_effected_offset {
                max_effected_offset = end_offset;
            }

            if end_offset <= last_modified_offset {
                for _ in start_offset..end_offset {
                    self.content.remove(start_offset);
                    delta -= 1;
                }

                for (i, c) in e.new_text.encode_utf16().enumerate() {
                    let offset = start_offset + i;
                    self.content.insert(offset, c);
                    delta += 1;
                }
            } else {
                // Currently we panic because we cannot rollback in case of an error.
                // Maybe an iteration just to validate the overlaps?
                panic!("Overlaps");
            }
            last_modified_offset = start_offset;
        }

        let old_range = self.span_to_range(Span::from_positions(
            min_effected_offset,
            max_effected_offset,
        ));

        // TODO(qti3e) Make it incremental, we can use the return value of
        // the current function which is effected bytes to implement
        // compute_line_offsets_incremental().
        self.compute_line_offsets();

        let new_end_byte = ((max_effected_offset as i32) + delta) as usize;
        let new_end_position = self.position_at(new_end_byte);

        let result = TextEditResult::new(
            min_effected_offset,
            max_effected_offset,
            new_end_byte,
            old_range.start,
            old_range.end,
            new_end_position,
        );

        // TODO(qti3e) This sucks, reexport the tree-sitter InputEdit as TextEdit?.
        self.patch_tree(&InputEdit {
            start_byte: result.start_byte,
            old_end_byte: result.old_end_byte,
            new_end_byte: result.new_end_byte,
            start_position: Point::new(result.start_position.line, result.start_position.character),
            old_end_position: Point::new(
                result.old_end_position.line,
                result.old_end_position.character,
            ),
            new_end_position: Point::new(
                result.new_end_position.line,
                result.new_end_position.character,
            ),
        })
        .ok();

        result
    }
}

impl TextEdit {
    /// Creates a new TextEdit that inserts the given text at the given position.
    pub fn insert(position: Position, text: String) -> TextEdit {
        TextEdit {
            range: Range {
                start: Position {
                    line: position.line,
                    character: position.character,
                },
                end: Position {
                    line: position.line,
                    character: position.character,
                },
            },
            new_text: text,
        }
    }

    /// Creates a new TextEdit that replaces the data in the given range with
    /// the given text.
    pub fn replace(start: Position, end: Position, text: String) -> TextEdit {
        TextEdit {
            range: Range { start, end },
            new_text: text,
        }
    }
}

impl TextEditResult {
    pub fn new(
        start: usize,
        old_end: usize,
        new_end_byte: usize,
        start_position: Position,
        old_end_position: Position,
        new_end_position: Position,
    ) -> TextEditResult {
        TextEditResult {
            start_byte: start,
            old_end_byte: old_end,
            new_end_byte,
            start_position,
            old_end_position,
            new_end_position,
        }
    }

    pub fn zero() -> TextEditResult {
        TextEditResult {
            start_byte: 0,
            old_end_byte: 0,
            new_end_byte: 0,
            start_position: Position::zero(),
            old_end_position: Position::zero(),
            new_end_position: Position::zero(),
        }
    }
}
