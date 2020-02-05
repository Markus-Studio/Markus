#![allow(dead_code)]
use crate::program::{MarkusType, TypeId};
use std::collections::{HashMap, HashSet};

type FieldId = u32;

pub enum MarkusFunction {
    Add,
    Sub,
    Mul,
    Div,
    Pow,
    Floor,
    Ceil,
    Clamp,
    Min,
    Max,
    Count,
    Sqrt,
}

pub enum IrValue {
    Int(i64),
    Float(f64),
    Boolean(bool),
    Field(MarkusType, Vec<FieldId>),
    Parameter(MarkusType, String, Vec<FieldId>),
    InternalVariable(MarkusType, String, Vec<FieldId>),
    Call(MarkusType, MarkusFunction, Vec<IrValue>),
}

/// A funnel is always either `filter`, `map` or `reduce`.
#[derive(PartialEq)]
pub enum FunnelKind {
    /// Only decides if an element should stay in the result set or not.
    Filter,
    /// Converts values of type A to values of type B.
    Map,
    /// Collects data of type A produces a result of type B.
    Reduce,
}

pub enum Funnel {
    // `And` and `Or` can only contain `filter` or `map`, no `reduce`.
    And {
        funnels: Vec<Funnel>,
    },
    Or {
        funnels: Vec<Funnel>,
    },
    Is {
        selected: TypeId,
    },
    Eq {
        lhs: IrValue,
        rhs: IrValue,
    },
    GroupBy {
        axis: IrValue,
        inner_query: Vec<Funnel>,
    },
    Select {
        axis: IrValue,
    },
    Add {
        lhs: IrValue,
        rhs: IrValue,
    },
    Mul {
        lhs: IrValue,
        rhs: IrValue,
    },
    Div {
        lhs: IrValue,
        rhs: IrValue,
    },
    Sub {
        lhs: IrValue,
        rhs: IrValue,
    },
    Pow {
        lhs: IrValue,
        rhs: IrValue,
    },
    Floor {
        value: IrValue,
    },
    Ceil {
        value: IrValue,
    },
    Clamp {
        value: IrValue,
    },
    AggregationAvg {
        axis: IrValue,
    },
    AggregationCount {},
    AggregationMax {
        axis: IrValue,
    },
    AggregationMin {
        axis: IrValue,
    },
    AggregationMode {
        axis: IrValue,
    },
    AggregationRange {
        axis: IrValue,
    },
    AggregationSum {
        axis: IrValue,
    },
    AggregationVariance {
        axis: IrValue,
    },
    AggregationStdDeviation {
        axis: IrValue,
    },
    AggregationSkewness {
        axis: IrValue,
    },
    AggregationKurtosis {
        axis: IrValue,
    },
}

pub struct Query {
    name: String,
    parameters: Vec<String>,
    funnels: Vec<Funnel>,
}

pub struct Permission {
    name: String,
    funnels: Vec<Funnel>,
}

/// First 50 IDs are reserved for future usage.
pub enum InternalTypes {
    I32 = 1,
    I64 = 2,
    U32 = 3,
    U64 = 4,
    F32 = 5,
    F64 = 6,
    STRING = 7,
    BOOL = 8,
    TIME = 9,
}

pub struct Program {
    type_names: HashMap<TypeId, String>,
    field_names: HashMap<FieldId, String>,
    user_types: HashSet<TypeId>,
    queries: Vec<Query>,
    permissions: Vec<Permission>,
    is_matrix: Vec<(TypeId, TypeId, bool)>,
    type_fields: Vec<(
        FieldId,
        TypeId,
        (TypeId /* field type */, bool /* nullable? */),
    )>,
}

impl Funnel {
    /// Returns kind of this funnel.
    pub fn get_kind(&self) -> FunnelKind {
        match self {
            Funnel::And { funnels } | Funnel::Or { funnels } => {
                for funnel in funnels {
                    if funnel.get_kind() == FunnelKind::Map {
                        return FunnelKind::Map;
                    }
                }
                FunnelKind::Filter
            }
            Funnel::Is { .. } | Funnel::Eq { .. } => FunnelKind::Filter,
            Funnel::Select { .. } => FunnelKind::Map,
            Funnel::GroupBy { .. }
            | Funnel::AggregationAvg { .. }
            | Funnel::AggregationCount { .. }
            | Funnel::AggregationKurtosis { .. }
            | Funnel::AggregationMax { .. }
            | Funnel::AggregationMin { .. }
            | Funnel::AggregationMode { .. }
            | Funnel::AggregationRange { .. }
            | Funnel::AggregationSkewness { .. }
            | Funnel::AggregationStdDeviation { .. }
            | Funnel::AggregationSum { .. }
            | Funnel::AggregationVariance { .. } => FunnelKind::Reduce,
            Funnel::Add { .. }
            | Funnel::Sub { .. }
            | Funnel::Mul { .. }
            | Funnel::Div { .. }
            | Funnel::Pow { .. }
            | Funnel::Clamp { .. }
            | Funnel::Floor { .. }
            | Funnel::Ceil { .. } => FunnelKind::Map,
        }
    }
}
