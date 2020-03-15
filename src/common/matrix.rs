use num_traits::int::PrimInt;
use num_traits::ToPrimitive;

#[derive(PartialEq, Debug)]
pub struct Matrix<T, S = usize> {
    row: S,
    col: S,
    data: Vec<T>,
}

impl<T, S> Matrix<T, S>
where
    T: Copy,
    S: PrimInt + ToPrimitive,
{
    pub fn new(row: S, col: S, default: T) -> Matrix<T, S> {
        let size = (row * col).to_usize().unwrap();
        let mut data = Vec::with_capacity(size);
        for _ in 0..size {
            data.push(default);
        }
        data.shrink_to_fit();
        Matrix { row, col, data }
    }

    pub fn from_vec(row: S, col: S, data: Vec<T>) -> Matrix<T, S> {
        let size = (row * col).to_usize().unwrap();
        assert_eq!(size, data.len());
        Matrix { row, col, data }
    }

    pub fn get(&self, r: S, c: S) -> T {
        assert!(r < self.row && c < self.col);
        let index = (self.col * r + c).to_usize().unwrap();
        self.data[index]
    }

    pub fn set(&mut self, r: S, c: S, value: T) {
        assert!(r < self.row && c < self.col);
        let index = (self.col * r + c).to_usize().unwrap();
        self.data[index] = value;
    }

    pub fn get_dimensions(&self) -> (S, S) {
        (self.row, self.col)
    }
}
