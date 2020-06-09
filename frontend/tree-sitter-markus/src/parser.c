#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 11
#define STATE_COUNT 151
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 71
#define ALIAS_COUNT 0
#define TOKEN_COUNT 27
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 15
#define MAX_ALIAS_SEQUENCE_LENGTH 7

enum {
  anon_sym_type = 1,
  anon_sym_COLON = 2,
  anon_sym_LBRACE = 3,
  anon_sym_RBRACE = 4,
  anon_sym_COMMA = 5,
  anon_sym_QMARK = 6,
  anon_sym_permission = 7,
  anon_sym_query = 8,
  anon_sym_allow = 9,
  anon_sym_action = 10,
  anon_sym_create = 11,
  anon_sym_SEMI = 12,
  anon_sym_delete = 13,
  anon_sym_update = 14,
  sym_identifier = 15,
  sym_parameter_name = 16,
  anon_sym_LPAREN = 17,
  anon_sym_RPAREN = 18,
  anon_sym_DOT = 19,
  sym_user = 20,
  sym_number = 21,
  anon_sym_DQUOTE = 22,
  aux_sym_string_token1 = 23,
  anon_sym_SQUOTE = 24,
  aux_sym_string_token2 = 25,
  sym_escape_sequence = 26,
  sym_source_file = 27,
  sym__declaration = 28,
  sym_type_declaration = 29,
  sym_bases_list = 30,
  sym_type_fields = 31,
  sym_type_field = 32,
  sym_permission_declaration = 33,
  sym_query_declaration = 34,
  sym_guards_list = 35,
  sym_guard = 36,
  sym_action_declaration = 37,
  sym_statements = 38,
  sym__statement = 39,
  sym_create_statement = 40,
  sym_delete_statement = 41,
  sym_update_statement = 42,
  sym_binding = 43,
  sym_binding_fields = 44,
  sym_binding_field = 45,
  sym__binding_value = 46,
  sym_parameters_list = 47,
  sym_parameter = 48,
  sym__value = 49,
  sym_variable = 50,
  sym_uri = 51,
  sym_parameter_reference = 52,
  sym_type_reference = 53,
  sym_query = 54,
  sym__query_body = 55,
  sym_call = 56,
  sym_arguments = 57,
  sym_string = 58,
  aux_sym_source_file_repeat1 = 59,
  aux_sym_bases_list_repeat1 = 60,
  aux_sym_type_fields_repeat1 = 61,
  aux_sym_guards_list_repeat1 = 62,
  aux_sym_statements_repeat1 = 63,
  aux_sym_binding_fields_repeat1 = 64,
  aux_sym_parameters_list_repeat1 = 65,
  aux_sym_uri_repeat1 = 66,
  aux_sym__query_body_repeat1 = 67,
  aux_sym_arguments_repeat1 = 68,
  aux_sym_string_repeat1 = 69,
  aux_sym_string_repeat2 = 70,
};

static const char *ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
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
  [sym_identifier] = "identifier",
  [sym_parameter_name] = "parameter_name",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [anon_sym_DOT] = ".",
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
  [sym_identifier] = sym_identifier,
  [sym_parameter_name] = sym_parameter_name,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [anon_sym_DOT] = anon_sym_DOT,
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
  [sym_identifier] = {
    .visible = true,
    .named = true,
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
      if (eof) ADVANCE(64);
      if (lookahead == '"') ADVANCE(88);
      if (lookahead == '$') ADVANCE(62);
      if (lookahead == '%') ADVANCE(47);
      if (lookahead == '\'') ADVANCE(92);
      if (lookahead == '(') ADVANCE(81);
      if (lookahead == ')') ADVANCE(82);
      if (lookahead == ',') ADVANCE(69);
      if (lookahead == '.') ADVANCE(83);
      if (lookahead == ':') ADVANCE(66);
      if (lookahead == ';') ADVANCE(76);
      if (lookahead == '?') ADVANCE(70);
      if (lookahead == '\\') ADVANCE(48);
      if (lookahead == 'a') ADVANCE(11);
      if (lookahead == 'c') ADVANCE(39);
      if (lookahead == 'd') ADVANCE(19);
      if (lookahead == 'p') ADVANCE(18);
      if (lookahead == 'q') ADVANCE(49);
      if (lookahead == 't') ADVANCE(52);
      if (lookahead == 'u') ADVANCE(34);
      if (lookahead == '{') ADVANCE(67);
      if (lookahead == '}') ADVANCE(68);
      if (('+' <= lookahead && lookahead <= '-')) ADVANCE(8);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(63)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(85);
      END_STATE();
    case 1:
      if (lookahead == '\n') SKIP(7)
      if (lookahead == '\'') ADVANCE(92);
      if (lookahead == '\\') ADVANCE(2);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(94);
      if (lookahead != 0) ADVANCE(95);
      END_STATE();
    case 2:
      if (lookahead == '\n') ADVANCE(93);
      if (lookahead == '\r') ADVANCE(97);
      if (lookahead == 'u') ADVANCE(53);
      if (lookahead == 'x') ADVANCE(61);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(100);
      if (lookahead != 0) ADVANCE(96);
      END_STATE();
    case 3:
      if (lookahead == '\n') SKIP(6)
      if (lookahead == '"') ADVANCE(88);
      if (lookahead == '\\') ADVANCE(4);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(90);
      if (lookahead != 0) ADVANCE(91);
      END_STATE();
    case 4:
      if (lookahead == '\n') ADVANCE(89);
      if (lookahead == '\r') ADVANCE(98);
      if (lookahead == 'u') ADVANCE(53);
      if (lookahead == 'x') ADVANCE(61);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(100);
      if (lookahead != 0) ADVANCE(96);
      END_STATE();
    case 5:
      if (lookahead == '"') ADVANCE(88);
      if (lookahead == '$') ADVANCE(62);
      if (lookahead == '%') ADVANCE(47);
      if (lookahead == '\'') ADVANCE(92);
      if (lookahead == ')') ADVANCE(82);
      if (lookahead == ',') ADVANCE(69);
      if (lookahead == '.') ADVANCE(83);
      if (lookahead == '{') ADVANCE(67);
      if (lookahead == '}') ADVANCE(68);
      if (('+' <= lookahead && lookahead <= '-')) ADVANCE(8);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(5)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(85);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(79);
      END_STATE();
    case 6:
      if (lookahead == '"') ADVANCE(88);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(6)
      END_STATE();
    case 7:
      if (lookahead == '\'') ADVANCE(92);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(7)
      END_STATE();
    case 8:
      if (lookahead == '.') ADVANCE(56);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(85);
      END_STATE();
    case 9:
      if (lookahead == 'a') ADVANCE(44);
      END_STATE();
    case 10:
      if (lookahead == 'a') ADVANCE(46);
      END_STATE();
    case 11:
      if (lookahead == 'c') ADVANCE(43);
      if (lookahead == 'l') ADVANCE(26);
      END_STATE();
    case 12:
      if (lookahead == 'd') ADVANCE(10);
      END_STATE();
    case 13:
      if (lookahead == 'e') ADVANCE(9);
      END_STATE();
    case 14:
      if (lookahead == 'e') ADVANCE(65);
      END_STATE();
    case 15:
      if (lookahead == 'e') ADVANCE(75);
      END_STATE();
    case 16:
      if (lookahead == 'e') ADVANCE(77);
      END_STATE();
    case 17:
      if (lookahead == 'e') ADVANCE(78);
      END_STATE();
    case 18:
      if (lookahead == 'e') ADVANCE(36);
      END_STATE();
    case 19:
      if (lookahead == 'e') ADVANCE(27);
      END_STATE();
    case 20:
      if (lookahead == 'e') ADVANCE(38);
      END_STATE();
    case 21:
      if (lookahead == 'e') ADVANCE(37);
      END_STATE();
    case 22:
      if (lookahead == 'e') ADVANCE(45);
      END_STATE();
    case 23:
      if (lookahead == 'i') ADVANCE(40);
      END_STATE();
    case 24:
      if (lookahead == 'i') ADVANCE(32);
      END_STATE();
    case 25:
      if (lookahead == 'i') ADVANCE(33);
      END_STATE();
    case 26:
      if (lookahead == 'l') ADVANCE(31);
      END_STATE();
    case 27:
      if (lookahead == 'l') ADVANCE(22);
      END_STATE();
    case 28:
      if (lookahead == 'm') ADVANCE(23);
      END_STATE();
    case 29:
      if (lookahead == 'n') ADVANCE(74);
      END_STATE();
    case 30:
      if (lookahead == 'n') ADVANCE(71);
      END_STATE();
    case 31:
      if (lookahead == 'o') ADVANCE(50);
      END_STATE();
    case 32:
      if (lookahead == 'o') ADVANCE(29);
      END_STATE();
    case 33:
      if (lookahead == 'o') ADVANCE(30);
      END_STATE();
    case 34:
      if (lookahead == 'p') ADVANCE(12);
      END_STATE();
    case 35:
      if (lookahead == 'p') ADVANCE(14);
      END_STATE();
    case 36:
      if (lookahead == 'r') ADVANCE(28);
      END_STATE();
    case 37:
      if (lookahead == 'r') ADVANCE(84);
      END_STATE();
    case 38:
      if (lookahead == 'r') ADVANCE(51);
      END_STATE();
    case 39:
      if (lookahead == 'r') ADVANCE(13);
      END_STATE();
    case 40:
      if (lookahead == 's') ADVANCE(42);
      END_STATE();
    case 41:
      if (lookahead == 's') ADVANCE(21);
      END_STATE();
    case 42:
      if (lookahead == 's') ADVANCE(25);
      END_STATE();
    case 43:
      if (lookahead == 't') ADVANCE(24);
      END_STATE();
    case 44:
      if (lookahead == 't') ADVANCE(15);
      END_STATE();
    case 45:
      if (lookahead == 't') ADVANCE(16);
      END_STATE();
    case 46:
      if (lookahead == 't') ADVANCE(17);
      END_STATE();
    case 47:
      if (lookahead == 'u') ADVANCE(41);
      END_STATE();
    case 48:
      if (lookahead == 'u') ADVANCE(53);
      if (lookahead == 'x') ADVANCE(61);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(100);
      if (lookahead != 0) ADVANCE(96);
      END_STATE();
    case 49:
      if (lookahead == 'u') ADVANCE(20);
      END_STATE();
    case 50:
      if (lookahead == 'w') ADVANCE(73);
      END_STATE();
    case 51:
      if (lookahead == 'y') ADVANCE(72);
      END_STATE();
    case 52:
      if (lookahead == 'y') ADVANCE(35);
      END_STATE();
    case 53:
      if (lookahead == '{') ADVANCE(60);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(58);
      END_STATE();
    case 54:
      if (lookahead == '}') ADVANCE(96);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(54);
      END_STATE();
    case 55:
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(57);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(87);
      END_STATE();
    case 56:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(86);
      END_STATE();
    case 57:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(87);
      END_STATE();
    case 58:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(61);
      END_STATE();
    case 59:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(96);
      END_STATE();
    case 60:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(54);
      END_STATE();
    case 61:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(59);
      END_STATE();
    case 62:
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(80);
      END_STATE();
    case 63:
      if (eof) ADVANCE(64);
      if (lookahead == '"') ADVANCE(88);
      if (lookahead == '$') ADVANCE(62);
      if (lookahead == '%') ADVANCE(47);
      if (lookahead == '\'') ADVANCE(92);
      if (lookahead == '(') ADVANCE(81);
      if (lookahead == ')') ADVANCE(82);
      if (lookahead == ',') ADVANCE(69);
      if (lookahead == '.') ADVANCE(83);
      if (lookahead == ':') ADVANCE(66);
      if (lookahead == ';') ADVANCE(76);
      if (lookahead == '?') ADVANCE(70);
      if (lookahead == 'a') ADVANCE(11);
      if (lookahead == 'c') ADVANCE(39);
      if (lookahead == 'd') ADVANCE(19);
      if (lookahead == 'p') ADVANCE(18);
      if (lookahead == 'q') ADVANCE(49);
      if (lookahead == 't') ADVANCE(52);
      if (lookahead == 'u') ADVANCE(34);
      if (lookahead == '{') ADVANCE(67);
      if (lookahead == '}') ADVANCE(68);
      if (('+' <= lookahead && lookahead <= '-')) ADVANCE(8);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(63)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(85);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(anon_sym_type);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 68:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 70:
      ACCEPT_TOKEN(anon_sym_QMARK);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(anon_sym_permission);
      END_STATE();
    case 72:
      ACCEPT_TOKEN(anon_sym_query);
      END_STATE();
    case 73:
      ACCEPT_TOKEN(anon_sym_allow);
      END_STATE();
    case 74:
      ACCEPT_TOKEN(anon_sym_action);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(anon_sym_create);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 77:
      ACCEPT_TOKEN(anon_sym_delete);
      END_STATE();
    case 78:
      ACCEPT_TOKEN(anon_sym_update);
      END_STATE();
    case 79:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(79);
      END_STATE();
    case 80:
      ACCEPT_TOKEN(sym_parameter_name);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(80);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 82:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 83:
      ACCEPT_TOKEN(anon_sym_DOT);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(86);
      END_STATE();
    case 84:
      ACCEPT_TOKEN(sym_user);
      END_STATE();
    case 85:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(56);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(55);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(85);
      END_STATE();
    case 86:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(55);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(86);
      END_STATE();
    case 87:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(87);
      END_STATE();
    case 88:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 89:
      ACCEPT_TOKEN(aux_sym_string_token1);
      END_STATE();
    case 90:
      ACCEPT_TOKEN(aux_sym_string_token1);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(90);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(91);
      END_STATE();
    case 91:
      ACCEPT_TOKEN(aux_sym_string_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(91);
      END_STATE();
    case 92:
      ACCEPT_TOKEN(anon_sym_SQUOTE);
      END_STATE();
    case 93:
      ACCEPT_TOKEN(aux_sym_string_token2);
      END_STATE();
    case 94:
      ACCEPT_TOKEN(aux_sym_string_token2);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(94);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(95);
      END_STATE();
    case 95:
      ACCEPT_TOKEN(aux_sym_string_token2);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(95);
      END_STATE();
    case 96:
      ACCEPT_TOKEN(sym_escape_sequence);
      END_STATE();
    case 97:
      ACCEPT_TOKEN(sym_escape_sequence);
      if (lookahead == '\n') ADVANCE(93);
      END_STATE();
    case 98:
      ACCEPT_TOKEN(sym_escape_sequence);
      if (lookahead == '\n') ADVANCE(89);
      END_STATE();
    case 99:
      ACCEPT_TOKEN(sym_escape_sequence);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(96);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(sym_escape_sequence);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(99);
      END_STATE();
    default:
      return false;
  }
}

static TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 0},
  [2] = {.lex_state = 5},
  [3] = {.lex_state = 5},
  [4] = {.lex_state = 5},
  [5] = {.lex_state = 0},
  [6] = {.lex_state = 0},
  [7] = {.lex_state = 0},
  [8] = {.lex_state = 0},
  [9] = {.lex_state = 0},
  [10] = {.lex_state = 0},
  [11] = {.lex_state = 0},
  [12] = {.lex_state = 0},
  [13] = {.lex_state = 0},
  [14] = {.lex_state = 5},
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
  [37] = {.lex_state = 5},
  [38] = {.lex_state = 1},
  [39] = {.lex_state = 1},
  [40] = {.lex_state = 5},
  [41] = {.lex_state = 3},
  [42] = {.lex_state = 5},
  [43] = {.lex_state = 0},
  [44] = {.lex_state = 3},
  [45] = {.lex_state = 3},
  [46] = {.lex_state = 0},
  [47] = {.lex_state = 1},
  [48] = {.lex_state = 0},
  [49] = {.lex_state = 0},
  [50] = {.lex_state = 0},
  [51] = {.lex_state = 0},
  [52] = {.lex_state = 5},
  [53] = {.lex_state = 0},
  [54] = {.lex_state = 0},
  [55] = {.lex_state = 0},
  [56] = {.lex_state = 0},
  [57] = {.lex_state = 0},
  [58] = {.lex_state = 5},
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
  [72] = {.lex_state = 5},
  [73] = {.lex_state = 0},
  [74] = {.lex_state = 0},
  [75] = {.lex_state = 0},
  [76] = {.lex_state = 0},
  [77] = {.lex_state = 0},
  [78] = {.lex_state = 5},
  [79] = {.lex_state = 0},
  [80] = {.lex_state = 0},
  [81] = {.lex_state = 5},
  [82] = {.lex_state = 0},
  [83] = {.lex_state = 5},
  [84] = {.lex_state = 0},
  [85] = {.lex_state = 5},
  [86] = {.lex_state = 0},
  [87] = {.lex_state = 5},
  [88] = {.lex_state = 0},
  [89] = {.lex_state = 0},
  [90] = {.lex_state = 0},
  [91] = {.lex_state = 0},
  [92] = {.lex_state = 5},
  [93] = {.lex_state = 0},
  [94] = {.lex_state = 0},
  [95] = {.lex_state = 0},
  [96] = {.lex_state = 5},
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
  [108] = {.lex_state = 5},
  [109] = {.lex_state = 0},
  [110] = {.lex_state = 0},
  [111] = {.lex_state = 5},
  [112] = {.lex_state = 0},
  [113] = {.lex_state = 0},
  [114] = {.lex_state = 0},
  [115] = {.lex_state = 0},
  [116] = {.lex_state = 5},
  [117] = {.lex_state = 0},
  [118] = {.lex_state = 0},
  [119] = {.lex_state = 0},
  [120] = {.lex_state = 5},
  [121] = {.lex_state = 0},
  [122] = {.lex_state = 0},
  [123] = {.lex_state = 5},
  [124] = {.lex_state = 0},
  [125] = {.lex_state = 0},
  [126] = {.lex_state = 5},
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
  [137] = {.lex_state = 5},
  [138] = {.lex_state = 0},
  [139] = {.lex_state = 0},
  [140] = {.lex_state = 5},
  [141] = {.lex_state = 5},
  [142] = {.lex_state = 5},
  [143] = {.lex_state = 0},
  [144] = {.lex_state = 5},
  [145] = {.lex_state = 0},
  [146] = {.lex_state = 5},
  [147] = {.lex_state = 5},
  [148] = {.lex_state = 5},
  [149] = {.lex_state = 5},
  [150] = {.lex_state = 0},
};

static uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
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
  [0] = 14,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(15), 1,
      anon_sym_COMMA,
    ACTIONS(17), 1,
      sym_identifier,
    ACTIONS(19), 1,
      sym_parameter_name,
    ACTIONS(21), 1,
      anon_sym_RPAREN,
    ACTIONS(23), 1,
      anon_sym_DOT,
    ACTIONS(25), 1,
      sym_user,
    ACTIONS(27), 1,
      sym_number,
    ACTIONS(29), 1,
      anon_sym_DQUOTE,
    ACTIONS(31), 1,
      anon_sym_SQUOTE,
    STATE(23), 1,
      aux_sym_uri_repeat1,
    STATE(55), 1,
      aux_sym_arguments_repeat1,
    STATE(13), 2,
      sym_parameter_reference,
      sym_type_reference,
    STATE(65), 6,
      sym__value,
      sym_variable,
      sym_uri,
      sym_query,
      sym_call,
      sym_string,
  [49] = 11,
    ACTIONS(17), 1,
      sym_identifier,
    ACTIONS(19), 1,
      sym_parameter_name,
    ACTIONS(23), 1,
      anon_sym_DOT,
    ACTIONS(25), 1,
      sym_user,
    ACTIONS(29), 1,
      anon_sym_DQUOTE,
    ACTIONS(31), 1,
      anon_sym_SQUOTE,
    ACTIONS(33), 1,
      anon_sym_LBRACE,
    ACTIONS(35), 1,
      sym_number,
    STATE(23), 1,
      aux_sym_uri_repeat1,
    STATE(13), 2,
      sym_parameter_reference,
      sym_type_reference,
    STATE(100), 8,
      sym_binding,
      sym__binding_value,
      sym__value,
      sym_variable,
      sym_uri,
      sym_query,
      sym_call,
      sym_string,
  [91] = 12,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(17), 1,
      sym_identifier,
    ACTIONS(19), 1,
      sym_parameter_name,
    ACTIONS(23), 1,
      anon_sym_DOT,
    ACTIONS(25), 1,
      sym_user,
    ACTIONS(29), 1,
      anon_sym_DQUOTE,
    ACTIONS(31), 1,
      anon_sym_SQUOTE,
    ACTIONS(39), 1,
      sym_number,
    STATE(23), 1,
      aux_sym_uri_repeat1,
    ACTIONS(37), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
    STATE(13), 2,
      sym_parameter_reference,
      sym_type_reference,
    STATE(88), 6,
      sym__value,
      sym_variable,
      sym_uri,
      sym_query,
      sym_call,
      sym_string,
  [135] = 6,
    ACTIONS(5), 1,
      anon_sym_type,
    ACTIONS(7), 1,
      anon_sym_permission,
    ACTIONS(9), 1,
      anon_sym_query,
    ACTIONS(11), 1,
      anon_sym_action,
    ACTIONS(41), 1,
      ts_builtin_sym_end,
    STATE(6), 6,
      sym__declaration,
      sym_type_declaration,
      sym_permission_declaration,
      sym_query_declaration,
      sym_action_declaration,
      aux_sym_source_file_repeat1,
  [159] = 6,
    ACTIONS(43), 1,
      ts_builtin_sym_end,
    ACTIONS(45), 1,
      anon_sym_type,
    ACTIONS(48), 1,
      anon_sym_permission,
    ACTIONS(51), 1,
      anon_sym_query,
    ACTIONS(54), 1,
      anon_sym_action,
    STATE(6), 6,
      sym__declaration,
      sym_type_declaration,
      sym_permission_declaration,
      sym_query_declaration,
      sym_action_declaration,
      aux_sym_source_file_repeat1,
  [183] = 6,
    ACTIONS(57), 1,
      anon_sym_RBRACE,
    ACTIONS(59), 1,
      anon_sym_create,
    ACTIONS(61), 1,
      anon_sym_delete,
    ACTIONS(63), 1,
      anon_sym_update,
    STATE(138), 1,
      sym_statements,
    STATE(12), 5,
      sym__statement,
      sym_create_statement,
      sym_delete_statement,
      sym_update_statement,
      aux_sym_statements_repeat1,
  [206] = 1,
    ACTIONS(65), 10,
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
  [219] = 6,
    ACTIONS(59), 1,
      anon_sym_create,
    ACTIONS(61), 1,
      anon_sym_delete,
    ACTIONS(63), 1,
      anon_sym_update,
    ACTIONS(67), 1,
      anon_sym_RBRACE,
    STATE(150), 1,
      sym_statements,
    STATE(12), 5,
      sym__statement,
      sym_create_statement,
      sym_delete_statement,
      sym_update_statement,
      aux_sym_statements_repeat1,
  [242] = 5,
    ACTIONS(69), 1,
      anon_sym_RBRACE,
    ACTIONS(71), 1,
      anon_sym_create,
    ACTIONS(74), 1,
      anon_sym_delete,
    ACTIONS(77), 1,
      anon_sym_update,
    STATE(10), 5,
      sym__statement,
      sym_create_statement,
      sym_delete_statement,
      sym_update_statement,
      aux_sym_statements_repeat1,
  [262] = 1,
    ACTIONS(80), 9,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_LBRACE,
      anon_sym_COMMA,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
      anon_sym_SEMI,
      anon_sym_RPAREN,
  [274] = 5,
    ACTIONS(59), 1,
      anon_sym_create,
    ACTIONS(61), 1,
      anon_sym_delete,
    ACTIONS(63), 1,
      anon_sym_update,
    ACTIONS(82), 1,
      anon_sym_RBRACE,
    STATE(10), 5,
      sym__statement,
      sym_create_statement,
      sym_delete_statement,
      sym_update_statement,
      aux_sym_statements_repeat1,
  [294] = 4,
    ACTIONS(86), 1,
      anon_sym_DOT,
    STATE(23), 1,
      aux_sym_uri_repeat1,
    STATE(74), 1,
      sym_uri,
    ACTIONS(84), 3,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [309] = 6,
    ACTIONS(88), 1,
      anon_sym_RBRACE,
    ACTIONS(90), 1,
      sym_identifier,
    STATE(60), 1,
      sym_call,
    STATE(63), 1,
      sym_binding_field,
    STATE(131), 1,
      sym_binding_fields,
    STATE(132), 1,
      sym__query_body,
  [328] = 1,
    ACTIONS(92), 6,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      anon_sym_DOT,
  [337] = 3,
    ACTIONS(96), 1,
      anon_sym_LPAREN,
    STATE(34), 1,
      sym_arguments,
    ACTIONS(94), 4,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_DOT,
  [350] = 5,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(98), 1,
      anon_sym_allow,
    STATE(33), 1,
      sym_query,
    STATE(122), 1,
      sym_guards_list,
    STATE(49), 2,
      sym_guard,
      aux_sym_guards_list_repeat1,
  [367] = 4,
    ACTIONS(98), 1,
      anon_sym_allow,
    ACTIONS(100), 1,
      anon_sym_LBRACE,
    STATE(124), 1,
      sym_guards_list,
    STATE(49), 2,
      sym_guard,
      aux_sym_guards_list_repeat1,
  [381] = 1,
    ACTIONS(102), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [389] = 1,
    ACTIONS(104), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [397] = 1,
    ACTIONS(106), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [405] = 1,
    ACTIONS(108), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [413] = 3,
    ACTIONS(86), 1,
      anon_sym_DOT,
    STATE(27), 1,
      aux_sym_uri_repeat1,
    ACTIONS(110), 3,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [425] = 1,
    ACTIONS(112), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [433] = 1,
    ACTIONS(114), 5,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_allow,
      anon_sym_RPAREN,
  [441] = 1,
    ACTIONS(116), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [449] = 3,
    ACTIONS(120), 1,
      anon_sym_DOT,
    STATE(27), 1,
      aux_sym_uri_repeat1,
    ACTIONS(118), 3,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [461] = 1,
    ACTIONS(123), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [469] = 1,
    ACTIONS(125), 5,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_allow,
      anon_sym_RPAREN,
  [477] = 1,
    ACTIONS(127), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [485] = 1,
    ACTIONS(129), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [493] = 1,
    ACTIONS(131), 5,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_allow,
      anon_sym_RPAREN,
  [501] = 1,
    ACTIONS(133), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [509] = 1,
    ACTIONS(135), 5,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_allow,
      anon_sym_RPAREN,
  [517] = 1,
    ACTIONS(137), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [525] = 1,
    ACTIONS(139), 4,
      anon_sym_RBRACE,
      anon_sym_create,
      anon_sym_delete,
      anon_sym_update,
  [532] = 4,
    ACTIONS(141), 1,
      anon_sym_RBRACE,
    ACTIONS(143), 1,
      sym_identifier,
    STATE(60), 1,
      sym_call,
    STATE(132), 1,
      sym__query_body,
  [545] = 4,
    ACTIONS(145), 1,
      anon_sym_SQUOTE,
    ACTIONS(147), 1,
      aux_sym_string_token2,
    ACTIONS(149), 1,
      sym_escape_sequence,
    STATE(39), 1,
      aux_sym_string_repeat2,
  [558] = 4,
    ACTIONS(151), 1,
      anon_sym_SQUOTE,
    ACTIONS(153), 1,
      aux_sym_string_token2,
    ACTIONS(156), 1,
      sym_escape_sequence,
    STATE(39), 1,
      aux_sym_string_repeat2,
  [571] = 4,
    ACTIONS(159), 1,
      anon_sym_RBRACE,
    ACTIONS(161), 1,
      sym_identifier,
    STATE(64), 1,
      sym_type_field,
    STATE(139), 1,
      sym_type_fields,
  [584] = 4,
    ACTIONS(145), 1,
      anon_sym_DQUOTE,
    ACTIONS(163), 1,
      aux_sym_string_token1,
    ACTIONS(165), 1,
      sym_escape_sequence,
    STATE(44), 1,
      aux_sym_string_repeat1,
  [597] = 4,
    ACTIONS(161), 1,
      sym_identifier,
    ACTIONS(167), 1,
      anon_sym_RBRACE,
    STATE(64), 1,
      sym_type_field,
    STATE(134), 1,
      sym_type_fields,
  [610] = 4,
    ACTIONS(169), 1,
      anon_sym_COMMA,
    ACTIONS(171), 1,
      sym_parameter_name,
    ACTIONS(173), 1,
      anon_sym_RPAREN,
    STATE(57), 1,
      sym_parameter,
  [623] = 4,
    ACTIONS(175), 1,
      anon_sym_DQUOTE,
    ACTIONS(177), 1,
      aux_sym_string_token1,
    ACTIONS(180), 1,
      sym_escape_sequence,
    STATE(44), 1,
      aux_sym_string_repeat1,
  [636] = 4,
    ACTIONS(183), 1,
      anon_sym_DQUOTE,
    ACTIONS(185), 1,
      aux_sym_string_token1,
    ACTIONS(187), 1,
      sym_escape_sequence,
    STATE(41), 1,
      aux_sym_string_repeat1,
  [649] = 1,
    ACTIONS(118), 4,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_DOT,
  [656] = 4,
    ACTIONS(183), 1,
      anon_sym_SQUOTE,
    ACTIONS(189), 1,
      aux_sym_string_token2,
    ACTIONS(191), 1,
      sym_escape_sequence,
    STATE(38), 1,
      aux_sym_string_repeat2,
  [669] = 1,
    ACTIONS(193), 4,
      anon_sym_RBRACE,
      anon_sym_create,
      anon_sym_delete,
      anon_sym_update,
  [676] = 3,
    ACTIONS(98), 1,
      anon_sym_allow,
    ACTIONS(195), 1,
      anon_sym_LBRACE,
    STATE(54), 2,
      sym_guard,
      aux_sym_guards_list_repeat1,
  [687] = 3,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(19), 1,
      sym_parameter_name,
    STATE(118), 2,
      sym_parameter_reference,
      sym_query,
  [698] = 1,
    ACTIONS(197), 4,
      anon_sym_RBRACE,
      anon_sym_create,
      anon_sym_delete,
      anon_sym_update,
  [705] = 4,
    ACTIONS(199), 1,
      anon_sym_RBRACE,
    ACTIONS(201), 1,
      sym_identifier,
    STATE(63), 1,
      sym_binding_field,
    STATE(131), 1,
      sym_binding_fields,
  [718] = 3,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    ACTIONS(19), 1,
      sym_parameter_name,
    STATE(145), 2,
      sym_parameter_reference,
      sym_query,
  [729] = 3,
    ACTIONS(203), 1,
      anon_sym_LBRACE,
    ACTIONS(205), 1,
      anon_sym_allow,
    STATE(54), 2,
      sym_guard,
      aux_sym_guards_list_repeat1,
  [740] = 3,
    ACTIONS(15), 1,
      anon_sym_COMMA,
    ACTIONS(208), 1,
      anon_sym_RPAREN,
    STATE(62), 1,
      aux_sym_arguments_repeat1,
  [750] = 1,
    ACTIONS(210), 3,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [756] = 3,
    ACTIONS(212), 1,
      anon_sym_COMMA,
    ACTIONS(214), 1,
      anon_sym_RPAREN,
    STATE(67), 1,
      aux_sym_parameters_list_repeat1,
  [766] = 3,
    ACTIONS(143), 1,
      sym_identifier,
    ACTIONS(216), 1,
      anon_sym_RBRACE,
    STATE(110), 1,
      sym_call,
  [776] = 3,
    ACTIONS(218), 1,
      anon_sym_LBRACE,
    ACTIONS(220), 1,
      anon_sym_COMMA,
    STATE(66), 1,
      aux_sym_bases_list_repeat1,
  [786] = 3,
    ACTIONS(222), 1,
      anon_sym_RBRACE,
    ACTIONS(224), 1,
      anon_sym_COMMA,
    STATE(82), 1,
      aux_sym__query_body_repeat1,
  [796] = 3,
    ACTIONS(15), 1,
      anon_sym_COMMA,
    ACTIONS(226), 1,
      anon_sym_RPAREN,
    STATE(62), 1,
      aux_sym_arguments_repeat1,
  [806] = 3,
    ACTIONS(228), 1,
      anon_sym_COMMA,
    ACTIONS(231), 1,
      anon_sym_RPAREN,
    STATE(62), 1,
      aux_sym_arguments_repeat1,
  [816] = 3,
    ACTIONS(233), 1,
      anon_sym_RBRACE,
    ACTIONS(235), 1,
      anon_sym_COMMA,
    STATE(84), 1,
      aux_sym_binding_fields_repeat1,
  [826] = 3,
    ACTIONS(237), 1,
      anon_sym_RBRACE,
    ACTIONS(239), 1,
      anon_sym_COMMA,
    STATE(75), 1,
      aux_sym_type_fields_repeat1,
  [836] = 3,
    ACTIONS(15), 1,
      anon_sym_COMMA,
    ACTIONS(208), 1,
      anon_sym_RPAREN,
    STATE(61), 1,
      aux_sym_arguments_repeat1,
  [846] = 3,
    ACTIONS(241), 1,
      anon_sym_LBRACE,
    ACTIONS(243), 1,
      anon_sym_COMMA,
    STATE(66), 1,
      aux_sym_bases_list_repeat1,
  [856] = 3,
    ACTIONS(246), 1,
      anon_sym_COMMA,
    ACTIONS(248), 1,
      anon_sym_RPAREN,
    STATE(77), 1,
      aux_sym_parameters_list_repeat1,
  [866] = 3,
    ACTIONS(171), 1,
      sym_parameter_name,
    ACTIONS(248), 1,
      anon_sym_RPAREN,
    STATE(91), 1,
      sym_parameter,
  [876] = 3,
    ACTIONS(96), 1,
      anon_sym_LPAREN,
    ACTIONS(250), 1,
      anon_sym_COLON,
    STATE(34), 1,
      sym_arguments,
  [886] = 3,
    ACTIONS(252), 1,
      anon_sym_RBRACE,
    ACTIONS(254), 1,
      anon_sym_COMMA,
    STATE(70), 1,
      aux_sym__query_body_repeat1,
  [896] = 3,
    ACTIONS(257), 1,
      anon_sym_LBRACE,
    ACTIONS(259), 1,
      anon_sym_COMMA,
    STATE(59), 1,
      aux_sym_bases_list_repeat1,
  [906] = 3,
    ACTIONS(161), 1,
      sym_identifier,
    ACTIONS(261), 1,
      anon_sym_RBRACE,
    STATE(104), 1,
      sym_type_field,
  [916] = 3,
    ACTIONS(263), 1,
      anon_sym_RBRACE,
    ACTIONS(265), 1,
      anon_sym_COMMA,
    STATE(73), 1,
      aux_sym_type_fields_repeat1,
  [926] = 1,
    ACTIONS(268), 3,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [932] = 3,
    ACTIONS(270), 1,
      anon_sym_RBRACE,
    ACTIONS(272), 1,
      anon_sym_COMMA,
    STATE(73), 1,
      aux_sym_type_fields_repeat1,
  [942] = 3,
    ACTIONS(171), 1,
      sym_parameter_name,
    ACTIONS(274), 1,
      anon_sym_RPAREN,
    STATE(91), 1,
      sym_parameter,
  [952] = 3,
    ACTIONS(276), 1,
      anon_sym_COMMA,
    ACTIONS(279), 1,
      anon_sym_RPAREN,
    STATE(77), 1,
      aux_sym_parameters_list_repeat1,
  [962] = 3,
    ACTIONS(161), 1,
      sym_identifier,
    ACTIONS(270), 1,
      anon_sym_RBRACE,
    STATE(104), 1,
      sym_type_field,
  [972] = 1,
    ACTIONS(281), 3,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [978] = 1,
    ACTIONS(283), 3,
      anon_sym_RBRACE,
      anon_sym_COMMA,
      anon_sym_SEMI,
  [984] = 3,
    ACTIONS(143), 1,
      sym_identifier,
    ACTIONS(285), 1,
      anon_sym_RBRACE,
    STATE(110), 1,
      sym_call,
  [994] = 3,
    ACTIONS(285), 1,
      anon_sym_RBRACE,
    ACTIONS(287), 1,
      anon_sym_COMMA,
    STATE(70), 1,
      aux_sym__query_body_repeat1,
  [1004] = 3,
    ACTIONS(201), 1,
      sym_identifier,
    ACTIONS(289), 1,
      anon_sym_RBRACE,
    STATE(94), 1,
      sym_binding_field,
  [1014] = 3,
    ACTIONS(289), 1,
      anon_sym_RBRACE,
    ACTIONS(291), 1,
      anon_sym_COMMA,
    STATE(86), 1,
      aux_sym_binding_fields_repeat1,
  [1024] = 3,
    ACTIONS(201), 1,
      sym_identifier,
    ACTIONS(293), 1,
      anon_sym_RBRACE,
    STATE(94), 1,
      sym_binding_field,
  [1034] = 3,
    ACTIONS(295), 1,
      anon_sym_RBRACE,
    ACTIONS(297), 1,
      anon_sym_COMMA,
    STATE(86), 1,
      aux_sym_binding_fields_repeat1,
  [1044] = 2,
    ACTIONS(218), 1,
      anon_sym_LBRACE,
    ACTIONS(300), 1,
      sym_identifier,
  [1051] = 1,
    ACTIONS(231), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [1056] = 1,
    ACTIONS(302), 2,
      anon_sym_LBRACE,
      anon_sym_allow,
  [1061] = 2,
    ACTIONS(304), 1,
      anon_sym_LBRACE,
    STATE(135), 1,
      sym_binding,
  [1068] = 1,
    ACTIONS(279), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [1073] = 2,
    ACTIONS(201), 1,
      sym_identifier,
    STATE(94), 1,
      sym_binding_field,
  [1080] = 1,
    ACTIONS(306), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [1085] = 1,
    ACTIONS(295), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [1090] = 1,
    ACTIONS(308), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [1095] = 2,
    ACTIONS(161), 1,
      sym_identifier,
    STATE(104), 1,
      sym_type_field,
  [1102] = 1,
    ACTIONS(310), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [1107] = 1,
    ACTIONS(312), 2,
      anon_sym_LBRACE,
      anon_sym_allow,
  [1112] = 2,
    ACTIONS(171), 1,
      sym_parameter_name,
    STATE(91), 1,
      sym_parameter,
  [1119] = 1,
    ACTIONS(314), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [1124] = 2,
    ACTIONS(316), 1,
      anon_sym_COLON,
    ACTIONS(318), 1,
      anon_sym_LBRACE,
  [1131] = 1,
    ACTIONS(320), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [1136] = 2,
    ACTIONS(322), 1,
      anon_sym_LPAREN,
    STATE(112), 1,
      sym_parameters_list,
  [1143] = 1,
    ACTIONS(263), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [1148] = 2,
    ACTIONS(322), 1,
      anon_sym_LPAREN,
    STATE(17), 1,
      sym_parameters_list,
  [1155] = 1,
    ACTIONS(324), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [1160] = 2,
    ACTIONS(322), 1,
      anon_sym_LPAREN,
    STATE(18), 1,
      sym_parameters_list,
  [1167] = 2,
    ACTIONS(300), 1,
      sym_identifier,
    ACTIONS(326), 1,
      anon_sym_LBRACE,
  [1174] = 1,
    ACTIONS(241), 2,
      anon_sym_LBRACE,
      anon_sym_COMMA,
  [1179] = 1,
    ACTIONS(252), 2,
      anon_sym_RBRACE,
      anon_sym_COMMA,
  [1184] = 2,
    ACTIONS(328), 1,
      sym_identifier,
    STATE(136), 1,
      sym_bases_list,
  [1191] = 2,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    STATE(30), 1,
      sym_query,
  [1198] = 1,
    ACTIONS(330), 2,
      anon_sym_LBRACE,
      anon_sym_allow,
  [1203] = 2,
    ACTIONS(332), 1,
      anon_sym_COLON,
    ACTIONS(334), 1,
      anon_sym_QMARK,
  [1210] = 2,
    ACTIONS(336), 1,
      anon_sym_COLON,
    ACTIONS(338), 1,
      anon_sym_QMARK,
  [1217] = 2,
    ACTIONS(143), 1,
      sym_identifier,
    STATE(110), 1,
      sym_call,
  [1224] = 2,
    ACTIONS(96), 1,
      anon_sym_LPAREN,
    STATE(34), 1,
      sym_arguments,
  [1231] = 2,
    ACTIONS(304), 1,
      anon_sym_LBRACE,
    STATE(128), 1,
      sym_binding,
  [1238] = 1,
    ACTIONS(340), 2,
      anon_sym_LBRACE,
      anon_sym_allow,
  [1243] = 2,
    ACTIONS(143), 1,
      sym_identifier,
    STATE(113), 1,
      sym_call,
  [1250] = 1,
    ACTIONS(342), 2,
      anon_sym_LBRACE,
      anon_sym_allow,
  [1255] = 2,
    ACTIONS(13), 1,
      anon_sym_LBRACE,
    STATE(28), 1,
      sym_query,
  [1262] = 1,
    ACTIONS(344), 1,
      sym_identifier,
  [1266] = 1,
    ACTIONS(346), 1,
      anon_sym_LBRACE,
  [1270] = 1,
    ACTIONS(348), 1,
      anon_sym_COLON,
  [1274] = 1,
    ACTIONS(350), 1,
      sym_identifier,
  [1278] = 1,
    ACTIONS(352), 1,
      anon_sym_COLON,
  [1282] = 1,
    ACTIONS(354), 1,
      anon_sym_SEMI,
  [1286] = 1,
    ACTIONS(306), 1,
      anon_sym_SEMI,
  [1290] = 1,
    ACTIONS(250), 1,
      anon_sym_COLON,
  [1294] = 1,
    ACTIONS(356), 1,
      anon_sym_RBRACE,
  [1298] = 1,
    ACTIONS(358), 1,
      anon_sym_RBRACE,
  [1302] = 1,
    ACTIONS(214), 1,
      anon_sym_RPAREN,
  [1306] = 1,
    ACTIONS(360), 1,
      anon_sym_RBRACE,
  [1310] = 1,
    ACTIONS(362), 1,
      anon_sym_SEMI,
  [1314] = 1,
    ACTIONS(364), 1,
      anon_sym_LBRACE,
  [1318] = 1,
    ACTIONS(366), 1,
      sym_identifier,
  [1322] = 1,
    ACTIONS(368), 1,
      anon_sym_RBRACE,
  [1326] = 1,
    ACTIONS(370), 1,
      anon_sym_RBRACE,
  [1330] = 1,
    ACTIONS(372), 1,
      sym_identifier,
  [1334] = 1,
    ACTIONS(374), 1,
      sym_identifier,
  [1338] = 1,
    ACTIONS(376), 1,
      sym_identifier,
  [1342] = 1,
    ACTIONS(378), 1,
      ts_builtin_sym_end,
  [1346] = 1,
    ACTIONS(380), 1,
      sym_identifier,
  [1350] = 1,
    ACTIONS(382), 1,
      anon_sym_SEMI,
  [1354] = 1,
    ACTIONS(384), 1,
      sym_identifier,
  [1358] = 1,
    ACTIONS(386), 1,
      sym_identifier,
  [1362] = 1,
    ACTIONS(300), 1,
      sym_identifier,
  [1366] = 1,
    ACTIONS(388), 1,
      sym_identifier,
  [1370] = 1,
    ACTIONS(390), 1,
      anon_sym_RBRACE,
};

static uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 49,
  [SMALL_STATE(4)] = 91,
  [SMALL_STATE(5)] = 135,
  [SMALL_STATE(6)] = 159,
  [SMALL_STATE(7)] = 183,
  [SMALL_STATE(8)] = 206,
  [SMALL_STATE(9)] = 219,
  [SMALL_STATE(10)] = 242,
  [SMALL_STATE(11)] = 262,
  [SMALL_STATE(12)] = 274,
  [SMALL_STATE(13)] = 294,
  [SMALL_STATE(14)] = 309,
  [SMALL_STATE(15)] = 328,
  [SMALL_STATE(16)] = 337,
  [SMALL_STATE(17)] = 350,
  [SMALL_STATE(18)] = 367,
  [SMALL_STATE(19)] = 381,
  [SMALL_STATE(20)] = 389,
  [SMALL_STATE(21)] = 397,
  [SMALL_STATE(22)] = 405,
  [SMALL_STATE(23)] = 413,
  [SMALL_STATE(24)] = 425,
  [SMALL_STATE(25)] = 433,
  [SMALL_STATE(26)] = 441,
  [SMALL_STATE(27)] = 449,
  [SMALL_STATE(28)] = 461,
  [SMALL_STATE(29)] = 469,
  [SMALL_STATE(30)] = 477,
  [SMALL_STATE(31)] = 485,
  [SMALL_STATE(32)] = 493,
  [SMALL_STATE(33)] = 501,
  [SMALL_STATE(34)] = 509,
  [SMALL_STATE(35)] = 517,
  [SMALL_STATE(36)] = 525,
  [SMALL_STATE(37)] = 532,
  [SMALL_STATE(38)] = 545,
  [SMALL_STATE(39)] = 558,
  [SMALL_STATE(40)] = 571,
  [SMALL_STATE(41)] = 584,
  [SMALL_STATE(42)] = 597,
  [SMALL_STATE(43)] = 610,
  [SMALL_STATE(44)] = 623,
  [SMALL_STATE(45)] = 636,
  [SMALL_STATE(46)] = 649,
  [SMALL_STATE(47)] = 656,
  [SMALL_STATE(48)] = 669,
  [SMALL_STATE(49)] = 676,
  [SMALL_STATE(50)] = 687,
  [SMALL_STATE(51)] = 698,
  [SMALL_STATE(52)] = 705,
  [SMALL_STATE(53)] = 718,
  [SMALL_STATE(54)] = 729,
  [SMALL_STATE(55)] = 740,
  [SMALL_STATE(56)] = 750,
  [SMALL_STATE(57)] = 756,
  [SMALL_STATE(58)] = 766,
  [SMALL_STATE(59)] = 776,
  [SMALL_STATE(60)] = 786,
  [SMALL_STATE(61)] = 796,
  [SMALL_STATE(62)] = 806,
  [SMALL_STATE(63)] = 816,
  [SMALL_STATE(64)] = 826,
  [SMALL_STATE(65)] = 836,
  [SMALL_STATE(66)] = 846,
  [SMALL_STATE(67)] = 856,
  [SMALL_STATE(68)] = 866,
  [SMALL_STATE(69)] = 876,
  [SMALL_STATE(70)] = 886,
  [SMALL_STATE(71)] = 896,
  [SMALL_STATE(72)] = 906,
  [SMALL_STATE(73)] = 916,
  [SMALL_STATE(74)] = 926,
  [SMALL_STATE(75)] = 932,
  [SMALL_STATE(76)] = 942,
  [SMALL_STATE(77)] = 952,
  [SMALL_STATE(78)] = 962,
  [SMALL_STATE(79)] = 972,
  [SMALL_STATE(80)] = 978,
  [SMALL_STATE(81)] = 984,
  [SMALL_STATE(82)] = 994,
  [SMALL_STATE(83)] = 1004,
  [SMALL_STATE(84)] = 1014,
  [SMALL_STATE(85)] = 1024,
  [SMALL_STATE(86)] = 1034,
  [SMALL_STATE(87)] = 1044,
  [SMALL_STATE(88)] = 1051,
  [SMALL_STATE(89)] = 1056,
  [SMALL_STATE(90)] = 1061,
  [SMALL_STATE(91)] = 1068,
  [SMALL_STATE(92)] = 1073,
  [SMALL_STATE(93)] = 1080,
  [SMALL_STATE(94)] = 1085,
  [SMALL_STATE(95)] = 1090,
  [SMALL_STATE(96)] = 1095,
  [SMALL_STATE(97)] = 1102,
  [SMALL_STATE(98)] = 1107,
  [SMALL_STATE(99)] = 1112,
  [SMALL_STATE(100)] = 1119,
  [SMALL_STATE(101)] = 1124,
  [SMALL_STATE(102)] = 1131,
  [SMALL_STATE(103)] = 1136,
  [SMALL_STATE(104)] = 1143,
  [SMALL_STATE(105)] = 1148,
  [SMALL_STATE(106)] = 1155,
  [SMALL_STATE(107)] = 1160,
  [SMALL_STATE(108)] = 1167,
  [SMALL_STATE(109)] = 1174,
  [SMALL_STATE(110)] = 1179,
  [SMALL_STATE(111)] = 1184,
  [SMALL_STATE(112)] = 1191,
  [SMALL_STATE(113)] = 1198,
  [SMALL_STATE(114)] = 1203,
  [SMALL_STATE(115)] = 1210,
  [SMALL_STATE(116)] = 1217,
  [SMALL_STATE(117)] = 1224,
  [SMALL_STATE(118)] = 1231,
  [SMALL_STATE(119)] = 1238,
  [SMALL_STATE(120)] = 1243,
  [SMALL_STATE(121)] = 1250,
  [SMALL_STATE(122)] = 1255,
  [SMALL_STATE(123)] = 1262,
  [SMALL_STATE(124)] = 1266,
  [SMALL_STATE(125)] = 1270,
  [SMALL_STATE(126)] = 1274,
  [SMALL_STATE(127)] = 1278,
  [SMALL_STATE(128)] = 1282,
  [SMALL_STATE(129)] = 1286,
  [SMALL_STATE(130)] = 1290,
  [SMALL_STATE(131)] = 1294,
  [SMALL_STATE(132)] = 1298,
  [SMALL_STATE(133)] = 1302,
  [SMALL_STATE(134)] = 1306,
  [SMALL_STATE(135)] = 1310,
  [SMALL_STATE(136)] = 1314,
  [SMALL_STATE(137)] = 1318,
  [SMALL_STATE(138)] = 1322,
  [SMALL_STATE(139)] = 1326,
  [SMALL_STATE(140)] = 1330,
  [SMALL_STATE(141)] = 1334,
  [SMALL_STATE(142)] = 1338,
  [SMALL_STATE(143)] = 1342,
  [SMALL_STATE(144)] = 1346,
  [SMALL_STATE(145)] = 1350,
  [SMALL_STATE(146)] = 1354,
  [SMALL_STATE(147)] = 1358,
  [SMALL_STATE(148)] = 1362,
  [SMALL_STATE(149)] = 1366,
  [SMALL_STATE(150)] = 1370,
};

static TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(144),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(149),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(147),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(146),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [23] = {.entry = {.count = 1, .reusable = false}}, SHIFT(141),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [27] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [29] = {.entry = {.count = 1, .reusable = true}}, SHIFT(45),
  [31] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [33] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [35] = {.entry = {.count = 1, .reusable = true}}, SHIFT(100),
  [37] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_arguments_repeat1, 1),
  [39] = {.entry = {.count = 1, .reusable = true}}, SHIFT(88),
  [41] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1),
  [43] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2),
  [45] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(144),
  [48] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(149),
  [51] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(147),
  [54] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(146),
  [57] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [59] = {.entry = {.count = 1, .reusable = true}}, SHIFT(137),
  [61] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [63] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [65] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query, 3),
  [67] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [69] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_statements_repeat1, 2),
  [71] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_statements_repeat1, 2), SHIFT_REPEAT(137),
  [74] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_statements_repeat1, 2), SHIFT_REPEAT(53),
  [77] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_statements_repeat1, 2), SHIFT_REPEAT(50),
  [80] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query, 2),
  [82] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_statements, 1),
  [84] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_variable, 1, .production_id = 14),
  [86] = {.entry = {.count = 1, .reusable = true}}, SHIFT(141),
  [88] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [90] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [92] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameter_reference, 1),
  [94] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_reference, 1),
  [96] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [98] = {.entry = {.count = 1, .reusable = true}}, SHIFT(120),
  [100] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [102] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_action_declaration, 6, .production_id = 11),
  [104] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 6, .production_id = 7),
  [106] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 4, .production_id = 1),
  [108] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 7, .production_id = 12),
  [110] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_uri, 1),
  [112] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 5, .production_id = 3),
  [114] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_arguments, 2),
  [116] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_action_declaration, 5, .production_id = 6),
  [118] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_uri_repeat1, 2),
  [120] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_uri_repeat1, 2), SHIFT_REPEAT(141),
  [123] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query_declaration, 5, .production_id = 5),
  [125] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_arguments, 4),
  [127] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_permission_declaration, 4, .production_id = 2),
  [129] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_action_declaration, 7, .production_id = 16),
  [131] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_arguments, 3),
  [133] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query_declaration, 4, .production_id = 2),
  [135] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call, 2, .production_id = 9),
  [137] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_action_declaration, 6, .production_id = 10),
  [139] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_update_statement, 4, .production_id = 19),
  [141] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [143] = {.entry = {.count = 1, .reusable = true}}, SHIFT(117),
  [145] = {.entry = {.count = 1, .reusable = false}}, SHIFT(56),
  [147] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [149] = {.entry = {.count = 1, .reusable = false}}, SHIFT(39),
  [151] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_string_repeat2, 2),
  [153] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_string_repeat2, 2), SHIFT_REPEAT(39),
  [156] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_string_repeat2, 2), SHIFT_REPEAT(39),
  [159] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [161] = {.entry = {.count = 1, .reusable = true}}, SHIFT(114),
  [163] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [165] = {.entry = {.count = 1, .reusable = false}}, SHIFT(44),
  [167] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [169] = {.entry = {.count = 1, .reusable = true}}, SHIFT(133),
  [171] = {.entry = {.count = 1, .reusable = true}}, SHIFT(115),
  [173] = {.entry = {.count = 1, .reusable = true}}, SHIFT(119),
  [175] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_string_repeat1, 2),
  [177] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_string_repeat1, 2), SHIFT_REPEAT(44),
  [180] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_string_repeat1, 2), SHIFT_REPEAT(44),
  [183] = {.entry = {.count = 1, .reusable = false}}, SHIFT(79),
  [185] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [187] = {.entry = {.count = 1, .reusable = false}}, SHIFT(41),
  [189] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [191] = {.entry = {.count = 1, .reusable = false}}, SHIFT(38),
  [193] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_statement, 4, .production_id = 18),
  [195] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_guards_list, 1),
  [197] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_delete_statement, 3, .production_id = 15),
  [199] = {.entry = {.count = 1, .reusable = true}}, SHIFT(129),
  [201] = {.entry = {.count = 1, .reusable = true}}, SHIFT(130),
  [203] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_guards_list_repeat1, 2),
  [205] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_guards_list_repeat1, 2), SHIFT_REPEAT(120),
  [208] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [210] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 3),
  [212] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [214] = {.entry = {.count = 1, .reusable = true}}, SHIFT(121),
  [216] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__query_body, 3),
  [218] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bases_list, 2),
  [220] = {.entry = {.count = 1, .reusable = true}}, SHIFT(108),
  [222] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__query_body, 1),
  [224] = {.entry = {.count = 1, .reusable = true}}, SHIFT(81),
  [226] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [228] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_arguments_repeat1, 2), SHIFT_REPEAT(4),
  [231] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_arguments_repeat1, 2),
  [233] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding_fields, 1),
  [235] = {.entry = {.count = 1, .reusable = true}}, SHIFT(83),
  [237] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_fields, 1),
  [239] = {.entry = {.count = 1, .reusable = true}}, SHIFT(78),
  [241] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_bases_list_repeat1, 2),
  [243] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_bases_list_repeat1, 2), SHIFT_REPEAT(148),
  [246] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [248] = {.entry = {.count = 1, .reusable = true}}, SHIFT(89),
  [250] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [252] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2),
  [254] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__query_body_repeat1, 2), SHIFT_REPEAT(116),
  [257] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bases_list, 1),
  [259] = {.entry = {.count = 1, .reusable = true}}, SHIFT(87),
  [261] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_fields, 3),
  [263] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_type_fields_repeat1, 2),
  [265] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_type_fields_repeat1, 2), SHIFT_REPEAT(96),
  [268] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_variable, 2, .production_id = 17),
  [270] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_fields, 2),
  [272] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [274] = {.entry = {.count = 1, .reusable = true}}, SHIFT(98),
  [276] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_parameters_list_repeat1, 2), SHIFT_REPEAT(99),
  [279] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_parameters_list_repeat1, 2),
  [281] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 2),
  [283] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding, 3, .production_id = 20),
  [285] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__query_body, 2),
  [287] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [289] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding_fields, 2),
  [291] = {.entry = {.count = 1, .reusable = true}}, SHIFT(85),
  [293] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding_fields, 3),
  [295] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_binding_fields_repeat1, 2),
  [297] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_binding_fields_repeat1, 2), SHIFT_REPEAT(92),
  [300] = {.entry = {.count = 1, .reusable = true}}, SHIFT(109),
  [302] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameters_list, 4),
  [304] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [306] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding, 2),
  [308] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_field, 4, .production_id = 13),
  [310] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameter, 4),
  [312] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameters_list, 5),
  [314] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding_field, 3, .production_id = 21),
  [316] = {.entry = {.count = 1, .reusable = true}}, SHIFT(111),
  [318] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [320] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameter, 3),
  [322] = {.entry = {.count = 1, .reusable = true}}, SHIFT(43),
  [324] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_field, 3, .production_id = 8),
  [326] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bases_list, 3),
  [328] = {.entry = {.count = 1, .reusable = true}}, SHIFT(71),
  [330] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_guard, 2, .production_id = 4),
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
    .external_token_count = EXTERNAL_TOKEN_COUNT,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
