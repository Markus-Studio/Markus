#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 11
#define STATE_COUNT 151
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 75
#define ALIAS_COUNT 0
#define TOKEN_COUNT 30
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 16
#define MAX_ALIAS_SEQUENCE_LENGTH 7

enum {
  sym_identifier = 1,
  anon_sym_type = 2,
  anon_sym_COLON = 3,
  anon_sym_LBRACE = 4,
  anon_sym_RBRACE = 5,
  anon_sym_COMMA = 6,
  anon_sym_permission = 7,
  anon_sym_query = 8,
  anon_sym_allow = 9,
  anon_sym_action = 10,
  anon_sym_create = 11,
  anon_sym_SEMI = 12,
  anon_sym_delete = 13,
  anon_sym_update = 14,
  sym_parameter_name = 15,
  anon_sym_LPAREN = 16,
  anon_sym_RPAREN = 17,
  sym_optional_flag = 18,
  anon_sym_DOT = 19,
  sym_true_literal = 20,
  sym_false_literal = 21,
  sym_user = 22,
  sym_number = 23,
  anon_sym_DQUOTE = 24,
  aux_sym_string_token1 = 25,
  anon_sym_SQUOTE = 26,
  aux_sym_string_token2 = 27,
  sym_escape_sequence = 28,
  sym_comment = 29,
  sym_source_file = 30,
  sym__declaration = 31,
  sym_type_declaration = 32,
  sym__bases_list = 33,
  sym_type_fields = 34,
  sym_type_field = 35,
  sym_permission_declaration = 36,
  sym_query_declaration = 37,
  sym_guards_list = 38,
  sym_guard = 39,
  sym_action_declaration = 40,
  sym_statements = 41,
  sym__statement = 42,
  sym_create_statement = 43,
  sym_delete_statement = 44,
  sym_update_statement = 45,
  sym_binding = 46,
  sym_binding_fields = 47,
  sym_binding_field = 48,
  sym__binding_value = 49,
  sym_parameters_list = 50,
  sym_parameter = 51,
  sym__value = 52,
  sym_variable = 53,
  sym_uri = 54,
  sym__boolean = 55,
  sym_parameter_reference = 56,
  sym_type_reference = 57,
  sym_query = 58,
  sym__query_body = 59,
  sym_call = 60,
  sym_arguments = 61,
  sym_string = 62,
  aux_sym_source_file_repeat1 = 63,
  aux_sym__bases_list_repeat1 = 64,
  aux_sym_type_fields_repeat1 = 65,
  aux_sym_guards_list_repeat1 = 66,
  aux_sym_statements_repeat1 = 67,
  aux_sym_binding_fields_repeat1 = 68,
  aux_sym_parameters_list_repeat1 = 69,
  aux_sym_uri_repeat1 = 70,
  aux_sym__query_body_repeat1 = 71,
  aux_sym_arguments_repeat1 = 72,
  aux_sym_string_repeat1 = 73,
  aux_sym_string_repeat2 = 74,
};

static const char *ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_identifier] = "identifier",
  [anon_sym_type] = "type",
  [anon_sym_COLON] = ":",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
  [anon_sym_COMMA] = ",",
  [anon_sym_permission] = "permission",
  [anon_sym_query] = "query",
  [anon_sym_allow] = "allow",
  [anon_sym_action] = "action",
  [anon_sym_create] = "create",
  [anon_sym_SEMI] = ";",
  [anon_sym_delete] = "delete",
  [anon_sym_update] = "update",
  [sym_parameter_name] = "parameter_name",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [sym_optional_flag] = "optional_flag",
  [anon_sym_DOT] = ".",
  [sym_true_literal] = "true_literal",
  [sym_false_literal] = "false_literal",
  [sym_user] = "user",
  [sym_number] = "number",
  [anon_sym_DQUOTE] = "\"",
  [aux_sym_string_token1] = "string_token1",
  [anon_sym_SQUOTE] = "'",
  [aux_sym_string_token2] = "string_token2",
  [sym_escape_sequence] = "escape_sequence",
  [sym_comment] = "comment",
  [sym_source_file] = "source_file",
  [sym__declaration] = "_declaration",
  [sym_type_declaration] = "type_declaration",
  [sym__bases_list] = "_bases_list",
  [sym_type_fields] = "type_fields",
  [sym_type_field] = "type_field",
  [sym_permission_declaration] = "permission_declaration",
  [sym_query_declaration] = "query_declaration",
  [sym_guards_list] = "guards_list",
  [sym_guard] = "guard",
  [sym_action_declaration] = "action_declaration",
  [sym_statements] = "statements",
  [sym__statement] = "_statement",
  [sym_create_statement] = "create_statement",
  [sym_delete_statement] = "delete_statement",
  [sym_update_statement] = "update_statement",
  [sym_binding] = "binding",
  [sym_binding_fields] = "binding_fields",
  [sym_binding_field] = "binding_field",
  [sym__binding_value] = "_binding_value",
  [sym_parameters_list] = "parameters_list",
  [sym_parameter] = "parameter",
  [sym__value] = "_value",
  [sym_variable] = "variable",
  [sym_uri] = "uri",
  [sym__boolean] = "_boolean",
  [sym_parameter_reference] = "parameter_reference",
  [sym_type_reference] = "type_reference",
  [sym_query] = "query",
  [sym__query_body] = "_query_body",
  [sym_call] = "call",
  [sym_arguments] = "arguments",
  [sym_string] = "string",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
  [aux_sym__bases_list_repeat1] = "_bases_list_repeat1",
  [aux_sym_type_fields_repeat1] = "type_fields_repeat1",
  [aux_sym_guards_list_repeat1] = "guards_list_repeat1",
  [aux_sym_statements_repeat1] = "statements_repeat1",
  [aux_sym_binding_fields_repeat1] = "binding_fields_repeat1",
  [aux_sym_parameters_list_repeat1] = "parameters_list_repeat1",
  [aux_sym_uri_repeat1] = "uri_repeat1",
  [aux_sym__query_body_repeat1] = "_query_body_repeat1",
  [aux_sym_arguments_repeat1] = "arguments_repeat1",
  [aux_sym_string_repeat1] = "string_repeat1",
  [aux_sym_string_repeat2] = "string_repeat2",
};

static TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_identifier] = sym_identifier,
  [anon_sym_type] = anon_sym_type,
  [anon_sym_COLON] = anon_sym_COLON,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_permission] = anon_sym_permission,
  [anon_sym_query] = anon_sym_query,
  [anon_sym_allow] = anon_sym_allow,
  [anon_sym_action] = anon_sym_action,
  [anon_sym_create] = anon_sym_create,
  [anon_sym_SEMI] = anon_sym_SEMI,
  [anon_sym_delete] = anon_sym_delete,
  [anon_sym_update] = anon_sym_update,
  [sym_parameter_name] = sym_parameter_name,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [sym_optional_flag] = sym_optional_flag,
  [anon_sym_DOT] = anon_sym_DOT,
  [sym_true_literal] = sym_true_literal,
  [sym_false_literal] = sym_false_literal,
  [sym_user] = sym_user,
  [sym_number] = sym_number,
  [anon_sym_DQUOTE] = anon_sym_DQUOTE,
  [aux_sym_string_token1] = aux_sym_string_token1,
  [anon_sym_SQUOTE] = anon_sym_SQUOTE,
  [aux_sym_string_token2] = aux_sym_string_token2,
  [sym_escape_sequence] = sym_escape_sequence,
  [sym_comment] = sym_comment,
  [sym_source_file] = sym_source_file,
  [sym__declaration] = sym__declaration,
  [sym_type_declaration] = sym_type_declaration,
  [sym__bases_list] = sym__bases_list,
  [sym_type_fields] = sym_type_fields,
  [sym_type_field] = sym_type_field,
  [sym_permission_declaration] = sym_permission_declaration,
  [sym_query_declaration] = sym_query_declaration,
  [sym_guards_list] = sym_guards_list,
  [sym_guard] = sym_guard,
  [sym_action_declaration] = sym_action_declaration,
  [sym_statements] = sym_statements,
  [sym__statement] = sym__statement,
  [sym_create_statement] = sym_create_statement,
  [sym_delete_statement] = sym_delete_statement,
  [sym_update_statement] = sym_update_statement,
  [sym_binding] = sym_binding,
  [sym_binding_fields] = sym_binding_fields,
  [sym_binding_field] = sym_binding_field,
  [sym__binding_value] = sym__binding_value,
  [sym_parameters_list] = sym_parameters_list,
  [sym_parameter] = sym_parameter,
  [sym__value] = sym__value,
  [sym_variable] = sym_variable,
  [sym_uri] = sym_uri,
  [sym__boolean] = sym__boolean,
  [sym_parameter_reference] = sym_parameter_reference,
  [sym_type_reference] = sym_type_reference,
  [sym_query] = sym_query,
  [sym__query_body] = sym__query_body,
  [sym_call] = sym_call,
  [sym_arguments] = sym_arguments,
  [sym_string] = sym_string,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
  [aux_sym__bases_list_repeat1] = aux_sym__bases_list_repeat1,
  [aux_sym_type_fields_repeat1] = aux_sym_type_fields_repeat1,
  [aux_sym_guards_list_repeat1] = aux_sym_guards_list_repeat1,
  [aux_sym_statements_repeat1] = aux_sym_statements_repeat1,
  [aux_sym_binding_fields_repeat1] = aux_sym_binding_fields_repeat1,
  [aux_sym_parameters_list_repeat1] = aux_sym_parameters_list_repeat1,
  [aux_sym_uri_repeat1] = aux_sym_uri_repeat1,
  [aux_sym__query_body_repeat1] = aux_sym__query_body_repeat1,
  [aux_sym_arguments_repeat1] = aux_sym_arguments_repeat1,
  [aux_sym_string_repeat1] = aux_sym_string_repeat1,
  [aux_sym_string_repeat2] = aux_sym_string_repeat2,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [sym_identifier] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_type] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLON] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COMMA] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_permission] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_query] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_allow] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_action] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_create] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SEMI] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_delete] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_update] = {
    .visible = true,
    .named = false,
  },
  [sym_parameter_name] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [sym_optional_flag] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_DOT] = {
    .visible = true,
    .named = false,
  },
  [sym_true_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_false_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_user] = {
    .visible = true,
    .named = true,
  },
  [sym_number] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_DQUOTE] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_string_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_SQUOTE] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_string_token2] = {
    .visible = false,
    .named = false,
  },
  [sym_escape_sequence] = {
    .visible = true,
    .named = true,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym__declaration] = {
    .visible = false,
    .named = true,
  },
  [sym_type_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym__bases_list] = {
    .visible = false,
    .named = true,
  },
  [sym_type_fields] = {
    .visible = true,
    .named = true,
  },
  [sym_type_field] = {
    .visible = true,
    .named = true,
  },
  [sym_permission_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_query_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_guards_list] = {
    .visible = true,
    .named = true,
  },
  [sym_guard] = {
    .visible = true,
    .named = true,
  },
  [sym_action_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_statements] = {
    .visible = true,
    .named = true,
  },
  [sym__statement] = {
    .visible = false,
    .named = true,
  },
  [sym_create_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_delete_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_update_statement] = {
    .visible = true,
    .named = true,
  },
  [sym_binding] = {
    .visible = true,
    .named = true,
  },
  [sym_binding_fields] = {
    .visible = true,
    .named = true,
  },
  [sym_binding_field] = {
    .visible = true,
    .named = true,
  },
  [sym__binding_value] = {
    .visible = false,
    .named = true,
  },
  [sym_parameters_list] = {
    .visible = true,
    .named = true,
  },
  [sym_parameter] = {
    .visible = true,
    .named = true,
  },
  [sym__value] = {
    .visible = false,
    .named = true,
  },
  [sym_variable] = {
    .visible = true,
    .named = true,
  },
  [sym_uri] = {
    .visible = true,
    .named = true,
  },
  [sym__boolean] = {
    .visible = false,
    .named = true,
  },
  [sym_parameter_reference] = {
    .visible = true,
    .named = true,
  },
  [sym_type_reference] = {
    .visible = true,
    .named = true,
  },
  [sym_query] = {
    .visible = true,
    .named = true,
  },
  [sym__query_body] = {
    .visible = false,
    .named = true,
  },
  [sym_call] = {
    .visible = true,
    .named = true,
  },
  [sym_arguments] = {
    .visible = true,
    .named = true,
  },
  [sym_string] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__bases_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_type_fields_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_guards_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_statements_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_binding_fields_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_parameters_list_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_uri_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__query_body_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_arguments_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_string_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_string_repeat2] = {
    .visible = false,
    .named = false,
  },
};

enum {
  field_arguments = 1,
  field_base = 2,
  field_binding = 3,
  field_body = 4,
  field_callee = 5,
  field_field = 6,
  field_field_type = 7,
  field_guards = 8,
  field_name = 9,
  field_optional = 10,
  field_parameters = 11,
  field_patch = 12,
  field_selection = 13,
  field_target = 14,
  field_type = 15,
  field_value = 16,
};

static const char *ts_field_names[] = {
  [0] = NULL,
  [field_arguments] = "arguments",
  [field_base] = "base",
  [field_binding] = "binding",
  [field_body] = "body",
  [field_callee] = "callee",
  [field_field] = "field",
  [field_field_type] = "field_type",
  [field_guards] = "guards",
  [field_name] = "name",
  [field_optional] = "optional",
  [field_parameters] = "parameters",
  [field_patch] = "patch",
  [field_selection] = "selection",
  [field_target] = "target",
  [field_type] = "type",
  [field_value] = "value",
};

static const TSFieldMapSlice ts_field_map_slices[27] = {
  [1] = {.index = 0, .length = 1},
  [2] = {.index = 1, .length = 1},
  [3] = {.index = 2, .length = 3},
  [4] = {.index = 5, .length = 2},
  [5] = {.index = 7, .length = 2},
  [6] = {.index = 9, .length = 1},
  [7] = {.index = 10, .length = 4},
  [8] = {.index = 14, .length = 2},
  [9] = {.index = 16, .length = 1},
  [10] = {.index = 17, .length = 2},
  [11] = {.index = 19, .length = 2},
  [12] = {.index = 21, .length = 2},
  [13] = {.index = 23, .length = 2},
  [14] = {.index = 25, .length = 2},
  [15] = {.index = 27, .length = 3},
  [16] = {.index = 30, .length = 3},
  [17] = {.index = 33, .length = 3},
  [18] = {.index = 36, .length = 3},
  [19] = {.index = 39, .length = 3},
  [20] = {.index = 42, .length = 1},
  [21] = {.index = 43, .length = 4},
  [22] = {.index = 47, .length = 2},
  [23] = {.index = 49, .length = 2},
  [24] = {.index = 51, .length = 2},
  [25] = {.index = 53, .length = 1},
  [26] = {.index = 54, .length = 2},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_base, 0},
  [1] =
    {field_name, 1},
  [2] =
    {field_body, 3},
    {field_name, 1},
    {field_parameters, 2},
  [5] =
    {field_base, 0},
    {field_base, 1, .inherited = true},
  [7] =
    {field_body, 3},
    {field_name, 1},
  [9] =
    {field_selection, 1},
  [10] =
    {field_body, 4},
    {field_guards, 3},
    {field_name, 1},
    {field_parameters, 2},
  [14] =
    {field_name, 1},
    {field_parameters, 2},
  [16] =
    {field_base, 1},
  [17] =
    {field_base, 0, .inherited = true},
    {field_base, 1, .inherited = true},
  [19] =
    {field_base, 3, .inherited = true},
    {field_name, 1},
  [21] =
    {field_field_type, 2},
    {field_name, 0},
  [23] =
    {field_name, 0},
    {field_type, 2},
  [25] =
    {field_arguments, 1},
    {field_callee, 0},
  [27] =
    {field_body, 4},
    {field_name, 1},
    {field_parameters, 2},
  [30] =
    {field_guards, 3},
    {field_name, 1},
    {field_parameters, 2},
  [33] =
    {field_base, 3, .inherited = true},
    {field_body, 5},
    {field_name, 1},
  [36] =
    {field_field_type, 3},
    {field_name, 0},
    {field_optional, 1},
  [39] =
    {field_name, 0},
    {field_optional, 1},
    {field_type, 3},
  [42] =
    {field_target, 1},
  [43] =
    {field_body, 5},
    {field_guards, 3},
    {field_name, 1},
    {field_parameters, 2},
  [47] =
    {field_base, 0},
    {field_field, 1},
  [49] =
    {field_binding, 2},
    {field_name, 1},
  [51] =
    {field_patch, 2},
    {field_target, 1},
  [53] =
    {field_body, 1},
  [54] =
    {field_name, 0},
    {field_value, 2},
};

static TSSymbol ts_alias_sequences[27][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(27);
      if (lookahead == '"') ADVANCE(43);
      if (lookahead == '$') ADVANCE(25);
      if (lookahead == '%') ADVANCE(14);
      if (lookahead == '\'') ADVANCE(51);
      if (lookahead == '(') ADVANCE(35);
      if (lookahead == ')') ADVANCE(36);
      if (lookahead == ',') ADVANCE(31);
      if (lookahead == '.') ADVANCE(38);
      if (lookahead == '/') ADVANCE(7);
      if (lookahead == ':') ADVANCE(28);
      if (lookahead == ';') ADVANCE(32);
      if (lookahead == '?') ADVANCE(37);
      if (lookahead == '\\') ADVANCE(15);
      if (lookahead == '{') ADVANCE(29);
      if (lookahead == '}') ADVANCE(30);
      if (('+' <= lookahead && lookahead <= '-')) ADVANCE(10);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 160 ||
          lookahead == 8203 ||
          lookahead == 8288 ||
          lookahead == 65279) SKIP(26)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(40);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(33);
      END_STATE();
    case 1:
      if (lookahead == '\n') SKIP(6)
      if (lookahead == '\'') ADVANCE(51);
      if (lookahead == '/') ADVANCE(53);
      if (lookahead == '\\') ADVANCE(2);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 160 ||
          lookahead == 8203 ||
          lookahead == 8288 ||
          lookahead == 65279) ADVANCE(56);
      if (lookahead != 0) ADVANCE(58);
      END_STATE();
    case 2:
      if (lookahead == '\n') ADVANCE(52);
      if (lookahead == '\r') ADVANCE(60);
      if (lookahead == 'u') ADVANCE(16);
      if (lookahead == 'x') ADVANCE(24);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(63);
      if (lookahead != 0) ADVANCE(59);
      END_STATE();
    case 3:
      if (lookahead == '\n') SKIP(5)
      if (lookahead == '"') ADVANCE(43);
      if (lookahead == '/') ADVANCE(45);
      if (lookahead == '\\') ADVANCE(4);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 160 ||
          lookahead == 8203 ||
          lookahead == 8288 ||
          lookahead == 65279) ADVANCE(48);
      if (lookahead != 0) ADVANCE(50);
      END_STATE();
    case 4:
      if (lookahead == '\n') ADVANCE(44);
      if (lookahead == '\r') ADVANCE(61);
      if (lookahead == 'u') ADVANCE(16);
      if (lookahead == 'x') ADVANCE(24);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(63);
      if (lookahead != 0) ADVANCE(59);
      END_STATE();
    case 5:
      if (lookahead == '"') ADVANCE(43);
      if (lookahead == '/') ADVANCE(7);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 160 ||
          lookahead == 8203 ||
          lookahead == 8288 ||
          lookahead == 65279) SKIP(5)
      END_STATE();
    case 6:
      if (lookahead == '\'') ADVANCE(51);
      if (lookahead == '/') ADVANCE(7);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 160 ||
          lookahead == 8203 ||
          lookahead == 8288 ||
          lookahead == 65279) SKIP(6)
      END_STATE();
    case 7:
      if (lookahead == '*') ADVANCE(9);
      if (lookahead == '/') ADVANCE(65);
      END_STATE();
    case 8:
      if (lookahead == '*') ADVANCE(8);
      if (lookahead == '/') ADVANCE(64);
      if (lookahead != 0) ADVANCE(9);
      END_STATE();
    case 9:
      if (lookahead == '*') ADVANCE(8);
      if (lookahead != 0) ADVANCE(9);
      END_STATE();
    case 10:
      if (lookahead == '.') ADVANCE(19);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(40);
      END_STATE();
    case 11:
      if (lookahead == 'e') ADVANCE(12);
      END_STATE();
    case 12:
      if (lookahead == 'r') ADVANCE(39);
      END_STATE();
    case 13:
      if (lookahead == 's') ADVANCE(11);
      END_STATE();
    case 14:
      if (lookahead == 'u') ADVANCE(13);
      END_STATE();
    case 15:
      if (lookahead == 'u') ADVANCE(16);
      if (lookahead == 'x') ADVANCE(24);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(63);
      if (lookahead != 0) ADVANCE(59);
      END_STATE();
    case 16:
      if (lookahead == '{') ADVANCE(23);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(21);
      END_STATE();
    case 17:
      if (lookahead == '}') ADVANCE(59);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(17);
      END_STATE();
    case 18:
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(20);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(42);
      END_STATE();
    case 19:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(41);
      END_STATE();
    case 20:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(42);
      END_STATE();
    case 21:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(24);
      END_STATE();
    case 22:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(59);
      END_STATE();
    case 23:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(17);
      END_STATE();
    case 24:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(22);
      END_STATE();
    case 25:
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(34);
      END_STATE();
    case 26:
      if (eof) ADVANCE(27);
      if (lookahead == '"') ADVANCE(43);
      if (lookahead == '$') ADVANCE(25);
      if (lookahead == '%') ADVANCE(14);
      if (lookahead == '\'') ADVANCE(51);
      if (lookahead == '(') ADVANCE(35);
      if (lookahead == ')') ADVANCE(36);
      if (lookahead == ',') ADVANCE(31);
      if (lookahead == '.') ADVANCE(38);
      if (lookahead == '/') ADVANCE(7);
      if (lookahead == ':') ADVANCE(28);
      if (lookahead == ';') ADVANCE(32);
      if (lookahead == '?') ADVANCE(37);
      if (lookahead == '{') ADVANCE(29);
      if (lookahead == '}') ADVANCE(30);
      if (('+' <= lookahead && lookahead <= '-')) ADVANCE(10);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 160 ||
          lookahead == 8203 ||
          lookahead == 8288 ||
          lookahead == 65279) SKIP(26)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(40);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(33);
      END_STATE();
    case 27:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 28:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 29:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 30:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 31:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 32:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 33:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(33);
      END_STATE();
    case 34:
      ACCEPT_TOKEN(sym_parameter_name);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(34);
      END_STATE();
    case 35:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 36:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 37:
      ACCEPT_TOKEN(sym_optional_flag);
      END_STATE();
    case 38:
      ACCEPT_TOKEN(anon_sym_DOT);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(41);
      END_STATE();
    case 39:
      ACCEPT_TOKEN(sym_user);
      END_STATE();
    case 40:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(19);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(18);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(40);
      END_STATE();
    case 41:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(18);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(41);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(42);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 44:
      ACCEPT_TOKEN(aux_sym_string_token1);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(aux_sym_string_token1);
      if (lookahead == '*') ADVANCE(47);
      if (lookahead == '/') ADVANCE(49);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(50);
      END_STATE();
    case 46:
      ACCEPT_TOKEN(aux_sym_string_token1);
      if (lookahead == '*') ADVANCE(46);
      if (lookahead == '/') ADVANCE(50);
      if (lookahead == '\n' ||
          lookahead == '"' ||
          lookahead == '\\') ADVANCE(9);
      if (lookahead != 0) ADVANCE(47);
      END_STATE();
    case 47:
      ACCEPT_TOKEN(aux_sym_string_token1);
      if (lookahead == '*') ADVANCE(46);
      if (lookahead == '\n' ||
          lookahead == '"' ||
          lookahead == '\\') ADVANCE(9);
      if (lookahead != 0) ADVANCE(47);
      END_STATE();
    case 48:
      ACCEPT_TOKEN(aux_sym_string_token1);
      if (lookahead == '/') ADVANCE(45);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 160 ||
          lookahead == 8203 ||
          lookahead == 8288 ||
          lookahead == 65279) ADVANCE(48);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(50);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(aux_sym_string_token1);
      if (lookahead == '"' ||
          lookahead == '\\') ADVANCE(65);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(49);
      END_STATE();
    case 50:
      ACCEPT_TOKEN(aux_sym_string_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(50);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(anon_sym_SQUOTE);
      END_STATE();
    case 52:
      ACCEPT_TOKEN(aux_sym_string_token2);
      END_STATE();
    case 53:
      ACCEPT_TOKEN(aux_sym_string_token2);
      if (lookahead == '*') ADVANCE(55);
      if (lookahead == '/') ADVANCE(57);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(58);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(aux_sym_string_token2);
      if (lookahead == '*') ADVANCE(54);
      if (lookahead == '/') ADVANCE(58);
      if (lookahead == '\n' ||
          lookahead == '\'' ||
          lookahead == '\\') ADVANCE(9);
      if (lookahead != 0) ADVANCE(55);
      END_STATE();
    case 55:
      ACCEPT_TOKEN(aux_sym_string_token2);
      if (lookahead == '*') ADVANCE(54);
      if (lookahead == '\n' ||
          lookahead == '\'' ||
          lookahead == '\\') ADVANCE(9);
      if (lookahead != 0) ADVANCE(55);
      END_STATE();
    case 56:
      ACCEPT_TOKEN(aux_sym_string_token2);
      if (lookahead == '/') ADVANCE(53);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 160 ||
          lookahead == 8203 ||
          lookahead == 8288 ||
          lookahead == 65279) ADVANCE(56);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(58);
      END_STATE();
    case 57:
      ACCEPT_TOKEN(aux_sym_string_token2);
      if (lookahead == '\'' ||
          lookahead == '\\') ADVANCE(65);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(57);
      END_STATE();
    case 58:
      ACCEPT_TOKEN(aux_sym_string_token2);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(58);
      END_STATE();
    case 59:
      ACCEPT_TOKEN(sym_escape_sequence);
      END_STATE();
    case 60:
      ACCEPT_TOKEN(sym_escape_sequence);
      if (lookahead == '\n') ADVANCE(52);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(sym_escape_sequence);
      if (lookahead == '\n') ADVANCE(44);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(sym_escape_sequence);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(59);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(sym_escape_sequence);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(62);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(sym_comment);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(65);
      END_STATE();
    default:
      return false;
  }
}

static bool ts_lex_keywords(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (lookahead == 'a') ADVANCE(1);
      if (lookahead == 'c') ADVANCE(2);
      if (lookahead == 'd') ADVANCE(3);
      if (lookahead == 'f') ADVANCE(4);
      if (lookahead == 'p') ADVANCE(5);
      if (lookahead == 'q') ADVANCE(6);
      if (lookahead == 't') ADVANCE(7);
      if (lookahead == 'u') ADVANCE(8);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 160 ||
          lookahead == 8203 ||
          lookahead == 8288 ||
          lookahead == 65279) SKIP(0)
      END_STATE();
    case 1:
      if (lookahead == 'c') ADVANCE(9);
      if (lookahead == 'l') ADVANCE(10);
      END_STATE();
    case 2:
      if (lookahead == 'r') ADVANCE(11);
      END_STATE();
    case 3:
      if (lookahead == 'e') ADVANCE(12);
      END_STATE();
    case 4:
      if (lookahead == 'a') ADVANCE(13);
      END_STATE();
    case 5:
      if (lookahead == 'e') ADVANCE(14);
      END_STATE();
    case 6:
      if (lookahead == 'u') ADVANCE(15);
      END_STATE();
    case 7:
      if (lookahead == 'r') ADVANCE(16);
      if (lookahead == 'y') ADVANCE(17);
      END_STATE();
    case 8:
      if (lookahead == 'p') ADVANCE(18);
      END_STATE();
    case 9:
      if (lookahead == 't') ADVANCE(19);
      END_STATE();
    case 10:
      if (lookahead == 'l') ADVANCE(20);
      END_STATE();
    case 11:
      if (lookahead == 'e') ADVANCE(21);
      END_STATE();
    case 12:
      if (lookahead == 'l') ADVANCE(22);
      END_STATE();
    case 13:
      if (lookahead == 'l') ADVANCE(23);
      END_STATE();
    case 14:
      if (lookahead == 'r') ADVANCE(24);
      END_STATE();
    case 15:
      if (lookahead == 'e') ADVANCE(25);
      END_STATE();
    case 16:
      if (lookahead == 'u') ADVANCE(26);
      END_STATE();
    case 17:
      if (lookahead == 'p') ADVANCE(27);
      END_STATE();
    case 18:
      if (lookahead == 'd') ADVANCE(28);
      END_STATE();
    case 19:
      if (lookahead == 'i') ADVANCE(29);
      END_STATE();
    case 20:
      if (lookahead == 'o') ADVANCE(30);
      END_STATE();
    case 21:
      if (lookahead == 'a') ADVANCE(31);
      END_STATE();
    case 22:
      if (lookahead == 'e') ADVANCE(32);
      END_STATE();
    case 23:
      if (lookahead == 's') ADVANCE(33);
      END_STATE();
    case 24:
      if (lookahead == 'm') ADVANCE(34);
      END_STATE();
    case 25:
      if (lookahead == 'r') ADVANCE(35);
      END_STATE();
    case 26:
      if (lookahead == 'e') ADVANCE(36);
      END_STATE();
    case 27:
      if (lookahead == 'e') ADVANCE(37);
      END_STATE();
    case 28:
      if (lookahead == 'a') ADVANCE(38);
      END_STATE();
    case 29:
      if (lookahead == 'o') ADVANCE(39);
      END_STATE();
    case 30:
      if (lookahead == 'w') ADVANCE(40);
      END_STATE();
    case 31:
      if (lookahead == 't') ADVANCE(41);
      END_STATE();
    case 32:
      if (lookahead == 't') ADVANCE(42);
      END_STATE();
    case 33:
      if (lookahead == 'e') ADVANCE(43);
      END_STATE();
    case 34:
      if (lookahead == 'i') ADVANCE(44);
      END_STATE();
    case 35:
      if (lookahead == 'y') ADVANCE(45);
      END_STATE();
    case 36:
      ACCEPT_TOKEN(sym_true_literal);
      END_STATE();
    case 37:
      ACCEPT_TOKEN(anon_sym_type);
      END_STATE();
    case 38:
      if (lookahead == 't') ADVANCE(46);
      END_STATE();
    case 39:
      if (lookahead == 'n') ADVANCE(47);
      END_STATE();
    case 40:
      ACCEPT_TOKEN(anon_sym_allow);
      END_STATE();
    case 41:
      if (lookahead == 'e') ADVANCE(48);
      END_STATE();
    case 42:
      if (lookahead == 'e') ADVANCE(49);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(sym_false_literal);
      END_STATE();
    case 44:
      if (lookahead == 's') ADVANCE(50);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(anon_sym_query);
      END_STATE();
    case 46:
      if (lookahead == 'e') ADVANCE(51);
      END_STATE();
    case 47:
      ACCEPT_TOKEN(anon_sym_action);
      END_STATE();
    case 48:
      ACCEPT_TOKEN(anon_sym_create);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(anon_sym_delete);
      END_STATE();
    case 50:
      if (lookahead == 's') ADVANCE(52);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(anon_sym_update);
      END_STATE();
    case 52:
      if (lookahead == 'i') ADVANCE(53);
      END_STATE();
    case 53:
      if (lookahead == 'o') ADVANCE(54);
      END_STATE();
    case 54:
      if (lookahead == 'n') ADVANCE(55);
      END_STATE();
    case 55:
      ACCEPT_TOKEN(anon_sym_permission);
      END_STATE();
    default:
      return false;
  }
}

static TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 0},
  [2] = {.lex_state = 0},
  [3] = {.lex_state = 0},
  [4] = {.lex_state = 0},
  [5] = {.lex_state = 0},
  [6] = {.lex_state = 0},
  [7] = {.lex_state = 0},
  [8] = {.lex_state = 0},
  [9] = {.lex_state = 0},
  [10] = {.lex_state = 0},
  [11] = {.lex_state = 0},
  [12] = {.lex_state = 0},
  [13] = {.lex_state = 0},
  [14] = {.lex_state = 0},
  [15] = {.lex_state = 0},
  [16] = {.lex_state = 0},
  [17] = {.lex_state = 0},
  [18] = {.lex_state = 0},
  [19] = {.lex_state = 0},
  [20] = {.lex_state = 0},
  [21] = {.lex_state = 0},
  [22] = {.lex_state = 0},
  [23] = {.lex_state = 0},
  [24] = {.lex_state = 0},
  [25] = {.lex_state = 0},
  [26] = {.lex_state = 0},
  [27] = {.lex_state = 0},
  [28] = {.lex_state = 0},
  [29] = {.lex_state = 0},
  [30] = {.lex_state = 0},
  [31] = {.lex_state = 0},
  [32] = {.lex_state = 0},
  [33] = {.lex_state = 0},
  [34] = {.lex_state = 0},
  [35] = {.lex_state = 0},
  [36] = {.lex_state = 0},
  [37] = {.lex_state = 0},
  [38] = {.lex_state = 1},
  [39] = {.lex_state = 1},
  [40] = {.lex_state = 0},
  [41] = {.lex_state = 3},
  [42] = {.lex_state = 0},
  [43] = {.lex_state = 0},
  [44] = {.lex_state = 3},
  [45] = {.lex_state = 3},
  [46] = {.lex_state = 0},
  [47] = {.lex_state = 1},
  [48] = {.lex_state = 0},
  [49] = {.lex_state = 0},
  [50] = {.lex_state = 0},
  [51] = {.lex_state = 0},
  [52] = {.lex_state = 0},
  [53] = {.lex_state = 0},
  [54] = {.lex_state = 0},
  [55] = {.lex_state = 0},
  [56] = {.lex_state = 0},
  [57] = {.lex_state = 0},
  [58] = {.lex_state = 0},
  [59] = {.lex_state = 0},
  [60] = {.lex_state = 0},
  [61] = {.lex_state = 0},
  [62] = {.lex_state = 0},
  [63] = {.lex_state = 0},
  [64] = {.lex_state = 0},
  [65] = {.lex_state = 0},
  [66] = {.lex_state = 0},
  [67] = {.lex_state = 0},
  [68] = {.lex_state = 0},
  [69] = {.lex_state = 0},
  [70] = {.lex_state = 0},
  [71] = {.lex_state = 0},
  [72] = {.lex_state = 0},
  [73] = {.lex_state = 0},
  [74] = {.lex_state = 0},
  [75] = {.lex_state = 0},
  [76] = {.lex_state = 0},
  [77] = {.lex_state = 0},
  [78] = {.lex_state = 0},
  [79] = {.lex_state = 0},
  [80] = {.lex_state = 0},
  [81] = {.lex_state = 0},
  [82] = {.lex_state = 0},
  [83] = {.lex_state = 0},
  [84] = {.lex_state = 0},
  [85] = {.lex_state = 0},
  [86] = {.lex_state = 0},
  [87] = {.lex_state = 0},
  [88] = {.lex_state = 0},
  [89] = {.lex_state = 0},
  [90] = {.lex_state = 0},
  [91] = {.lex_state = 0},
  [92] = {.lex_state = 0},
  [93] = {.lex_state = 0},
  [94] = {.lex_state = 0},
  [95] = {.lex_state = 0},
  [96] = {.lex_state = 0},
  [97] = {.lex_state = 0},
  [98] = {.lex_state = 0},
  [99] = {.lex_state = 0},
  [100] = {.lex_state = 0},
  [101] = {.lex_state = 0},
  [102] = {.lex_state = 0},
  [103] = {.lex_state = 0},
  [104] = {.lex_state = 0},
  [105] = {.lex_state = 0},
  [106] = {.lex_state = 0},
  [107] = {.lex_state = 0},
  [108] = {.lex_state = 0},
  [109] = {.lex_state = 0},
  [110] = {.lex_state = 0},
  [111] = {.lex_state = 0},
  [112] = {.lex_state = 0},
  [113] = {.lex_state = 0},
  [114] = {.lex_state = 0},
  [115] = {.lex_state = 0},
  [116] = {.lex_state = 0},
  [117] = {.lex_state = 0},
  [118] = {.lex_state = 0},
  [119] = {.lex_state = 0},
  [120] = {.lex_state = 0},
  [121] = {.lex_state = 0},
  [122] = {.lex_state = 0},
  [123] = {.lex_state = 0},
  [124] = {.lex_state = 0},
  [125] = {.lex_state = 0},
  [126] = {.lex_state = 0},
  [127] = {.lex_state = 0},
  [128] = {.lex_state = 0},
  [129] = {.lex_state = 0},
  [130] = {.lex_state = 0},
  [131] = {.lex_state = 0},
  [132] = {.lex_state = 0},
  [133] = {.lex_state = 0},
  [134] = {.lex_state = 0},
  [135] = {.lex_state = 0},
  [136] = {.lex_state = 0},
  [137] = {.lex_state = 0},
  [138] = {.lex_state = 0},
  [139] = {.lex_state = 0},
  [140] = {.lex_state = 0},
  [141] = {.lex_state = 0},
  [142] = {.lex_state = 0},
  [143] = {.lex_state = 0},
  [144] = {.lex_state = 0},
  [145] = {.lex_state = 0},
  [146] = {.lex_state = 0},
  [147] = {.lex_state = 0},
  [148] = {.lex_state = 0},
  [149] = {.lex_state = 0},
  [150] = {.lex_state = 0},
};

static uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_identifier] = ACTIONS(1),
    [anon_sym_type] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_permission] = ACTIONS(1),
    [anon_sym_query] = ACTIONS(1),
    [anon_sym_allow] = ACTIONS(1),
    [anon_sym_action] = ACTIONS(1),
    [anon_sym_create] = ACTIONS(1),
    [anon_sym_SEMI] = ACTIONS(1),
    [anon_sym_delete] = ACTIONS(1),
    [anon_sym_update] = ACTIONS(1),
    [sym_parameter_name] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [sym_optional_flag] = ACTIONS(1),
    [anon_sym_DOT] = ACTIONS(1),
    [sym_true_literal] = ACTIONS(1),
    [sym_false_literal] = ACTIONS(1),
    [sym_user] = ACTIONS(1),
    [sym_number] = ACTIONS(1),
    [anon_sym_DQUOTE] = ACTIONS(1),
    [anon_sym_SQUOTE] = ACTIONS(1),
    [sym_escape_sequence] = ACTIONS(1),
    [sym_comment] = ACTIONS(3),
  },
  [1] = {
    [sym_source_file] = STATE(143),
    [sym__declaration] = STATE(5),
    [sym_type_declaration] = STATE(5),
    [sym_permission_declaration] = STATE(5),
    [sym_query_declaration] = STATE(5),
    [sym_action_declaration] = STATE(5),
    [aux_sym_source_file_repeat1] = STATE(5),
    [ts_builtin_sym_end] = ACTIONS(5),
    [anon_sym_type] = ACTIONS(7),
    [anon_sym_permission] = ACTIONS(9),
    [anon_sym_query] = ACTIONS(11),
    [anon_sym_action] = ACTIONS(13),
    [sym_comment] = ACTIONS(3),
  },
};

static uint16_t ts_small_parse_table[] = {
  [0] = 16,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(15), 1,
      sym_identifier,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    ACTIONS(19), 1,
      anon_sym_COMMA,
    ACTIONS(21), 1,
      sym_parameter_name,
    ACTIONS(23), 1,
      anon_sym_RPAREN,
    ACTIONS(25), 1,
      anon_sym_DOT,
    ACTIONS(29), 1,
      sym_user,
    ACTIONS(31), 1,
      sym_number,
    ACTIONS(33), 1,
      anon_sym_DQUOTE,
    ACTIONS(35), 1,
      anon_sym_SQUOTE,
    STATE(23), 1,
      aux_sym_uri_repeat1,
    STATE(55), 1,
      aux_sym_arguments_repeat1,
    ACTIONS(27), 2,
      sym_true_literal,
      sym_false_literal,
    STATE(13), 2,
      sym_parameter_reference,
      sym_type_reference,
    STATE(65), 7,
      sym__value,
      sym_variable,
      sym_uri,
      sym__boolean,
      sym_query,
      sym_call,
      sym_string,
  [57] = 13,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(15), 1,
      sym_identifier,
    ACTIONS(21), 1,
      sym_parameter_name,
    ACTIONS(25), 1,
      anon_sym_DOT,
    ACTIONS(29), 1,
      sym_user,
    ACTIONS(33), 1,
      anon_sym_DQUOTE,
    ACTIONS(35), 1,
      anon_sym_SQUOTE,
    ACTIONS(37), 1,
      anon_sym_LBRACE,
    ACTIONS(41), 1,
      sym_number,
    STATE(23), 1,
      aux_sym_uri_repeat1,
    ACTIONS(39), 2,
      sym_true_literal,
      sym_false_literal,
    STATE(13), 2,
      sym_parameter_reference,
      sym_type_reference,
    STATE(100), 9,
      sym_binding,
      sym__binding_value,
      sym__value,
      sym_variable,
      sym_uri,
      sym__boolean,
      sym_query,
      sym_call,
      sym_string,
  [107] = 14,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(15), 1,
      sym_identifier,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    ACTIONS(21), 1,
      sym_parameter_name,
    ACTIONS(25), 1,
      anon_sym_DOT,
    ACTIONS(29), 1,
      sym_user,
    ACTIONS(33), 1,
      anon_sym_DQUOTE,
    ACTIONS(35), 1,
      anon_sym_SQUOTE,
    ACTIONS(47), 1,
      sym_number,
    STATE(23), 1,
      aux_sym_uri_repeat1,
    ACTIONS(43), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
    ACTIONS(45), 2,
      sym_true_literal,
      sym_false_literal,
    STATE(13), 2,
      sym_parameter_reference,
      sym_type_reference,
    STATE(88), 7,
      sym__value,
      sym_variable,
      sym_uri,
      sym__boolean,
      sym_query,
      sym_call,
      sym_string,
  [159] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 1,
      anon_sym_type,
    ACTIONS(9), 1,
      anon_sym_permission,
    ACTIONS(11), 1,
      anon_sym_query,
    ACTIONS(13), 1,
      anon_sym_action,
    ACTIONS(49), 1,
      ts_builtin_sym_end,
    STATE(6), 6,
      sym__declaration,
      sym_type_declaration,
      sym_permission_declaration,
      sym_query_declaration,
      sym_action_declaration,
      aux_sym_source_file_repeat1,
  [186] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(51), 1,
      ts_builtin_sym_end,
    ACTIONS(53), 1,
      anon_sym_type,
    ACTIONS(56), 1,
      anon_sym_permission,
    ACTIONS(59), 1,
      anon_sym_query,
    ACTIONS(62), 1,
      anon_sym_action,
    STATE(6), 6,
      sym__declaration,
      sym_type_declaration,
      sym_permission_declaration,
      sym_query_declaration,
      sym_action_declaration,
      aux_sym_source_file_repeat1,
  [213] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(65), 1,
      anon_sym_RBRACE,
    ACTIONS(67), 1,
      anon_sym_create,
    ACTIONS(69), 1,
      anon_sym_delete,
    ACTIONS(71), 1,
      anon_sym_update,
    STATE(138), 1,
      sym_statements,
    STATE(12), 5,
      sym__statement,
      sym_create_statement,
      sym_delete_statement,
      sym_update_statement,
      aux_sym_statements_repeat1,
  [239] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(73), 10,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
      anon_sym_SEMI,
      anon_sym_RPAREN,
  [255] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(67), 1,
      anon_sym_create,
    ACTIONS(69), 1,
      anon_sym_delete,
    ACTIONS(71), 1,
      anon_sym_update,
    ACTIONS(75), 1,
      anon_sym_RBRACE,
    STATE(150), 1,
      sym_statements,
    STATE(12), 5,
      sym__statement,
      sym_create_statement,
      sym_delete_statement,
      sym_update_statement,
      aux_sym_statements_repeat1,
  [281] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(77), 1,
      anon_sym_RBRACE,
    ACTIONS(79), 1,
      anon_sym_create,
    ACTIONS(82), 1,
      anon_sym_delete,
    ACTIONS(85), 1,
      anon_sym_update,
    STATE(10), 5,
      sym__statement,
      sym_create_statement,
      sym_delete_statement,
      sym_update_statement,
      aux_sym_statements_repeat1,
  [304] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(88), 9,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_LBRACE,
      anon_sym_COMMA,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
      anon_sym_SEMI,
      anon_sym_RPAREN,
  [319] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(67), 1,
      anon_sym_create,
    ACTIONS(69), 1,
      anon_sym_delete,
    ACTIONS(71), 1,
      anon_sym_update,
    ACTIONS(90), 1,
      anon_sym_RBRACE,
    STATE(10), 5,
      sym__statement,
      sym_create_statement,
      sym_delete_statement,
      sym_update_statement,
      aux_sym_statements_repeat1,
  [342] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(94), 1,
      anon_sym_DOT,
    STATE(23), 1,
      aux_sym_uri_repeat1,
    STATE(74), 1,
      sym_uri,
    ACTIONS(92), 3,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [360] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(96), 1,
      sym_identifier,
    ACTIONS(98), 1,
      anon_sym_RBRACE,
    STATE(60), 1,
      sym_call,
    STATE(63), 1,
      sym_binding_field,
    STATE(131), 1,
      sym_binding_fields,
    STATE(132), 1,
      sym__query_body,
  [382] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(100), 6,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      anon_sym_DOT,
  [394] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(104), 1,
      anon_sym_LPAREN,
    STATE(34), 1,
      sym_arguments,
    ACTIONS(102), 4,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_DOT,
  [410] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    ACTIONS(106), 1,
      anon_sym_allow,
    STATE(33), 1,
      sym_query,
    STATE(122), 1,
      sym_guards_list,
    STATE(49), 2,
      sym_guard,
      aux_sym_guards_list_repeat1,
  [430] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(106), 1,
      anon_sym_allow,
    ACTIONS(108), 1,
      anon_sym_LBRACE,
    STATE(124), 1,
      sym_guards_list,
    STATE(49), 2,
      sym_guard,
      aux_sym_guards_list_repeat1,
  [447] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(110), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [458] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(112), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [469] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(114), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [480] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(116), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [491] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(94), 1,
      anon_sym_DOT,
    STATE(27), 1,
      aux_sym_uri_repeat1,
    ACTIONS(118), 3,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [506] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(120), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [517] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(122), 5,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_allow,
      anon_sym_RPAREN,
  [528] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(124), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [539] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(128), 1,
      anon_sym_DOT,
    STATE(27), 1,
      aux_sym_uri_repeat1,
    ACTIONS(126), 3,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [554] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(131), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [565] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(133), 5,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_allow,
      anon_sym_RPAREN,
  [576] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(135), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [587] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(137), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [598] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(139), 5,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_allow,
      anon_sym_RPAREN,
  [609] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(141), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [620] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(143), 5,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_allow,
      anon_sym_RPAREN,
  [631] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(145), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [642] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(147), 4,
      anon_sym_RBRACE,
      anon_sym_create,
      anon_sym_delete,
      anon_sym_update,
  [652] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(149), 1,
      sym_identifier,
    ACTIONS(151), 1,
      anon_sym_RBRACE,
    STATE(60), 1,
      sym_call,
    STATE(132), 1,
      sym__query_body,
  [668] = 4,
    ACTIONS(153), 1,
      anon_sym_SQUOTE,
    ACTIONS(157), 1,
      sym_comment,
    STATE(39), 1,
      aux_sym_string_repeat2,
    ACTIONS(155), 2,
      aux_sym_string_token2,
      sym_escape_sequence,
  [682] = 4,
    ACTIONS(157), 1,
      sym_comment,
    ACTIONS(159), 1,
      anon_sym_SQUOTE,
    STATE(39), 1,
      aux_sym_string_repeat2,
    ACTIONS(161), 2,
      aux_sym_string_token2,
      sym_escape_sequence,
  [696] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(164), 1,
      sym_identifier,
    ACTIONS(166), 1,
      anon_sym_RBRACE,
    STATE(64), 1,
      sym_type_field,
    STATE(139), 1,
      sym_type_fields,
  [712] = 4,
    ACTIONS(153), 1,
      anon_sym_DQUOTE,
    ACTIONS(157), 1,
      sym_comment,
    STATE(44), 1,
      aux_sym_string_repeat1,
    ACTIONS(168), 2,
      aux_sym_string_token1,
      sym_escape_sequence,
  [726] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(164), 1,
      sym_identifier,
    ACTIONS(170), 1,
      anon_sym_RBRACE,
    STATE(64), 1,
      sym_type_field,
    STATE(134), 1,
      sym_type_fields,
  [742] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(172), 1,
      anon_sym_COMMA,
    ACTIONS(174), 1,
      sym_parameter_name,
    ACTIONS(176), 1,
      anon_sym_RPAREN,
    STATE(57), 1,
      sym_parameter,
  [758] = 4,
    ACTIONS(157), 1,
      sym_comment,
    ACTIONS(178), 1,
      anon_sym_DQUOTE,
    STATE(44), 1,
      aux_sym_string_repeat1,
    ACTIONS(180), 2,
      aux_sym_string_token1,
      sym_escape_sequence,
  [772] = 4,
    ACTIONS(157), 1,
      sym_comment,
    ACTIONS(183), 1,
      anon_sym_DQUOTE,
    STATE(41), 1,
      aux_sym_string_repeat1,
    ACTIONS(185), 2,
      aux_sym_string_token1,
      sym_escape_sequence,
  [786] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(126), 4,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_DOT,
  [796] = 4,
    ACTIONS(157), 1,
      sym_comment,
    ACTIONS(183), 1,
      anon_sym_SQUOTE,
    STATE(38), 1,
      aux_sym_string_repeat2,
    ACTIONS(187), 2,
      aux_sym_string_token2,
      sym_escape_sequence,
  [810] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(189), 4,
      anon_sym_RBRACE,
      anon_sym_create,
      anon_sym_delete,
      anon_sym_update,
  [820] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(106), 1,
      anon_sym_allow,
    ACTIONS(191), 1,
      anon_sym_LBRACE,
    STATE(54), 2,
      sym_guard,
      aux_sym_guards_list_repeat1,
  [834] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    ACTIONS(21), 1,
      sym_parameter_name,
    STATE(118), 2,
      sym_parameter_reference,
      sym_query,
  [848] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(193), 4,
      anon_sym_RBRACE,
      anon_sym_create,
      anon_sym_delete,
      anon_sym_update,
  [858] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(195), 1,
      sym_identifier,
    ACTIONS(197), 1,
      anon_sym_RBRACE,
    STATE(63), 1,
      sym_binding_field,
    STATE(131), 1,
      sym_binding_fields,
  [874] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    ACTIONS(21), 1,
      sym_parameter_name,
    STATE(145), 2,
      sym_parameter_reference,
      sym_query,
  [888] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(199), 1,
      anon_sym_LBRACE,
    ACTIONS(201), 1,
      anon_sym_allow,
    STATE(54), 2,
      sym_guard,
      aux_sym_guards_list_repeat1,
  [902] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(19), 1,
      anon_sym_COMMA,
    ACTIONS(204), 1,
      anon_sym_RPAREN,
    STATE(62), 1,
      aux_sym_arguments_repeat1,
  [915] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(206), 3,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [924] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(208), 1,
      anon_sym_COMMA,
    ACTIONS(210), 1,
      anon_sym_RPAREN,
    STATE(67), 1,
      aux_sym_parameters_list_repeat1,
  [937] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(149), 1,
      sym_identifier,
    ACTIONS(212), 1,
      anon_sym_RBRACE,
    STATE(110), 1,
      sym_call,
  [950] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(214), 1,
      anon_sym_LBRACE,
    ACTIONS(216), 1,
      anon_sym_COMMA,
    STATE(66), 1,
      aux_sym__bases_list_repeat1,
  [963] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(218), 1,
      anon_sym_RBRACE,
    ACTIONS(220), 1,
      anon_sym_COMMA,
    STATE(82), 1,
      aux_sym__query_body_repeat1,
  [976] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(19), 1,
      anon_sym_COMMA,
    ACTIONS(222), 1,
      anon_sym_RPAREN,
    STATE(62), 1,
      aux_sym_arguments_repeat1,
  [989] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(224), 1,
      anon_sym_COMMA,
    ACTIONS(227), 1,
      anon_sym_RPAREN,
    STATE(62), 1,
      aux_sym_arguments_repeat1,
  [1002] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(229), 1,
      anon_sym_RBRACE,
    ACTIONS(231), 1,
      anon_sym_COMMA,
    STATE(84), 1,
      aux_sym_binding_fields_repeat1,
  [1015] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(233), 1,
      anon_sym_RBRACE,
    ACTIONS(235), 1,
      anon_sym_COMMA,
    STATE(75), 1,
      aux_sym_type_fields_repeat1,
  [1028] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(19), 1,
      anon_sym_COMMA,
    ACTIONS(204), 1,
      anon_sym_RPAREN,
    STATE(61), 1,
      aux_sym_arguments_repeat1,
  [1041] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(237), 1,
      anon_sym_LBRACE,
    ACTIONS(239), 1,
      anon_sym_COMMA,
    STATE(66), 1,
      aux_sym__bases_list_repeat1,
  [1054] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(242), 1,
      anon_sym_COMMA,
    ACTIONS(244), 1,
      anon_sym_RPAREN,
    STATE(77), 1,
      aux_sym_parameters_list_repeat1,
  [1067] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(174), 1,
      sym_parameter_name,
    ACTIONS(244), 1,
      anon_sym_RPAREN,
    STATE(91), 1,
      sym_parameter,
  [1080] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(104), 1,
      anon_sym_LPAREN,
    ACTIONS(246), 1,
      anon_sym_COLON,
    STATE(34), 1,
      sym_arguments,
  [1093] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(248), 1,
      anon_sym_RBRACE,
    ACTIONS(250), 1,
      anon_sym_COMMA,
    STATE(70), 1,
      aux_sym__query_body_repeat1,
  [1106] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(253), 1,
      anon_sym_LBRACE,
    ACTIONS(255), 1,
      anon_sym_COMMA,
    STATE(59), 1,
      aux_sym__bases_list_repeat1,
  [1119] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(164), 1,
      sym_identifier,
    ACTIONS(257), 1,
      anon_sym_RBRACE,
    STATE(104), 1,
      sym_type_field,
  [1132] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(259), 1,
      anon_sym_RBRACE,
    ACTIONS(261), 1,
      anon_sym_COMMA,
    STATE(73), 1,
      aux_sym_type_fields_repeat1,
  [1145] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(264), 3,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [1154] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(266), 1,
      anon_sym_RBRACE,
    ACTIONS(268), 1,
      anon_sym_COMMA,
    STATE(73), 1,
      aux_sym_type_fields_repeat1,
  [1167] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(174), 1,
      sym_parameter_name,
    ACTIONS(270), 1,
      anon_sym_RPAREN,
    STATE(91), 1,
      sym_parameter,
  [1180] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(272), 1,
      anon_sym_COMMA,
    ACTIONS(275), 1,
      anon_sym_RPAREN,
    STATE(77), 1,
      aux_sym_parameters_list_repeat1,
  [1193] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(164), 1,
      sym_identifier,
    ACTIONS(266), 1,
      anon_sym_RBRACE,
    STATE(104), 1,
      sym_type_field,
  [1206] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(277), 3,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [1215] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 3,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_SEMI,
  [1224] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(149), 1,
      sym_identifier,
    ACTIONS(281), 1,
      anon_sym_RBRACE,
    STATE(110), 1,
      sym_call,
  [1237] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(281), 1,
      anon_sym_RBRACE,
    ACTIONS(283), 1,
      anon_sym_COMMA,
    STATE(70), 1,
      aux_sym__query_body_repeat1,
  [1250] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(195), 1,
      sym_identifier,
    ACTIONS(285), 1,
      anon_sym_RBRACE,
    STATE(94), 1,
      sym_binding_field,
  [1263] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(285), 1,
      anon_sym_RBRACE,
    ACTIONS(287), 1,
      anon_sym_COMMA,
    STATE(86), 1,
      aux_sym_binding_fields_repeat1,
  [1276] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(195), 1,
      sym_identifier,
    ACTIONS(289), 1,
      anon_sym_RBRACE,
    STATE(94), 1,
      sym_binding_field,
  [1289] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(291), 1,
      anon_sym_RBRACE,
    ACTIONS(293), 1,
      anon_sym_COMMA,
    STATE(86), 1,
      aux_sym_binding_fields_repeat1,
  [1302] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(296), 1,
      sym_identifier,
    ACTIONS(298), 1,
      anon_sym_LBRACE,
  [1312] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(227), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [1320] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(300), 2,
      anon_sym_LBRACE,
      anon_sym_allow,
  [1328] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(302), 1,
      anon_sym_LBRACE,
    STATE(135), 1,
      sym_binding,
  [1338] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(275), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [1346] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(195), 1,
      sym_identifier,
    STATE(94), 1,
      sym_binding_field,
  [1356] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(304), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [1364] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(291), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [1372] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(306), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [1380] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(164), 1,
      sym_identifier,
    STATE(104), 1,
      sym_type_field,
  [1390] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(308), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [1398] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(310), 2,
      anon_sym_LBRACE,
      anon_sym_allow,
  [1406] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(174), 1,
      sym_parameter_name,
    STATE(91), 1,
      sym_parameter,
  [1416] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(312), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [1424] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(314), 1,
      anon_sym_COLON,
    ACTIONS(316), 1,
      anon_sym_LBRACE,
  [1434] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(318), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [1442] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(320), 1,
      anon_sym_LPAREN,
    STATE(112), 1,
      sym_parameters_list,
  [1452] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(259), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [1460] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(320), 1,
      anon_sym_LPAREN,
    STATE(17), 1,
      sym_parameters_list,
  [1470] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(322), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [1478] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(320), 1,
      anon_sym_LPAREN,
    STATE(18), 1,
      sym_parameters_list,
  [1488] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(296), 1,
      sym_identifier,
    ACTIONS(324), 1,
      anon_sym_LBRACE,
  [1498] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(326), 2,
      anon_sym_LBRACE,
      anon_sym_COMMA,
  [1506] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(248), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [1514] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(328), 1,
      sym_identifier,
    STATE(136), 1,
      sym__bases_list,
  [1524] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    STATE(30), 1,
      sym_query,
  [1534] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(330), 2,
      anon_sym_LBRACE,
      anon_sym_allow,
  [1542] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(332), 1,
      anon_sym_COLON,
    ACTIONS(334), 1,
      sym_optional_flag,
  [1552] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(336), 1,
      anon_sym_COLON,
    ACTIONS(338), 1,
      sym_optional_flag,
  [1562] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(149), 1,
      sym_identifier,
    STATE(110), 1,
      sym_call,
  [1572] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(104), 1,
      anon_sym_LPAREN,
    STATE(34), 1,
      sym_arguments,
  [1582] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(302), 1,
      anon_sym_LBRACE,
    STATE(128), 1,
      sym_binding,
  [1592] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(340), 2,
      anon_sym_LBRACE,
      anon_sym_allow,
  [1600] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(149), 1,
      sym_identifier,
    STATE(113), 1,
      sym_call,
  [1610] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(342), 2,
      anon_sym_LBRACE,
      anon_sym_allow,
  [1618] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    STATE(28), 1,
      sym_query,
  [1628] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(344), 1,
      sym_identifier,
  [1635] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(346), 1,
      anon_sym_LBRACE,
  [1642] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(348), 1,
      anon_sym_COLON,
  [1649] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(350), 1,
      sym_identifier,
  [1656] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(352), 1,
      anon_sym_COLON,
  [1663] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(354), 1,
      anon_sym_SEMI,
  [1670] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(304), 1,
      anon_sym_SEMI,
  [1677] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(246), 1,
      anon_sym_COLON,
  [1684] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(356), 1,
      anon_sym_RBRACE,
  [1691] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(358), 1,
      anon_sym_RBRACE,
  [1698] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(210), 1,
      anon_sym_RPAREN,
  [1705] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(360), 1,
      anon_sym_RBRACE,
  [1712] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(362), 1,
      anon_sym_SEMI,
  [1719] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(364), 1,
      anon_sym_LBRACE,
  [1726] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(366), 1,
      sym_identifier,
  [1733] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(368), 1,
      anon_sym_RBRACE,
  [1740] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(370), 1,
      anon_sym_RBRACE,
  [1747] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(372), 1,
      sym_identifier,
  [1754] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(374), 1,
      sym_identifier,
  [1761] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(376), 1,
      sym_identifier,
  [1768] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(378), 1,
      ts_builtin_sym_end,
  [1775] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(380), 1,
      sym_identifier,
  [1782] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(382), 1,
      anon_sym_SEMI,
  [1789] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(384), 1,
      sym_identifier,
  [1796] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(386), 1,
      sym_identifier,
  [1803] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(296), 1,
      sym_identifier,
  [1810] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(388), 1,
      sym_identifier,
  [1817] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(390), 1,
      anon_sym_RBRACE,
};

static uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 57,
  [SMALL_STATE(4)] = 107,
  [SMALL_STATE(5)] = 159,
  [SMALL_STATE(6)] = 186,
  [SMALL_STATE(7)] = 213,
  [SMALL_STATE(8)] = 239,
  [SMALL_STATE(9)] = 255,
  [SMALL_STATE(10)] = 281,
  [SMALL_STATE(11)] = 304,
  [SMALL_STATE(12)] = 319,
  [SMALL_STATE(13)] = 342,
  [SMALL_STATE(14)] = 360,
  [SMALL_STATE(15)] = 382,
  [SMALL_STATE(16)] = 394,
  [SMALL_STATE(17)] = 410,
  [SMALL_STATE(18)] = 430,
  [SMALL_STATE(19)] = 447,
  [SMALL_STATE(20)] = 458,
  [SMALL_STATE(21)] = 469,
  [SMALL_STATE(22)] = 480,
  [SMALL_STATE(23)] = 491,
  [SMALL_STATE(24)] = 506,
  [SMALL_STATE(25)] = 517,
  [SMALL_STATE(26)] = 528,
  [SMALL_STATE(27)] = 539,
  [SMALL_STATE(28)] = 554,
  [SMALL_STATE(29)] = 565,
  [SMALL_STATE(30)] = 576,
  [SMALL_STATE(31)] = 587,
  [SMALL_STATE(32)] = 598,
  [SMALL_STATE(33)] = 609,
  [SMALL_STATE(34)] = 620,
  [SMALL_STATE(35)] = 631,
  [SMALL_STATE(36)] = 642,
  [SMALL_STATE(37)] = 652,
  [SMALL_STATE(38)] = 668,
  [SMALL_STATE(39)] = 682,
  [SMALL_STATE(40)] = 696,
  [SMALL_STATE(41)] = 712,
  [SMALL_STATE(42)] = 726,
  [SMALL_STATE(43)] = 742,
  [SMALL_STATE(44)] = 758,
  [SMALL_STATE(45)] = 772,
  [SMALL_STATE(46)] = 786,
  [SMALL_STATE(47)] = 796,
  [SMALL_STATE(48)] = 810,
  [SMALL_STATE(49)] = 820,
  [SMALL_STATE(50)] = 834,
  [SMALL_STATE(51)] = 848,
  [SMALL_STATE(52)] = 858,
  [SMALL_STATE(53)] = 874,
  [SMALL_STATE(54)] = 888,
  [SMALL_STATE(55)] = 902,
  [SMALL_STATE(56)] = 915,
  [SMALL_STATE(57)] = 924,
  [SMALL_STATE(58)] = 937,
  [SMALL_STATE(59)] = 950,
  [SMALL_STATE(60)] = 963,
  [SMALL_STATE(61)] = 976,
  [SMALL_STATE(62)] = 989,
  [SMALL_STATE(63)] = 1002,
  [SMALL_STATE(64)] = 1015,
  [SMALL_STATE(65)] = 1028,
  [SMALL_STATE(66)] = 1041,
  [SMALL_STATE(67)] = 1054,
  [SMALL_STATE(68)] = 1067,
  [SMALL_STATE(69)] = 1080,
  [SMALL_STATE(70)] = 1093,
  [SMALL_STATE(71)] = 1106,
  [SMALL_STATE(72)] = 1119,
  [SMALL_STATE(73)] = 1132,
  [SMALL_STATE(74)] = 1145,
  [SMALL_STATE(75)] = 1154,
  [SMALL_STATE(76)] = 1167,
  [SMALL_STATE(77)] = 1180,
  [SMALL_STATE(78)] = 1193,
  [SMALL_STATE(79)] = 1206,
  [SMALL_STATE(80)] = 1215,
  [SMALL_STATE(81)] = 1224,
  [SMALL_STATE(82)] = 1237,
  [SMALL_STATE(83)] = 1250,
  [SMALL_STATE(84)] = 1263,
  [SMALL_STATE(85)] = 1276,
  [SMALL_STATE(86)] = 1289,
  [SMALL_STATE(87)] = 1302,
  [SMALL_STATE(88)] = 1312,
  [SMALL_STATE(89)] = 1320,
  [SMALL_STATE(90)] = 1328,
  [SMALL_STATE(91)] = 1338,
  [SMALL_STATE(92)] = 1346,
  [SMALL_STATE(93)] = 1356,
  [SMALL_STATE(94)] = 1364,
  [SMALL_STATE(95)] = 1372,
  [SMALL_STATE(96)] = 1380,
  [SMALL_STATE(97)] = 1390,
  [SMALL_STATE(98)] = 1398,
  [SMALL_STATE(99)] = 1406,
  [SMALL_STATE(100)] = 1416,
  [SMALL_STATE(101)] = 1424,
  [SMALL_STATE(102)] = 1434,
  [SMALL_STATE(103)] = 1442,
  [SMALL_STATE(104)] = 1452,
  [SMALL_STATE(105)] = 1460,
  [SMALL_STATE(106)] = 1470,
  [SMALL_STATE(107)] = 1478,
  [SMALL_STATE(108)] = 1488,
  [SMALL_STATE(109)] = 1498,
  [SMALL_STATE(110)] = 1506,
  [SMALL_STATE(111)] = 1514,
  [SMALL_STATE(112)] = 1524,
  [SMALL_STATE(113)] = 1534,
  [SMALL_STATE(114)] = 1542,
  [SMALL_STATE(115)] = 1552,
  [SMALL_STATE(116)] = 1562,
  [SMALL_STATE(117)] = 1572,
  [SMALL_STATE(118)] = 1582,
  [SMALL_STATE(119)] = 1592,
  [SMALL_STATE(120)] = 1600,
  [SMALL_STATE(121)] = 1610,
  [SMALL_STATE(122)] = 1618,
  [SMALL_STATE(123)] = 1628,
  [SMALL_STATE(124)] = 1635,
  [SMALL_STATE(125)] = 1642,
  [SMALL_STATE(126)] = 1649,
  [SMALL_STATE(127)] = 1656,
  [SMALL_STATE(128)] = 1663,
  [SMALL_STATE(129)] = 1670,
  [SMALL_STATE(130)] = 1677,
  [SMALL_STATE(131)] = 1684,
  [SMALL_STATE(132)] = 1691,
  [SMALL_STATE(133)] = 1698,
  [SMALL_STATE(134)] = 1705,
  [SMALL_STATE(135)] = 1712,
  [SMALL_STATE(136)] = 1719,
  [SMALL_STATE(137)] = 1726,
  [SMALL_STATE(138)] = 1733,
  [SMALL_STATE(139)] = 1740,
  [SMALL_STATE(140)] = 1747,
  [SMALL_STATE(141)] = 1754,
  [SMALL_STATE(142)] = 1761,
  [SMALL_STATE(143)] = 1768,
  [SMALL_STATE(144)] = 1775,
  [SMALL_STATE(145)] = 1782,
  [SMALL_STATE(146)] = 1789,
  [SMALL_STATE(147)] = 1796,
  [SMALL_STATE(148)] = 1803,
  [SMALL_STATE(149)] = 1810,
  [SMALL_STATE(150)] = 1817,
};

static TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(144),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(149),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(147),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(146),
  [15] = {.entry = {.count = 1, .reusable = false}}, SHIFT(16),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [25] = {.entry = {.count = 1, .reusable = false}}, SHIFT(141),
  [27] = {.entry = {.count = 1, .reusable = false}}, SHIFT(65),
  [29] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [31] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [33] = {.entry = {.count = 1, .reusable = true}}, SHIFT(45),
  [35] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [37] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [39] = {.entry = {.count = 1, .reusable = false}}, SHIFT(100),
  [41] = {.entry = {.count = 1, .reusable = true}}, SHIFT(100),
  [43] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_arguments_repeat1, 1),
  [45] = {.entry = {.count = 1, .reusable = false}}, SHIFT(88),
  [47] = {.entry = {.count = 1, .reusable = true}}, SHIFT(88),
  [49] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1),
  [51] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2),
  [53] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(144),
  [56] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(149),
  [59] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(147),
  [62] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(146),
  [65] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [67] = {.entry = {.count = 1, .reusable = true}}, SHIFT(137),
  [69] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [71] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [73] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query, 3),
  [75] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [77] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_statements_repeat1, 2),
  [79] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_statements_repeat1, 2), SHIFT_REPEAT(137),
  [82] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_statements_repeat1, 2), SHIFT_REPEAT(53),
  [85] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_statements_repeat1, 2), SHIFT_REPEAT(50),
  [88] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query, 2),
  [90] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_statements, 1),
  [92] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_variable, 1, .production_id = 1),
  [94] = {.entry = {.count = 1, .reusable = true}}, SHIFT(141),
  [96] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [98] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [100] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameter_reference, 1),
  [102] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_reference, 1),
  [104] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [106] = {.entry = {.count = 1, .reusable = true}}, SHIFT(120),
  [108] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [110] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_action_declaration, 6, .production_id = 16),
  [112] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 6, .production_id = 11),
  [114] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 4, .production_id = 2),
  [116] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 7, .production_id = 17),
  [118] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_uri, 1),
  [120] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 5, .production_id = 5),
  [122] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_arguments, 2),
  [124] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_action_declaration, 5, .production_id = 8),
  [126] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_uri_repeat1, 2),
  [128] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_uri_repeat1, 2), SHIFT_REPEAT(141),
  [131] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query_declaration, 5, .production_id = 7),
  [133] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_arguments, 4),
  [135] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_permission_declaration, 4, .production_id = 3),
  [137] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_action_declaration, 7, .production_id = 21),
  [139] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_arguments, 3),
  [141] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query_declaration, 4, .production_id = 3),
  [143] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call, 2, .production_id = 14),
  [145] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_action_declaration, 6, .production_id = 15),
  [147] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_update_statement, 4, .production_id = 24),
  [149] = {.entry = {.count = 1, .reusable = true}}, SHIFT(117),
  [151] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [153] = {.entry = {.count = 1, .reusable = false}}, SHIFT(56),
  [155] = {.entry = {.count = 1, .reusable = false}}, SHIFT(39),
  [157] = {.entry = {.count = 1, .reusable = false}}, SHIFT_EXTRA(),
  [159] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_string_repeat2, 2),
  [161] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_string_repeat2, 2), SHIFT_REPEAT(39),
  [164] = {.entry = {.count = 1, .reusable = true}}, SHIFT(114),
  [166] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [168] = {.entry = {.count = 1, .reusable = false}}, SHIFT(44),
  [170] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [172] = {.entry = {.count = 1, .reusable = true}}, SHIFT(133),
  [174] = {.entry = {.count = 1, .reusable = true}}, SHIFT(115),
  [176] = {.entry = {.count = 1, .reusable = true}}, SHIFT(119),
  [178] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_string_repeat1, 2),
  [180] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_string_repeat1, 2), SHIFT_REPEAT(44),
  [183] = {.entry = {.count = 1, .reusable = false}}, SHIFT(79),
  [185] = {.entry = {.count = 1, .reusable = false}}, SHIFT(41),
  [187] = {.entry = {.count = 1, .reusable = false}}, SHIFT(38),
  [189] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_statement, 4, .production_id = 23),
  [191] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_guards_list, 1),
  [193] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_delete_statement, 3, .production_id = 20),
  [195] = {.entry = {.count = 1, .reusable = true}}, SHIFT(130),
  [197] = {.entry = {.count = 1, .reusable = true}}, SHIFT(129),
  [199] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_guards_list_repeat1, 2),
  [201] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_guards_list_repeat1, 2), SHIFT_REPEAT(120),
  [204] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [206] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 3),
  [208] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [210] = {.entry = {.count = 1, .reusable = true}}, SHIFT(121),
  [212] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__query_body, 3),
  [214] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__bases_list, 2, .production_id = 4),
  [216] = {.entry = {.count = 1, .reusable = true}}, SHIFT(108),
  [218] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__query_body, 1),
  [220] = {.entry = {.count = 1, .reusable = true}}, SHIFT(81),
  [222] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [224] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_arguments_repeat1, 2), SHIFT_REPEAT(4),
  [227] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_arguments_repeat1, 2),
  [229] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding_fields, 1),
  [231] = {.entry = {.count = 1, .reusable = true}}, SHIFT(83),
  [233] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_fields, 1),
  [235] = {.entry = {.count = 1, .reusable = true}}, SHIFT(78),
  [237] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym__bases_list_repeat1, 2, .production_id = 10),
  [239] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__bases_list_repeat1, 2, .production_id = 10), SHIFT_REPEAT(148),
  [242] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [244] = {.entry = {.count = 1, .reusable = true}}, SHIFT(89),
  [246] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [248] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2),
  [250] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2), SHIFT_REPEAT(116),
  [253] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__bases_list, 1, .production_id = 1),
  [255] = {.entry = {.count = 1, .reusable = true}}, SHIFT(87),
  [257] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_fields, 3),
  [259] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_type_fields_repeat1, 2),
  [261] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_type_fields_repeat1, 2), SHIFT_REPEAT(96),
  [264] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_variable, 2, .production_id = 22),
  [266] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_fields, 2),
  [268] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [270] = {.entry = {.count = 1, .reusable = true}}, SHIFT(98),
  [272] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_parameters_list_repeat1, 2), SHIFT_REPEAT(99),
  [275] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_parameters_list_repeat1, 2),
  [277] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 2),
  [279] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding, 3, .production_id = 25),
  [281] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__query_body, 2),
  [283] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [285] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding_fields, 2),
  [287] = {.entry = {.count = 1, .reusable = true}}, SHIFT(85),
  [289] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding_fields, 3),
  [291] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_binding_fields_repeat1, 2),
  [293] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_binding_fields_repeat1, 2), SHIFT_REPEAT(92),
  [296] = {.entry = {.count = 1, .reusable = true}}, SHIFT(109),
  [298] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__bases_list, 2, .production_id = 1),
  [300] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameters_list, 4),
  [302] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [304] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding, 2),
  [306] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_field, 4, .production_id = 18),
  [308] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameter, 4, .production_id = 19),
  [310] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameters_list, 5),
  [312] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding_field, 3, .production_id = 26),
  [314] = {.entry = {.count = 1, .reusable = true}}, SHIFT(111),
  [316] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [318] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameter, 3, .production_id = 13),
  [320] = {.entry = {.count = 1, .reusable = true}}, SHIFT(43),
  [322] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_field, 3, .production_id = 12),
  [324] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__bases_list, 3, .production_id = 4),
  [326] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym__bases_list_repeat1, 2, .production_id = 9),
  [328] = {.entry = {.count = 1, .reusable = true}}, SHIFT(71),
  [330] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_guard, 2, .production_id = 6),
  [332] = {.entry = {.count = 1, .reusable = true}}, SHIFT(123),
  [334] = {.entry = {.count = 1, .reusable = true}}, SHIFT(125),
  [336] = {.entry = {.count = 1, .reusable = true}}, SHIFT(126),
  [338] = {.entry = {.count = 1, .reusable = true}}, SHIFT(127),
  [340] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameters_list, 2),
  [342] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameters_list, 3),
  [344] = {.entry = {.count = 1, .reusable = true}}, SHIFT(106),
  [346] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [348] = {.entry = {.count = 1, .reusable = true}}, SHIFT(140),
  [350] = {.entry = {.count = 1, .reusable = true}}, SHIFT(102),
  [352] = {.entry = {.count = 1, .reusable = true}}, SHIFT(142),
  [354] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [356] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [358] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [360] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [362] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [364] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [366] = {.entry = {.count = 1, .reusable = true}}, SHIFT(90),
  [368] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [370] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [372] = {.entry = {.count = 1, .reusable = true}}, SHIFT(95),
  [374] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [376] = {.entry = {.count = 1, .reusable = true}}, SHIFT(97),
  [378] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [380] = {.entry = {.count = 1, .reusable = true}}, SHIFT(101),
  [382] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [384] = {.entry = {.count = 1, .reusable = true}}, SHIFT(107),
  [386] = {.entry = {.count = 1, .reusable = true}}, SHIFT(105),
  [388] = {.entry = {.count = 1, .reusable = true}}, SHIFT(103),
  [390] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_markus(void) {
  static TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .symbol_metadata = ts_symbol_metadata,
    .parse_table = (const unsigned short *)ts_parse_table,
    .small_parse_table = (const uint16_t *)ts_small_parse_table,
    .small_parse_table_map = (const uint32_t *)ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .lex_modes = ts_lex_modes,
    .symbol_names = ts_symbol_names,
    .public_symbol_map = ts_symbol_map,
    .alias_sequences = (const TSSymbol *)ts_alias_sequences,
    .field_count = FIELD_COUNT,
    .field_names = ts_field_names,
    .field_map_slices = (const TSFieldMapSlice *)ts_field_map_slices,
    .field_map_entries = (const TSFieldMapEntry *)ts_field_map_entries,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .lex_fn = ts_lex,
    .keyword_lex_fn = ts_lex_keywords,
    .keyword_capture_token = sym_identifier,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
