#[cfg(test)]
use crate::common::Matrix;
#[cfg(test)]
use crate::ir::*;

/// Creates a Truth Table for n variables.
#[cfg(test)]
fn create_truth_table(n: usize) -> Matrix<u8> {
    debug_assert!(n > 0);

    let row = (2 as usize).pow(n as u32);
    let col = n + 1; // reserve 1 extra column for the result.
    let mut matrix = Matrix::new(row, col, 0);

    let mut interval = row / 2;
    for c in 0..n as usize {
        let mut value = true;
        let mut r = 0;

        while r < row {
            for _ in 0..interval {
                if value {
                    matrix.set(r, c, 1);
                }
                r += 1;
            }
            value = !value;
        }

        interval /= 2;
    }

    matrix
}

#[cfg(test)]
fn eval_compound(matrix: &Matrix<u8>, row: usize, filter: &CompoundFilter) -> u8 {
    match filter {
        CompoundFilter::True => 1,
        CompoundFilter::False => 0,
        CompoundFilter::Conjunction(members) => {
            let mut result = true;

            for (neg, filter) in members {
                match filter {
                    AtomicFilter::TestVariable(id) => {
                        let tmp = matrix.get(row, *id) == 1;
                        result = result && if *neg { !tmp } else { tmp };
                    }
                    _ => unimplemented!(),
                }
            }

            if result {
                1
            } else {
                0
            }
        }
    }
}

#[cfg(test)]
fn eval_filter_vector(matrix: &Matrix<u8>, row: usize, vector: &FilterVector) -> u8 {
    match vector {
        FilterVector::True => 1,
        FilterVector::False => 0,
        FilterVector::Disjunction(filters) => {
            for filter in filters {
                if eval_compound(matrix, row, filter) == 1 {
                    return 1;
                }
            }
            0
        }
    }
}

#[cfg(test)]
fn compute(selection: Selection, n: usize) -> Matrix<u8> {
    let mut table = create_truth_table(n);
    let (row, _) = table.get_dimensions();
    for r in 0..row {
        if eval_filter_vector(&table, r, &selection) == 1 {
            table.set(r, n, 1);
        }
    }
    table
}

#[test]
fn test_selection_01() {
    // Expr: `A`
    let mut builder = builder::SelectionBuilder::new();
    builder.test_variable(0);
    #[rustfmt::skip]
    let expected = Matrix::from_vec(2, 2, vec![
        1, 1,
        0, 0
    ]);
    assert_eq!(compute(builder.build(), 1), expected)
}

#[test]
fn test_selection_02() {
    // Expr: `!A`
    let mut builder = builder::SelectionBuilder::new();
    builder.test_variable(0);
    builder.neg();
    #[rustfmt::skip]
    let expected = Matrix::from_vec(2, 2, vec![
        1, 0,
        0, 1
    ]);
    assert_eq!(compute(builder.build(), 1), expected)
}

#[test]
fn test_selection_03() {
    // Expr: `A | B`
    let mut builder = builder::SelectionBuilder::new();
    builder.test_variable(0);
    builder.test_variable(1);
    builder.or();
    #[rustfmt::skip]
    let expected = Matrix::from_vec(4, 3, vec![
        1, 1, 1,
        1, 0, 1,
        0, 1, 1,
        0, 0, 0
    ]);
    assert_eq!(compute(builder.build(), 2), expected)
}

#[test]
fn test_selection_04() {
    // Expr: `!(A | B)`
    let mut builder = builder::SelectionBuilder::new();
    builder.test_variable(0);
    builder.test_variable(1);
    builder.or();
    builder.neg();
    #[rustfmt::skip]
    let expected = Matrix::from_vec(4, 3, vec![
        1, 1, 0,
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
    ]);
    assert_eq!(compute(builder.build(), 2), expected)
}

#[test]
fn test_selection_05() {
    // Expr: `A & B`
    let mut builder = builder::SelectionBuilder::new();
    builder.test_variable(0);
    builder.test_variable(1);
    builder.and();
    #[rustfmt::skip]
    let expected = Matrix::from_vec(4, 3, vec![
        1, 1, 1,
        1, 0, 0,
        0, 1, 0,
        0, 0, 0
    ]);
    assert_eq!(compute(builder.build(), 2), expected)
}

#[test]
fn test_selection_06() {
    // Expr: `!(A & B)`
    let mut builder = builder::SelectionBuilder::new();
    builder.test_variable(0);
    builder.test_variable(1);
    builder.and();
    builder.neg();
    #[rustfmt::skip]
    let expected = Matrix::from_vec(4, 3, vec![
        1, 1, 0,
        1, 0, 1,
        0, 1, 1,
        0, 0, 1
    ]);
    assert_eq!(compute(builder.build(), 2), expected)
}

#[test]
fn test_selection_07() {
    // Expr: `A | !B`
    let mut builder = builder::SelectionBuilder::new();
    builder.test_variable(0);
    builder.test_variable(1);
    builder.neg();
    builder.or();
    #[rustfmt::skip]
    let expected = Matrix::from_vec(4, 3, vec![
        1, 1, 1,
        1, 0, 1,
        0, 1, 0,
        0, 0, 1
    ]);
    assert_eq!(compute(builder.build(), 2), expected)
}

#[test]
fn test_selection_08() {
    // Expr: `A & !B`
    let mut builder = builder::SelectionBuilder::new();
    builder.test_variable(0);
    builder.test_variable(1);
    builder.neg();
    builder.and();
    #[rustfmt::skip]
    let expected = Matrix::from_vec(4, 3, vec![
        1, 1, 0,
        1, 0, 1,
        0, 1, 0,
        0, 0, 0
    ]);
    assert_eq!(compute(builder.build(), 2), expected)
}

#[test]
fn test_selection_09() {
    // Expr: `(A & B) | (!A & !B)`
    let mut builder = builder::SelectionBuilder::new();
    // lhs
    builder.test_variable(0);
    builder.test_variable(1);
    builder.and();
    // rhs
    builder.test_variable(0);
    builder.neg();
    builder.test_variable(1);
    builder.neg();
    builder.and();
    // final or.
    builder.or();
    #[rustfmt::skip]
    let expected = Matrix::from_vec(4, 3, vec![
        1, 1, 1,
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
    ]);
    assert_eq!(compute(builder.build(), 2), expected)
}

#[test]
fn test_selection_10() {
    // Expr: `A | !A`
    let mut builder = builder::SelectionBuilder::new();
    builder.test_variable(0);
    builder.test_variable(0);
    builder.neg();
    builder.or();
    let selection = builder.build();
    assert!(selection.is_true());
}

#[test]
fn test_selection_11() {
    // Expr: `A & !A`
    let mut builder = builder::SelectionBuilder::new();
    builder.test_variable(0);
    builder.test_variable(0);
    builder.neg();
    builder.and();
    let selection = builder.build();
    assert!(selection.is_false());
}

#[test]
fn test_selection_12() {
    // Expr: `(A | B) & !(A | B)`
    let mut builder = builder::SelectionBuilder::new();
    builder.test_variable(0);
    builder.test_variable(1);
    builder.or();
    builder.test_variable(0);
    builder.test_variable(1);
    builder.or();
    builder.neg();
    builder.and();
    let selection = builder.build();
    assert!(selection.is_false());
}

#[test]
fn test_selection_13() {
    // Expr: `(A | B) | !(A | B)`
    let mut builder = builder::SelectionBuilder::new();
    builder.test_variable(0);
    builder.test_variable(1);
    builder.or();
    builder.test_variable(0);
    builder.test_variable(1);
    builder.or();
    builder.neg();
    builder.or();
    let selection = builder.build();
    assert!(selection.is_true());
}

#[test]
fn test_selection_14() {
    // Expr: `(A | B | C) | !(A | B)`
    let mut builder = builder::SelectionBuilder::new();
    builder.test_variable(0);
    builder.test_variable(1);
    builder.or();
    builder.test_variable(2);
    builder.or();
    builder.test_variable(0);
    builder.test_variable(1);
    builder.or();
    builder.neg();
    builder.or();
    let selection = builder.build();
    assert!(selection.is_true());
}

#[test]
fn test_selection_15() {
    // Expr: `(A | B) | !A`
    let mut builder = builder::SelectionBuilder::new();
    builder.test_variable(0);
    builder.test_variable(1);
    builder.or();
    builder.test_variable(0);
    builder.neg();
    builder.or();
    let selection = builder.build();
    assert!(selection.is_true());
}

#[test]
fn test_selection_16() {
    // Expr: `(A & B) & !A`
    let mut builder = builder::SelectionBuilder::new();
    builder.test_variable(0);
    builder.test_variable(1);
    builder.and();
    builder.test_variable(0);
    builder.neg();
    builder.and();
    let selection = builder.build();
    assert!(selection.is_false());
}

#[test]
fn test_selection_17() {
    // Expr: `A & (B & !A)`
    let mut builder = builder::SelectionBuilder::new();
    builder.test_variable(0);
    builder.test_variable(1);
    builder.test_variable(0);
    builder.neg();
    builder.and();
    builder.and();
    let selection = builder.build();
    assert!(selection.is_false());
}

#[test]
fn test_selection_18() {
    // Expr: `!((A & B) | (C & D))`
    let mut builder = builder::SelectionBuilder::new();
    builder.test_variable(0);
    builder.test_variable(1);
    builder.and();
    builder.test_variable(2);
    builder.test_variable(3);
    builder.and();
    builder.or();
    builder.neg();
    #[rustfmt::skip]
    let expected = Matrix::from_vec(16, 5, vec![
        1, 1, 1, 1, 0,
        1, 1, 1, 0, 0,
        1, 1, 0, 1, 0,
        1, 1, 0, 0, 0,
        1, 0, 1, 1, 0,
        1, 0, 1, 0, 1,
        1, 0, 0, 1, 1,
        1, 0, 0, 0, 1,
        0, 1, 1, 1, 0,
        0, 1, 1, 0, 1,
        0, 1, 0, 1, 1,
        0, 1, 0, 0, 1,
        0, 0, 1, 1, 0,
        0, 0, 1, 0, 1,
        0, 0, 0, 1, 1,
        0, 0, 0, 0, 1
    ]);
    assert_eq!(compute(builder.build(), 4), expected)
}
