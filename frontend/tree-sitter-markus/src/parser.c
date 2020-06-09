#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 11
#define STATE_COUNT 151
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 74
#define ALIAS_COUNT 0
#define TOKEN_COUNT 29
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 15
#define MAX_ALIAS_SEQUENCE_LENGTH 7

enum {
  sym_identifier = 1,
  anon_sym_type = 2,
  anon_sym_COLON = 3,
  anon_sym_LBRACE = 4,
  anon_sym_RBRACE = 5,
  anon_sym_COMMA = 6,
  anon_sym_QMARK = 7,
  anon_sym_permission = 8,
  anon_sym_query = 9,
  anon_sym_allow = 10,
  anon_sym_action = 11,
  anon_sym_create = 12,
  anon_sym_SEMI = 13,
  anon_sym_delete = 14,
  anon_sym_update = 15,
  sym_parameter_name = 16,
  anon_sym_LPAREN = 17,
  anon_sym_RPAREN = 18,
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
  sym_source_file = 29,
  sym__declaration = 30,
  sym_type_declaration = 31,
  sym_bases_list = 32,
  sym_type_fields = 33,
  sym_type_field = 34,
  sym_permission_declaration = 35,
  sym_query_declaration = 36,
  sym_guards_list = 37,
  sym_guard = 38,
  sym_action_declaration = 39,
  sym_statements = 40,
  sym__statement = 41,
  sym_create_statement = 42,
  sym_delete_statement = 43,
  sym_update_statement = 44,
  sym_binding = 45,
  sym_binding_fields = 46,
  sym_binding_field = 47,
  sym__binding_value = 48,
  sym_parameters_list = 49,
  sym_parameter = 50,
  sym__value = 51,
  sym_variable = 52,
  sym_uri = 53,
  sym__boolean = 54,
  sym_parameter_reference = 55,
  sym_type_reference = 56,
  sym_query = 57,
  sym__query_body = 58,
  sym_call = 59,
  sym_arguments = 60,
  sym_string = 61,
  aux_sym_source_file_repeat1 = 62,
  aux_sym_bases_list_repeat1 = 63,
  aux_sym_type_fields_repeat1 = 64,
  aux_sym_guards_list_repeat1 = 65,
  aux_sym_statements_repeat1 = 66,
  aux_sym_binding_fields_repeat1 = 67,
  aux_sym_parameters_list_repeat1 = 68,
  aux_sym_uri_repeat1 = 69,
  aux_sym__query_body_repeat1 = 70,
  aux_sym_arguments_repeat1 = 71,
  aux_sym_string_repeat1 = 72,
  aux_sym_string_repeat2 = 73,
};

static const char *ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_identifier] = "identifier",
  [anon_sym_type] = "type",
  [anon_sym_COLON] = ":",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
  [anon_sym_COMMA] = ",",
  [anon_sym_QMARK] = "?",
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
  [sym_source_file] = "source_file",
  [sym__declaration] = "_declaration",
  [sym_type_declaration] = "type_declaration",
  [sym_bases_list] = "bases_list",
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
  [aux_sym_bases_list_repeat1] = "bases_list_repeat1",
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
  [anon_sym_QMARK] = anon_sym_QMARK,
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
  [sym_source_file] = sym_source_file,
  [sym__declaration] = sym__declaration,
  [sym_type_declaration] = sym_type_declaration,
  [sym_bases_list] = sym_bases_list,
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
  [aux_sym_bases_list_repeat1] = aux_sym_bases_list_repeat1,
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
  [anon_sym_QMARK] = {
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
  [sym_bases_list] = {
    .visible = true,
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
  [aux_sym_bases_list_repeat1] = {
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
  field_bases = 3,
  field_binding = 4,
  field_body = 5,
  field_callee = 6,
  field_field = 7,
  field_field_type = 8,
  field_guards = 9,
  field_name = 10,
  field_parameters = 11,
  field_patch = 12,
  field_selection = 13,
  field_target = 14,
  field_value = 15,
};

static const char *ts_field_names[] = {
  [0] = NULL,
  [field_arguments] = "arguments",
  [field_base] = "base",
  [field_bases] = "bases",
  [field_binding] = "binding",
  [field_body] = "body",
  [field_callee] = "callee",
  [field_field] = "field",
  [field_field_type] = "field_type",
  [field_guards] = "guards",
  [field_name] = "name",
  [field_parameters] = "parameters",
  [field_patch] = "patch",
  [field_selection] = "selection",
  [field_target] = "target",
  [field_value] = "value",
};

static const TSFieldMapSlice ts_field_map_slices[22] = {
  [1] = {.index = 0, .length = 1},
  [2] = {.index = 1, .length = 3},
  [3] = {.index = 4, .length = 2},
  [4] = {.index = 6, .length = 1},
  [5] = {.index = 7, .length = 4},
  [6] = {.index = 11, .length = 2},
  [7] = {.index = 13, .length = 3},
  [8] = {.index = 16, .length = 2},
  [9] = {.index = 18, .length = 2},
  [10] = {.index = 20, .length = 3},
  [11] = {.index = 23, .length = 3},
  [12] = {.index = 26, .length = 4},
  [13] = {.index = 30, .length = 2},
  [14] = {.index = 32, .length = 1},
  [15] = {.index = 33, .length = 1},
  [16] = {.index = 34, .length = 4},
  [17] = {.index = 38, .length = 2},
  [18] = {.index = 40, .length = 2},
  [19] = {.index = 42, .length = 2},
  [20] = {.index = 44, .length = 1},
  [21] = {.index = 45, .length = 2},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_name, 1},
  [1] =
    {field_body, 3},
    {field_name, 1},
    {field_parameters, 2},
  [4] =
    {field_body, 3},
    {field_name, 1},
  [6] =
    {field_selection, 1},
  [7] =
    {field_body, 4},
    {field_guards, 3},
    {field_name, 1},
    {field_parameters, 2},
  [11] =
    {field_name, 1},
    {field_parameters, 2},
  [13] =
    {field_bases, 2},
    {field_bases, 3},
    {field_name, 1},
  [16] =
    {field_field_type, 2},
    {field_name, 0},
  [18] =
    {field_arguments, 1},
    {field_callee, 0},
  [20] =
    {field_body, 4},
    {field_name, 1},
    {field_parameters, 2},
  [23] =
    {field_guards, 3},
    {field_name, 1},
    {field_parameters, 2},
  [26] =
    {field_bases, 2},
    {field_bases, 3},
    {field_body, 5},
    {field_name, 1},
  [30] =
    {field_field_type, 3},
    {field_name, 0},
  [32] =
    {field_base, 0},
  [33] =
    {field_target, 1},
  [34] =
    {field_body, 5},
    {field_guards, 3},
    {field_name, 1},
    {field_parameters, 2},
  [38] =
    {field_base, 0},
    {field_field, 1},
  [40] =
    {field_binding, 2},
    {field_name, 1},
  [42] =
    {field_patch, 2},
    {field_target, 1},
  [44] =
    {field_body, 1},
  [45] =
    {field_name, 0},
    {field_value, 2},
};

static TSSymbol ts_alias_sequences[22][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(24);
      if (lookahead == '"') ADVANCE(40);
      if (lookahead == '$') ADVANCE(22);
      if (lookahead == '%') ADVANCE(11);
      if (lookahead == '\'') ADVANCE(44);
      if (lookahead == '(') ADVANCE(33);
      if (lookahead == ')') ADVANCE(34);
      if (lookahead == ',') ADVANCE(28);
      if (lookahead == '.') ADVANCE(35);
      if (lookahead == ':') ADVANCE(25);
      if (lookahead == ';') ADVANCE(30);
      if (lookahead == '?') ADVANCE(29);
      if (lookahead == '\\') ADVANCE(12);
      if (lookahead == '{') ADVANCE(26);
      if (lookahead == '}') ADVANCE(27);
      if (('+' <= lookahead && lookahead <= '-')) ADVANCE(7);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(23)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(37);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(31);
      END_STATE();
    case 1:
      if (lookahead == '\n') SKIP(6)
      if (lookahead == '\'') ADVANCE(44);
      if (lookahead == '\\') ADVANCE(2);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(46);
      if (lookahead != 0) ADVANCE(47);
      END_STATE();
    case 2:
      if (lookahead == '\n') ADVANCE(45);
      if (lookahead == '\r') ADVANCE(49);
      if (lookahead == 'u') ADVANCE(13);
      if (lookahead == 'x') ADVANCE(21);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(52);
      if (lookahead != 0) ADVANCE(48);
      END_STATE();
    case 3:
      if (lookahead == '\n') SKIP(5)
      if (lookahead == '"') ADVANCE(40);
      if (lookahead == '\\') ADVANCE(4);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(42);
      if (lookahead != 0) ADVANCE(43);
      END_STATE();
    case 4:
      if (lookahead == '\n') ADVANCE(41);
      if (lookahead == '\r') ADVANCE(50);
      if (lookahead == 'u') ADVANCE(13);
      if (lookahead == 'x') ADVANCE(21);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(52);
      if (lookahead != 0) ADVANCE(48);
      END_STATE();
    case 5:
      if (lookahead == '"') ADVANCE(40);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(5)
      END_STATE();
    case 6:
      if (lookahead == '\'') ADVANCE(44);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(6)
      END_STATE();
    case 7:
      if (lookahead == '.') ADVANCE(16);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(37);
      END_STATE();
    case 8:
      if (lookahead == 'e') ADVANCE(9);
      END_STATE();
    case 9:
      if (lookahead == 'r') ADVANCE(36);
      END_STATE();
    case 10:
      if (lookahead == 's') ADVANCE(8);
      END_STATE();
    case 11:
      if (lookahead == 'u') ADVANCE(10);
      END_STATE();
    case 12:
      if (lookahead == 'u') ADVANCE(13);
      if (lookahead == 'x') ADVANCE(21);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(52);
      if (lookahead != 0) ADVANCE(48);
      END_STATE();
    case 13:
      if (lookahead == '{') ADVANCE(20);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(18);
      END_STATE();
    case 14:
      if (lookahead == '}') ADVANCE(48);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(14);
      END_STATE();
    case 15:
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(17);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(39);
      END_STATE();
    case 16:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(38);
      END_STATE();
    case 17:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(39);
      END_STATE();
    case 18:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(21);
      END_STATE();
    case 19:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(48);
      END_STATE();
    case 20:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(14);
      END_STATE();
    case 21:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(19);
      END_STATE();
    case 22:
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(32);
      END_STATE();
    case 23:
      if (eof) ADVANCE(24);
      if (lookahead == '"') ADVANCE(40);
      if (lookahead == '$') ADVANCE(22);
      if (lookahead == '%') ADVANCE(11);
      if (lookahead == '\'') ADVANCE(44);
      if (lookahead == '(') ADVANCE(33);
      if (lookahead == ')') ADVANCE(34);
      if (lookahead == ',') ADVANCE(28);
      if (lookahead == '.') ADVANCE(35);
      if (lookahead == ':') ADVANCE(25);
      if (lookahead == ';') ADVANCE(30);
      if (lookahead == '?') ADVANCE(29);
      if (lookahead == '{') ADVANCE(26);
      if (lookahead == '}') ADVANCE(27);
      if (('+' <= lookahead && lookahead <= '-')) ADVANCE(7);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(23)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(37);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(31);
      END_STATE();
    case 24:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 25:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 26:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 27:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 28:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 29:
      ACCEPT_TOKEN(anon_sym_QMARK);
      END_STATE();
    case 30:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 31:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(31);
      END_STATE();
    case 32:
      ACCEPT_TOKEN(sym_parameter_name);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(32);
      END_STATE();
    case 33:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 34:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 35:
      ACCEPT_TOKEN(anon_sym_DOT);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(38);
      END_STATE();
    case 36:
      ACCEPT_TOKEN(sym_user);
      END_STATE();
    case 37:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(16);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(15);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(37);
      END_STATE();
    case 38:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(15);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(38);
      END_STATE();
    case 39:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(39);
      END_STATE();
    case 40:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 41:
      ACCEPT_TOKEN(aux_sym_string_token1);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(aux_sym_string_token1);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(42);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(43);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(aux_sym_string_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(43);
      END_STATE();
    case 44:
      ACCEPT_TOKEN(anon_sym_SQUOTE);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(aux_sym_string_token2);
      END_STATE();
    case 46:
      ACCEPT_TOKEN(aux_sym_string_token2);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(46);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(47);
      END_STATE();
    case 47:
      ACCEPT_TOKEN(aux_sym_string_token2);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(47);
      END_STATE();
    case 48:
      ACCEPT_TOKEN(sym_escape_sequence);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(sym_escape_sequence);
      if (lookahead == '\n') ADVANCE(45);
      END_STATE();
    case 50:
      ACCEPT_TOKEN(sym_escape_sequence);
      if (lookahead == '\n') ADVANCE(41);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(sym_escape_sequence);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(48);
      END_STATE();
    case 52:
      ACCEPT_TOKEN(sym_escape_sequence);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(51);
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
          lookahead == ' ') SKIP(0)
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
    [anon_sym_QMARK] = ACTIONS(1),
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
    [anon_sym_DOT] = ACTIONS(1),
    [sym_true_literal] = ACTIONS(1),
    [sym_false_literal] = ACTIONS(1),
    [sym_user] = ACTIONS(1),
    [sym_number] = ACTIONS(1),
    [anon_sym_DQUOTE] = ACTIONS(1),
    [anon_sym_SQUOTE] = ACTIONS(1),
    [sym_escape_sequence] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(143),
    [sym__declaration] = STATE(5),
    [sym_type_declaration] = STATE(5),
    [sym_permission_declaration] = STATE(5),
    [sym_query_declaration] = STATE(5),
    [sym_action_declaration] = STATE(5),
    [aux_sym_source_file_repeat1] = STATE(5),
    [ts_builtin_sym_end] = ACTIONS(3),
    [anon_sym_type] = ACTIONS(5),
    [anon_sym_permission] = ACTIONS(7),
    [anon_sym_query] = ACTIONS(9),
    [anon_sym_action] = ACTIONS(11),
  },
};

static uint16_t ts_small_parse_table[] = {
  [0] = 15,
    ACTIONS(13), 1,
      sym_identifier,
    ACTIONS(15), 1,
      anon_sym_LBRACE,
    ACTIONS(17), 1,
      anon_sym_COMMA,
    ACTIONS(19), 1,
      sym_parameter_name,
    ACTIONS(21), 1,
      anon_sym_RPAREN,
    ACTIONS(23), 1,
      anon_sym_DOT,
    ACTIONS(27), 1,
      sym_user,
    ACTIONS(29), 1,
      sym_number,
    ACTIONS(31), 1,
      anon_sym_DQUOTE,
    ACTIONS(33), 1,
      anon_sym_SQUOTE,
    STATE(23), 1,
      aux_sym_uri_repeat1,
    STATE(55), 1,
      aux_sym_arguments_repeat1,
    ACTIONS(25), 2,
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
  [54] = 12,
    ACTIONS(13), 1,
      sym_identifier,
    ACTIONS(19), 1,
      sym_parameter_name,
    ACTIONS(23), 1,
      anon_sym_DOT,
    ACTIONS(27), 1,
      sym_user,
    ACTIONS(31), 1,
      anon_sym_DQUOTE,
    ACTIONS(33), 1,
      anon_sym_SQUOTE,
    ACTIONS(35), 1,
      anon_sym_LBRACE,
    ACTIONS(39), 1,
      sym_number,
    STATE(23), 1,
      aux_sym_uri_repeat1,
    ACTIONS(37), 2,
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
  [101] = 13,
    ACTIONS(13), 1,
      sym_identifier,
    ACTIONS(15), 1,
      anon_sym_LBRACE,
    ACTIONS(19), 1,
      sym_parameter_name,
    ACTIONS(23), 1,
      anon_sym_DOT,
    ACTIONS(27), 1,
      sym_user,
    ACTIONS(31), 1,
      anon_sym_DQUOTE,
    ACTIONS(33), 1,
      anon_sym_SQUOTE,
    ACTIONS(45), 1,
      sym_number,
    STATE(23), 1,
      aux_sym_uri_repeat1,
    ACTIONS(41), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
    ACTIONS(43), 2,
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
  [150] = 6,
    ACTIONS(5), 1,
      anon_sym_type,
    ACTIONS(7), 1,
      anon_sym_permission,
    ACTIONS(9), 1,
      anon_sym_query,
    ACTIONS(11), 1,
      anon_sym_action,
    ACTIONS(47), 1,
      ts_builtin_sym_end,
    STATE(6), 6,
      sym__declaration,
      sym_type_declaration,
      sym_permission_declaration,
      sym_query_declaration,
      sym_action_declaration,
      aux_sym_source_file_repeat1,
  [174] = 6,
    ACTIONS(49), 1,
      ts_builtin_sym_end,
    ACTIONS(51), 1,
      anon_sym_type,
    ACTIONS(54), 1,
      anon_sym_permission,
    ACTIONS(57), 1,
      anon_sym_query,
    ACTIONS(60), 1,
      anon_sym_action,
    STATE(6), 6,
      sym__declaration,
      sym_type_declaration,
      sym_permission_declaration,
      sym_query_declaration,
      sym_action_declaration,
      aux_sym_source_file_repeat1,
  [198] = 6,
    ACTIONS(63), 1,
      anon_sym_RBRACE,
    ACTIONS(65), 1,
      anon_sym_create,
    ACTIONS(67), 1,
      anon_sym_delete,
    ACTIONS(69), 1,
      anon_sym_update,
    STATE(138), 1,
      sym_statements,
    STATE(12), 5,
      sym__statement,
      sym_create_statement,
      sym_delete_statement,
      sym_update_statement,
      aux_sym_statements_repeat1,
  [221] = 1,
    ACTIONS(71), 10,
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
  [234] = 6,
    ACTIONS(65), 1,
      anon_sym_create,
    ACTIONS(67), 1,
      anon_sym_delete,
    ACTIONS(69), 1,
      anon_sym_update,
    ACTIONS(73), 1,
      anon_sym_RBRACE,
    STATE(150), 1,
      sym_statements,
    STATE(12), 5,
      sym__statement,
      sym_create_statement,
      sym_delete_statement,
      sym_update_statement,
      aux_sym_statements_repeat1,
  [257] = 5,
    ACTIONS(75), 1,
      anon_sym_RBRACE,
    ACTIONS(77), 1,
      anon_sym_create,
    ACTIONS(80), 1,
      anon_sym_delete,
    ACTIONS(83), 1,
      anon_sym_update,
    STATE(10), 5,
      sym__statement,
      sym_create_statement,
      sym_delete_statement,
      sym_update_statement,
      aux_sym_statements_repeat1,
  [277] = 1,
    ACTIONS(86), 9,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_LBRACE,
      anon_sym_COMMA,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
      anon_sym_SEMI,
      anon_sym_RPAREN,
  [289] = 5,
    ACTIONS(65), 1,
      anon_sym_create,
    ACTIONS(67), 1,
      anon_sym_delete,
    ACTIONS(69), 1,
      anon_sym_update,
    ACTIONS(88), 1,
      anon_sym_RBRACE,
    STATE(10), 5,
      sym__statement,
      sym_create_statement,
      sym_delete_statement,
      sym_update_statement,
      aux_sym_statements_repeat1,
  [309] = 4,
    ACTIONS(92), 1,
      anon_sym_DOT,
    STATE(23), 1,
      aux_sym_uri_repeat1,
    STATE(74), 1,
      sym_uri,
    ACTIONS(90), 3,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [324] = 6,
    ACTIONS(94), 1,
      sym_identifier,
    ACTIONS(96), 1,
      anon_sym_RBRACE,
    STATE(60), 1,
      sym_call,
    STATE(63), 1,
      sym_binding_field,
    STATE(131), 1,
      sym_binding_fields,
    STATE(132), 1,
      sym__query_body,
  [343] = 1,
    ACTIONS(98), 6,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      anon_sym_DOT,
  [352] = 3,
    ACTIONS(102), 1,
      anon_sym_LPAREN,
    STATE(34), 1,
      sym_arguments,
    ACTIONS(100), 4,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_DOT,
  [365] = 5,
    ACTIONS(15), 1,
      anon_sym_LBRACE,
    ACTIONS(104), 1,
      anon_sym_allow,
    STATE(33), 1,
      sym_query,
    STATE(122), 1,
      sym_guards_list,
    STATE(49), 2,
      sym_guard,
      aux_sym_guards_list_repeat1,
  [382] = 4,
    ACTIONS(104), 1,
      anon_sym_allow,
    ACTIONS(106), 1,
      anon_sym_LBRACE,
    STATE(124), 1,
      sym_guards_list,
    STATE(49), 2,
      sym_guard,
      aux_sym_guards_list_repeat1,
  [396] = 1,
    ACTIONS(108), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [404] = 1,
    ACTIONS(110), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [412] = 1,
    ACTIONS(112), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [420] = 1,
    ACTIONS(114), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [428] = 3,
    ACTIONS(92), 1,
      anon_sym_DOT,
    STATE(27), 1,
      aux_sym_uri_repeat1,
    ACTIONS(116), 3,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [440] = 1,
    ACTIONS(118), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [448] = 1,
    ACTIONS(120), 5,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_allow,
      anon_sym_RPAREN,
  [456] = 1,
    ACTIONS(122), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [464] = 3,
    ACTIONS(126), 1,
      anon_sym_DOT,
    STATE(27), 1,
      aux_sym_uri_repeat1,
    ACTIONS(124), 3,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [476] = 1,
    ACTIONS(129), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [484] = 1,
    ACTIONS(131), 5,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_allow,
      anon_sym_RPAREN,
  [492] = 1,
    ACTIONS(133), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [500] = 1,
    ACTIONS(135), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [508] = 1,
    ACTIONS(137), 5,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_allow,
      anon_sym_RPAREN,
  [516] = 1,
    ACTIONS(139), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [524] = 1,
    ACTIONS(141), 5,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_allow,
      anon_sym_RPAREN,
  [532] = 1,
    ACTIONS(143), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [540] = 1,
    ACTIONS(145), 4,
      anon_sym_RBRACE,
      anon_sym_create,
      anon_sym_delete,
      anon_sym_update,
  [547] = 4,
    ACTIONS(147), 1,
      sym_identifier,
    ACTIONS(149), 1,
      anon_sym_RBRACE,
    STATE(60), 1,
      sym_call,
    STATE(132), 1,
      sym__query_body,
  [560] = 4,
    ACTIONS(151), 1,
      anon_sym_SQUOTE,
    ACTIONS(153), 1,
      aux_sym_string_token2,
    ACTIONS(155), 1,
      sym_escape_sequence,
    STATE(39), 1,
      aux_sym_string_repeat2,
  [573] = 4,
    ACTIONS(157), 1,
      anon_sym_SQUOTE,
    ACTIONS(159), 1,
      aux_sym_string_token2,
    ACTIONS(162), 1,
      sym_escape_sequence,
    STATE(39), 1,
      aux_sym_string_repeat2,
  [586] = 4,
    ACTIONS(165), 1,
      sym_identifier,
    ACTIONS(167), 1,
      anon_sym_RBRACE,
    STATE(64), 1,
      sym_type_field,
    STATE(139), 1,
      sym_type_fields,
  [599] = 4,
    ACTIONS(151), 1,
      anon_sym_DQUOTE,
    ACTIONS(169), 1,
      aux_sym_string_token1,
    ACTIONS(171), 1,
      sym_escape_sequence,
    STATE(44), 1,
      aux_sym_string_repeat1,
  [612] = 4,
    ACTIONS(165), 1,
      sym_identifier,
    ACTIONS(173), 1,
      anon_sym_RBRACE,
    STATE(64), 1,
      sym_type_field,
    STATE(134), 1,
      sym_type_fields,
  [625] = 4,
    ACTIONS(175), 1,
      anon_sym_COMMA,
    ACTIONS(177), 1,
      sym_parameter_name,
    ACTIONS(179), 1,
      anon_sym_RPAREN,
    STATE(57), 1,
      sym_parameter,
  [638] = 4,
    ACTIONS(181), 1,
      anon_sym_DQUOTE,
    ACTIONS(183), 1,
      aux_sym_string_token1,
    ACTIONS(186), 1,
      sym_escape_sequence,
    STATE(44), 1,
      aux_sym_string_repeat1,
  [651] = 4,
    ACTIONS(189), 1,
      anon_sym_DQUOTE,
    ACTIONS(191), 1,
      aux_sym_string_token1,
    ACTIONS(193), 1,
      sym_escape_sequence,
    STATE(41), 1,
      aux_sym_string_repeat1,
  [664] = 1,
    ACTIONS(124), 4,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_DOT,
  [671] = 4,
    ACTIONS(189), 1,
      anon_sym_SQUOTE,
    ACTIONS(195), 1,
      aux_sym_string_token2,
    ACTIONS(197), 1,
      sym_escape_sequence,
    STATE(38), 1,
      aux_sym_string_repeat2,
  [684] = 1,
    ACTIONS(199), 4,
      anon_sym_RBRACE,
      anon_sym_create,
      anon_sym_delete,
      anon_sym_update,
  [691] = 3,
    ACTIONS(104), 1,
      anon_sym_allow,
    ACTIONS(201), 1,
      anon_sym_LBRACE,
    STATE(54), 2,
      sym_guard,
      aux_sym_guards_list_repeat1,
  [702] = 3,
    ACTIONS(15), 1,
      anon_sym_LBRACE,
    ACTIONS(19), 1,
      sym_parameter_name,
    STATE(118), 2,
      sym_parameter_reference,
      sym_query,
  [713] = 1,
    ACTIONS(203), 4,
      anon_sym_RBRACE,
      anon_sym_create,
      anon_sym_delete,
      anon_sym_update,
  [720] = 4,
    ACTIONS(205), 1,
      sym_identifier,
    ACTIONS(207), 1,
      anon_sym_RBRACE,
    STATE(63), 1,
      sym_binding_field,
    STATE(131), 1,
      sym_binding_fields,
  [733] = 3,
    ACTIONS(15), 1,
      anon_sym_LBRACE,
    ACTIONS(19), 1,
      sym_parameter_name,
    STATE(145), 2,
      sym_parameter_reference,
      sym_query,
  [744] = 3,
    ACTIONS(209), 1,
      anon_sym_LBRACE,
    ACTIONS(211), 1,
      anon_sym_allow,
    STATE(54), 2,
      sym_guard,
      aux_sym_guards_list_repeat1,
  [755] = 3,
    ACTIONS(17), 1,
      anon_sym_COMMA,
    ACTIONS(214), 1,
      anon_sym_RPAREN,
    STATE(62), 1,
      aux_sym_arguments_repeat1,
  [765] = 1,
    ACTIONS(216), 3,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [771] = 3,
    ACTIONS(218), 1,
      anon_sym_COMMA,
    ACTIONS(220), 1,
      anon_sym_RPAREN,
    STATE(67), 1,
      aux_sym_parameters_list_repeat1,
  [781] = 3,
    ACTIONS(147), 1,
      sym_identifier,
    ACTIONS(222), 1,
      anon_sym_RBRACE,
    STATE(110), 1,
      sym_call,
  [791] = 3,
    ACTIONS(224), 1,
      anon_sym_LBRACE,
    ACTIONS(226), 1,
      anon_sym_COMMA,
    STATE(66), 1,
      aux_sym_bases_list_repeat1,
  [801] = 3,
    ACTIONS(228), 1,
      anon_sym_RBRACE,
    ACTIONS(230), 1,
      anon_sym_COMMA,
    STATE(82), 1,
      aux_sym__query_body_repeat1,
  [811] = 3,
    ACTIONS(17), 1,
      anon_sym_COMMA,
    ACTIONS(232), 1,
      anon_sym_RPAREN,
    STATE(62), 1,
      aux_sym_arguments_repeat1,
  [821] = 3,
    ACTIONS(234), 1,
      anon_sym_COMMA,
    ACTIONS(237), 1,
      anon_sym_RPAREN,
    STATE(62), 1,
      aux_sym_arguments_repeat1,
  [831] = 3,
    ACTIONS(239), 1,
      anon_sym_RBRACE,
    ACTIONS(241), 1,
      anon_sym_COMMA,
    STATE(84), 1,
      aux_sym_binding_fields_repeat1,
  [841] = 3,
    ACTIONS(243), 1,
      anon_sym_RBRACE,
    ACTIONS(245), 1,
      anon_sym_COMMA,
    STATE(75), 1,
      aux_sym_type_fields_repeat1,
  [851] = 3,
    ACTIONS(17), 1,
      anon_sym_COMMA,
    ACTIONS(214), 1,
      anon_sym_RPAREN,
    STATE(61), 1,
      aux_sym_arguments_repeat1,
  [861] = 3,
    ACTIONS(247), 1,
      anon_sym_LBRACE,
    ACTIONS(249), 1,
      anon_sym_COMMA,
    STATE(66), 1,
      aux_sym_bases_list_repeat1,
  [871] = 3,
    ACTIONS(252), 1,
      anon_sym_COMMA,
    ACTIONS(254), 1,
      anon_sym_RPAREN,
    STATE(77), 1,
      aux_sym_parameters_list_repeat1,
  [881] = 3,
    ACTIONS(177), 1,
      sym_parameter_name,
    ACTIONS(254), 1,
      anon_sym_RPAREN,
    STATE(91), 1,
      sym_parameter,
  [891] = 3,
    ACTIONS(102), 1,
      anon_sym_LPAREN,
    ACTIONS(256), 1,
      anon_sym_COLON,
    STATE(34), 1,
      sym_arguments,
  [901] = 3,
    ACTIONS(258), 1,
      anon_sym_RBRACE,
    ACTIONS(260), 1,
      anon_sym_COMMA,
    STATE(70), 1,
      aux_sym__query_body_repeat1,
  [911] = 3,
    ACTIONS(263), 1,
      anon_sym_LBRACE,
    ACTIONS(265), 1,
      anon_sym_COMMA,
    STATE(59), 1,
      aux_sym_bases_list_repeat1,
  [921] = 3,
    ACTIONS(165), 1,
      sym_identifier,
    ACTIONS(267), 1,
      anon_sym_RBRACE,
    STATE(104), 1,
      sym_type_field,
  [931] = 3,
    ACTIONS(269), 1,
      anon_sym_RBRACE,
    ACTIONS(271), 1,
      anon_sym_COMMA,
    STATE(73), 1,
      aux_sym_type_fields_repeat1,
  [941] = 1,
    ACTIONS(274), 3,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [947] = 3,
    ACTIONS(276), 1,
      anon_sym_RBRACE,
    ACTIONS(278), 1,
      anon_sym_COMMA,
    STATE(73), 1,
      aux_sym_type_fields_repeat1,
  [957] = 3,
    ACTIONS(177), 1,
      sym_parameter_name,
    ACTIONS(280), 1,
      anon_sym_RPAREN,
    STATE(91), 1,
      sym_parameter,
  [967] = 3,
    ACTIONS(282), 1,
      anon_sym_COMMA,
    ACTIONS(285), 1,
      anon_sym_RPAREN,
    STATE(77), 1,
      aux_sym_parameters_list_repeat1,
  [977] = 3,
    ACTIONS(165), 1,
      sym_identifier,
    ACTIONS(276), 1,
      anon_sym_RBRACE,
    STATE(104), 1,
      sym_type_field,
  [987] = 1,
    ACTIONS(287), 3,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [993] = 1,
    ACTIONS(289), 3,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_SEMI,
  [999] = 3,
    ACTIONS(147), 1,
      sym_identifier,
    ACTIONS(291), 1,
      anon_sym_RBRACE,
    STATE(110), 1,
      sym_call,
  [1009] = 3,
    ACTIONS(291), 1,
      anon_sym_RBRACE,
    ACTIONS(293), 1,
      anon_sym_COMMA,
    STATE(70), 1,
      aux_sym__query_body_repeat1,
  [1019] = 3,
    ACTIONS(205), 1,
      sym_identifier,
    ACTIONS(295), 1,
      anon_sym_RBRACE,
    STATE(94), 1,
      sym_binding_field,
  [1029] = 3,
    ACTIONS(295), 1,
      anon_sym_RBRACE,
    ACTIONS(297), 1,
      anon_sym_COMMA,
    STATE(86), 1,
      aux_sym_binding_fields_repeat1,
  [1039] = 3,
    ACTIONS(205), 1,
      sym_identifier,
    ACTIONS(299), 1,
      anon_sym_RBRACE,
    STATE(94), 1,
      sym_binding_field,
  [1049] = 3,
    ACTIONS(301), 1,
      anon_sym_RBRACE,
    ACTIONS(303), 1,
      anon_sym_COMMA,
    STATE(86), 1,
      aux_sym_binding_fields_repeat1,
  [1059] = 2,
    ACTIONS(224), 1,
      anon_sym_LBRACE,
    ACTIONS(306), 1,
      sym_identifier,
  [1066] = 1,
    ACTIONS(237), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [1071] = 1,
    ACTIONS(308), 2,
      anon_sym_LBRACE,
      anon_sym_allow,
  [1076] = 2,
    ACTIONS(310), 1,
      anon_sym_LBRACE,
    STATE(135), 1,
      sym_binding,
  [1083] = 1,
    ACTIONS(285), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [1088] = 2,
    ACTIONS(205), 1,
      sym_identifier,
    STATE(94), 1,
      sym_binding_field,
  [1095] = 1,
    ACTIONS(312), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [1100] = 1,
    ACTIONS(301), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [1105] = 1,
    ACTIONS(314), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [1110] = 2,
    ACTIONS(165), 1,
      sym_identifier,
    STATE(104), 1,
      sym_type_field,
  [1117] = 1,
    ACTIONS(316), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [1122] = 1,
    ACTIONS(318), 2,
      anon_sym_LBRACE,
      anon_sym_allow,
  [1127] = 2,
    ACTIONS(177), 1,
      sym_parameter_name,
    STATE(91), 1,
      sym_parameter,
  [1134] = 1,
    ACTIONS(320), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [1139] = 2,
    ACTIONS(322), 1,
      anon_sym_COLON,
    ACTIONS(324), 1,
      anon_sym_LBRACE,
  [1146] = 1,
    ACTIONS(326), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [1151] = 2,
    ACTIONS(328), 1,
      anon_sym_LPAREN,
    STATE(112), 1,
      sym_parameters_list,
  [1158] = 1,
    ACTIONS(269), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [1163] = 2,
    ACTIONS(328), 1,
      anon_sym_LPAREN,
    STATE(17), 1,
      sym_parameters_list,
  [1170] = 1,
    ACTIONS(330), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [1175] = 2,
    ACTIONS(328), 1,
      anon_sym_LPAREN,
    STATE(18), 1,
      sym_parameters_list,
  [1182] = 2,
    ACTIONS(306), 1,
      sym_identifier,
    ACTIONS(332), 1,
      anon_sym_LBRACE,
  [1189] = 1,
    ACTIONS(247), 2,
      anon_sym_LBRACE,
      anon_sym_COMMA,
  [1194] = 1,
    ACTIONS(258), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [1199] = 2,
    ACTIONS(334), 1,
      sym_identifier,
    STATE(136), 1,
      sym_bases_list,
  [1206] = 2,
    ACTIONS(15), 1,
      anon_sym_LBRACE,
    STATE(30), 1,
      sym_query,
  [1213] = 1,
    ACTIONS(336), 2,
      anon_sym_LBRACE,
      anon_sym_allow,
  [1218] = 2,
    ACTIONS(338), 1,
      anon_sym_COLON,
    ACTIONS(340), 1,
      anon_sym_QMARK,
  [1225] = 2,
    ACTIONS(342), 1,
      anon_sym_COLON,
    ACTIONS(344), 1,
      anon_sym_QMARK,
  [1232] = 2,
    ACTIONS(147), 1,
      sym_identifier,
    STATE(110), 1,
      sym_call,
  [1239] = 2,
    ACTIONS(102), 1,
      anon_sym_LPAREN,
    STATE(34), 1,
      sym_arguments,
  [1246] = 2,
    ACTIONS(310), 1,
      anon_sym_LBRACE,
    STATE(128), 1,
      sym_binding,
  [1253] = 1,
    ACTIONS(346), 2,
      anon_sym_LBRACE,
      anon_sym_allow,
  [1258] = 2,
    ACTIONS(147), 1,
      sym_identifier,
    STATE(113), 1,
      sym_call,
  [1265] = 1,
    ACTIONS(348), 2,
      anon_sym_LBRACE,
      anon_sym_allow,
  [1270] = 2,
    ACTIONS(15), 1,
      anon_sym_LBRACE,
    STATE(28), 1,
      sym_query,
  [1277] = 1,
    ACTIONS(350), 1,
      sym_identifier,
  [1281] = 1,
    ACTIONS(352), 1,
      anon_sym_LBRACE,
  [1285] = 1,
    ACTIONS(354), 1,
      anon_sym_COLON,
  [1289] = 1,
    ACTIONS(356), 1,
      sym_identifier,
  [1293] = 1,
    ACTIONS(358), 1,
      anon_sym_COLON,
  [1297] = 1,
    ACTIONS(360), 1,
      anon_sym_SEMI,
  [1301] = 1,
    ACTIONS(312), 1,
      anon_sym_SEMI,
  [1305] = 1,
    ACTIONS(256), 1,
      anon_sym_COLON,
  [1309] = 1,
    ACTIONS(362), 1,
      anon_sym_RBRACE,
  [1313] = 1,
    ACTIONS(364), 1,
      anon_sym_RBRACE,
  [1317] = 1,
    ACTIONS(220), 1,
      anon_sym_RPAREN,
  [1321] = 1,
    ACTIONS(366), 1,
      anon_sym_RBRACE,
  [1325] = 1,
    ACTIONS(368), 1,
      anon_sym_SEMI,
  [1329] = 1,
    ACTIONS(370), 1,
      anon_sym_LBRACE,
  [1333] = 1,
    ACTIONS(372), 1,
      sym_identifier,
  [1337] = 1,
    ACTIONS(374), 1,
      anon_sym_RBRACE,
  [1341] = 1,
    ACTIONS(376), 1,
      anon_sym_RBRACE,
  [1345] = 1,
    ACTIONS(378), 1,
      sym_identifier,
  [1349] = 1,
    ACTIONS(380), 1,
      sym_identifier,
  [1353] = 1,
    ACTIONS(382), 1,
      sym_identifier,
  [1357] = 1,
    ACTIONS(384), 1,
      ts_builtin_sym_end,
  [1361] = 1,
    ACTIONS(386), 1,
      sym_identifier,
  [1365] = 1,
    ACTIONS(388), 1,
      anon_sym_SEMI,
  [1369] = 1,
    ACTIONS(390), 1,
      sym_identifier,
  [1373] = 1,
    ACTIONS(392), 1,
      sym_identifier,
  [1377] = 1,
    ACTIONS(306), 1,
      sym_identifier,
  [1381] = 1,
    ACTIONS(394), 1,
      sym_identifier,
  [1385] = 1,
    ACTIONS(396), 1,
      anon_sym_RBRACE,
};

static uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 54,
  [SMALL_STATE(4)] = 101,
  [SMALL_STATE(5)] = 150,
  [SMALL_STATE(6)] = 174,
  [SMALL_STATE(7)] = 198,
  [SMALL_STATE(8)] = 221,
  [SMALL_STATE(9)] = 234,
  [SMALL_STATE(10)] = 257,
  [SMALL_STATE(11)] = 277,
  [SMALL_STATE(12)] = 289,
  [SMALL_STATE(13)] = 309,
  [SMALL_STATE(14)] = 324,
  [SMALL_STATE(15)] = 343,
  [SMALL_STATE(16)] = 352,
  [SMALL_STATE(17)] = 365,
  [SMALL_STATE(18)] = 382,
  [SMALL_STATE(19)] = 396,
  [SMALL_STATE(20)] = 404,
  [SMALL_STATE(21)] = 412,
  [SMALL_STATE(22)] = 420,
  [SMALL_STATE(23)] = 428,
  [SMALL_STATE(24)] = 440,
  [SMALL_STATE(25)] = 448,
  [SMALL_STATE(26)] = 456,
  [SMALL_STATE(27)] = 464,
  [SMALL_STATE(28)] = 476,
  [SMALL_STATE(29)] = 484,
  [SMALL_STATE(30)] = 492,
  [SMALL_STATE(31)] = 500,
  [SMALL_STATE(32)] = 508,
  [SMALL_STATE(33)] = 516,
  [SMALL_STATE(34)] = 524,
  [SMALL_STATE(35)] = 532,
  [SMALL_STATE(36)] = 540,
  [SMALL_STATE(37)] = 547,
  [SMALL_STATE(38)] = 560,
  [SMALL_STATE(39)] = 573,
  [SMALL_STATE(40)] = 586,
  [SMALL_STATE(41)] = 599,
  [SMALL_STATE(42)] = 612,
  [SMALL_STATE(43)] = 625,
  [SMALL_STATE(44)] = 638,
  [SMALL_STATE(45)] = 651,
  [SMALL_STATE(46)] = 664,
  [SMALL_STATE(47)] = 671,
  [SMALL_STATE(48)] = 684,
  [SMALL_STATE(49)] = 691,
  [SMALL_STATE(50)] = 702,
  [SMALL_STATE(51)] = 713,
  [SMALL_STATE(52)] = 720,
  [SMALL_STATE(53)] = 733,
  [SMALL_STATE(54)] = 744,
  [SMALL_STATE(55)] = 755,
  [SMALL_STATE(56)] = 765,
  [SMALL_STATE(57)] = 771,
  [SMALL_STATE(58)] = 781,
  [SMALL_STATE(59)] = 791,
  [SMALL_STATE(60)] = 801,
  [SMALL_STATE(61)] = 811,
  [SMALL_STATE(62)] = 821,
  [SMALL_STATE(63)] = 831,
  [SMALL_STATE(64)] = 841,
  [SMALL_STATE(65)] = 851,
  [SMALL_STATE(66)] = 861,
  [SMALL_STATE(67)] = 871,
  [SMALL_STATE(68)] = 881,
  [SMALL_STATE(69)] = 891,
  [SMALL_STATE(70)] = 901,
  [SMALL_STATE(71)] = 911,
  [SMALL_STATE(72)] = 921,
  [SMALL_STATE(73)] = 931,
  [SMALL_STATE(74)] = 941,
  [SMALL_STATE(75)] = 947,
  [SMALL_STATE(76)] = 957,
  [SMALL_STATE(77)] = 967,
  [SMALL_STATE(78)] = 977,
  [SMALL_STATE(79)] = 987,
  [SMALL_STATE(80)] = 993,
  [SMALL_STATE(81)] = 999,
  [SMALL_STATE(82)] = 1009,
  [SMALL_STATE(83)] = 1019,
  [SMALL_STATE(84)] = 1029,
  [SMALL_STATE(85)] = 1039,
  [SMALL_STATE(86)] = 1049,
  [SMALL_STATE(87)] = 1059,
  [SMALL_STATE(88)] = 1066,
  [SMALL_STATE(89)] = 1071,
  [SMALL_STATE(90)] = 1076,
  [SMALL_STATE(91)] = 1083,
  [SMALL_STATE(92)] = 1088,
  [SMALL_STATE(93)] = 1095,
  [SMALL_STATE(94)] = 1100,
  [SMALL_STATE(95)] = 1105,
  [SMALL_STATE(96)] = 1110,
  [SMALL_STATE(97)] = 1117,
  [SMALL_STATE(98)] = 1122,
  [SMALL_STATE(99)] = 1127,
  [SMALL_STATE(100)] = 1134,
  [SMALL_STATE(101)] = 1139,
  [SMALL_STATE(102)] = 1146,
  [SMALL_STATE(103)] = 1151,
  [SMALL_STATE(104)] = 1158,
  [SMALL_STATE(105)] = 1163,
  [SMALL_STATE(106)] = 1170,
  [SMALL_STATE(107)] = 1175,
  [SMALL_STATE(108)] = 1182,
  [SMALL_STATE(109)] = 1189,
  [SMALL_STATE(110)] = 1194,
  [SMALL_STATE(111)] = 1199,
  [SMALL_STATE(112)] = 1206,
  [SMALL_STATE(113)] = 1213,
  [SMALL_STATE(114)] = 1218,
  [SMALL_STATE(115)] = 1225,
  [SMALL_STATE(116)] = 1232,
  [SMALL_STATE(117)] = 1239,
  [SMALL_STATE(118)] = 1246,
  [SMALL_STATE(119)] = 1253,
  [SMALL_STATE(120)] = 1258,
  [SMALL_STATE(121)] = 1265,
  [SMALL_STATE(122)] = 1270,
  [SMALL_STATE(123)] = 1277,
  [SMALL_STATE(124)] = 1281,
  [SMALL_STATE(125)] = 1285,
  [SMALL_STATE(126)] = 1289,
  [SMALL_STATE(127)] = 1293,
  [SMALL_STATE(128)] = 1297,
  [SMALL_STATE(129)] = 1301,
  [SMALL_STATE(130)] = 1305,
  [SMALL_STATE(131)] = 1309,
  [SMALL_STATE(132)] = 1313,
  [SMALL_STATE(133)] = 1317,
  [SMALL_STATE(134)] = 1321,
  [SMALL_STATE(135)] = 1325,
  [SMALL_STATE(136)] = 1329,
  [SMALL_STATE(137)] = 1333,
  [SMALL_STATE(138)] = 1337,
  [SMALL_STATE(139)] = 1341,
  [SMALL_STATE(140)] = 1345,
  [SMALL_STATE(141)] = 1349,
  [SMALL_STATE(142)] = 1353,
  [SMALL_STATE(143)] = 1357,
  [SMALL_STATE(144)] = 1361,
  [SMALL_STATE(145)] = 1365,
  [SMALL_STATE(146)] = 1369,
  [SMALL_STATE(147)] = 1373,
  [SMALL_STATE(148)] = 1377,
  [SMALL_STATE(149)] = 1381,
  [SMALL_STATE(150)] = 1385,
};

static TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(144),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(149),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(147),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(146),
  [13] = {.entry = {.count = 1, .reusable = false}}, SHIFT(16),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [23] = {.entry = {.count = 1, .reusable = false}}, SHIFT(141),
  [25] = {.entry = {.count = 1, .reusable = false}}, SHIFT(65),
  [27] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [29] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [31] = {.entry = {.count = 1, .reusable = true}}, SHIFT(45),
  [33] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [35] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [37] = {.entry = {.count = 1, .reusable = false}}, SHIFT(100),
  [39] = {.entry = {.count = 1, .reusable = true}}, SHIFT(100),
  [41] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_arguments_repeat1, 1),
  [43] = {.entry = {.count = 1, .reusable = false}}, SHIFT(88),
  [45] = {.entry = {.count = 1, .reusable = true}}, SHIFT(88),
  [47] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1),
  [49] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2),
  [51] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(144),
  [54] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(149),
  [57] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(147),
  [60] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(146),
  [63] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [65] = {.entry = {.count = 1, .reusable = true}}, SHIFT(137),
  [67] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [69] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [71] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query, 3),
  [73] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [75] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_statements_repeat1, 2),
  [77] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_statements_repeat1, 2), SHIFT_REPEAT(137),
  [80] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_statements_repeat1, 2), SHIFT_REPEAT(53),
  [83] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_statements_repeat1, 2), SHIFT_REPEAT(50),
  [86] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query, 2),
  [88] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_statements, 1),
  [90] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_variable, 1, .production_id = 14),
  [92] = {.entry = {.count = 1, .reusable = true}}, SHIFT(141),
  [94] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [96] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [98] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameter_reference, 1),
  [100] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_reference, 1),
  [102] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [104] = {.entry = {.count = 1, .reusable = true}}, SHIFT(120),
  [106] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [108] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_action_declaration, 6, .production_id = 11),
  [110] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 6, .production_id = 7),
  [112] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 4, .production_id = 1),
  [114] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 7, .production_id = 12),
  [116] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_uri, 1),
  [118] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 5, .production_id = 3),
  [120] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_arguments, 2),
  [122] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_action_declaration, 5, .production_id = 6),
  [124] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_uri_repeat1, 2),
  [126] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_uri_repeat1, 2), SHIFT_REPEAT(141),
  [129] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query_declaration, 5, .production_id = 5),
  [131] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_arguments, 4),
  [133] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_permission_declaration, 4, .production_id = 2),
  [135] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_action_declaration, 7, .production_id = 16),
  [137] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_arguments, 3),
  [139] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query_declaration, 4, .production_id = 2),
  [141] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call, 2, .production_id = 9),
  [143] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_action_declaration, 6, .production_id = 10),
  [145] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_update_statement, 4, .production_id = 19),
  [147] = {.entry = {.count = 1, .reusable = true}}, SHIFT(117),
  [149] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [151] = {.entry = {.count = 1, .reusable = false}}, SHIFT(56),
  [153] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [155] = {.entry = {.count = 1, .reusable = false}}, SHIFT(39),
  [157] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_string_repeat2, 2),
  [159] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_string_repeat2, 2), SHIFT_REPEAT(39),
  [162] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_string_repeat2, 2), SHIFT_REPEAT(39),
  [165] = {.entry = {.count = 1, .reusable = true}}, SHIFT(114),
  [167] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [169] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [171] = {.entry = {.count = 1, .reusable = false}}, SHIFT(44),
  [173] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [175] = {.entry = {.count = 1, .reusable = true}}, SHIFT(133),
  [177] = {.entry = {.count = 1, .reusable = true}}, SHIFT(115),
  [179] = {.entry = {.count = 1, .reusable = true}}, SHIFT(119),
  [181] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_string_repeat1, 2),
  [183] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_string_repeat1, 2), SHIFT_REPEAT(44),
  [186] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_string_repeat1, 2), SHIFT_REPEAT(44),
  [189] = {.entry = {.count = 1, .reusable = false}}, SHIFT(79),
  [191] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [193] = {.entry = {.count = 1, .reusable = false}}, SHIFT(41),
  [195] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [197] = {.entry = {.count = 1, .reusable = false}}, SHIFT(38),
  [199] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_statement, 4, .production_id = 18),
  [201] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_guards_list, 1),
  [203] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_delete_statement, 3, .production_id = 15),
  [205] = {.entry = {.count = 1, .reusable = true}}, SHIFT(130),
  [207] = {.entry = {.count = 1, .reusable = true}}, SHIFT(129),
  [209] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_guards_list_repeat1, 2),
  [211] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_guards_list_repeat1, 2), SHIFT_REPEAT(120),
  [214] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [216] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 3),
  [218] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [220] = {.entry = {.count = 1, .reusable = true}}, SHIFT(121),
  [222] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__query_body, 3),
  [224] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bases_list, 2),
  [226] = {.entry = {.count = 1, .reusable = true}}, SHIFT(108),
  [228] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__query_body, 1),
  [230] = {.entry = {.count = 1, .reusable = true}}, SHIFT(81),
  [232] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [234] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_arguments_repeat1, 2), SHIFT_REPEAT(4),
  [237] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_arguments_repeat1, 2),
  [239] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding_fields, 1),
  [241] = {.entry = {.count = 1, .reusable = true}}, SHIFT(83),
  [243] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_fields, 1),
  [245] = {.entry = {.count = 1, .reusable = true}}, SHIFT(78),
  [247] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_bases_list_repeat1, 2),
  [249] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_bases_list_repeat1, 2), SHIFT_REPEAT(148),
  [252] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [254] = {.entry = {.count = 1, .reusable = true}}, SHIFT(89),
  [256] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [258] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2),
  [260] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2), SHIFT_REPEAT(116),
  [263] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bases_list, 1),
  [265] = {.entry = {.count = 1, .reusable = true}}, SHIFT(87),
  [267] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_fields, 3),
  [269] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_type_fields_repeat1, 2),
  [271] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_type_fields_repeat1, 2), SHIFT_REPEAT(96),
  [274] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_variable, 2, .production_id = 17),
  [276] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_fields, 2),
  [278] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [280] = {.entry = {.count = 1, .reusable = true}}, SHIFT(98),
  [282] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_parameters_list_repeat1, 2), SHIFT_REPEAT(99),
  [285] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_parameters_list_repeat1, 2),
  [287] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 2),
  [289] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding, 3, .production_id = 20),
  [291] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__query_body, 2),
  [293] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [295] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding_fields, 2),
  [297] = {.entry = {.count = 1, .reusable = true}}, SHIFT(85),
  [299] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding_fields, 3),
  [301] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_binding_fields_repeat1, 2),
  [303] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_binding_fields_repeat1, 2), SHIFT_REPEAT(92),
  [306] = {.entry = {.count = 1, .reusable = true}}, SHIFT(109),
  [308] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameters_list, 4),
  [310] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [312] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding, 2),
  [314] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_field, 4, .production_id = 13),
  [316] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameter, 4),
  [318] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameters_list, 5),
  [320] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding_field, 3, .production_id = 21),
  [322] = {.entry = {.count = 1, .reusable = true}}, SHIFT(111),
  [324] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [326] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameter, 3),
  [328] = {.entry = {.count = 1, .reusable = true}}, SHIFT(43),
  [330] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_field, 3, .production_id = 8),
  [332] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bases_list, 3),
  [334] = {.entry = {.count = 1, .reusable = true}}, SHIFT(71),
  [336] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_guard, 2, .production_id = 4),
  [338] = {.entry = {.count = 1, .reusable = true}}, SHIFT(123),
  [340] = {.entry = {.count = 1, .reusable = true}}, SHIFT(125),
  [342] = {.entry = {.count = 1, .reusable = true}}, SHIFT(126),
  [344] = {.entry = {.count = 1, .reusable = true}}, SHIFT(127),
  [346] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameters_list, 2),
  [348] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameters_list, 3),
  [350] = {.entry = {.count = 1, .reusable = true}}, SHIFT(106),
  [352] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [354] = {.entry = {.count = 1, .reusable = true}}, SHIFT(140),
  [356] = {.entry = {.count = 1, .reusable = true}}, SHIFT(102),
  [358] = {.entry = {.count = 1, .reusable = true}}, SHIFT(142),
  [360] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [362] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [364] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [366] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [368] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [370] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [372] = {.entry = {.count = 1, .reusable = true}}, SHIFT(90),
  [374] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [376] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [378] = {.entry = {.count = 1, .reusable = true}}, SHIFT(95),
  [380] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [382] = {.entry = {.count = 1, .reusable = true}}, SHIFT(97),
  [384] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [386] = {.entry = {.count = 1, .reusable = true}}, SHIFT(101),
  [388] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [390] = {.entry = {.count = 1, .reusable = true}}, SHIFT(107),
  [392] = {.entry = {.count = 1, .reusable = true}}, SHIFT(105),
  [394] = {.entry = {.count = 1, .reusable = true}}, SHIFT(103),
  [396] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
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
