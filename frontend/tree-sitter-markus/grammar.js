const common = {
  identifier: $ => /[a-zA-Z][a-zA-Z0-9_]*/,
  parameter_name: $ => /\$[a-zA-Z][a-zA-Z0-9_]*/,
  optional_flag: $ => token("?"),
  neg_flag: $ => token("-")
};

/**
 * An expression, it matches:
 *  - Query
 *  - Call
 *  - Boolean/Numeric/String literal.
 */
const expression = {
  ...common,
  _expression: $ => choice($.query, $._primitive_expression),
  _primitive_expression: $ =>
    choice(
      $.call,
      $.variable,
      $.uri,
      $.true_literal,
      $.false_literal,
      $.numeric_literal,
      $.string_literal
    ),
  call: $ =>
    seq(
      field("callee", $.identifier),
      "(",
      optional(commaSep(field("argument", $._expression))),
      ")"
    ),
  user: $ => token("%user"),
  variable: $ =>
    seq(
      field("base", choice($.parameter_name, $.identifier, $.user)),
      field("field", optional($.uri))
    ),
  uri: $ => repeat1(seq(".", field("part", $.identifier))),
  true_literal: $ => token("true"),
  false_literal: $ => token("false"),
  numeric_literal: _ => /[-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?/,
  string_literal: $ =>
    choice(
      seq(
        '"',
        repeat(choice(token.immediate(/[^"\\\n]+|\\\r?\n/), $.escape_sequence)),
        '"'
      ),
      seq(
        "'",
        repeat(choice(token.immediate(/[^'\\\n]+|\\\r?\n/), $.escape_sequence)),
        "'"
      )
    ),
  escape_sequence: $ =>
    token.immediate(
      seq(
        "\\",
        choice(
          /[^xu0-7]/,
          /[0-7]{1,3}/,
          /x[0-9a-fA-F]{2}/,
          /u[0-9a-fA-F]{4}/,
          /u{[0-9a-fA-F]+}/
        )
      )
    )
};

/**
 * A query body that matches:
 *
 * ```markus
 * {
 *  fn(),
 *  f2(arg0, arg2)
 * }
 * ```
 */
const query = {
  ...expression,
  query: $ => seq("{", commaSep(field("pipe", $.call)), "}")
};

// Function declaration parameters list.
const parameters = {
  ...common,
  _parameters: $ => commaSep1(field("parameter", $.parameter)),
  parameter: $ =>
    seq(
      field("name", $.parameter_name),
      field("optional", optional($.optional_flag)),
      ":",
      field("type", $.identifier)
    )
};

const binding = {
  ...expression,
  binding: $ => seq("{", commaSep(field("field", $.binding_field)), "}"),
  binding_field: $ =>
    seq(field("name", $.identifier), "=", field("value", $._binding_value)),
  _binding_value: $ => choice($._primitive_expression, $.binding)
};

const statement = {
  ...binding,
  _statement: $ =>
    choice($.create_statement, $.delete_statement, $.update_statement),
  create_statement: $ =>
    seq(
      "create",
      field("name", $.identifier),
      field("binding", $.binding),
      ";"
    ),
  delete_statement: $ =>
    seq("delete", field("target", $._statement_target), ";"),
  update_statement: $ =>
    seq(
      "update",
      field("target", $._statement_target),
      field("updates", $.binding),
      ";"
    ),
  _statement_target: $ => choice($.query, $.parameter_name)
};

/**
 * A type declaration:
 *
 * ```markus
 * type Name: B0, B1 {
 *  x: f32,
 *  y?: f32
 * }
 * ```
 */
const type_declaration = {
  type_declaration: $ =>
    seq(
      "type",
      field("name", $.identifier),
      optional(seq(":", commaSep1(field("base", $.identifier)))),
      "{",
      commaSep(field("field", $.type_field)),
      "}"
    ),
  type_field: $ =>
    seq(
      field("name", $.identifier),
      field("optional", optional($.optional_flag)),
      ":",
      field("field_type", $.identifier)
    )
};

const permission_declaration = {
  ...query,
  ...parameters,
  permission_declaration: $ =>
    seq(
      "permission",
      field("name", $.identifier),
      "(",
      optional($._parameters),
      ")",
      field("query", $.query)
    )
};

const query_declaration = {
  ...query,
  ...parameters,
  query_declaration: $ =>
    seq(
      "query",
      field("name", $.identifier),
      "(",
      optional($._parameters),
      ")",
      repeat(field("guard", $.guard)),
      field("query", $.query)
    ),
  guard: $ => seq(field("not", optional($.neg_flag)), "allow", field("selection", $.call))
};

const action_declaration = {
  ...statement,
  // for `guard`.
  ...query_declaration,
  action_declaration: $ =>
    seq(
      "action",
      field("name", $.identifier),
      "(",
      optional($._parameters),
      ")",
      repeat(field("guard", $.guard)),
      "{",
      repeat(field("statement", $._statement)),
      "}"
    )
};

module.exports = grammar({
  name: "markus",
  word: $ => $.identifier,
  extras: $ => [$.comment, /[\s\uFEFF\u2060\u200B\u00A0]/],
  supertypes: $ => [$._statement, $._declaration, $._expression],
  rules: {
    source_file: $ => repeat($._declaration),
    // Super types
    _declaration: $ =>
      choice(
        $.type_declaration,
        $.permission_declaration,
        $.query_declaration,
        $.action_declaration
      ),
    // http://stackoverflow.com/questions/13014947/regex-to-match-a-c-style-multiline-comment/36328890#36328890
    comment: $ =>
      token(
        choice(seq("//", /.*/), seq("/*", /[^*]*\*+([^/*][^*]*\*+)*/, "/"))
      ),
    ...type_declaration,
    ...permission_declaration,
    ...query_declaration,
    ...action_declaration
  }
});

function commaSep1(rule) {
  return seq(rule, repeat(seq(",", rule)), optional(","));
}

function commaSep(rule) {
  return optional(commaSep1(rule));
}
