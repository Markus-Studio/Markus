pub use tree_sitter::{Point, Range};

#[derive(PartialEq, Copy, Clone, Debug)]
pub struct Span {
    pub offset: usize,
    pub size: usize,
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
