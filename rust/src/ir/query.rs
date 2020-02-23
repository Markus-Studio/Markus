use crate::ir::selection::Selection;
use crate::ir::typespace::{IrType, WordId};
use crate::parser::ast::QueryNode;

pub struct Query {
    pub pipelines: Vec<Pipeline>,
}

pub enum Pipeline {
    Selection(Selection),
    Map(MapPipeline),
    Aggregation(AggregationPipeline),
}

pub enum MapPipeline {
    Select(Vec<WordId>),
}

pub enum AggregationPipeline {
    Sum(IrType, Vec<WordId>),
    Avg(IrType, Vec<WordId>),
    Min(IrType, Vec<WordId>),
    Max(IrType, Vec<WordId>),
    Count(),
}

impl Query {
    pub fn from_ast(query: &QueryNode) {}
}
