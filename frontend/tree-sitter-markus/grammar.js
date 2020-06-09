module.exports = grammar({
  name: "markus",
  word: $ => $.identifier,
  extras: $ => [$.comment, /[\s\uFEFF\u2060\u200B\u00A0]/],
  supertypes: $ => [$._statement, $._declaration, $._value],
  rules: {
    source_file: $ => repeat($._declaration),
    _declaration: $ =>
      choice(
        $.type_declaration,
        $.permission_declaration,
        $.query_declaration,
        $.action_declaration
      ),
    // -------- TYPE DECLARATION.
    type_declaration: $ =>
      seq(
        "type",
        field("name", $.identifier),
        field("bases", optional(seq(":", $.bases_list))),
        "{",
        field("body", optional($.type_fields)),
        "}"
      ),
    bases_list: $ => seq(commaSep1($.identifier), optional(",")),
    type_fields: $ => seq(commaSep1($.type_field), optional(",")),
    type_field: $ =>
      seq(
        field("name", $.identifier),
        field("optional", optional($.optional_flag)),
        ":",
        field("field_type", $.identifier)
      ),
    // -------- PERMISSION DECLARATION.
    permission_declaration: $ =>
      seq(
        "permission",
        field("name", $.identifier),
        field("parameters", $.parameters_list),
        field("body", $.query)
      ),
    // -------- QUERY DECLARATION.
    query_declaration: $ =>
      seq(
        "query",
        field("name", $.identifier),
        field("parameters", $.parameters_list),
        field("guards", optional($.guards_list)),
        field("body", $.query)
      ),
    guards_list: $ => repeat1($.guard),
    guard: $ => seq("allow", field("selection", $.call)),
    // -------- ACTION DECLARATION.
    action_declaration: $ =>
      seq(
        "action",
        field("name", $.identifier),
        field("parameters", $.parameters_list),
        field("guards", optional($.guards_list)),
        "{",
        field("body", optional($.statements)),
        "}"
      ),
    statements: $ => repeat1($._statement),
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
      seq(
        "delete",
        field("target", choice($.query, $.parameter_reference)),
        ";"
      ),
    update_statement: $ =>
      seq(
        "update",
        field("target", choice($.query, $.parameter_reference)),
        field("patch", $.binding),
        ";"
      ),
    binding: $ =>
      prec(1, seq("{", field("body", optional($.binding_fields)), "}")),
    binding_fields: $ => seq(commaSep1($.binding_field), optional(",")),
    binding_field: $ =>
      seq(field("name", $.identifier), ":", field("value", $._binding_value)),
    _binding_value: $ => choice($._value, $.binding),
    // ------- COMMON
    identifier: $ => /[a-zA-Z][a-zA-Z0-9_]*/,
    parameter_name: $ => /\$[a-zA-Z][a-zA-Z0-9_]*/,
    parameters_list: $ => seq("(", commaSep($.parameter), optional(","), ")"),
    optional_flag: $ => token("?"),
    parameter: $ =>
      seq(
        field("name", $.parameter_name),
        field("optional", optional($.optional_flag)),
        ":",
        field("type", $.identifier)
      ),
    _value: $ =>
      choice(
        $.query,
        $.call,
        $.number,
        $.string,
        $._boolean,
        $.variable,
        $.uri
      ),
    variable: $ =>
      seq(
        field("base", choice($.parameter_reference, $.type_reference, $.user)),
        field("field", optional($.uri))
      ),
    uri: $ => repeat1(seq(".", $.identifier)),
    _boolean: $ => choice($.true_literal, $.false_literal),
    true_literal: $ => token("true"),
    false_literal: $ => token("false"),
    parameter_reference: $ => $.parameter_name,
    type_reference: $ => $.identifier,
    user: $ => token("%user"),
    query: $ => seq("{", optional($._query_body), "}"),
    _query_body: $ => seq(commaSep1($.call), optional(",")),
    call: $ =>
      seq(field("callee", $.identifier), field("arguments", $.arguments)),
    arguments: $ => seq("(", commaSep(optional($._value)), ")"),
    number: _ => /[-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?/,
    string: $ =>
      choice(
        seq(
          '"',
          repeat(
            choice(token.immediate(/[^"\\\n]+|\\\r?\n/), $.escape_sequence)
          ),
          '"'
        ),
        seq(
          "'",
          repeat(
            choice(token.immediate(/[^'\\\n]+|\\\r?\n/), $.escape_sequence)
          ),
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
      ),
    // http://stackoverflow.com/questions/13014947/regex-to-match-a-c-style-multiline-comment/36328890#36328890
    comment: $ =>
      token(choice(seq("//", /.*/), seq("/*", /[^*]*\*+([^/*][^*]*\*+)*/, "/")))
  }
});

function commaSep1(rule) {
  return seq(rule, repeat(seq(",", rule)));
}

function commaSep(rule) {
  return optional(commaSep1(rule));
}
