use crate::ir::typespace::WordId;

pub enum IrValue {
    Null(),
    I32(i32),
    I64(i64),
    U32(u32),
    U64(u64),
    F32(f32),
    F64(f64),
    Bool(bool),
    Str(String),
    Uri(Vec<WordId>),
    Variable(String, Vec<WordId>),
}

pub enum Selection {
    IS(WordId),
    EQ(IrValue, IrValue),
    LT(IrValue, IrValue),
    GT(IrValue, IrValue),
    NIS(WordId),
    NEQ(IrValue, IrValue),
    LTE(IrValue, IrValue),
    GTE(IrValue, IrValue),
}
