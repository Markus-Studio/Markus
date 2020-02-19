pub type FieldId = u32;

pub enum SelectionValue {
    Null(),
    I32(i32),
    I64(i64),
    U32(u32),
    U64(u64),
    F32(f32),
    F64(f64),
    Bool(bool),
    Str(String),
    Uri(Vec<FieldId>),
}

pub enum Selection {
    AND(Vec<Box<Selection>>),
    OR(Vec<Box<Selection>>),
    NOT(Box<Selection>),
    EQ(SelectionValue, SelectionValue),
    NEQ(SelectionValue, SelectionValue),
    LT(SelectionValue, SelectionValue),
    LTE(SelectionValue, SelectionValue),
    GT(SelectionValue, SelectionValue),
    GTE(SelectionValue, SelectionValue),
}
