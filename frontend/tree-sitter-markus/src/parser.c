#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 11
#define STATE_COUNT 182
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 68
#define ALIAS_COUNT 0
#define TOKEN_COUNT 31
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 19
#define MAX_ALIAS_SEQUENCE_LENGTH 11

enum {
  sym_identifier = 1,
  sym_comment = 2,
  anon_sym_type = 3,
  anon_sym_COLON = 4,
  anon_sym_COMMA = 5,
  anon_sym_LBRACE = 6,
  anon_sym_RBRACE = 7,
  sym_parameter_name = 8,
  sym_optional_flag = 9,
  anon_sym_LPAREN = 10,
  anon_sym_RPAREN = 11,
  sym_user = 12,
  anon_sym_DOT = 13,
  sym_true_literal = 14,
  sym_false_literal = 15,
  sym_numeric_literal = 16,
  anon_sym_DQUOTE = 17,
  aux_sym_string_literal_token1 = 18,
  anon_sym_SQUOTE = 19,
  aux_sym_string_literal_token2 = 20,
  sym_escape_sequence = 21,
  anon_sym_permission = 22,
  anon_sym_query = 23,
  anon_sym_allow = 24,
  anon_sym_EQ = 25,
  anon_sym_create = 26,
  anon_sym_SEMI = 27,
  anon_sym_delete = 28,
  anon_sym_update = 29,
  anon_sym_action = 30,
  sym_source_file = 31,
  sym__declaration = 32,
  sym_type_declaration = 33,
  sym_type_field = 34,
  sym__expression = 35,
  sym__primitive_expression = 36,
  sym_call = 37,
  sym_variable = 38,
  sym_uri = 39,
  sym_string_literal = 40,
  sym_query = 41,
  sym__parameters = 42,
  sym_parameter = 43,
  sym_permission_declaration = 44,
  sym_query_declaration = 45,
  sym_guard = 46,
  sym_binding = 47,
  sym_binding_field = 48,
  sym__binding_value = 49,
  sym__statement = 50,
  sym_create_statement = 51,
  sym_delete_statement = 52,
  sym_update_statement = 53,
  sym__statement_target = 54,
  sym_action_declaration = 55,
  aux_sym_source_file_repeat1 = 56,
  aux_sym_type_declaration_repeat1 = 57,
  aux_sym_type_declaration_repeat2 = 58,
  aux_sym_call_repeat1 = 59,
  aux_sym_uri_repeat1 = 60,
  aux_sym_string_literal_repeat1 = 61,
  aux_sym_string_literal_repeat2 = 62,
  aux_sym_query_repeat1 = 63,
  aux_sym__parameters_repeat1 = 64,
  aux_sym_query_declaration_repeat1 = 65,
  aux_sym_binding_repeat1 = 66,
  aux_sym_action_declaration_repeat1 = 67,
};

static const char *ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_identifier] = "identifier",
  [sym_comment] = "comment",
  [anon_sym_type] = "type",
  [anon_sym_COLON] = ":",
  [anon_sym_COMMA] = ",",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
  [sym_parameter_name] = "parameter_name",
  [sym_optional_flag] = "optional_flag",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [sym_user] = "user",
  [anon_sym_DOT] = ".",
  [sym_true_literal] = "true_literal",
  [sym_false_literal] = "false_literal",
  [sym_numeric_literal] = "numeric_literal",
  [anon_sym_DQUOTE] = "\"",
  [aux_sym_string_literal_token1] = "string_literal_token1",
  [anon_sym_SQUOTE] = "'",
  [aux_sym_string_literal_token2] = "string_literal_token2",
  [sym_escape_sequence] = "escape_sequence",
  [anon_sym_permission] = "permission",
  [anon_sym_query] = "query",
  [anon_sym_allow] = "allow",
  [anon_sym_EQ] = "=",
  [anon_sym_create] = "create",
  [anon_sym_SEMI] = ";",
  [anon_sym_delete] = "delete",
  [anon_sym_update] = "update",
  [anon_sym_action] = "action",
  [sym_source_file] = "source_file",
  [sym__declaration] = "_declaration",
  [sym_type_declaration] = "type_declaration",
  [sym_type_field] = "type_field",
  [sym__expression] = "_expression",
  [sym__primitive_expression] = "_primitive_expression",
  [sym_call] = "call",
  [sym_variable] = "variable",
  [sym_uri] = "uri",
  [sym_string_literal] = "string_literal",
  [sym_query] = "query",
  [sym__parameters] = "_parameters",
  [sym_parameter] = "parameter",
  [sym_permission_declaration] = "permission_declaration",
  [sym_query_declaration] = "query_declaration",
  [sym_guard] = "guard",
  [sym_binding] = "binding",
  [sym_binding_field] = "binding_field",
  [sym__binding_value] = "_binding_value",
  [sym__statement] = "_statement",
  [sym_create_statement] = "create_statement",
  [sym_delete_statement] = "delete_statement",
  [sym_update_statement] = "update_statement",
  [sym__statement_target] = "_statement_target",
  [sym_action_declaration] = "action_declaration",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
  [aux_sym_type_declaration_repeat1] = "type_declaration_repeat1",
  [aux_sym_type_declaration_repeat2] = "type_declaration_repeat2",
  [aux_sym_call_repeat1] = "call_repeat1",
  [aux_sym_uri_repeat1] = "uri_repeat1",
  [aux_sym_string_literal_repeat1] = "string_literal_repeat1",
  [aux_sym_string_literal_repeat2] = "string_literal_repeat2",
  [aux_sym_query_repeat1] = "query_repeat1",
  [aux_sym__parameters_repeat1] = "_parameters_repeat1",
  [aux_sym_query_declaration_repeat1] = "query_declaration_repeat1",
  [aux_sym_binding_repeat1] = "binding_repeat1",
  [aux_sym_action_declaration_repeat1] = "action_declaration_repeat1",
};

static TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_identifier] = sym_identifier,
  [sym_comment] = sym_comment,
  [anon_sym_type] = anon_sym_type,
  [anon_sym_COLON] = anon_sym_COLON,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [sym_parameter_name] = sym_parameter_name,
  [sym_optional_flag] = sym_optional_flag,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [sym_user] = sym_user,
  [anon_sym_DOT] = anon_sym_DOT,
  [sym_true_literal] = sym_true_literal,
  [sym_false_literal] = sym_false_literal,
  [sym_numeric_literal] = sym_numeric_literal,
  [anon_sym_DQUOTE] = anon_sym_DQUOTE,
  [aux_sym_string_literal_token1] = aux_sym_string_literal_token1,
  [anon_sym_SQUOTE] = anon_sym_SQUOTE,
  [aux_sym_string_literal_token2] = aux_sym_string_literal_token2,
  [sym_escape_sequence] = sym_escape_sequence,
  [anon_sym_permission] = anon_sym_permission,
  [anon_sym_query] = anon_sym_query,
  [anon_sym_allow] = anon_sym_allow,
  [anon_sym_EQ] = anon_sym_EQ,
  [anon_sym_create] = anon_sym_create,
  [anon_sym_SEMI] = anon_sym_SEMI,
  [anon_sym_delete] = anon_sym_delete,
  [anon_sym_update] = anon_sym_update,
  [anon_sym_action] = anon_sym_action,
  [sym_source_file] = sym_source_file,
  [sym__declaration] = sym__declaration,
  [sym_type_declaration] = sym_type_declaration,
  [sym_type_field] = sym_type_field,
  [sym__expression] = sym__expression,
  [sym__primitive_expression] = sym__primitive_expression,
  [sym_call] = sym_call,
  [sym_variable] = sym_variable,
  [sym_uri] = sym_uri,
  [sym_string_literal] = sym_string_literal,
  [sym_query] = sym_query,
  [sym__parameters] = sym__parameters,
  [sym_parameter] = sym_parameter,
  [sym_permission_declaration] = sym_permission_declaration,
  [sym_query_declaration] = sym_query_declaration,
  [sym_guard] = sym_guard,
  [sym_binding] = sym_binding,
  [sym_binding_field] = sym_binding_field,
  [sym__binding_value] = sym__binding_value,
  [sym__statement] = sym__statement,
  [sym_create_statement] = sym_create_statement,
  [sym_delete_statement] = sym_delete_statement,
  [sym_update_statement] = sym_update_statement,
  [sym__statement_target] = sym__statement_target,
  [sym_action_declaration] = sym_action_declaration,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
  [aux_sym_type_declaration_repeat1] = aux_sym_type_declaration_repeat1,
  [aux_sym_type_declaration_repeat2] = aux_sym_type_declaration_repeat2,
  [aux_sym_call_repeat1] = aux_sym_call_repeat1,
  [aux_sym_uri_repeat1] = aux_sym_uri_repeat1,
  [aux_sym_string_literal_repeat1] = aux_sym_string_literal_repeat1,
  [aux_sym_string_literal_repeat2] = aux_sym_string_literal_repeat2,
  [aux_sym_query_repeat1] = aux_sym_query_repeat1,
  [aux_sym__parameters_repeat1] = aux_sym__parameters_repeat1,
  [aux_sym_query_declaration_repeat1] = aux_sym_query_declaration_repeat1,
  [aux_sym_binding_repeat1] = aux_sym_binding_repeat1,
  [aux_sym_action_declaration_repeat1] = aux_sym_action_declaration_repeat1,
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
  [sym_comment] = {
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
  [anon_sym_COMMA] = {
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
  [sym_parameter_name] = {
    .visible = true,
    .named = true,
  },
  [sym_optional_flag] = {
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
  [sym_user] = {
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
  [sym_numeric_literal] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_DQUOTE] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_string_literal_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_SQUOTE] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_string_literal_token2] = {
    .visible = false,
    .named = false,
  },
  [sym_escape_sequence] = {
    .visible = true,
    .named = true,
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
  [anon_sym_EQ] = {
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
  [anon_sym_action] = {
    .visible = true,
    .named = false,
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
  [sym_type_field] = {
    .visible = true,
    .named = true,
  },
  [sym__expression] = {
    .visible = false,
    .named = true,
  },
  [sym__primitive_expression] = {
    .visible = false,
    .named = true,
  },
  [sym_call] = {
    .visible = true,
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
  [sym_string_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_query] = {
    .visible = true,
    .named = true,
  },
  [sym__parameters] = {
    .visible = false,
    .named = true,
  },
  [sym_parameter] = {
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
  [sym_guard] = {
    .visible = true,
    .named = true,
  },
  [sym_binding] = {
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
  [sym__statement_target] = {
    .visible = false,
    .named = true,
  },
  [sym_action_declaration] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_type_declaration_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_type_declaration_repeat2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_call_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_uri_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_string_literal_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_string_literal_repeat2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_query_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__parameters_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_query_declaration_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_binding_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_action_declaration_repeat1] = {
    .visible = false,
    .named = false,
  },
};

enum {
  field_argument = 1,
  field_base = 2,
  field_binding = 3,
  field_callee = 4,
  field_field = 5,
  field_field_type = 6,
  field_guard = 7,
  field_name = 8,
  field_optional = 9,
  field_parameter = 10,
  field_part = 11,
  field_pipe = 12,
  field_query = 13,
  field_selection = 14,
  field_statement = 15,
  field_target = 16,
  field_type = 17,
  field_updates = 18,
  field_value = 19,
};

static const char *ts_field_names[] = {
  [0] = NULL,
  [field_argument] = "argument",
  [field_base] = "base",
  [field_binding] = "binding",
  [field_callee] = "callee",
  [field_field] = "field",
  [field_field_type] = "field_type",
  [field_guard] = "guard",
  [field_name] = "name",
  [field_optional] = "optional",
  [field_parameter] = "parameter",
  [field_part] = "part",
  [field_pipe] = "pipe",
  [field_query] = "query",
  [field_selection] = "selection",
  [field_statement] = "statement",
  [field_target] = "target",
  [field_type] = "type",
  [field_updates] = "updates",
  [field_value] = "value",
};

static const TSFieldMapSlice ts_field_map_slices[54] = {
  [1] = {.index = 0, .length = 1},
  [2] = {.index = 1, .length = 1},
  [3] = {.index = 2, .length = 2},
  [4] = {.index = 4, .length = 2},
  [5] = {.index = 6, .length = 2},
  [6] = {.index = 8, .length = 1},
  [7] = {.index = 9, .length = 1},
  [8] = {.index = 10, .length = 2},
  [9] = {.index = 12, .length = 2},
  [10] = {.index = 14, .length = 2},
  [11] = {.index = 16, .length = 1},
  [12] = {.index = 17, .length = 2},
  [13] = {.index = 19, .length = 2},
  [14] = {.index = 21, .length = 3},
  [15] = {.index = 24, .length = 1},
  [16] = {.index = 25, .length = 2},
  [17] = {.index = 27, .length = 1},
  [18] = {.index = 28, .length = 3},
  [19] = {.index = 31, .length = 2},
  [20] = {.index = 33, .length = 1},
  [21] = {.index = 34, .length = 3},
  [22] = {.index = 37, .length = 3},
  [23] = {.index = 40, .length = 3},
  [24] = {.index = 43, .length = 3},
  [25] = {.index = 46, .length = 1},
  [26] = {.index = 47, .length = 4},
  [27] = {.index = 51, .length = 2},
  [28] = {.index = 53, .length = 2},
  [29] = {.index = 55, .length = 3},
  [30] = {.index = 58, .length = 3},
  [31] = {.index = 61, .length = 1},
  [32] = {.index = 62, .length = 1},
  [33] = {.index = 63, .length = 1},
  [34] = {.index = 64, .length = 2},
  [35] = {.index = 66, .length = 1},
  [36] = {.index = 67, .length = 3},
  [37] = {.index = 70, .length = 4},
  [38] = {.index = 74, .length = 4},
  [39] = {.index = 78, .length = 2},
  [40] = {.index = 80, .length = 1},
  [41] = {.index = 81, .length = 2},
  [42] = {.index = 83, .length = 2},
  [43] = {.index = 85, .length = 2},
  [44] = {.index = 87, .length = 2},
  [45] = {.index = 89, .length = 2},
  [46] = {.index = 91, .length = 4},
  [47] = {.index = 95, .length = 4},
  [48] = {.index = 99, .length = 1},
  [49] = {.index = 100, .length = 2},
  [50] = {.index = 102, .length = 5},
  [51] = {.index = 107, .length = 3},
  [52] = {.index = 110, .length = 2},
  [53] = {.index = 112, .length = 2},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_name, 1},
  [1] =
    {field_parameter, 0},
  [2] =
    {field_field, 3},
    {field_name, 1},
  [4] =
    {field_name, 1},
    {field_query, 4},
  [6] =
    {field_parameter, 0},
    {field_parameter, 1, .inherited = true},
  [8] =
    {field_guard, 0},
  [9] =
    {field_base, 1},
  [10] =
    {field_base, 3},
    {field_name, 1},
  [12] =
    {field_base, 0, .inherited = true},
    {field_base, 1, .inherited = true},
  [14] =
    {field_field_type, 2},
    {field_name, 0},
  [16] =
    {field_field, 1},
  [17] =
    {field_field, 0, .inherited = true},
    {field_field, 1, .inherited = true},
  [19] =
    {field_name, 0},
    {field_type, 2},
  [21] =
    {field_name, 1},
    {field_parameter, 3, .inherited = true},
    {field_query, 5},
  [24] =
    {field_parameter, 1},
  [25] =
    {field_parameter, 0, .inherited = true},
    {field_parameter, 1, .inherited = true},
  [27] =
    {field_selection, 1},
  [28] =
    {field_guard, 4, .inherited = true},
    {field_name, 1},
    {field_query, 5},
  [31] =
    {field_guard, 0, .inherited = true},
    {field_guard, 1, .inherited = true},
  [33] =
    {field_statement, 0},
  [34] =
    {field_base, 3},
    {field_field, 5},
    {field_name, 1},
  [37] =
    {field_field_type, 3},
    {field_name, 0},
    {field_optional, 1},
  [40] =
    {field_field, 3},
    {field_field, 4, .inherited = true},
    {field_name, 1},
  [43] =
    {field_name, 0},
    {field_optional, 1},
    {field_type, 3},
  [46] =
    {field_pipe, 1},
  [47] =
    {field_guard, 5, .inherited = true},
    {field_name, 1},
    {field_parameter, 3, .inherited = true},
    {field_query, 6},
  [51] =
    {field_name, 1},
    {field_statement, 5, .inherited = true},
  [53] =
    {field_statement, 0, .inherited = true},
    {field_statement, 1, .inherited = true},
  [55] =
    {field_base, 3},
    {field_field, 6},
    {field_name, 1},
  [58] =
    {field_base, 3},
    {field_base, 4, .inherited = true},
    {field_name, 1},
  [61] =
    {field_base, 0},
  [62] =
    {field_callee, 0},
  [63] =
    {field_part, 0, .inherited = true},
  [64] =
    {field_pipe, 0, .inherited = true},
    {field_pipe, 1, .inherited = true},
  [66] =
    {field_target, 1},
  [67] =
    {field_guard, 4, .inherited = true},
    {field_name, 1},
    {field_statement, 6, .inherited = true},
  [70] =
    {field_base, 3},
    {field_field, 5},
    {field_field, 6, .inherited = true},
    {field_name, 1},
  [74] =
    {field_base, 3},
    {field_base, 4, .inherited = true},
    {field_field, 7},
    {field_name, 1},
  [78] =
    {field_base, 0},
    {field_field, 1},
  [80] =
    {field_part, 1},
  [81] =
    {field_argument, 2},
    {field_callee, 0},
  [83] =
    {field_part, 0, .inherited = true},
    {field_part, 1, .inherited = true},
  [85] =
    {field_pipe, 1},
    {field_pipe, 2, .inherited = true},
  [87] =
    {field_binding, 2},
    {field_name, 1},
  [89] =
    {field_target, 1},
    {field_updates, 2},
  [91] =
    {field_guard, 5, .inherited = true},
    {field_name, 1},
    {field_parameter, 3, .inherited = true},
    {field_statement, 7, .inherited = true},
  [95] =
    {field_base, 3},
    {field_field, 6},
    {field_field, 7, .inherited = true},
    {field_name, 1},
  [99] =
    {field_argument, 1},
  [100] =
    {field_argument, 0, .inherited = true},
    {field_argument, 1, .inherited = true},
  [102] =
    {field_base, 3},
    {field_base, 4, .inherited = true},
    {field_field, 7},
    {field_field, 8, .inherited = true},
    {field_name, 1},
  [107] =
    {field_argument, 2},
    {field_argument, 3, .inherited = true},
    {field_callee, 0},
  [110] =
    {field_name, 0},
    {field_value, 2},
  [112] =
    {field_field, 1},
    {field_field, 2, .inherited = true},
};

static TSSymbol ts_alias_sequences[54][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(27);
      if (lookahead == '"') ADVANCE(44);
      if (lookahead == '$') ADVANCE(25);
      if (lookahead == '%') ADVANCE(14);
      if (lookahead == '\'') ADVANCE(52);
      if (lookahead == '(') ADVANCE(37);
      if (lookahead == ')') ADVANCE(38);
      if (lookahead == ',') ADVANCE(31);
      if (lookahead == '.') ADVANCE(40);
      if (lookahead == '/') ADVANCE(7);
      if (lookahead == ':') ADVANCE(30);
      if (lookahead == ';') ADVANCE(66);
      if (lookahead == '=') ADVANCE(65);
      if (lookahead == '?') ADVANCE(36);
      if (lookahead == '\\') ADVANCE(15);
      if (lookahead == '{') ADVANCE(32);
      if (lookahead == '}') ADVANCE(33);
      if (('+' <= lookahead && lookahead <= '-')) ADVANCE(10);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 160 ||
          lookahead == 8203 ||
          lookahead == 8288 ||
          lookahead == 65279) SKIP(26)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(41);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(34);
      END_STATE();
    case 1:
      if (lookahead == '\n') SKIP(6)
      if (lookahead == '\'') ADVANCE(52);
      if (lookahead == '/') ADVANCE(54);
      if (lookahead == '\\') ADVANCE(2);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 160 ||
          lookahead == 8203 ||
          lookahead == 8288 ||
          lookahead == 65279) ADVANCE(57);
      if (lookahead != 0) ADVANCE(59);
      END_STATE();
    case 2:
      if (lookahead == '\n') ADVANCE(53);
      if (lookahead == '\r') ADVANCE(61);
      if (lookahead == 'u') ADVANCE(16);
      if (lookahead == 'x') ADVANCE(24);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(64);
      if (lookahead != 0) ADVANCE(60);
      END_STATE();
    case 3:
      if (lookahead == '\n') SKIP(5)
      if (lookahead == '"') ADVANCE(44);
      if (lookahead == '/') ADVANCE(46);
      if (lookahead == '\\') ADVANCE(4);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 160 ||
          lookahead == 8203 ||
          lookahead == 8288 ||
          lookahead == 65279) ADVANCE(49);
      if (lookahead != 0) ADVANCE(51);
      END_STATE();
    case 4:
      if (lookahead == '\n') ADVANCE(45);
      if (lookahead == '\r') ADVANCE(62);
      if (lookahead == 'u') ADVANCE(16);
      if (lookahead == 'x') ADVANCE(24);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(64);
      if (lookahead != 0) ADVANCE(60);
      END_STATE();
    case 5:
      if (lookahead == '"') ADVANCE(44);
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
      if (lookahead == '\'') ADVANCE(52);
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
      if (lookahead == '/') ADVANCE(29);
      END_STATE();
    case 8:
      if (lookahead == '*') ADVANCE(8);
      if (lookahead == '/') ADVANCE(28);
      if (lookahead != 0) ADVANCE(9);
      END_STATE();
    case 9:
      if (lookahead == '*') ADVANCE(8);
      if (lookahead != 0) ADVANCE(9);
      END_STATE();
    case 10:
      if (lookahead == '.') ADVANCE(19);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(41);
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
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(64);
      if (lookahead != 0) ADVANCE(60);
      END_STATE();
    case 16:
      if (lookahead == '{') ADVANCE(23);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(21);
      END_STATE();
    case 17:
      if (lookahead == '}') ADVANCE(60);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(17);
      END_STATE();
    case 18:
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(20);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(43);
      END_STATE();
    case 19:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(42);
      END_STATE();
    case 20:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(43);
      END_STATE();
    case 21:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(24);
      END_STATE();
    case 22:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(60);
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
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(35);
      END_STATE();
    case 26:
      if (eof) ADVANCE(27);
      if (lookahead == '"') ADVANCE(44);
      if (lookahead == '$') ADVANCE(25);
      if (lookahead == '%') ADVANCE(14);
      if (lookahead == '\'') ADVANCE(52);
      if (lookahead == '(') ADVANCE(37);
      if (lookahead == ')') ADVANCE(38);
      if (lookahead == ',') ADVANCE(31);
      if (lookahead == '.') ADVANCE(40);
      if (lookahead == '/') ADVANCE(7);
      if (lookahead == ':') ADVANCE(30);
      if (lookahead == ';') ADVANCE(66);
      if (lookahead == '=') ADVANCE(65);
      if (lookahead == '?') ADVANCE(36);
      if (lookahead == '{') ADVANCE(32);
      if (lookahead == '}') ADVANCE(33);
      if (('+' <= lookahead && lookahead <= '-')) ADVANCE(10);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 160 ||
          lookahead == 8203 ||
          lookahead == 8288 ||
          lookahead == 65279) SKIP(26)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(41);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(34);
      END_STATE();
    case 27:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 28:
      ACCEPT_TOKEN(sym_comment);
      END_STATE();
    case 29:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(29);
      END_STATE();
    case 30:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 31:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 32:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 33:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 34:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(34);
      END_STATE();
    case 35:
      ACCEPT_TOKEN(sym_parameter_name);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(35);
      END_STATE();
    case 36:
      ACCEPT_TOKEN(sym_optional_flag);
      END_STATE();
    case 37:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 38:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 39:
      ACCEPT_TOKEN(sym_user);
      END_STATE();
    case 40:
      ACCEPT_TOKEN(anon_sym_DOT);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(42);
      END_STATE();
    case 41:
      ACCEPT_TOKEN(sym_numeric_literal);
      if (lookahead == '.') ADVANCE(19);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(18);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(41);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(sym_numeric_literal);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(18);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(42);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(sym_numeric_literal);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(43);
      END_STATE();
    case 44:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(aux_sym_string_literal_token1);
      END_STATE();
    case 46:
      ACCEPT_TOKEN(aux_sym_string_literal_token1);
      if (lookahead == '*') ADVANCE(48);
      if (lookahead == '/') ADVANCE(50);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(51);
      END_STATE();
    case 47:
      ACCEPT_TOKEN(aux_sym_string_literal_token1);
      if (lookahead == '*') ADVANCE(47);
      if (lookahead == '/') ADVANCE(51);
      if (lookahead == '\n' ||
          lookahead == '"' ||
          lookahead == '\\') ADVANCE(9);
      if (lookahead != 0) ADVANCE(48);
      END_STATE();
    case 48:
      ACCEPT_TOKEN(aux_sym_string_literal_token1);
      if (lookahead == '*') ADVANCE(47);
      if (lookahead == '\n' ||
          lookahead == '"' ||
          lookahead == '\\') ADVANCE(9);
      if (lookahead != 0) ADVANCE(48);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(aux_sym_string_literal_token1);
      if (lookahead == '/') ADVANCE(46);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 160 ||
          lookahead == 8203 ||
          lookahead == 8288 ||
          lookahead == 65279) ADVANCE(49);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(51);
      END_STATE();
    case 50:
      ACCEPT_TOKEN(aux_sym_string_literal_token1);
      if (lookahead == '"' ||
          lookahead == '\\') ADVANCE(29);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(50);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(aux_sym_string_literal_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(51);
      END_STATE();
    case 52:
      ACCEPT_TOKEN(anon_sym_SQUOTE);
      END_STATE();
    case 53:
      ACCEPT_TOKEN(aux_sym_string_literal_token2);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(aux_sym_string_literal_token2);
      if (lookahead == '*') ADVANCE(56);
      if (lookahead == '/') ADVANCE(58);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(59);
      END_STATE();
    case 55:
      ACCEPT_TOKEN(aux_sym_string_literal_token2);
      if (lookahead == '*') ADVANCE(55);
      if (lookahead == '/') ADVANCE(59);
      if (lookahead == '\n' ||
          lookahead == '\'' ||
          lookahead == '\\') ADVANCE(9);
      if (lookahead != 0) ADVANCE(56);
      END_STATE();
    case 56:
      ACCEPT_TOKEN(aux_sym_string_literal_token2);
      if (lookahead == '*') ADVANCE(55);
      if (lookahead == '\n' ||
          lookahead == '\'' ||
          lookahead == '\\') ADVANCE(9);
      if (lookahead != 0) ADVANCE(56);
      END_STATE();
    case 57:
      ACCEPT_TOKEN(aux_sym_string_literal_token2);
      if (lookahead == '/') ADVANCE(54);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 160 ||
          lookahead == 8203 ||
          lookahead == 8288 ||
          lookahead == 65279) ADVANCE(57);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(59);
      END_STATE();
    case 58:
      ACCEPT_TOKEN(aux_sym_string_literal_token2);
      if (lookahead == '\'' ||
          lookahead == '\\') ADVANCE(29);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(58);
      END_STATE();
    case 59:
      ACCEPT_TOKEN(aux_sym_string_literal_token2);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(59);
      END_STATE();
    case 60:
      ACCEPT_TOKEN(sym_escape_sequence);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(sym_escape_sequence);
      if (lookahead == '\n') ADVANCE(53);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(sym_escape_sequence);
      if (lookahead == '\n') ADVANCE(45);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(sym_escape_sequence);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(60);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(sym_escape_sequence);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(63);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(anon_sym_SEMI);
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
  [38] = {.lex_state = 0},
  [39] = {.lex_state = 0},
  [40] = {.lex_state = 0},
  [41] = {.lex_state = 0},
  [42] = {.lex_state = 0},
  [43] = {.lex_state = 0},
  [44] = {.lex_state = 0},
  [45] = {.lex_state = 0},
  [46] = {.lex_state = 0},
  [47] = {.lex_state = 0},
  [48] = {.lex_state = 0},
  [49] = {.lex_state = 0},
  [50] = {.lex_state = 0},
  [51] = {.lex_state = 0},
  [52] = {.lex_state = 0},
  [53] = {.lex_state = 0},
  [54] = {.lex_state = 0},
  [55] = {.lex_state = 0},
  [56] = {.lex_state = 0},
  [57] = {.lex_state = 1},
  [58] = {.lex_state = 0},
  [59] = {.lex_state = 0},
  [60] = {.lex_state = 0},
  [61] = {.lex_state = 0},
  [62] = {.lex_state = 0},
  [63] = {.lex_state = 3},
  [64] = {.lex_state = 3},
  [65] = {.lex_state = 1},
  [66] = {.lex_state = 0},
  [67] = {.lex_state = 0},
  [68] = {.lex_state = 0},
  [69] = {.lex_state = 0},
  [70] = {.lex_state = 0},
  [71] = {.lex_state = 0},
  [72] = {.lex_state = 0},
  [73] = {.lex_state = 3},
  [74] = {.lex_state = 0},
  [75] = {.lex_state = 1},
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
  [151] = {.lex_state = 0},
  [152] = {.lex_state = 0},
  [153] = {.lex_state = 0},
  [154] = {.lex_state = 0},
  [155] = {.lex_state = 0},
  [156] = {.lex_state = 0},
  [157] = {.lex_state = 0},
  [158] = {.lex_state = 0},
  [159] = {.lex_state = 0},
  [160] = {.lex_state = 0},
  [161] = {.lex_state = 0},
  [162] = {.lex_state = 0},
  [163] = {.lex_state = 0},
  [164] = {.lex_state = 0},
  [165] = {.lex_state = 0},
  [166] = {.lex_state = 0},
  [167] = {.lex_state = 0},
  [168] = {.lex_state = 0},
  [169] = {.lex_state = 0},
  [170] = {.lex_state = 0},
  [171] = {.lex_state = 0},
  [172] = {.lex_state = 0},
  [173] = {.lex_state = 0},
  [174] = {.lex_state = 0},
  [175] = {.lex_state = 0},
  [176] = {.lex_state = 0},
  [177] = {.lex_state = 0},
  [178] = {.lex_state = 0},
  [179] = {.lex_state = 0},
  [180] = {.lex_state = 0},
  [181] = {.lex_state = 0},
};

static uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_identifier] = ACTIONS(1),
    [sym_comment] = ACTIONS(3),
    [anon_sym_type] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [sym_parameter_name] = ACTIONS(1),
    [sym_optional_flag] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [sym_user] = ACTIONS(1),
    [anon_sym_DOT] = ACTIONS(1),
    [sym_true_literal] = ACTIONS(1),
    [sym_false_literal] = ACTIONS(1),
    [sym_numeric_literal] = ACTIONS(1),
    [anon_sym_DQUOTE] = ACTIONS(1),
    [anon_sym_SQUOTE] = ACTIONS(1),
    [sym_escape_sequence] = ACTIONS(1),
    [anon_sym_permission] = ACTIONS(1),
    [anon_sym_query] = ACTIONS(1),
    [anon_sym_allow] = ACTIONS(1),
    [anon_sym_EQ] = ACTIONS(1),
    [anon_sym_create] = ACTIONS(1),
    [anon_sym_SEMI] = ACTIONS(1),
    [anon_sym_delete] = ACTIONS(1),
    [anon_sym_update] = ACTIONS(1),
    [anon_sym_action] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(162),
    [sym__declaration] = STATE(7),
    [sym_type_declaration] = STATE(7),
    [sym_permission_declaration] = STATE(7),
    [sym_query_declaration] = STATE(7),
    [sym_action_declaration] = STATE(7),
    [aux_sym_source_file_repeat1] = STATE(7),
    [ts_builtin_sym_end] = ACTIONS(5),
    [sym_comment] = ACTIONS(3),
    [anon_sym_type] = ACTIONS(7),
    [anon_sym_permission] = ACTIONS(9),
    [anon_sym_query] = ACTIONS(11),
    [anon_sym_action] = ACTIONS(13),
  },
};

static uint16_t ts_small_parse_table[] = {
  [0] = 12,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(15), 1,
      sym_identifier,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    ACTIONS(21), 1,
      anon_sym_RPAREN,
    ACTIONS(23), 1,
      anon_sym_DOT,
    ACTIONS(27), 1,
      sym_numeric_literal,
    ACTIONS(29), 1,
      anon_sym_DQUOTE,
    ACTIONS(31), 1,
      anon_sym_SQUOTE,
    STATE(22), 1,
      aux_sym_uri_repeat1,
    ACTIONS(19), 2,
      sym_parameter_name,
      sym_user,
    ACTIONS(25), 2,
      sym_true_literal,
      sym_false_literal,
    STATE(123), 7,
      sym__expression,
      sym__primitive_expression,
      sym_call,
      sym_variable,
      sym_uri,
      sym_string_literal,
      sym_query,
  [45] = 12,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(15), 1,
      sym_identifier,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    ACTIONS(23), 1,
      anon_sym_DOT,
    ACTIONS(29), 1,
      anon_sym_DQUOTE,
    ACTIONS(31), 1,
      anon_sym_SQUOTE,
    ACTIONS(33), 1,
      anon_sym_RPAREN,
    ACTIONS(37), 1,
      sym_numeric_literal,
    STATE(22), 1,
      aux_sym_uri_repeat1,
    ACTIONS(19), 2,
      sym_parameter_name,
      sym_user,
    ACTIONS(35), 2,
      sym_true_literal,
      sym_false_literal,
    STATE(146), 7,
      sym__expression,
      sym__primitive_expression,
      sym_call,
      sym_variable,
      sym_uri,
      sym_string_literal,
      sym_query,
  [90] = 12,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(15), 1,
      sym_identifier,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    ACTIONS(23), 1,
      anon_sym_DOT,
    ACTIONS(29), 1,
      anon_sym_DQUOTE,
    ACTIONS(31), 1,
      anon_sym_SQUOTE,
    ACTIONS(37), 1,
      sym_numeric_literal,
    ACTIONS(39), 1,
      anon_sym_RPAREN,
    STATE(22), 1,
      aux_sym_uri_repeat1,
    ACTIONS(19), 2,
      sym_parameter_name,
      sym_user,
    ACTIONS(35), 2,
      sym_true_literal,
      sym_false_literal,
    STATE(146), 7,
      sym__expression,
      sym__primitive_expression,
      sym_call,
      sym_variable,
      sym_uri,
      sym_string_literal,
      sym_query,
  [135] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(15), 1,
      sym_identifier,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    ACTIONS(23), 1,
      anon_sym_DOT,
    ACTIONS(29), 1,
      anon_sym_DQUOTE,
    ACTIONS(31), 1,
      anon_sym_SQUOTE,
    ACTIONS(37), 1,
      sym_numeric_literal,
    STATE(22), 1,
      aux_sym_uri_repeat1,
    ACTIONS(19), 2,
      sym_parameter_name,
      sym_user,
    ACTIONS(35), 2,
      sym_true_literal,
      sym_false_literal,
    STATE(146), 7,
      sym__expression,
      sym__primitive_expression,
      sym_call,
      sym_variable,
      sym_uri,
      sym_string_literal,
      sym_query,
  [177] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(15), 1,
      sym_identifier,
    ACTIONS(23), 1,
      anon_sym_DOT,
    ACTIONS(29), 1,
      anon_sym_DQUOTE,
    ACTIONS(31), 1,
      anon_sym_SQUOTE,
    ACTIONS(41), 1,
      anon_sym_LBRACE,
    ACTIONS(45), 1,
      sym_numeric_literal,
    STATE(22), 1,
      aux_sym_uri_repeat1,
    ACTIONS(19), 2,
      sym_parameter_name,
      sym_user,
    ACTIONS(43), 2,
      sym_true_literal,
      sym_false_literal,
    STATE(134), 7,
      sym__primitive_expression,
      sym_call,
      sym_variable,
      sym_uri,
      sym_string_literal,
      sym_binding,
      sym__binding_value,
  [219] = 7,
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
    ACTIONS(47), 1,
      ts_builtin_sym_end,
    STATE(8), 6,
      sym__declaration,
      sym_type_declaration,
      sym_permission_declaration,
      sym_query_declaration,
      sym_action_declaration,
      aux_sym_source_file_repeat1,
  [246] = 7,
    ACTIONS(3), 1,
      sym_comment,
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
    STATE(8), 6,
      sym__declaration,
      sym_type_declaration,
      sym_permission_declaration,
      sym_query_declaration,
      sym_action_declaration,
      aux_sym_source_file_repeat1,
  [273] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(63), 9,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_COMMA,
      anon_sym_LBRACE,
      anon_sym_RPAREN,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_SEMI,
      anon_sym_action,
  [288] = 7,
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
    STATE(11), 1,
      aux_sym_action_declaration_repeat1,
    STATE(71), 4,
      sym__statement,
      sym_create_statement,
      sym_delete_statement,
      sym_update_statement,
  [313] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(73), 1,
      anon_sym_RBRACE,
    ACTIONS(75), 1,
      anon_sym_create,
    ACTIONS(78), 1,
      anon_sym_delete,
    ACTIONS(81), 1,
      anon_sym_update,
    STATE(11), 1,
      aux_sym_action_declaration_repeat1,
    STATE(71), 4,
      sym__statement,
      sym_create_statement,
      sym_delete_statement,
      sym_update_statement,
  [338] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(67), 1,
      anon_sym_create,
    ACTIONS(69), 1,
      anon_sym_delete,
    ACTIONS(71), 1,
      anon_sym_update,
    ACTIONS(84), 1,
      anon_sym_RBRACE,
    STATE(13), 1,
      aux_sym_action_declaration_repeat1,
    STATE(71), 4,
      sym__statement,
      sym_create_statement,
      sym_delete_statement,
      sym_update_statement,
  [363] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(67), 1,
      anon_sym_create,
    ACTIONS(69), 1,
      anon_sym_delete,
    ACTIONS(71), 1,
      anon_sym_update,
    ACTIONS(86), 1,
      anon_sym_RBRACE,
    STATE(11), 1,
      aux_sym_action_declaration_repeat1,
    STATE(71), 4,
      sym__statement,
      sym_create_statement,
      sym_delete_statement,
      sym_update_statement,
  [388] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(67), 1,
      anon_sym_create,
    ACTIONS(69), 1,
      anon_sym_delete,
    ACTIONS(71), 1,
      anon_sym_update,
    ACTIONS(86), 1,
      anon_sym_RBRACE,
    STATE(10), 1,
      aux_sym_action_declaration_repeat1,
    STATE(71), 4,
      sym__statement,
      sym_create_statement,
      sym_delete_statement,
      sym_update_statement,
  [413] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(67), 1,
      anon_sym_create,
    ACTIONS(69), 1,
      anon_sym_delete,
    ACTIONS(71), 1,
      anon_sym_update,
    ACTIONS(88), 1,
      anon_sym_RBRACE,
    STATE(18), 1,
      aux_sym_action_declaration_repeat1,
    STATE(71), 4,
      sym__statement,
      sym_create_statement,
      sym_delete_statement,
      sym_update_statement,
  [438] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(90), 9,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_COMMA,
      anon_sym_LBRACE,
      anon_sym_RPAREN,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_SEMI,
      anon_sym_action,
  [453] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(92), 9,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_COMMA,
      anon_sym_LBRACE,
      anon_sym_RPAREN,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_SEMI,
      anon_sym_action,
  [468] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(67), 1,
      anon_sym_create,
    ACTIONS(69), 1,
      anon_sym_delete,
    ACTIONS(71), 1,
      anon_sym_update,
    ACTIONS(84), 1,
      anon_sym_RBRACE,
    STATE(11), 1,
      aux_sym_action_declaration_repeat1,
    STATE(71), 4,
      sym__statement,
      sym_create_statement,
      sym_delete_statement,
      sym_update_statement,
  [493] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(94), 9,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_COMMA,
      anon_sym_LBRACE,
      anon_sym_RPAREN,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_SEMI,
      anon_sym_action,
  [508] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(98), 1,
      anon_sym_LPAREN,
    ACTIONS(100), 1,
      anon_sym_DOT,
    STATE(22), 1,
      aux_sym_uri_repeat1,
    STATE(109), 1,
      sym_uri,
    ACTIONS(96), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
  [529] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(100), 1,
      anon_sym_DOT,
    STATE(22), 1,
      aux_sym_uri_repeat1,
    STATE(109), 1,
      sym_uri,
    ACTIONS(96), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
  [547] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(100), 1,
      anon_sym_DOT,
    STATE(25), 1,
      aux_sym_uri_repeat1,
    ACTIONS(102), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
  [562] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    ACTIONS(104), 1,
      anon_sym_allow,
    STATE(24), 1,
      aux_sym_query_declaration_repeat1,
    STATE(27), 1,
      sym_query,
    STATE(139), 1,
      sym_guard,
  [581] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    ACTIONS(104), 1,
      anon_sym_allow,
    STATE(50), 1,
      sym_query,
    STATE(76), 1,
      aux_sym_query_declaration_repeat1,
    STATE(139), 1,
      sym_guard,
  [600] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(108), 1,
      anon_sym_DOT,
    STATE(25), 1,
      aux_sym_uri_repeat1,
    ACTIONS(106), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
  [615] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(111), 5,
      anon_sym_COMMA,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_allow,
  [626] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(113), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [637] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    ACTIONS(104), 1,
      anon_sym_allow,
    STATE(46), 1,
      sym_query,
    STATE(48), 1,
      aux_sym_query_declaration_repeat1,
    STATE(139), 1,
      sym_guard,
  [656] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(115), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [667] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(117), 5,
      anon_sym_COMMA,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_allow,
  [678] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(119), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [689] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(121), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [700] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(123), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [711] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(125), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [722] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(127), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [733] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(129), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [744] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(131), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [755] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(133), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [766] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(135), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [777] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(137), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [788] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(139), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [799] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(141), 5,
      anon_sym_COMMA,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_allow,
  [810] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(143), 5,
      anon_sym_COMMA,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_allow,
  [821] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(145), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [832] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(147), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [843] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(149), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [854] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(151), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [865] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    ACTIONS(104), 1,
      anon_sym_allow,
    STATE(27), 1,
      sym_query,
    STATE(76), 1,
      aux_sym_query_declaration_repeat1,
    STATE(139), 1,
      sym_guard,
  [884] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(153), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [895] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(155), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [906] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(157), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [917] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(159), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [928] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(161), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [939] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(163), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [950] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(165), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [961] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(167), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [972] = 4,
    ACTIONS(169), 1,
      sym_comment,
    ACTIONS(171), 1,
      anon_sym_SQUOTE,
    STATE(57), 1,
      aux_sym_string_literal_repeat2,
    ACTIONS(173), 2,
      aux_sym_string_literal_token2,
      sym_escape_sequence,
  [986] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(104), 1,
      anon_sym_allow,
    ACTIONS(176), 1,
      anon_sym_LBRACE,
    STATE(74), 1,
      aux_sym_query_declaration_repeat1,
    STATE(139), 1,
      sym_guard,
  [1002] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(104), 1,
      anon_sym_allow,
    ACTIONS(176), 1,
      anon_sym_LBRACE,
    STATE(76), 1,
      aux_sym_query_declaration_repeat1,
    STATE(139), 1,
      sym_guard,
  [1018] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(178), 1,
      sym_parameter_name,
    ACTIONS(180), 1,
      anon_sym_RPAREN,
    STATE(106), 1,
      sym_parameter,
    STATE(166), 1,
      sym__parameters,
  [1034] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(178), 1,
      sym_parameter_name,
    ACTIONS(182), 1,
      anon_sym_RPAREN,
    STATE(106), 1,
      sym_parameter,
    STATE(170), 1,
      sym__parameters,
  [1050] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(184), 4,
      anon_sym_RBRACE,
      anon_sym_create,
      anon_sym_delete,
      anon_sym_update,
  [1060] = 4,
    ACTIONS(169), 1,
      sym_comment,
    ACTIONS(186), 1,
      anon_sym_DQUOTE,
    STATE(63), 1,
      aux_sym_string_literal_repeat1,
    ACTIONS(188), 2,
      aux_sym_string_literal_token1,
      sym_escape_sequence,
  [1074] = 4,
    ACTIONS(169), 1,
      sym_comment,
    ACTIONS(191), 1,
      anon_sym_DQUOTE,
    STATE(73), 1,
      aux_sym_string_literal_repeat1,
    ACTIONS(193), 2,
      aux_sym_string_literal_token1,
      sym_escape_sequence,
  [1088] = 4,
    ACTIONS(169), 1,
      sym_comment,
    ACTIONS(191), 1,
      anon_sym_SQUOTE,
    STATE(75), 1,
      aux_sym_string_literal_repeat2,
    ACTIONS(195), 2,
      aux_sym_string_literal_token2,
      sym_escape_sequence,
  [1102] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(197), 4,
      anon_sym_RBRACE,
      anon_sym_create,
      anon_sym_delete,
      anon_sym_update,
  [1112] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(178), 1,
      sym_parameter_name,
    ACTIONS(199), 1,
      anon_sym_RPAREN,
    STATE(106), 1,
      sym_parameter,
    STATE(161), 1,
      sym__parameters,
  [1128] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    ACTIONS(201), 1,
      sym_parameter_name,
    STATE(160), 2,
      sym_query,
      sym__statement_target,
  [1142] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    ACTIONS(203), 1,
      sym_parameter_name,
    STATE(148), 2,
      sym_query,
      sym__statement_target,
  [1156] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(205), 4,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_DOT,
  [1166] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(207), 4,
      anon_sym_RBRACE,
      anon_sym_create,
      anon_sym_delete,
      anon_sym_update,
  [1176] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(104), 1,
      anon_sym_allow,
    ACTIONS(209), 1,
      anon_sym_LBRACE,
    STATE(59), 1,
      aux_sym_query_declaration_repeat1,
    STATE(139), 1,
      sym_guard,
  [1192] = 4,
    ACTIONS(169), 1,
      sym_comment,
    ACTIONS(211), 1,
      anon_sym_DQUOTE,
    STATE(63), 1,
      aux_sym_string_literal_repeat1,
    ACTIONS(213), 2,
      aux_sym_string_literal_token1,
      sym_escape_sequence,
  [1206] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(104), 1,
      anon_sym_allow,
    ACTIONS(215), 1,
      anon_sym_LBRACE,
    STATE(76), 1,
      aux_sym_query_declaration_repeat1,
    STATE(139), 1,
      sym_guard,
  [1222] = 4,
    ACTIONS(169), 1,
      sym_comment,
    ACTIONS(211), 1,
      anon_sym_SQUOTE,
    STATE(57), 1,
      aux_sym_string_literal_repeat2,
    ACTIONS(217), 2,
      aux_sym_string_literal_token2,
      sym_escape_sequence,
  [1236] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(219), 1,
      anon_sym_LBRACE,
    ACTIONS(221), 1,
      anon_sym_allow,
    STATE(76), 1,
      aux_sym_query_declaration_repeat1,
    STATE(139), 1,
      sym_guard,
  [1252] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(224), 4,
      anon_sym_RBRACE,
      anon_sym_create,
      anon_sym_delete,
      anon_sym_update,
  [1262] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(226), 1,
      anon_sym_COMMA,
    ACTIONS(228), 1,
      anon_sym_RPAREN,
    STATE(84), 1,
      aux_sym__parameters_repeat1,
  [1275] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(230), 1,
      anon_sym_COMMA,
    ACTIONS(232), 1,
      anon_sym_RBRACE,
    STATE(125), 1,
      aux_sym_type_declaration_repeat2,
  [1288] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(234), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_SEMI,
  [1297] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(236), 1,
      anon_sym_COMMA,
    ACTIONS(238), 1,
      anon_sym_RBRACE,
    STATE(100), 1,
      aux_sym_query_repeat1,
  [1310] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(240), 1,
      anon_sym_COMMA,
    ACTIONS(243), 1,
      anon_sym_RBRACE,
    STATE(82), 1,
      aux_sym_binding_repeat1,
  [1323] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(178), 1,
      sym_parameter_name,
    ACTIONS(245), 1,
      anon_sym_RPAREN,
    STATE(155), 1,
      sym_parameter,
  [1336] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(247), 1,
      anon_sym_COMMA,
    ACTIONS(250), 1,
      anon_sym_RPAREN,
    STATE(84), 1,
      aux_sym__parameters_repeat1,
  [1349] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(252), 1,
      sym_identifier,
    ACTIONS(254), 1,
      anon_sym_RBRACE,
    STATE(133), 1,
      sym_binding_field,
  [1362] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(256), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_SEMI,
  [1371] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(258), 1,
      anon_sym_COMMA,
    ACTIONS(260), 1,
      anon_sym_RBRACE,
    STATE(112), 1,
      aux_sym_type_declaration_repeat2,
  [1384] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(262), 1,
      sym_identifier,
    ACTIONS(264), 1,
      anon_sym_RBRACE,
    STATE(136), 1,
      sym_type_field,
  [1397] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(266), 1,
      anon_sym_COMMA,
    ACTIONS(268), 1,
      anon_sym_RBRACE,
    STATE(82), 1,
      aux_sym_binding_repeat1,
  [1410] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(264), 1,
      anon_sym_RBRACE,
    ACTIONS(270), 1,
      anon_sym_COMMA,
    STATE(97), 1,
      aux_sym_type_declaration_repeat2,
  [1423] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(262), 1,
      sym_identifier,
    ACTIONS(272), 1,
      anon_sym_RBRACE,
    STATE(116), 1,
      sym_type_field,
  [1436] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(274), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_SEMI,
  [1445] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(252), 1,
      sym_identifier,
    ACTIONS(268), 1,
      anon_sym_RBRACE,
    STATE(133), 1,
      sym_binding_field,
  [1458] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(276), 1,
      anon_sym_COMMA,
    ACTIONS(279), 1,
      anon_sym_RPAREN,
    STATE(94), 1,
      aux_sym_call_repeat1,
  [1471] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(281), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
  [1480] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(262), 1,
      sym_identifier,
    ACTIONS(283), 1,
      anon_sym_RBRACE,
    STATE(136), 1,
      sym_type_field,
  [1493] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(285), 1,
      anon_sym_COMMA,
    ACTIONS(288), 1,
      anon_sym_RBRACE,
    STATE(97), 1,
      aux_sym_type_declaration_repeat2,
  [1506] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(290), 1,
      sym_identifier,
    ACTIONS(292), 1,
      anon_sym_RBRACE,
    STATE(135), 1,
      sym_call,
  [1519] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(262), 1,
      sym_identifier,
    ACTIONS(294), 1,
      anon_sym_RBRACE,
    STATE(136), 1,
      sym_type_field,
  [1532] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(292), 1,
      anon_sym_RBRACE,
    ACTIONS(296), 1,
      anon_sym_COMMA,
    STATE(128), 1,
      aux_sym_query_repeat1,
  [1545] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(262), 1,
      sym_identifier,
    ACTIONS(298), 1,
      anon_sym_RBRACE,
    STATE(79), 1,
      sym_type_field,
  [1558] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(300), 1,
      anon_sym_COMMA,
    ACTIONS(302), 1,
      anon_sym_LBRACE,
    STATE(120), 1,
      aux_sym_type_declaration_repeat1,
  [1571] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(304), 1,
      anon_sym_COMMA,
    ACTIONS(306), 1,
      anon_sym_RBRACE,
    STATE(89), 1,
      aux_sym_binding_repeat1,
  [1584] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(308), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_SEMI,
  [1593] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(33), 1,
      anon_sym_RPAREN,
    ACTIONS(310), 1,
      anon_sym_COMMA,
    STATE(94), 1,
      aux_sym_call_repeat1,
  [1606] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(312), 1,
      anon_sym_COMMA,
    ACTIONS(314), 1,
      anon_sym_RPAREN,
    STATE(78), 1,
      aux_sym__parameters_repeat1,
  [1619] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(316), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
  [1628] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(318), 1,
      anon_sym_COMMA,
    ACTIONS(321), 1,
      anon_sym_LBRACE,
    STATE(108), 1,
      aux_sym_type_declaration_repeat1,
  [1641] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(323), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
  [1650] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(262), 1,
      sym_identifier,
    ACTIONS(325), 1,
      anon_sym_RBRACE,
    STATE(136), 1,
      sym_type_field,
  [1663] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(327), 1,
      anon_sym_COMMA,
    ACTIONS(329), 1,
      anon_sym_RBRACE,
    STATE(90), 1,
      aux_sym_type_declaration_repeat2,
  [1676] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(325), 1,
      anon_sym_RBRACE,
    ACTIONS(331), 1,
      anon_sym_COMMA,
    STATE(97), 1,
      aux_sym_type_declaration_repeat2,
  [1689] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(333), 1,
      anon_sym_COMMA,
    ACTIONS(335), 1,
      anon_sym_RBRACE,
    STATE(97), 1,
      aux_sym_type_declaration_repeat2,
  [1702] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(262), 1,
      sym_identifier,
    ACTIONS(337), 1,
      anon_sym_RBRACE,
    STATE(136), 1,
      sym_type_field,
  [1715] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(262), 1,
      sym_identifier,
    ACTIONS(339), 1,
      anon_sym_RBRACE,
    STATE(87), 1,
      sym_type_field,
  [1728] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(341), 1,
      anon_sym_COMMA,
    ACTIONS(343), 1,
      anon_sym_RBRACE,
    STATE(113), 1,
      aux_sym_type_declaration_repeat2,
  [1741] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(262), 1,
      sym_identifier,
    ACTIONS(345), 1,
      anon_sym_RBRACE,
    STATE(111), 1,
      sym_type_field,
  [1754] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(262), 1,
      sym_identifier,
    ACTIONS(335), 1,
      anon_sym_RBRACE,
    STATE(136), 1,
      sym_type_field,
  [1767] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(178), 1,
      sym_parameter_name,
    ACTIONS(347), 1,
      anon_sym_RPAREN,
    STATE(155), 1,
      sym_parameter,
  [1780] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(349), 1,
      anon_sym_COMMA,
    ACTIONS(351), 1,
      anon_sym_LBRACE,
    STATE(108), 1,
      aux_sym_type_declaration_repeat1,
  [1793] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(262), 1,
      sym_identifier,
    ACTIONS(353), 1,
      anon_sym_RBRACE,
    STATE(136), 1,
      sym_type_field,
  [1806] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(290), 1,
      sym_identifier,
    ACTIONS(355), 1,
      anon_sym_RBRACE,
    STATE(81), 1,
      sym_call,
  [1819] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(357), 1,
      anon_sym_COMMA,
    ACTIONS(359), 1,
      anon_sym_RPAREN,
    STATE(105), 1,
      aux_sym_call_repeat1,
  [1832] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(262), 1,
      sym_identifier,
    ACTIONS(361), 1,
      anon_sym_RBRACE,
    STATE(136), 1,
      sym_type_field,
  [1845] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(361), 1,
      anon_sym_RBRACE,
    ACTIONS(363), 1,
      anon_sym_COMMA,
    STATE(97), 1,
      aux_sym_type_declaration_repeat2,
  [1858] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(252), 1,
      sym_identifier,
    ACTIONS(365), 1,
      anon_sym_RBRACE,
    STATE(103), 1,
      sym_binding_field,
  [1871] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(290), 1,
      sym_identifier,
    ACTIONS(367), 1,
      anon_sym_RBRACE,
    STATE(135), 1,
      sym_call,
  [1884] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(369), 1,
      anon_sym_COMMA,
    ACTIONS(372), 1,
      anon_sym_RBRACE,
    STATE(128), 1,
      aux_sym_query_repeat1,
  [1897] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(374), 1,
      anon_sym_COLON,
    ACTIONS(376), 1,
      sym_optional_flag,
  [1907] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    STATE(31), 1,
      sym_query,
  [1917] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(252), 1,
      sym_identifier,
    STATE(133), 1,
      sym_binding_field,
  [1927] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(378), 2,
      anon_sym_LBRACE,
      anon_sym_allow,
  [1935] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(380), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [1943] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(382), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [1951] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(384), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [1959] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(386), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [1967] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(388), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [1975] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(290), 1,
      sym_identifier,
    STATE(132), 1,
      sym_call,
  [1985] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(390), 2,
      anon_sym_LBRACE,
      anon_sym_allow,
  [1993] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(392), 2,
      anon_sym_COMMA,
      anon_sym_LBRACE,
  [2001] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(394), 1,
      sym_identifier,
    ACTIONS(396), 1,
      anon_sym_LBRACE,
  [2011] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(351), 1,
      anon_sym_LBRACE,
    ACTIONS(394), 1,
      sym_identifier,
  [2021] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(398), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [2029] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(400), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [2037] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(402), 1,
      anon_sym_COLON,
    ACTIONS(404), 1,
      anon_sym_LBRACE,
  [2047] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(406), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [2055] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(262), 1,
      sym_identifier,
    STATE(136), 1,
      sym_type_field,
  [2065] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(41), 1,
      anon_sym_LBRACE,
    STATE(178), 1,
      sym_binding,
  [2075] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    STATE(41), 1,
      sym_query,
  [2085] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(408), 1,
      anon_sym_COLON,
    ACTIONS(410), 1,
      sym_optional_flag,
  [2095] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(290), 1,
      sym_identifier,
    STATE(135), 1,
      sym_call,
  [2105] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(412), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [2113] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(178), 1,
      sym_parameter_name,
    STATE(155), 1,
      sym_parameter,
  [2123] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(41), 1,
      anon_sym_LBRACE,
    STATE(169), 1,
      sym_binding,
  [2133] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(414), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [2141] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(416), 1,
      anon_sym_LPAREN,
  [2148] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(418), 1,
      sym_identifier,
  [2155] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(420), 1,
      sym_identifier,
  [2162] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(422), 1,
      sym_identifier,
  [2169] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(424), 1,
      anon_sym_SEMI,
  [2176] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(426), 1,
      anon_sym_RPAREN,
  [2183] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(428), 1,
      ts_builtin_sym_end,
  [2190] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(430), 1,
      anon_sym_LPAREN,
  [2197] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(432), 1,
      anon_sym_LPAREN,
  [2204] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(434), 1,
      sym_identifier,
  [2211] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(436), 1,
      anon_sym_RPAREN,
  [2218] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(438), 1,
      sym_identifier,
  [2225] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(440), 1,
      anon_sym_EQ,
  [2232] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(442), 1,
      anon_sym_SEMI,
  [2239] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(444), 1,
      anon_sym_RPAREN,
  [2246] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(446), 1,
      sym_identifier,
  [2253] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(448), 1,
      sym_identifier,
  [2260] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(450), 1,
      sym_identifier,
  [2267] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(452), 1,
      sym_identifier,
  [2274] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(454), 1,
      anon_sym_COLON,
  [2281] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(456), 1,
      sym_identifier,
  [2288] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(458), 1,
      anon_sym_COLON,
  [2295] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(460), 1,
      anon_sym_SEMI,
  [2302] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(462), 1,
      sym_identifier,
  [2309] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(98), 1,
      anon_sym_LPAREN,
  [2316] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(394), 1,
      sym_identifier,
};

static uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 45,
  [SMALL_STATE(4)] = 90,
  [SMALL_STATE(5)] = 135,
  [SMALL_STATE(6)] = 177,
  [SMALL_STATE(7)] = 219,
  [SMALL_STATE(8)] = 246,
  [SMALL_STATE(9)] = 273,
  [SMALL_STATE(10)] = 288,
  [SMALL_STATE(11)] = 313,
  [SMALL_STATE(12)] = 338,
  [SMALL_STATE(13)] = 363,
  [SMALL_STATE(14)] = 388,
  [SMALL_STATE(15)] = 413,
  [SMALL_STATE(16)] = 438,
  [SMALL_STATE(17)] = 453,
  [SMALL_STATE(18)] = 468,
  [SMALL_STATE(19)] = 493,
  [SMALL_STATE(20)] = 508,
  [SMALL_STATE(21)] = 529,
  [SMALL_STATE(22)] = 547,
  [SMALL_STATE(23)] = 562,
  [SMALL_STATE(24)] = 581,
  [SMALL_STATE(25)] = 600,
  [SMALL_STATE(26)] = 615,
  [SMALL_STATE(27)] = 626,
  [SMALL_STATE(28)] = 637,
  [SMALL_STATE(29)] = 656,
  [SMALL_STATE(30)] = 667,
  [SMALL_STATE(31)] = 678,
  [SMALL_STATE(32)] = 689,
  [SMALL_STATE(33)] = 700,
  [SMALL_STATE(34)] = 711,
  [SMALL_STATE(35)] = 722,
  [SMALL_STATE(36)] = 733,
  [SMALL_STATE(37)] = 744,
  [SMALL_STATE(38)] = 755,
  [SMALL_STATE(39)] = 766,
  [SMALL_STATE(40)] = 777,
  [SMALL_STATE(41)] = 788,
  [SMALL_STATE(42)] = 799,
  [SMALL_STATE(43)] = 810,
  [SMALL_STATE(44)] = 821,
  [SMALL_STATE(45)] = 832,
  [SMALL_STATE(46)] = 843,
  [SMALL_STATE(47)] = 854,
  [SMALL_STATE(48)] = 865,
  [SMALL_STATE(49)] = 884,
  [SMALL_STATE(50)] = 895,
  [SMALL_STATE(51)] = 906,
  [SMALL_STATE(52)] = 917,
  [SMALL_STATE(53)] = 928,
  [SMALL_STATE(54)] = 939,
  [SMALL_STATE(55)] = 950,
  [SMALL_STATE(56)] = 961,
  [SMALL_STATE(57)] = 972,
  [SMALL_STATE(58)] = 986,
  [SMALL_STATE(59)] = 1002,
  [SMALL_STATE(60)] = 1018,
  [SMALL_STATE(61)] = 1034,
  [SMALL_STATE(62)] = 1050,
  [SMALL_STATE(63)] = 1060,
  [SMALL_STATE(64)] = 1074,
  [SMALL_STATE(65)] = 1088,
  [SMALL_STATE(66)] = 1102,
  [SMALL_STATE(67)] = 1112,
  [SMALL_STATE(68)] = 1128,
  [SMALL_STATE(69)] = 1142,
  [SMALL_STATE(70)] = 1156,
  [SMALL_STATE(71)] = 1166,
  [SMALL_STATE(72)] = 1176,
  [SMALL_STATE(73)] = 1192,
  [SMALL_STATE(74)] = 1206,
  [SMALL_STATE(75)] = 1222,
  [SMALL_STATE(76)] = 1236,
  [SMALL_STATE(77)] = 1252,
  [SMALL_STATE(78)] = 1262,
  [SMALL_STATE(79)] = 1275,
  [SMALL_STATE(80)] = 1288,
  [SMALL_STATE(81)] = 1297,
  [SMALL_STATE(82)] = 1310,
  [SMALL_STATE(83)] = 1323,
  [SMALL_STATE(84)] = 1336,
  [SMALL_STATE(85)] = 1349,
  [SMALL_STATE(86)] = 1362,
  [SMALL_STATE(87)] = 1371,
  [SMALL_STATE(88)] = 1384,
  [SMALL_STATE(89)] = 1397,
  [SMALL_STATE(90)] = 1410,
  [SMALL_STATE(91)] = 1423,
  [SMALL_STATE(92)] = 1436,
  [SMALL_STATE(93)] = 1445,
  [SMALL_STATE(94)] = 1458,
  [SMALL_STATE(95)] = 1471,
  [SMALL_STATE(96)] = 1480,
  [SMALL_STATE(97)] = 1493,
  [SMALL_STATE(98)] = 1506,
  [SMALL_STATE(99)] = 1519,
  [SMALL_STATE(100)] = 1532,
  [SMALL_STATE(101)] = 1545,
  [SMALL_STATE(102)] = 1558,
  [SMALL_STATE(103)] = 1571,
  [SMALL_STATE(104)] = 1584,
  [SMALL_STATE(105)] = 1593,
  [SMALL_STATE(106)] = 1606,
  [SMALL_STATE(107)] = 1619,
  [SMALL_STATE(108)] = 1628,
  [SMALL_STATE(109)] = 1641,
  [SMALL_STATE(110)] = 1650,
  [SMALL_STATE(111)] = 1663,
  [SMALL_STATE(112)] = 1676,
  [SMALL_STATE(113)] = 1689,
  [SMALL_STATE(114)] = 1702,
  [SMALL_STATE(115)] = 1715,
  [SMALL_STATE(116)] = 1728,
  [SMALL_STATE(117)] = 1741,
  [SMALL_STATE(118)] = 1754,
  [SMALL_STATE(119)] = 1767,
  [SMALL_STATE(120)] = 1780,
  [SMALL_STATE(121)] = 1793,
  [SMALL_STATE(122)] = 1806,
  [SMALL_STATE(123)] = 1819,
  [SMALL_STATE(124)] = 1832,
  [SMALL_STATE(125)] = 1845,
  [SMALL_STATE(126)] = 1858,
  [SMALL_STATE(127)] = 1871,
  [SMALL_STATE(128)] = 1884,
  [SMALL_STATE(129)] = 1897,
  [SMALL_STATE(130)] = 1907,
  [SMALL_STATE(131)] = 1917,
  [SMALL_STATE(132)] = 1927,
  [SMALL_STATE(133)] = 1935,
  [SMALL_STATE(134)] = 1943,
  [SMALL_STATE(135)] = 1951,
  [SMALL_STATE(136)] = 1959,
  [SMALL_STATE(137)] = 1967,
  [SMALL_STATE(138)] = 1975,
  [SMALL_STATE(139)] = 1985,
  [SMALL_STATE(140)] = 1993,
  [SMALL_STATE(141)] = 2001,
  [SMALL_STATE(142)] = 2011,
  [SMALL_STATE(143)] = 2021,
  [SMALL_STATE(144)] = 2029,
  [SMALL_STATE(145)] = 2037,
  [SMALL_STATE(146)] = 2047,
  [SMALL_STATE(147)] = 2055,
  [SMALL_STATE(148)] = 2065,
  [SMALL_STATE(149)] = 2075,
  [SMALL_STATE(150)] = 2085,
  [SMALL_STATE(151)] = 2095,
  [SMALL_STATE(152)] = 2105,
  [SMALL_STATE(153)] = 2113,
  [SMALL_STATE(154)] = 2123,
  [SMALL_STATE(155)] = 2133,
  [SMALL_STATE(156)] = 2141,
  [SMALL_STATE(157)] = 2148,
  [SMALL_STATE(158)] = 2155,
  [SMALL_STATE(159)] = 2162,
  [SMALL_STATE(160)] = 2169,
  [SMALL_STATE(161)] = 2176,
  [SMALL_STATE(162)] = 2183,
  [SMALL_STATE(163)] = 2190,
  [SMALL_STATE(164)] = 2197,
  [SMALL_STATE(165)] = 2204,
  [SMALL_STATE(166)] = 2211,
  [SMALL_STATE(167)] = 2218,
  [SMALL_STATE(168)] = 2225,
  [SMALL_STATE(169)] = 2232,
  [SMALL_STATE(170)] = 2239,
  [SMALL_STATE(171)] = 2246,
  [SMALL_STATE(172)] = 2253,
  [SMALL_STATE(173)] = 2260,
  [SMALL_STATE(174)] = 2267,
  [SMALL_STATE(175)] = 2274,
  [SMALL_STATE(176)] = 2281,
  [SMALL_STATE(177)] = 2288,
  [SMALL_STATE(178)] = 2295,
  [SMALL_STATE(179)] = 2302,
  [SMALL_STATE(180)] = 2309,
  [SMALL_STATE(181)] = 2316,
};

static TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(171),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(174),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(173),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(158),
  [15] = {.entry = {.count = 1, .reusable = false}}, SHIFT(20),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(122),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [23] = {.entry = {.count = 1, .reusable = false}}, SHIFT(167),
  [25] = {.entry = {.count = 1, .reusable = false}}, SHIFT(123),
  [27] = {.entry = {.count = 1, .reusable = true}}, SHIFT(123),
  [29] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [31] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [33] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [35] = {.entry = {.count = 1, .reusable = false}}, SHIFT(146),
  [37] = {.entry = {.count = 1, .reusable = true}}, SHIFT(146),
  [39] = {.entry = {.count = 1, .reusable = true}}, SHIFT(43),
  [41] = {.entry = {.count = 1, .reusable = true}}, SHIFT(126),
  [43] = {.entry = {.count = 1, .reusable = false}}, SHIFT(134),
  [45] = {.entry = {.count = 1, .reusable = true}}, SHIFT(134),
  [47] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1),
  [49] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2),
  [51] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(171),
  [54] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(174),
  [57] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(173),
  [60] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(158),
  [63] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query, 3, .production_id = 25),
  [65] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [67] = {.entry = {.count = 1, .reusable = true}}, SHIFT(176),
  [69] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [71] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [73] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_action_declaration_repeat1, 2, .production_id = 28),
  [75] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_action_declaration_repeat1, 2, .production_id = 28), SHIFT_REPEAT(176),
  [78] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_action_declaration_repeat1, 2, .production_id = 28), SHIFT_REPEAT(68),
  [81] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_action_declaration_repeat1, 2, .production_id = 28), SHIFT_REPEAT(69),
  [84] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [86] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [88] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [90] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query, 2),
  [92] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query, 4, .production_id = 25),
  [94] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query, 5, .production_id = 43),
  [96] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_variable, 1, .production_id = 31),
  [98] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [100] = {.entry = {.count = 1, .reusable = true}}, SHIFT(167),
  [102] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_uri, 1, .production_id = 33),
  [104] = {.entry = {.count = 1, .reusable = true}}, SHIFT(138),
  [106] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_uri_repeat1, 2, .production_id = 42),
  [108] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_uri_repeat1, 2, .production_id = 42), SHIFT_REPEAT(167),
  [111] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call, 4, .production_id = 41),
  [113] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query_declaration, 6, .production_id = 18),
  [115] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 11, .production_id = 50),
  [117] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call, 5, .production_id = 41),
  [119] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_permission_declaration, 6, .production_id = 14),
  [121] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 9, .production_id = 38),
  [123] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 9, .production_id = 37),
  [125] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 9, .production_id = 29),
  [127] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_action_declaration, 8, .production_id = 36),
  [129] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 7, .production_id = 8),
  [131] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 5, .production_id = 3),
  [133] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_action_declaration, 6, .production_id = 1),
  [135] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 7, .production_id = 21),
  [137] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 7, .production_id = 23),
  [139] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_permission_declaration, 5, .production_id = 4),
  [141] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call, 3, .production_id = 32),
  [143] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call, 6, .production_id = 51),
  [145] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 10, .production_id = 38),
  [147] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 6, .production_id = 3),
  [149] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query_declaration, 5, .production_id = 4),
  [151] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 8, .production_id = 30),
  [153] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 4, .production_id = 1),
  [155] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query_declaration, 7, .production_id = 26),
  [157] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_action_declaration, 7, .production_id = 27),
  [159] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 10, .production_id = 47),
  [161] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 8, .production_id = 21),
  [163] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 8, .production_id = 29),
  [165] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 6, .production_id = 8),
  [167] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_action_declaration, 9, .production_id = 46),
  [169] = {.entry = {.count = 1, .reusable = false}}, SHIFT_EXTRA(),
  [171] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_string_literal_repeat2, 2),
  [173] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_string_literal_repeat2, 2), SHIFT_REPEAT(57),
  [176] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [178] = {.entry = {.count = 1, .reusable = true}}, SHIFT(150),
  [180] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [182] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [184] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_update_statement, 4, .production_id = 45),
  [186] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_string_literal_repeat1, 2),
  [188] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_string_literal_repeat1, 2), SHIFT_REPEAT(63),
  [191] = {.entry = {.count = 1, .reusable = false}}, SHIFT(107),
  [193] = {.entry = {.count = 1, .reusable = false}}, SHIFT(73),
  [195] = {.entry = {.count = 1, .reusable = false}}, SHIFT(75),
  [197] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_delete_statement, 3, .production_id = 35),
  [199] = {.entry = {.count = 1, .reusable = true}}, SHIFT(149),
  [201] = {.entry = {.count = 1, .reusable = true}}, SHIFT(160),
  [203] = {.entry = {.count = 1, .reusable = true}}, SHIFT(148),
  [205] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_uri_repeat1, 2, .production_id = 40),
  [207] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_action_declaration_repeat1, 1, .production_id = 20),
  [209] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [211] = {.entry = {.count = 1, .reusable = false}}, SHIFT(95),
  [213] = {.entry = {.count = 1, .reusable = false}}, SHIFT(63),
  [215] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [217] = {.entry = {.count = 1, .reusable = false}}, SHIFT(57),
  [219] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_query_declaration_repeat1, 2, .production_id = 19),
  [221] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_query_declaration_repeat1, 2, .production_id = 19), SHIFT_REPEAT(138),
  [224] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_statement, 4, .production_id = 44),
  [226] = {.entry = {.count = 1, .reusable = true}}, SHIFT(83),
  [228] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__parameters, 2, .production_id = 5),
  [230] = {.entry = {.count = 1, .reusable = true}}, SHIFT(124),
  [232] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [234] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding, 5, .production_id = 53),
  [236] = {.entry = {.count = 1, .reusable = true}}, SHIFT(98),
  [238] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [240] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_binding_repeat1, 2, .production_id = 12), SHIFT_REPEAT(131),
  [243] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_binding_repeat1, 2, .production_id = 12),
  [245] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__parameters, 3, .production_id = 5),
  [247] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__parameters_repeat1, 2, .production_id = 16), SHIFT_REPEAT(153),
  [250] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym__parameters_repeat1, 2, .production_id = 16),
  [252] = {.entry = {.count = 1, .reusable = true}}, SHIFT(168),
  [254] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [256] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding, 4, .production_id = 11),
  [258] = {.entry = {.count = 1, .reusable = true}}, SHIFT(110),
  [260] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [262] = {.entry = {.count = 1, .reusable = true}}, SHIFT(129),
  [264] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [266] = {.entry = {.count = 1, .reusable = true}}, SHIFT(85),
  [268] = {.entry = {.count = 1, .reusable = true}}, SHIFT(86),
  [270] = {.entry = {.count = 1, .reusable = true}}, SHIFT(114),
  [272] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [274] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding, 3, .production_id = 11),
  [276] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_call_repeat1, 2, .production_id = 49), SHIFT_REPEAT(5),
  [279] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_call_repeat1, 2, .production_id = 49),
  [281] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string_literal, 3),
  [283] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [285] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_type_declaration_repeat2, 2, .production_id = 12), SHIFT_REPEAT(147),
  [288] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_type_declaration_repeat2, 2, .production_id = 12),
  [290] = {.entry = {.count = 1, .reusable = true}}, SHIFT(180),
  [292] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [294] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [296] = {.entry = {.count = 1, .reusable = true}}, SHIFT(127),
  [298] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [300] = {.entry = {.count = 1, .reusable = true}}, SHIFT(142),
  [302] = {.entry = {.count = 1, .reusable = true}}, SHIFT(117),
  [304] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [306] = {.entry = {.count = 1, .reusable = true}}, SHIFT(92),
  [308] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding, 2),
  [310] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [312] = {.entry = {.count = 1, .reusable = true}}, SHIFT(119),
  [314] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__parameters, 1, .production_id = 2),
  [316] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string_literal, 2),
  [318] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_type_declaration_repeat1, 2, .production_id = 9), SHIFT_REPEAT(181),
  [321] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_type_declaration_repeat1, 2, .production_id = 9),
  [323] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_variable, 2, .production_id = 39),
  [325] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [327] = {.entry = {.count = 1, .reusable = true}}, SHIFT(88),
  [329] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [331] = {.entry = {.count = 1, .reusable = true}}, SHIFT(121),
  [333] = {.entry = {.count = 1, .reusable = true}}, SHIFT(96),
  [335] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [337] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [339] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [341] = {.entry = {.count = 1, .reusable = true}}, SHIFT(118),
  [343] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [345] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [347] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__parameters, 2, .production_id = 2),
  [349] = {.entry = {.count = 1, .reusable = true}}, SHIFT(141),
  [351] = {.entry = {.count = 1, .reusable = true}}, SHIFT(115),
  [353] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [355] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [357] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [359] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [361] = {.entry = {.count = 1, .reusable = true}}, SHIFT(45),
  [363] = {.entry = {.count = 1, .reusable = true}}, SHIFT(99),
  [365] = {.entry = {.count = 1, .reusable = true}}, SHIFT(104),
  [367] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [369] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_query_repeat1, 2, .production_id = 34), SHIFT_REPEAT(151),
  [372] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_query_repeat1, 2, .production_id = 34),
  [374] = {.entry = {.count = 1, .reusable = true}}, SHIFT(157),
  [376] = {.entry = {.count = 1, .reusable = true}}, SHIFT(175),
  [378] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_guard, 2, .production_id = 17),
  [380] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_binding_repeat1, 2, .production_id = 11),
  [382] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding_field, 3, .production_id = 52),
  [384] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_query_repeat1, 2, .production_id = 25),
  [386] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_type_declaration_repeat2, 2, .production_id = 11),
  [388] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_field, 4, .production_id = 22),
  [390] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_query_declaration_repeat1, 1, .production_id = 6),
  [392] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_type_declaration_repeat1, 2, .production_id = 7),
  [394] = {.entry = {.count = 1, .reusable = true}}, SHIFT(140),
  [396] = {.entry = {.count = 1, .reusable = true}}, SHIFT(91),
  [398] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_field, 3, .production_id = 10),
  [400] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameter, 3, .production_id = 13),
  [402] = {.entry = {.count = 1, .reusable = true}}, SHIFT(159),
  [404] = {.entry = {.count = 1, .reusable = true}}, SHIFT(101),
  [406] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_call_repeat1, 2, .production_id = 48),
  [408] = {.entry = {.count = 1, .reusable = true}}, SHIFT(172),
  [410] = {.entry = {.count = 1, .reusable = true}}, SHIFT(177),
  [412] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameter, 4, .production_id = 24),
  [414] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym__parameters_repeat1, 2, .production_id = 15),
  [416] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [418] = {.entry = {.count = 1, .reusable = true}}, SHIFT(143),
  [420] = {.entry = {.count = 1, .reusable = true}}, SHIFT(156),
  [422] = {.entry = {.count = 1, .reusable = true}}, SHIFT(102),
  [424] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [426] = {.entry = {.count = 1, .reusable = true}}, SHIFT(130),
  [428] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [430] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [432] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [434] = {.entry = {.count = 1, .reusable = true}}, SHIFT(137),
  [436] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [438] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [440] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [442] = {.entry = {.count = 1, .reusable = true}}, SHIFT(77),
  [444] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [446] = {.entry = {.count = 1, .reusable = true}}, SHIFT(145),
  [448] = {.entry = {.count = 1, .reusable = true}}, SHIFT(144),
  [450] = {.entry = {.count = 1, .reusable = true}}, SHIFT(163),
  [452] = {.entry = {.count = 1, .reusable = true}}, SHIFT(164),
  [454] = {.entry = {.count = 1, .reusable = true}}, SHIFT(165),
  [456] = {.entry = {.count = 1, .reusable = true}}, SHIFT(154),
  [458] = {.entry = {.count = 1, .reusable = true}}, SHIFT(179),
  [460] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [462] = {.entry = {.count = 1, .reusable = true}}, SHIFT(152),
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
