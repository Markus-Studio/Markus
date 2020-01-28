#![allow(dead_code)]
use crate::parser::diagnostics;

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

/// The Source is used to store each source file and all of the diagnostics
/// related to them.
pub struct Source {
    /// The file name which this source is derived from.
    pub filename: String,
    /// All of the errors we encountered on this source file.
    diagnostics: Vec<diagnostics::Diagnostic>,
    /// Source code's content in UTF-16.
    /// We use UTF-16 to have an O(1) mapping from offset to character index.
    /// Also another reason to use a Vector in this situation over a string is
    /// it's so much easier/faster to edit the data.
    content: Vec<u16>,
    // Line's offsets.
    line_offsets: Option<Vec<usize>>,
}

impl Source {
    /// Constructs a new Source struct with the given filename and data.
    pub fn new(filename: String, data: &str) -> Source {
        Source {
            filename: filename,
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

    /// Apply a set of TextEdits to this source file.
    pub fn apply_edits(&mut self, edits: &mut Vec<TextEdit>) {
        if edits.len() == 0 {
            return;
        }

        edits.sort_by(|a, b| {
            let diff = a.range.start.line.cmp(&b.range.start.line);
            if diff == std::cmp::Ordering::Equal {
                a.range.start.character.cmp(&b.range.end.character)
            } else {
                diff
            }
        });

        edits.reverse();

        let mut last_modified_offset = self.content.len();

        for e in edits {
            let start_offset = self.offset_at(e.range.start);
            let end_offset = self.offset_at(e.range.end);
            if end_offset <= last_modified_offset {
                for _ in start_offset..end_offset {
                    self.content.remove(start_offset);
                }

                for (i, c) in e.new_text.encode_utf16().enumerate() {
                    self.content.insert(start_offset + i, c);
                }
            } else {
                panic!("Overlaps");
            }
            last_modified_offset = start_offset;
        }

        self.compute_line_offsets();
    }
}

impl Position {
    pub fn new(line: usize, character: usize) -> Position {
        Position {
            line: line,
            character: character,
        }
    }
}

impl TextEdit {
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
