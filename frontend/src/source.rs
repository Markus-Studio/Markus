#![allow(dead_code)]
use super::diagnostics;
use super::shared::*;
use super::verify::VerifyContext;
use std::cell::RefCell;
use std::io::{self, Write};
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
    start: usize,
    end: usize,
    delta: i32,
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
        // Parse the content as UTF-8, I tried parsing as UTF-16 but at the end
        // positions are wrongly computed. ()
        parser.parse(self.get_content_utf8(), None).unwrap()
    }

    #[inline]
    fn patch_tree(&mut self, edit: &InputEdit) -> Result<(), ()> {
        let content = self.get_content_utf8();
        let old_tree = self.tree.get_mut().as_mut().ok_or(())?;
        old_tree.edit(edit);
        let mut parser = self.parser.borrow_mut();
        let tree = parser.parse(content, Some(&old_tree)).unwrap();
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

    // Pretty-print the ast to stdout.
    pub fn ast(&self) {
        let stdout = io::stdout();
        let mut stdout = stdout.lock();
        let tree = self.get_tree();
        let mut cursor = tree.walk();

        // From:
        // https://github.com/tree-sitter/tree-sitter/blob/9b9329cb6c169a03458d6bc1bb594fff76b206ca/cli/src/parse.rs#L92
        let mut needs_newline = false;
        let mut indent_level = 0;
        let mut did_visit_children = false;
        loop {
            let node = cursor.node();
            let is_named = node.is_named();
            if did_visit_children {
                if is_named {
                    stdout.write(b")").unwrap();
                    needs_newline = true;
                }
                if cursor.goto_next_sibling() {
                    did_visit_children = false;
                } else if cursor.goto_parent() {
                    did_visit_children = true;
                    indent_level -= 1;
                } else {
                    break;
                }
            } else {
                if is_named {
                    if needs_newline {
                        stdout.write(b"\n").unwrap();
                    }
                    for _ in 0..indent_level {
                        stdout.write(b"  ").unwrap();
                    }
                    let start = node.start_position();
                    let end = node.end_position();
                    if let Some(field_name) = cursor.field_name() {
                        write!(&mut stdout, "{}: ", field_name).unwrap();
                    }
                    write!(
                        &mut stdout,
                        "({} [{}, {}] - [{}, {}]",
                        node.kind(),
                        start.row,
                        start.column,
                        end.row,
                        end.column
                    )
                    .unwrap();
                    needs_newline = true;
                }
                if cursor.goto_first_child() {
                    did_visit_children = false;
                    indent_level += 1;
                } else {
                    did_visit_children = true;
                }
            }
        }
        cursor.reset(tree.root_node());
        println!("");
    }

    pub fn verify(&self) -> Vec<diagnostics::Diagnostic> {
        let tree = self.get_tree();
        let mut ctx = VerifyContext::new(&self.content, &tree);
        ctx.verify();
        ctx.diagnostics
    }

    /// Returns the line_offsets of this source.
    pub fn get_line_offsets(&self) -> Vec<usize> {
        self.line_offsets_cache
            .borrow_mut()
            .get_or_insert_with(|| self.compute_line_offsets())
            .clone()
    }

    /// Returns the offset of the given position.
    pub fn offset_at(&self, position: Point) -> usize {
        let line_offsets = self.get_line_offsets();

        if position.row >= line_offsets.len() {
            self.content.len()
        } else {
            let line_offset = line_offsets[position.row];
            let next_line_offset = match position.row + 1 < line_offsets.len() {
                true => line_offsets[position.row + 1],
                false => self.content.len(),
            };

            std::cmp::max(
                std::cmp::min(line_offset + position.column, next_line_offset),
                line_offset,
            )
        }
    }

    /// Returns the position at the given offset.
    pub fn position_at(&self, mut offset: usize) -> Point {
        offset = std::cmp::min(offset, self.content.len());

        let line_offsets = self.get_line_offsets();
        let mut low = 0;
        let mut high = line_offsets.len();

        if high == 0 {
            return Point::new(0, offset);
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
        Point::new(line, offset - line_offsets[line])
    }

    /// Convert a Span to source Range.
    pub fn span_to_range(&self, span: Span) -> Range {
        // TODO(qti3e) It's possible to optimize this function, `low` in the second call to
        // position_at can be set to the `line` returned by first call to position_at
        let start_byte = span.offset;
        let end_byte = span.offset + span.size;
        Range {
            start_byte,
            end_byte,
            start_point: self.position_at(start_byte),
            end_point: self.position_at(end_byte),
        }
    }

    /// Apply a set of TextEdits to this source file, returns a range indicating
    /// the region that was effect (offsets are based on the current content)
    pub fn apply_edits(&mut self, edits: &mut Vec<TextEdit>) -> TextEditResult {
        if edits.len() == 0 {
            return TextEditResult::zero();
        }

        edits.sort_by(|a, b| {
            let diff = a.range.start_point.row.cmp(&b.range.start_point.row);
            if diff == std::cmp::Ordering::Equal {
                a.range.start_point.column.cmp(&b.range.end_point.column)
            } else {
                diff
            }
        });

        let mut last_modified_offset = self.content.len();

        let min_effected_offset = edits[0].range.start_byte;
        let mut max_effected_offset = 0;
        let mut delta: i32 = 0;

        edits.reverse();
        for e in edits {
            let start_offset = e.range.start_byte;
            let end_offset = e.range.end_byte;

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

        self.patch_tree(&InputEdit {
            start_byte: min_effected_offset,
            old_end_byte: max_effected_offset,
            new_end_byte,
            start_position: old_range.start_point,
            old_end_position: old_range.end_point,
            new_end_position,
        })
        .ok();

        TextEditResult::new(min_effected_offset, max_effected_offset, delta)
    }
}

impl TextEdit {
    /// Creates a new TextEdit that inserts the given text at the given position.
    pub fn insert(source: &Source, position: Point, text: String) -> TextEdit {
        let offset = source.offset_at(position);
        TextEdit {
            range: Range {
                start_byte: offset,
                end_byte: offset,
                start_point: position.clone(),
                end_point: position.clone(),
            },
            new_text: text,
        }
    }

    /// Creates a new TextEdit that replaces the data in the given range with
    /// the given text.
    pub fn replace(source: &Source, start: Point, end: Point, text: String) -> TextEdit {
        TextEdit {
            range: Range {
                start_byte: source.offset_at(start),
                end_byte: source.offset_at(end),
                start_point: start,
                end_point: end,
            },
            new_text: text,
        }
    }
}

impl TextEditResult {
    pub fn new(start: usize, end: usize, delta: i32) -> TextEditResult {
        TextEditResult { start, end, delta }
    }

    pub fn zero() -> TextEditResult {
        TextEditResult {
            start: 0,
            end: 0,
            delta: 0,
        }
    }
}

#[cfg(test)]
mod test {
    use super::*;

    // Editor tests taken from microsoft/vscode-languageserver-node

    #[cfg(test)]
    fn get_source(data: &str) -> Source {
        Source::new("foo://bar", data)
    }

    #[test]
    fn source_edit_inserts_0() {
        let mut source = get_source("012345678901234567890123456789");
        assert_eq!(
            source.apply_edits(&mut vec![TextEdit::insert(
                &source,
                Point::new(0, 0),
                String::from("Hello"),
            )]),
            TextEditResult::new(0, 0, 5)
        );
        assert_eq!(
            "Hello012345678901234567890123456789",
            source.get_content_utf8()
        );
    }

    #[test]
    fn source_edit_inserts_1() {
        let mut source = get_source("012345678901234567890123456789");
        assert_eq!(
            source.apply_edits(&mut vec![TextEdit::insert(
                &source,
                Point::new(0, 1),
                String::from("Hello"),
            )]),
            TextEditResult::new(1, 1, 5)
        );
        assert_eq!(
            "0Hello12345678901234567890123456789",
            source.get_content_utf8()
        );
    }

    #[test]
    fn source_edit_inserts_2() {
        let mut source = get_source("012345678901234567890123456789");
        assert_eq!(
            source.apply_edits(&mut vec![
                TextEdit::insert(&source, Point::new(0, 1), String::from("Hello")),
                TextEdit::insert(&source, Point::new(0, 1), String::from("World")),
            ]),
            TextEditResult::new(1, 1, 10)
        );
        assert_eq!(
            "0HelloWorld12345678901234567890123456789",
            source.get_content_utf8()
        );
    }

    #[test]
    fn source_edit_inserts_3() {
        let mut source = get_source("012345678901234567890123456789");
        assert_eq!(
            source.apply_edits(&mut vec![
                TextEdit::insert(&source, Point::new(0, 2), String::from("One")),
                TextEdit::insert(&source, Point::new(0, 1), String::from("Hello")),
                TextEdit::insert(&source, Point::new(0, 1), String::from("World")),
                TextEdit::insert(&source, Point::new(0, 2), String::from("Two")),
                TextEdit::insert(&source, Point::new(0, 2), String::from("Three")),
            ]),
            TextEditResult::new(1, 2, 21)
        );
        assert_eq!(
            "0HelloWorld1OneTwoThree2345678901234567890123456789",
            source.get_content_utf8()
        );
    }

    #[test]
    fn source_edit_replace_0() {
        let mut source = get_source("012345678901234567890123456789");
        assert_eq!(
            source.apply_edits(&mut vec![TextEdit::replace(
                &source,
                Point::new(0, 3),
                Point::new(0, 6),
                String::from("Hello"),
            )]),
            TextEditResult::new(3, 6, 2)
        );
        assert_eq!(
            "012Hello678901234567890123456789",
            source.get_content_utf8()
        );
    }

    #[test]
    fn source_edit_replace_1() {
        let mut source = get_source("012345678901234567890123456789");
        assert_eq!(
            source.apply_edits(&mut vec![
                TextEdit::replace(
                    &source,
                    Point::new(0, 3),
                    Point::new(0, 6),
                    String::from("Hello"),
                ),
                TextEdit::replace(
                    &source,
                    Point::new(0, 6),
                    Point::new(0, 9),
                    String::from("World"),
                ),
            ]),
            TextEditResult::new(3, 9, 4)
        );
        assert_eq!(
            "012HelloWorld901234567890123456789",
            source.get_content_utf8()
        );
    }

    #[test]
    fn source_edit_replace_2() {
        let mut source = get_source("012345678901234567890123456789");
        assert_eq!(
            source.apply_edits(&mut vec![
                TextEdit::replace(
                    &source,
                    Point::new(0, 3),
                    Point::new(0, 6),
                    String::from("Hello"),
                ),
                TextEdit::insert(&source, Point::new(0, 6), String::from("World")),
            ]),
            TextEditResult::new(3, 6, 7)
        );
        assert_eq!(
            "012HelloWorld678901234567890123456789",
            source.get_content_utf8()
        );
    }

    #[test]
    fn source_edit_replace_3() {
        let mut source = get_source("012345678901234567890123456789");
        assert_eq!(
            source.apply_edits(&mut vec![
                TextEdit::insert(&source, Point::new(0, 6), String::from("World")),
                TextEdit::replace(
                    &source,
                    Point::new(0, 3),
                    Point::new(0, 6),
                    String::from("Hello"),
                ),
            ]),
            TextEditResult::new(3, 6, 7)
        );
        assert_eq!(
            "012HelloWorld678901234567890123456789",
            source.get_content_utf8()
        );
    }

    #[test]
    fn source_edit_replace_4() {
        let mut source = get_source("012345678901234567890123456789");
        assert_eq!(
            source.apply_edits(&mut vec![
                TextEdit::insert(&source, Point::new(0, 3), String::from("World")),
                TextEdit::replace(
                    &source,
                    Point::new(0, 3),
                    Point::new(0, 6),
                    String::from("Hello"),
                ),
            ]),
            TextEditResult::new(3, 6, 7)
        );
        assert_eq!(
            "012WorldHello678901234567890123456789",
            source.get_content_utf8()
        );
    }

    #[test]
    fn source_edit_multiline() {
        let mut source = get_source("0\n1\n2\n3\n4");
        assert_eq!(
            source.apply_edits(&mut vec![
                TextEdit::replace(
                    &source,
                    Point::new(2, 0),
                    Point::new(3, 0),
                    String::from("Hello"),
                ),
                TextEdit::insert(&source, Point::new(1, 1), String::from("World")),
            ]),
            TextEditResult::new(3, 6, 8)
        );
        assert_eq!("0\n1World\nHello3\n4", source.get_content_utf8());
    }
}
