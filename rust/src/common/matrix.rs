pub struct Matrix<T> {
    row: usize,
    col: usize,
    data: Vec<T>,
}

impl<T> Matrix<T> {
    pub fn new(row: usize, col: usize, default: T) -> Matrix<T> {
        let size = row * col;
        let data = Vec::with_capacity(size);
        for _ in 0..size {
            data.push(default);
        }
        data.shrink_to_fit();
        Matrix { row, col, data }
    }

    pub fn get(&self, r: usize, c: usize) -> T {
        assert!(r < self.row && c < self.col);
        self.data[self.col * r + c]
    }

    pub fn set(&self, r: usize, c: usize, value: T) {
        assert!(r < self.row && c < self.col);
        self.data[self.col * r + c] = value;
    }
}
