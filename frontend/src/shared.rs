#[derive(PartialEq, Copy, Clone, Debug)]
pub struct Span {
    pub offset: usize,
    pub size: usize,
}

#[derive(Copy, Clone, Debug, PartialEq, Hash)]
pub struct Position {
    /// Line position in the source, zero-based.
    pub line: usize,
    /// The character offset on a line in source, zero-based.
    pub character: usize,
}

#[derive(Copy, Clone, PartialEq, Debug, Hash)]
pub struct Range {
    /// The range's start position.
    pub start: Position,
    /// The range's end position.
    pub end: Position,
}

impl Span {
    pub fn new(start: usize, size: usize) -> Span {
        Span {
            offset: start,
            size,
        }
    }

    pub fn from_positions(start: usize, end: usize) -> Span {
        Span {
            offset: start,
            size: end - start,
        }
    }
}

impl Position {
    pub fn new(line: usize, character: usize) -> Position {
        Position { line, character }
    }

    pub fn zero() -> Position {
        Position {
            line: 0,
            character: 0,
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
