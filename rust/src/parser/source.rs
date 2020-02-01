#![allow(dead_code)]
use crate::parser::diagnostics;
use crate::parser::tokenizer::Span;

#[derive(Copy, Clone)]
pub struct Position {
    /// Line position in the source, zero-based.
    pub line: usize,
    /// The character offset on a line in source, zero-based.
    pub character: usize,
}

#[derive(Copy, Clone)]
pub struct Range {
    /// The range's start position.
    pub start: Position,
    /// The range's end position.
    pub end: Position,
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
    range: Span,
    delta: i32,
}

/// The Source is used to store each source file and all of the diagnostics
/// related to them.
pub struct Source {
    /// The file name which this source is derived from.
    pub filename: String,
    /// All of the errors we encountered on this source file.
    pub diagnostics: Vec<diagnostics::Diagnostic>,
    /// Source code's content in UTF-16.
    /// We use UTF-16 to have an O(1) mapping from offset to character index.
    /// Also another reason to use a Vector in this situation over a string is
    /// it's so much easier/faster to edit the data.
    pub content: Vec<u16>,
    // Line's offsets.
    line_offsets: Option<Vec<usize>>,
}

impl Source {
    /// Constructs a new Source struct with the given filename and data.
    pub fn new(filename: &str, data: &str) -> Source {
        Source {
            filename: String::from(filename),
            diagnostics: vec![],
            content: data.encode_utf16().collect(),
            line_offsets: None,
        }
    }

    /// Returns true if there is no error attached to this source file.
    #[inline]
    pub fn is_good(&self) -> bool {
        self.diagnostics.is_empty()
    }

    /// Use this function to report an error on this source file.
    pub fn report(&mut self, diagnostic: diagnostics::Diagnostic) {
        self.diagnostics.push(diagnostic);
    }

    /// Returns the content of the source as a string.
    pub fn get_content_utf8(&self) -> String {
        String::from_utf16(&self.content).unwrap()
    }

    /// Recompute the line offsets.
    #[inline]
    fn compute_line_offsets(&mut self) {
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

        self.line_offsets = Some(result);
    }

    /// Returns the line_offsets of this source.
    pub fn get_line_offsets(&mut self) -> Vec<usize> {
        match &self.line_offsets {
            Some(offsets) => offsets.to_vec(),
            None => {
                self.compute_line_offsets();
                self.get_line_offsets()
            }
        }
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
    pub fn position_at(&mut self, mut offset: usize) -> Position {
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

    /// Apply a set of TextEdits to this source file, returns a range indicating
    /// the region that was effect (offsets are based on the current content)
    pub fn apply_edits(&mut self, edits: &mut Vec<TextEdit>) -> TextEditResult {
        if edits.len() == 0 {
            return TextEditResult::new(0, 0, 0);
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
                panic!("Overlaps");
            }
            last_modified_offset = start_offset;
        }

        // TODO(qti3e) Make it incremental, we can use the return value of
        // the current function which is effected bytes to implement
        // compute_line_offsets_incremental().
        self.compute_line_offsets();

        TextEditResult::new(min_effected_offset, max_effected_offset, delta)
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
            range: Range {
                start: start,
                end: end,
            },
            new_text: text,
        }
    }
}

impl Position {
    pub fn new(line: usize, character: usize) -> Position {
        Position {
            line: line,
            character: character,
        }
    }

    pub fn min(self, position: Position) -> Position {
        if self.line == position.line {
            if self.character < position.character {
                self
            } else {
                position
            }
        } else if self.line < position.line {
            self
        } else {
            position
        }
    }

    pub fn max(self, position: Position) -> Position {
        if self.line == position.line {
            if self.character < position.character {
                position
            } else {
                self
            }
        } else if self.line < position.line {
            position
        } else {
            self
        }
    }
}

impl Range {
    pub fn new(start: Position, end: Position) -> Range {
        Range {
            start: start.min(end),
            end: end.max(start),
        }
    }

    /// Returns true if the given position is inside the current range.
    #[inline]
    pub fn contains(&self, position: Position) -> bool {
        self.start.line >= position.line
            && self.start.character <= position.character
            && self.end.line <= position.line
            && self.end.character > position.character
    }
}

impl TextEditResult {
    pub fn new(start: usize, end: usize, delta: i32) -> TextEditResult {
        TextEditResult {
            range: Span::from_positions(start, end),
            delta: delta,
        }
    }
}
