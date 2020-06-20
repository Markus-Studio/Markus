#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 11
#define STATE_COUNT 185
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 69
#define ALIAS_COUNT 0
#define TOKEN_COUNT 32
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 20
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
  sym_neg_flag = 10,
  anon_sym_LPAREN = 11,
  anon_sym_RPAREN = 12,
  sym_user = 13,
  anon_sym_DOT = 14,
  sym_true_literal = 15,
  sym_false_literal = 16,
  sym_numeric_literal = 17,
  anon_sym_DQUOTE = 18,
  aux_sym_string_literal_token1 = 19,
  anon_sym_SQUOTE = 20,
  aux_sym_string_literal_token2 = 21,
  sym_escape_sequence = 22,
  anon_sym_permission = 23,
  anon_sym_query = 24,
  anon_sym_allow = 25,
  anon_sym_EQ = 26,
  anon_sym_create = 27,
  anon_sym_SEMI = 28,
  anon_sym_delete = 29,
  anon_sym_update = 30,
  anon_sym_action = 31,
  sym_source_file = 32,
  sym__declaration = 33,
  sym_type_declaration = 34,
  sym_type_field = 35,
  sym__expression = 36,
  sym__primitive_expression = 37,
  sym_call = 38,
  sym_variable = 39,
  sym_uri = 40,
  sym_string_literal = 41,
  sym_query = 42,
  sym__parameters = 43,
  sym_parameter = 44,
  sym_permission_declaration = 45,
  sym_query_declaration = 46,
  sym_guard = 47,
  sym_binding = 48,
  sym_binding_field = 49,
  sym__binding_value = 50,
  sym__statement = 51,
  sym_create_statement = 52,
  sym_delete_statement = 53,
  sym_update_statement = 54,
  sym__statement_target = 55,
  sym_action_declaration = 56,
  aux_sym_source_file_repeat1 = 57,
  aux_sym_type_declaration_repeat1 = 58,
  aux_sym_type_declaration_repeat2 = 59,
  aux_sym_call_repeat1 = 60,
  aux_sym_uri_repeat1 = 61,
  aux_sym_string_literal_repeat1 = 62,
  aux_sym_string_literal_repeat2 = 63,
  aux_sym_query_repeat1 = 64,
  aux_sym__parameters_repeat1 = 65,
  aux_sym_query_declaration_repeat1 = 66,
  aux_sym_binding_repeat1 = 67,
  aux_sym_action_declaration_repeat1 = 68,
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
  [sym_neg_flag] = "neg_flag",
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
  [sym_neg_flag] = sym_neg_flag,
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
  [sym_neg_flag] = {
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
  field_not = 9,
  field_optional = 10,
  field_parameter = 11,
  field_part = 12,
  field_pipe = 13,
  field_query = 14,
  field_selection = 15,
  field_statement = 16,
  field_target = 17,
  field_type = 18,
  field_updates = 19,
  field_value = 20,
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
  [field_not] = "not",
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

static const TSFieldMapSlice ts_field_map_slices[55] = {
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
  [26] = {.index = 47, .length = 2},
  [27] = {.index = 49, .length = 4},
  [28] = {.index = 53, .length = 2},
  [29] = {.index = 55, .length = 2},
  [30] = {.index = 57, .length = 3},
  [31] = {.index = 60, .length = 3},
  [32] = {.index = 63, .length = 1},
  [33] = {.index = 64, .length = 1},
  [34] = {.index = 65, .length = 1},
  [35] = {.index = 66, .length = 2},
  [36] = {.index = 68, .length = 1},
  [37] = {.index = 69, .length = 3},
  [38] = {.index = 72, .length = 4},
  [39] = {.index = 76, .length = 4},
  [40] = {.index = 80, .length = 2},
  [41] = {.index = 82, .length = 1},
  [42] = {.index = 83, .length = 2},
  [43] = {.index = 85, .length = 2},
  [44] = {.index = 87, .length = 2},
  [45] = {.index = 89, .length = 2},
  [46] = {.index = 91, .length = 2},
  [47] = {.index = 93, .length = 4},
  [48] = {.index = 97, .length = 4},
  [49] = {.index = 101, .length = 1},
  [50] = {.index = 102, .length = 2},
  [51] = {.index = 104, .length = 5},
  [52] = {.index = 109, .length = 3},
  [53] = {.index = 112, .length = 2},
  [54] = {.index = 114, .length = 2},
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
    {field_not, 0},
    {field_selection, 2},
  [49] =
    {field_guard, 5, .inherited = true},
    {field_name, 1},
    {field_parameter, 3, .inherited = true},
    {field_query, 6},
  [53] =
    {field_name, 1},
    {field_statement, 5, .inherited = true},
  [55] =
    {field_statement, 0, .inherited = true},
    {field_statement, 1, .inherited = true},
  [57] =
    {field_base, 3},
    {field_field, 6},
    {field_name, 1},
  [60] =
    {field_base, 3},
    {field_base, 4, .inherited = true},
    {field_name, 1},
  [63] =
    {field_base, 0},
  [64] =
    {field_callee, 0},
  [65] =
    {field_part, 0, .inherited = true},
  [66] =
    {field_pipe, 0, .inherited = true},
    {field_pipe, 1, .inherited = true},
  [68] =
    {field_target, 1},
  [69] =
    {field_guard, 4, .inherited = true},
    {field_name, 1},
    {field_statement, 6, .inherited = true},
  [72] =
    {field_base, 3},
    {field_field, 5},
    {field_field, 6, .inherited = true},
    {field_name, 1},
  [76] =
    {field_base, 3},
    {field_base, 4, .inherited = true},
    {field_field, 7},
    {field_name, 1},
  [80] =
    {field_base, 0},
    {field_field, 1},
  [82] =
    {field_part, 1},
  [83] =
    {field_argument, 2},
    {field_callee, 0},
  [85] =
    {field_part, 0, .inherited = true},
    {field_part, 1, .inherited = true},
  [87] =
    {field_pipe, 1},
    {field_pipe, 2, .inherited = true},
  [89] =
    {field_binding, 2},
    {field_name, 1},
  [91] =
    {field_target, 1},
    {field_updates, 2},
  [93] =
    {field_guard, 5, .inherited = true},
    {field_name, 1},
    {field_parameter, 3, .inherited = true},
    {field_statement, 7, .inherited = true},
  [97] =
    {field_base, 3},
    {field_field, 6},
    {field_field, 7, .inherited = true},
    {field_name, 1},
  [101] =
    {field_argument, 1},
  [102] =
    {field_argument, 0, .inherited = true},
    {field_argument, 1, .inherited = true},
  [104] =
    {field_base, 3},
    {field_base, 4, .inherited = true},
    {field_field, 7},
    {field_field, 8, .inherited = true},
    {field_name, 1},
  [109] =
    {field_argument, 2},
    {field_argument, 3, .inherited = true},
    {field_callee, 0},
  [112] =
    {field_name, 0},
    {field_value, 2},
  [114] =
    {field_field, 1},
    {field_field, 2, .inherited = true},
};

static TSSymbol ts_alias_sequences[55][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(29);
      if (lookahead == '"') ADVANCE(48);
      if (lookahead == '$') ADVANCE(27);
      if (lookahead == '%') ADVANCE(16);
      if (lookahead == '\'') ADVANCE(56);
      if (lookahead == '(') ADVANCE(41);
      if (lookahead == ')') ADVANCE(42);
      if (lookahead == '+') ADVANCE(12);
      if (lookahead == ',') ADVANCE(33);
      if (lookahead == '-') ADVANCE(40);
      if (lookahead == '.') ADVANCE(44);
      if (lookahead == '/') ADVANCE(9);
      if (lookahead == ':') ADVANCE(32);
      if (lookahead == ';') ADVANCE(70);
      if (lookahead == '=') ADVANCE(69);
      if (lookahead == '?') ADVANCE(38);
      if (lookahead == '\\') ADVANCE(17);
      if (lookahead == '{') ADVANCE(34);
      if (lookahead == '}') ADVANCE(35);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 160 ||
          lookahead == 8203 ||
          lookahead == 8288 ||
          lookahead == 65279) SKIP(28)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(45);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(36);
      END_STATE();
    case 1:
      if (lookahead == '\n') SKIP(7)
      if (lookahead == '\'') ADVANCE(56);
      if (lookahead == '/') ADVANCE(58);
      if (lookahead == '\\') ADVANCE(2);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 160 ||
          lookahead == 8203 ||
          lookahead == 8288 ||
          lookahead == 65279) ADVANCE(61);
      if (lookahead != 0) ADVANCE(63);
      END_STATE();
    case 2:
      if (lookahead == '\n') ADVANCE(57);
      if (lookahead == '\r') ADVANCE(65);
      if (lookahead == 'u') ADVANCE(18);
      if (lookahead == 'x') ADVANCE(26);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(68);
      if (lookahead != 0) ADVANCE(64);
      END_STATE();
    case 3:
      if (lookahead == '\n') SKIP(6)
      if (lookahead == '"') ADVANCE(48);
      if (lookahead == '/') ADVANCE(50);
      if (lookahead == '\\') ADVANCE(4);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 160 ||
          lookahead == 8203 ||
          lookahead == 8288 ||
          lookahead == 65279) ADVANCE(53);
      if (lookahead != 0) ADVANCE(55);
      END_STATE();
    case 4:
      if (lookahead == '\n') ADVANCE(49);
      if (lookahead == '\r') ADVANCE(66);
      if (lookahead == 'u') ADVANCE(18);
      if (lookahead == 'x') ADVANCE(26);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(68);
      if (lookahead != 0) ADVANCE(64);
      END_STATE();
    case 5:
      if (lookahead == '"') ADVANCE(48);
      if (lookahead == '$') ADVANCE(27);
      if (lookahead == '%') ADVANCE(16);
      if (lookahead == '\'') ADVANCE(56);
      if (lookahead == ')') ADVANCE(42);
      if (lookahead == '.') ADVANCE(44);
      if (lookahead == '/') ADVANCE(9);
      if (lookahead == '{') ADVANCE(34);
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(12);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 160 ||
          lookahead == 8203 ||
          lookahead == 8288 ||
          lookahead == 65279) SKIP(5)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(45);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(36);
      END_STATE();
    case 6:
      if (lookahead == '"') ADVANCE(48);
      if (lookahead == '/') ADVANCE(9);
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
      if (lookahead == '\'') ADVANCE(56);
      if (lookahead == '/') ADVANCE(9);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 160 ||
          lookahead == 8203 ||
          lookahead == 8288 ||
          lookahead == 65279) SKIP(7)
      END_STATE();
    case 8:
      if (lookahead == ')') ADVANCE(42);
      if (lookahead == ',') ADVANCE(33);
      if (lookahead == '-') ADVANCE(39);
      if (lookahead == '/') ADVANCE(9);
      if (lookahead == '{') ADVANCE(34);
      if (lookahead == '}') ADVANCE(35);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 160 ||
          lookahead == 8203 ||
          lookahead == 8288 ||
          lookahead == 65279) SKIP(8)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(36);
      END_STATE();
    case 9:
      if (lookahead == '*') ADVANCE(11);
      if (lookahead == '/') ADVANCE(31);
      END_STATE();
    case 10:
      if (lookahead == '*') ADVANCE(10);
      if (lookahead == '/') ADVANCE(30);
      if (lookahead != 0) ADVANCE(11);
      END_STATE();
    case 11:
      if (lookahead == '*') ADVANCE(10);
      if (lookahead != 0) ADVANCE(11);
      END_STATE();
    case 12:
      if (lookahead == '.') ADVANCE(21);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(45);
      END_STATE();
    case 13:
      if (lookahead == 'e') ADVANCE(14);
      END_STATE();
    case 14:
      if (lookahead == 'r') ADVANCE(43);
      END_STATE();
    case 15:
      if (lookahead == 's') ADVANCE(13);
      END_STATE();
    case 16:
      if (lookahead == 'u') ADVANCE(15);
      END_STATE();
    case 17:
      if (lookahead == 'u') ADVANCE(18);
      if (lookahead == 'x') ADVANCE(26);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(68);
      if (lookahead != 0) ADVANCE(64);
      END_STATE();
    case 18:
      if (lookahead == '{') ADVANCE(25);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(23);
      END_STATE();
    case 19:
      if (lookahead == '}') ADVANCE(64);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(19);
      END_STATE();
    case 20:
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(22);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(47);
      END_STATE();
    case 21:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(46);
      END_STATE();
    case 22:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(47);
      END_STATE();
    case 23:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(26);
      END_STATE();
    case 24:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(64);
      END_STATE();
    case 25:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(19);
      END_STATE();
    case 26:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(24);
      END_STATE();
    case 27:
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(37);
      END_STATE();
    case 28:
      if (eof) ADVANCE(29);
      if (lookahead == '"') ADVANCE(48);
      if (lookahead == '$') ADVANCE(27);
      if (lookahead == '%') ADVANCE(16);
      if (lookahead == '\'') ADVANCE(56);
      if (lookahead == '(') ADVANCE(41);
      if (lookahead == ')') ADVANCE(42);
      if (lookahead == '+') ADVANCE(12);
      if (lookahead == ',') ADVANCE(33);
      if (lookahead == '-') ADVANCE(40);
      if (lookahead == '.') ADVANCE(44);
      if (lookahead == '/') ADVANCE(9);
      if (lookahead == ':') ADVANCE(32);
      if (lookahead == ';') ADVANCE(70);
      if (lookahead == '=') ADVANCE(69);
      if (lookahead == '?') ADVANCE(38);
      if (lookahead == '{') ADVANCE(34);
      if (lookahead == '}') ADVANCE(35);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 160 ||
          lookahead == 8203 ||
          lookahead == 8288 ||
          lookahead == 65279) SKIP(28)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(45);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(36);
      END_STATE();
    case 29:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 30:
      ACCEPT_TOKEN(sym_comment);
      END_STATE();
    case 31:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(31);
      END_STATE();
    case 32:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 33:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 34:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 35:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 36:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(36);
      END_STATE();
    case 37:
      ACCEPT_TOKEN(sym_parameter_name);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(37);
      END_STATE();
    case 38:
      ACCEPT_TOKEN(sym_optional_flag);
      END_STATE();
    case 39:
      ACCEPT_TOKEN(sym_neg_flag);
      END_STATE();
    case 40:
      ACCEPT_TOKEN(sym_neg_flag);
      if (lookahead == '.') ADVANCE(21);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(45);
      END_STATE();
    case 41:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(sym_user);
      END_STATE();
    case 44:
      ACCEPT_TOKEN(anon_sym_DOT);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(46);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(sym_numeric_literal);
      if (lookahead == '.') ADVANCE(21);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(20);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(45);
      END_STATE();
    case 46:
      ACCEPT_TOKEN(sym_numeric_literal);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(20);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(46);
      END_STATE();
    case 47:
      ACCEPT_TOKEN(sym_numeric_literal);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(47);
      END_STATE();
    case 48:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(aux_sym_string_literal_token1);
      END_STATE();
    case 50:
      ACCEPT_TOKEN(aux_sym_string_literal_token1);
      if (lookahead == '*') ADVANCE(52);
      if (lookahead == '/') ADVANCE(54);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(55);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(aux_sym_string_literal_token1);
      if (lookahead == '*') ADVANCE(51);
      if (lookahead == '/') ADVANCE(55);
      if (lookahead == '\n' ||
          lookahead == '"' ||
          lookahead == '\\') ADVANCE(11);
      if (lookahead != 0) ADVANCE(52);
      END_STATE();
    case 52:
      ACCEPT_TOKEN(aux_sym_string_literal_token1);
      if (lookahead == '*') ADVANCE(51);
      if (lookahead == '\n' ||
          lookahead == '"' ||
          lookahead == '\\') ADVANCE(11);
      if (lookahead != 0) ADVANCE(52);
      END_STATE();
    case 53:
      ACCEPT_TOKEN(aux_sym_string_literal_token1);
      if (lookahead == '/') ADVANCE(50);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 160 ||
          lookahead == 8203 ||
          lookahead == 8288 ||
          lookahead == 65279) ADVANCE(53);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(55);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(aux_sym_string_literal_token1);
      if (lookahead == '"' ||
          lookahead == '\\') ADVANCE(31);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(54);
      END_STATE();
    case 55:
      ACCEPT_TOKEN(aux_sym_string_literal_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(55);
      END_STATE();
    case 56:
      ACCEPT_TOKEN(anon_sym_SQUOTE);
      END_STATE();
    case 57:
      ACCEPT_TOKEN(aux_sym_string_literal_token2);
      END_STATE();
    case 58:
      ACCEPT_TOKEN(aux_sym_string_literal_token2);
      if (lookahead == '*') ADVANCE(60);
      if (lookahead == '/') ADVANCE(62);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(63);
      END_STATE();
    case 59:
      ACCEPT_TOKEN(aux_sym_string_literal_token2);
      if (lookahead == '*') ADVANCE(59);
      if (lookahead == '/') ADVANCE(63);
      if (lookahead == '\n' ||
          lookahead == '\'' ||
          lookahead == '\\') ADVANCE(11);
      if (lookahead != 0) ADVANCE(60);
      END_STATE();
    case 60:
      ACCEPT_TOKEN(aux_sym_string_literal_token2);
      if (lookahead == '*') ADVANCE(59);
      if (lookahead == '\n' ||
          lookahead == '\'' ||
          lookahead == '\\') ADVANCE(11);
      if (lookahead != 0) ADVANCE(60);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(aux_sym_string_literal_token2);
      if (lookahead == '/') ADVANCE(58);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ' ||
          lookahead == 160 ||
          lookahead == 8203 ||
          lookahead == 8288 ||
          lookahead == 65279) ADVANCE(61);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(63);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(aux_sym_string_literal_token2);
      if (lookahead == '\'' ||
          lookahead == '\\') ADVANCE(31);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(62);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(aux_sym_string_literal_token2);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '\'' &&
          lookahead != '\\') ADVANCE(63);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(sym_escape_sequence);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(sym_escape_sequence);
      if (lookahead == '\n') ADVANCE(57);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(sym_escape_sequence);
      if (lookahead == '\n') ADVANCE(49);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(sym_escape_sequence);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(64);
      END_STATE();
    case 68:
      ACCEPT_TOKEN(sym_escape_sequence);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(67);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 70:
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
  [2] = {.lex_state = 5},
  [3] = {.lex_state = 5},
  [4] = {.lex_state = 5},
  [5] = {.lex_state = 5},
  [6] = {.lex_state = 5},
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
  [21] = {.lex_state = 8},
  [22] = {.lex_state = 8},
  [23] = {.lex_state = 8},
  [24] = {.lex_state = 8},
  [25] = {.lex_state = 8},
  [26] = {.lex_state = 8},
  [27] = {.lex_state = 8},
  [28] = {.lex_state = 0},
  [29] = {.lex_state = 8},
  [30] = {.lex_state = 0},
  [31] = {.lex_state = 8},
  [32] = {.lex_state = 0},
  [33] = {.lex_state = 0},
  [34] = {.lex_state = 0},
  [35] = {.lex_state = 0},
  [36] = {.lex_state = 0},
  [37] = {.lex_state = 0},
  [38] = {.lex_state = 0},
  [39] = {.lex_state = 8},
  [40] = {.lex_state = 0},
  [41] = {.lex_state = 0},
  [42] = {.lex_state = 0},
  [43] = {.lex_state = 8},
  [44] = {.lex_state = 0},
  [45] = {.lex_state = 0},
  [46] = {.lex_state = 0},
  [47] = {.lex_state = 0},
  [48] = {.lex_state = 0},
  [49] = {.lex_state = 0},
  [50] = {.lex_state = 0},
  [51] = {.lex_state = 0},
  [52] = {.lex_state = 8},
  [53] = {.lex_state = 0},
  [54] = {.lex_state = 0},
  [55] = {.lex_state = 0},
  [56] = {.lex_state = 8},
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
  [68] = {.lex_state = 1},
  [69] = {.lex_state = 3},
  [70] = {.lex_state = 0},
  [71] = {.lex_state = 3},
  [72] = {.lex_state = 0},
  [73] = {.lex_state = 0},
  [74] = {.lex_state = 3},
  [75] = {.lex_state = 1},
  [76] = {.lex_state = 1},
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
  [87] = {.lex_state = 8},
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
  [104] = {.lex_state = 8},
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
  [116] = {.lex_state = 8},
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
  [182] = {.lex_state = 0},
  [183] = {.lex_state = 0},
  [184] = {.lex_state = 0},
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
    [sym_neg_flag] = ACTIONS(1),
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
    [sym_source_file] = STATE(159),
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
    STATE(38), 1,
      aux_sym_uri_repeat1,
    ACTIONS(19), 2,
      sym_parameter_name,
      sym_user,
    ACTIONS(25), 2,
      sym_true_literal,
      sym_false_literal,
    STATE(148), 7,
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
    STATE(38), 1,
      aux_sym_uri_repeat1,
    ACTIONS(19), 2,
      sym_parameter_name,
      sym_user,
    ACTIONS(35), 2,
      sym_true_literal,
      sym_false_literal,
    STATE(126), 7,
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
    ACTIONS(27), 1,
      sym_numeric_literal,
    ACTIONS(29), 1,
      anon_sym_DQUOTE,
    ACTIONS(31), 1,
      anon_sym_SQUOTE,
    ACTIONS(39), 1,
      anon_sym_RPAREN,
    STATE(38), 1,
      aux_sym_uri_repeat1,
    ACTIONS(19), 2,
      sym_parameter_name,
      sym_user,
    ACTIONS(25), 2,
      sym_true_literal,
      sym_false_literal,
    STATE(148), 7,
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
    ACTIONS(27), 1,
      sym_numeric_literal,
    ACTIONS(29), 1,
      anon_sym_DQUOTE,
    ACTIONS(31), 1,
      anon_sym_SQUOTE,
    STATE(38), 1,
      aux_sym_uri_repeat1,
    ACTIONS(19), 2,
      sym_parameter_name,
      sym_user,
    ACTIONS(25), 2,
      sym_true_literal,
      sym_false_literal,
    STATE(148), 7,
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
    STATE(38), 1,
      aux_sym_uri_repeat1,
    ACTIONS(19), 2,
      sym_parameter_name,
      sym_user,
    ACTIONS(43), 2,
      sym_true_literal,
      sym_false_literal,
    STATE(139), 7,
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
  [273] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(63), 1,
      anon_sym_RBRACE,
    ACTIONS(65), 1,
      anon_sym_create,
    ACTIONS(67), 1,
      anon_sym_delete,
    ACTIONS(69), 1,
      anon_sym_update,
    STATE(19), 1,
      aux_sym_action_declaration_repeat1,
    STATE(73), 4,
      sym__statement,
      sym_create_statement,
      sym_delete_statement,
      sym_update_statement,
  [298] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(65), 1,
      anon_sym_create,
    ACTIONS(67), 1,
      anon_sym_delete,
    ACTIONS(69), 1,
      anon_sym_update,
    ACTIONS(71), 1,
      anon_sym_RBRACE,
    STATE(13), 1,
      aux_sym_action_declaration_repeat1,
    STATE(73), 4,
      sym__statement,
      sym_create_statement,
      sym_delete_statement,
      sym_update_statement,
  [323] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(73), 9,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_COMMA,
      anon_sym_LBRACE,
      anon_sym_RPAREN,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_SEMI,
      anon_sym_action,
  [338] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(75), 9,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_COMMA,
      anon_sym_LBRACE,
      anon_sym_RPAREN,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_SEMI,
      anon_sym_action,
  [353] = 7,
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
    STATE(13), 1,
      aux_sym_action_declaration_repeat1,
    STATE(73), 4,
      sym__statement,
      sym_create_statement,
      sym_delete_statement,
      sym_update_statement,
  [378] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(63), 1,
      anon_sym_RBRACE,
    ACTIONS(65), 1,
      anon_sym_create,
    ACTIONS(67), 1,
      anon_sym_delete,
    ACTIONS(69), 1,
      anon_sym_update,
    STATE(13), 1,
      aux_sym_action_declaration_repeat1,
    STATE(73), 4,
      sym__statement,
      sym_create_statement,
      sym_delete_statement,
      sym_update_statement,
  [403] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(88), 9,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_COMMA,
      anon_sym_LBRACE,
      anon_sym_RPAREN,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_SEMI,
      anon_sym_action,
  [418] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(65), 1,
      anon_sym_create,
    ACTIONS(67), 1,
      anon_sym_delete,
    ACTIONS(69), 1,
      anon_sym_update,
    ACTIONS(90), 1,
      anon_sym_RBRACE,
    STATE(10), 1,
      aux_sym_action_declaration_repeat1,
    STATE(73), 4,
      sym__statement,
      sym_create_statement,
      sym_delete_statement,
      sym_update_statement,
  [443] = 2,
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
  [458] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(65), 1,
      anon_sym_create,
    ACTIONS(67), 1,
      anon_sym_delete,
    ACTIONS(69), 1,
      anon_sym_update,
    ACTIONS(71), 1,
      anon_sym_RBRACE,
    STATE(14), 1,
      aux_sym_action_declaration_repeat1,
    STATE(73), 4,
      sym__statement,
      sym_create_statement,
      sym_delete_statement,
      sym_update_statement,
  [483] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(65), 1,
      anon_sym_create,
    ACTIONS(67), 1,
      anon_sym_delete,
    ACTIONS(69), 1,
      anon_sym_update,
    ACTIONS(94), 1,
      anon_sym_RBRACE,
    STATE(13), 1,
      aux_sym_action_declaration_repeat1,
    STATE(73), 4,
      sym__statement,
      sym_create_statement,
      sym_delete_statement,
      sym_update_statement,
  [508] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(98), 1,
      anon_sym_LPAREN,
    ACTIONS(100), 1,
      anon_sym_DOT,
    STATE(38), 1,
      aux_sym_uri_repeat1,
    STATE(110), 1,
      sym_uri,
    ACTIONS(96), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
  [529] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    ACTIONS(102), 1,
      sym_neg_flag,
    ACTIONS(104), 1,
      anon_sym_allow,
    STATE(56), 1,
      aux_sym_query_declaration_repeat1,
    STATE(59), 1,
      sym_query,
    STATE(116), 1,
      sym_guard,
  [551] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(106), 6,
      anon_sym_COMMA,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      sym_neg_flag,
      anon_sym_RPAREN,
      anon_sym_allow,
  [563] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(108), 6,
      anon_sym_COMMA,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      sym_neg_flag,
      anon_sym_RPAREN,
      anon_sym_allow,
  [575] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    ACTIONS(102), 1,
      sym_neg_flag,
    ACTIONS(104), 1,
      anon_sym_allow,
    STATE(21), 1,
      aux_sym_query_declaration_repeat1,
    STATE(36), 1,
      sym_query,
    STATE(116), 1,
      sym_guard,
  [597] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    ACTIONS(102), 1,
      sym_neg_flag,
    ACTIONS(104), 1,
      anon_sym_allow,
    STATE(36), 1,
      sym_query,
    STATE(56), 1,
      aux_sym_query_declaration_repeat1,
    STATE(116), 1,
      sym_guard,
  [619] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(110), 6,
      anon_sym_COMMA,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      sym_neg_flag,
      anon_sym_RPAREN,
      anon_sym_allow,
  [631] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    ACTIONS(102), 1,
      sym_neg_flag,
    ACTIONS(104), 1,
      anon_sym_allow,
    STATE(25), 1,
      aux_sym_query_declaration_repeat1,
    STATE(47), 1,
      sym_query,
    STATE(116), 1,
      sym_guard,
  [653] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(100), 1,
      anon_sym_DOT,
    STATE(38), 1,
      aux_sym_uri_repeat1,
    STATE(110), 1,
      sym_uri,
    ACTIONS(96), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
  [671] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(112), 6,
      anon_sym_COMMA,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      sym_neg_flag,
      anon_sym_RPAREN,
      anon_sym_allow,
  [683] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(114), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [694] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(102), 1,
      sym_neg_flag,
    ACTIONS(104), 1,
      anon_sym_allow,
    ACTIONS(116), 1,
      anon_sym_LBRACE,
    STATE(39), 1,
      aux_sym_query_declaration_repeat1,
    STATE(116), 1,
      sym_guard,
  [713] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(118), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [724] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(120), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [735] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(122), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [746] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(124), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [757] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(126), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [768] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(128), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [779] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(100), 1,
      anon_sym_DOT,
    STATE(50), 1,
      aux_sym_uri_repeat1,
    ACTIONS(130), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
  [794] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(102), 1,
      sym_neg_flag,
    ACTIONS(104), 1,
      anon_sym_allow,
    ACTIONS(132), 1,
      anon_sym_LBRACE,
    STATE(56), 1,
      aux_sym_query_declaration_repeat1,
    STATE(116), 1,
      sym_guard,
  [813] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(134), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [824] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(136), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [835] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(138), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [846] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(102), 1,
      sym_neg_flag,
    ACTIONS(104), 1,
      anon_sym_allow,
    ACTIONS(140), 1,
      anon_sym_LBRACE,
    STATE(52), 1,
      aux_sym_query_declaration_repeat1,
    STATE(116), 1,
      sym_guard,
  [865] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(142), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [876] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(144), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [887] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(146), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [898] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(148), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [909] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(150), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [920] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(152), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [931] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(156), 1,
      anon_sym_DOT,
    STATE(50), 1,
      aux_sym_uri_repeat1,
    ACTIONS(154), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
  [946] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(159), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [957] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(102), 1,
      sym_neg_flag,
    ACTIONS(104), 1,
      anon_sym_allow,
    ACTIONS(116), 1,
      anon_sym_LBRACE,
    STATE(56), 1,
      aux_sym_query_declaration_repeat1,
    STATE(116), 1,
      sym_guard,
  [976] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(161), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [987] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(163), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [998] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(165), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [1009] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(167), 1,
      anon_sym_LBRACE,
    ACTIONS(169), 1,
      sym_neg_flag,
    ACTIONS(172), 1,
      anon_sym_allow,
    STATE(56), 1,
      aux_sym_query_declaration_repeat1,
    STATE(116), 1,
      sym_guard,
  [1028] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(175), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [1039] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(177), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [1050] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(179), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [1061] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(181), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [1072] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(183), 5,
      ts_builtin_sym_end,
      anon_sym_type,
      anon_sym_permission,
      anon_sym_query,
      anon_sym_action,
  [1083] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(185), 1,
      sym_parameter_name,
    ACTIONS(187), 1,
      anon_sym_RPAREN,
    STATE(107), 1,
      sym_parameter,
    STATE(164), 1,
      sym__parameters,
  [1099] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(185), 1,
      sym_parameter_name,
    ACTIONS(189), 1,
      anon_sym_RPAREN,
    STATE(107), 1,
      sym_parameter,
    STATE(169), 1,
      sym__parameters,
  [1115] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(185), 1,
      sym_parameter_name,
    ACTIONS(191), 1,
      anon_sym_RPAREN,
    STATE(107), 1,
      sym_parameter,
    STATE(170), 1,
      sym__parameters,
  [1131] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(193), 4,
      anon_sym_RBRACE,
      anon_sym_create,
      anon_sym_delete,
      anon_sym_update,
  [1141] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(195), 4,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
      anon_sym_DOT,
  [1151] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(197), 4,
      anon_sym_RBRACE,
      anon_sym_create,
      anon_sym_delete,
      anon_sym_update,
  [1161] = 4,
    ACTIONS(199), 1,
      sym_comment,
    ACTIONS(201), 1,
      anon_sym_SQUOTE,
    STATE(75), 1,
      aux_sym_string_literal_repeat2,
    ACTIONS(203), 2,
      aux_sym_string_literal_token2,
      sym_escape_sequence,
  [1175] = 4,
    ACTIONS(199), 1,
      sym_comment,
    ACTIONS(201), 1,
      anon_sym_DQUOTE,
    STATE(74), 1,
      aux_sym_string_literal_repeat1,
    ACTIONS(205), 2,
      aux_sym_string_literal_token1,
      sym_escape_sequence,
  [1189] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    ACTIONS(207), 1,
      sym_parameter_name,
    STATE(168), 2,
      sym_query,
      sym__statement_target,
  [1203] = 4,
    ACTIONS(199), 1,
      sym_comment,
    ACTIONS(209), 1,
      anon_sym_DQUOTE,
    STATE(69), 1,
      aux_sym_string_literal_repeat1,
    ACTIONS(211), 2,
      aux_sym_string_literal_token1,
      sym_escape_sequence,
  [1217] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    ACTIONS(213), 1,
      sym_parameter_name,
    STATE(146), 2,
      sym_query,
      sym__statement_target,
  [1231] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(215), 4,
      anon_sym_RBRACE,
      anon_sym_create,
      anon_sym_delete,
      anon_sym_update,
  [1241] = 4,
    ACTIONS(199), 1,
      sym_comment,
    ACTIONS(217), 1,
      anon_sym_DQUOTE,
    STATE(74), 1,
      aux_sym_string_literal_repeat1,
    ACTIONS(219), 2,
      aux_sym_string_literal_token1,
      sym_escape_sequence,
  [1255] = 4,
    ACTIONS(199), 1,
      sym_comment,
    ACTIONS(222), 1,
      anon_sym_SQUOTE,
    STATE(75), 1,
      aux_sym_string_literal_repeat2,
    ACTIONS(224), 2,
      aux_sym_string_literal_token2,
      sym_escape_sequence,
  [1269] = 4,
    ACTIONS(199), 1,
      sym_comment,
    ACTIONS(209), 1,
      anon_sym_SQUOTE,
    STATE(68), 1,
      aux_sym_string_literal_repeat2,
    ACTIONS(227), 2,
      aux_sym_string_literal_token2,
      sym_escape_sequence,
  [1283] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(229), 4,
      anon_sym_RBRACE,
      anon_sym_create,
      anon_sym_delete,
      anon_sym_update,
  [1293] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(231), 1,
      anon_sym_COMMA,
    ACTIONS(233), 1,
      anon_sym_RBRACE,
    STATE(92), 1,
      aux_sym_type_declaration_repeat2,
  [1306] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(235), 1,
      anon_sym_COMMA,
    ACTIONS(237), 1,
      anon_sym_RBRACE,
    STATE(128), 1,
      aux_sym_type_declaration_repeat2,
  [1319] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(239), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_SEMI,
  [1328] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(241), 1,
      anon_sym_COMMA,
    ACTIONS(244), 1,
      anon_sym_RBRACE,
    STATE(81), 1,
      aux_sym_binding_repeat1,
  [1341] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(246), 1,
      anon_sym_COMMA,
    ACTIONS(248), 1,
      anon_sym_RBRACE,
    STATE(102), 1,
      aux_sym_query_repeat1,
  [1354] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(250), 1,
      sym_identifier,
    ACTIONS(252), 1,
      anon_sym_RBRACE,
    STATE(137), 1,
      sym_binding_field,
  [1367] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(185), 1,
      sym_parameter_name,
    ACTIONS(254), 1,
      anon_sym_RPAREN,
    STATE(136), 1,
      sym_parameter,
  [1380] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(256), 1,
      anon_sym_COMMA,
    ACTIONS(259), 1,
      anon_sym_RPAREN,
    STATE(85), 1,
      aux_sym__parameters_repeat1,
  [1393] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(261), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_SEMI,
  [1402] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(263), 3,
      anon_sym_LBRACE,
      sym_neg_flag,
      anon_sym_allow,
  [1411] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(265), 1,
      anon_sym_COMMA,
    ACTIONS(267), 1,
      anon_sym_RBRACE,
    STATE(81), 1,
      aux_sym_binding_repeat1,
  [1424] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(269), 1,
      anon_sym_COMMA,
    ACTIONS(271), 1,
      anon_sym_RBRACE,
    STATE(115), 1,
      aux_sym_type_declaration_repeat2,
  [1437] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(233), 1,
      anon_sym_RBRACE,
    ACTIONS(273), 1,
      sym_identifier,
    STATE(156), 1,
      sym_type_field,
  [1450] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(275), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_SEMI,
  [1459] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(277), 1,
      anon_sym_COMMA,
    ACTIONS(280), 1,
      anon_sym_RBRACE,
    STATE(92), 1,
      aux_sym_type_declaration_repeat2,
  [1472] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(273), 1,
      sym_identifier,
    ACTIONS(282), 1,
      anon_sym_RBRACE,
    STATE(119), 1,
      sym_type_field,
  [1485] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(250), 1,
      sym_identifier,
    ACTIONS(267), 1,
      anon_sym_RBRACE,
    STATE(137), 1,
      sym_binding_field,
  [1498] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(284), 1,
      anon_sym_COMMA,
    ACTIONS(287), 1,
      anon_sym_RPAREN,
    STATE(95), 1,
      aux_sym_call_repeat1,
  [1511] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(273), 1,
      sym_identifier,
    ACTIONS(289), 1,
      anon_sym_RBRACE,
    STATE(156), 1,
      sym_type_field,
  [1524] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(291), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
  [1533] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(273), 1,
      sym_identifier,
    ACTIONS(293), 1,
      anon_sym_RBRACE,
    STATE(156), 1,
      sym_type_field,
  [1546] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(273), 1,
      sym_identifier,
    ACTIONS(295), 1,
      anon_sym_RBRACE,
    STATE(79), 1,
      sym_type_field,
  [1559] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(297), 1,
      sym_identifier,
    ACTIONS(299), 1,
      anon_sym_RBRACE,
    STATE(135), 1,
      sym_call,
  [1572] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(301), 1,
      anon_sym_COMMA,
    ACTIONS(303), 1,
      anon_sym_LBRACE,
    STATE(123), 1,
      aux_sym_type_declaration_repeat1,
  [1585] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(299), 1,
      anon_sym_RBRACE,
    ACTIONS(305), 1,
      anon_sym_COMMA,
    STATE(131), 1,
      aux_sym_query_repeat1,
  [1598] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(307), 1,
      anon_sym_COMMA,
    ACTIONS(309), 1,
      anon_sym_RBRACE,
    STATE(88), 1,
      aux_sym_binding_repeat1,
  [1611] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(311), 3,
      anon_sym_LBRACE,
      sym_neg_flag,
      anon_sym_allow,
  [1620] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(313), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_SEMI,
  [1629] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(21), 1,
      anon_sym_RPAREN,
    ACTIONS(315), 1,
      anon_sym_COMMA,
    STATE(95), 1,
      aux_sym_call_repeat1,
  [1642] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(317), 1,
      anon_sym_COMMA,
    ACTIONS(319), 1,
      anon_sym_RPAREN,
    STATE(121), 1,
      aux_sym__parameters_repeat1,
  [1655] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(321), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
  [1664] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(323), 1,
      anon_sym_COMMA,
    ACTIONS(326), 1,
      anon_sym_LBRACE,
    STATE(109), 1,
      aux_sym_type_declaration_repeat1,
  [1677] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(328), 3,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_RPAREN,
  [1686] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(330), 1,
      anon_sym_COMMA,
    ACTIONS(332), 1,
      anon_sym_RBRACE,
    STATE(78), 1,
      aux_sym_type_declaration_repeat2,
  [1699] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(334), 1,
      anon_sym_COMMA,
    ACTIONS(336), 1,
      anon_sym_RBRACE,
    STATE(92), 1,
      aux_sym_type_declaration_repeat2,
  [1712] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(273), 1,
      sym_identifier,
    ACTIONS(338), 1,
      anon_sym_RBRACE,
    STATE(156), 1,
      sym_type_field,
  [1725] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(273), 1,
      sym_identifier,
    ACTIONS(340), 1,
      anon_sym_RBRACE,
    STATE(89), 1,
      sym_type_field,
  [1738] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(338), 1,
      anon_sym_RBRACE,
    ACTIONS(342), 1,
      anon_sym_COMMA,
    STATE(92), 1,
      aux_sym_type_declaration_repeat2,
  [1751] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(344), 3,
      anon_sym_LBRACE,
      sym_neg_flag,
      anon_sym_allow,
  [1760] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(273), 1,
      sym_identifier,
    ACTIONS(346), 1,
      anon_sym_RBRACE,
    STATE(156), 1,
      sym_type_field,
  [1773] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(273), 1,
      sym_identifier,
    ACTIONS(348), 1,
      anon_sym_RBRACE,
    STATE(111), 1,
      sym_type_field,
  [1786] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(350), 1,
      anon_sym_COMMA,
    ACTIONS(352), 1,
      anon_sym_RBRACE,
    STATE(112), 1,
      aux_sym_type_declaration_repeat2,
  [1799] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(273), 1,
      sym_identifier,
    ACTIONS(336), 1,
      anon_sym_RBRACE,
    STATE(156), 1,
      sym_type_field,
  [1812] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(354), 1,
      anon_sym_COMMA,
    ACTIONS(356), 1,
      anon_sym_RPAREN,
    STATE(85), 1,
      aux_sym__parameters_repeat1,
  [1825] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(185), 1,
      sym_parameter_name,
    ACTIONS(358), 1,
      anon_sym_RPAREN,
    STATE(136), 1,
      sym_parameter,
  [1838] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(360), 1,
      anon_sym_COMMA,
    ACTIONS(362), 1,
      anon_sym_LBRACE,
    STATE(109), 1,
      aux_sym_type_declaration_repeat1,
  [1851] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(273), 1,
      sym_identifier,
    ACTIONS(364), 1,
      anon_sym_RBRACE,
    STATE(156), 1,
      sym_type_field,
  [1864] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(297), 1,
      sym_identifier,
    ACTIONS(366), 1,
      anon_sym_RBRACE,
    STATE(82), 1,
      sym_call,
  [1877] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(368), 1,
      anon_sym_COMMA,
    ACTIONS(370), 1,
      anon_sym_RPAREN,
    STATE(106), 1,
      aux_sym_call_repeat1,
  [1890] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(273), 1,
      sym_identifier,
    ACTIONS(372), 1,
      anon_sym_RBRACE,
    STATE(156), 1,
      sym_type_field,
  [1903] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(372), 1,
      anon_sym_RBRACE,
    ACTIONS(374), 1,
      anon_sym_COMMA,
    STATE(92), 1,
      aux_sym_type_declaration_repeat2,
  [1916] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(250), 1,
      sym_identifier,
    ACTIONS(376), 1,
      anon_sym_RBRACE,
    STATE(103), 1,
      sym_binding_field,
  [1929] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(297), 1,
      sym_identifier,
    ACTIONS(378), 1,
      anon_sym_RBRACE,
    STATE(135), 1,
      sym_call,
  [1942] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(380), 1,
      anon_sym_COMMA,
    ACTIONS(383), 1,
      anon_sym_RBRACE,
    STATE(131), 1,
      aux_sym_query_repeat1,
  [1955] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(385), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [1963] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    STATE(40), 1,
      sym_query,
  [1973] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(250), 1,
      sym_identifier,
    STATE(137), 1,
      sym_binding_field,
  [1983] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(387), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [1991] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(389), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [1999] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(391), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [2007] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(297), 1,
      sym_identifier,
    STATE(104), 1,
      sym_call,
  [2017] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(393), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [2025] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(395), 1,
      anon_sym_COLON,
    ACTIONS(397), 1,
      sym_optional_flag,
  [2035] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(399), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [2043] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(297), 1,
      sym_identifier,
    STATE(87), 1,
      sym_call,
  [2053] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(401), 2,
      anon_sym_COMMA,
      anon_sym_LBRACE,
  [2061] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(403), 1,
      sym_identifier,
    ACTIONS(405), 1,
      anon_sym_LBRACE,
  [2071] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(362), 1,
      anon_sym_LBRACE,
    ACTIONS(403), 1,
      sym_identifier,
  [2081] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(41), 1,
      anon_sym_LBRACE,
    STATE(184), 1,
      sym_binding,
  [2091] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(407), 1,
      anon_sym_COLON,
    ACTIONS(409), 1,
      anon_sym_LBRACE,
  [2101] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(411), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [2109] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(273), 1,
      sym_identifier,
    STATE(156), 1,
      sym_type_field,
  [2119] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(413), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [2127] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(41), 1,
      anon_sym_LBRACE,
    STATE(161), 1,
      sym_binding,
  [2137] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    STATE(41), 1,
      sym_query,
  [2147] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(415), 1,
      anon_sym_COLON,
    ACTIONS(417), 1,
      sym_optional_flag,
  [2157] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(297), 1,
      sym_identifier,
    STATE(135), 1,
      sym_call,
  [2167] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(419), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [2175] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(421), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [2183] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(185), 1,
      sym_parameter_name,
    STATE(136), 1,
      sym_parameter,
  [2193] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(98), 1,
      anon_sym_LPAREN,
  [2200] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(423), 1,
      ts_builtin_sym_end,
  [2207] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(425), 1,
      sym_identifier,
  [2214] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(427), 1,
      anon_sym_SEMI,
  [2221] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(429), 1,
      sym_identifier,
  [2228] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(431), 1,
      anon_sym_EQ,
  [2235] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(433), 1,
      anon_sym_RPAREN,
  [2242] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(435), 1,
      anon_sym_LPAREN,
  [2249] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(437), 1,
      anon_sym_LPAREN,
  [2256] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(439), 1,
      anon_sym_LPAREN,
  [2263] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(441), 1,
      anon_sym_SEMI,
  [2270] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(443), 1,
      anon_sym_RPAREN,
  [2277] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(445), 1,
      anon_sym_RPAREN,
  [2284] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(447), 1,
      sym_identifier,
  [2291] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(403), 1,
      sym_identifier,
  [2298] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(449), 1,
      sym_identifier,
  [2305] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(451), 1,
      sym_identifier,
  [2312] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(453), 1,
      anon_sym_allow,
  [2319] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(455), 1,
      sym_identifier,
  [2326] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(457), 1,
      sym_identifier,
  [2333] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(459), 1,
      sym_identifier,
  [2340] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(461), 1,
      sym_identifier,
  [2347] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(463), 1,
      sym_identifier,
  [2354] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(465), 1,
      anon_sym_COLON,
  [2361] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(467), 1,
      anon_sym_COLON,
  [2368] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(469), 1,
      sym_identifier,
  [2375] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(471), 1,
      anon_sym_SEMI,
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
  [SMALL_STATE(10)] = 298,
  [SMALL_STATE(11)] = 323,
  [SMALL_STATE(12)] = 338,
  [SMALL_STATE(13)] = 353,
  [SMALL_STATE(14)] = 378,
  [SMALL_STATE(15)] = 403,
  [SMALL_STATE(16)] = 418,
  [SMALL_STATE(17)] = 443,
  [SMALL_STATE(18)] = 458,
  [SMALL_STATE(19)] = 483,
  [SMALL_STATE(20)] = 508,
  [SMALL_STATE(21)] = 529,
  [SMALL_STATE(22)] = 551,
  [SMALL_STATE(23)] = 563,
  [SMALL_STATE(24)] = 575,
  [SMALL_STATE(25)] = 597,
  [SMALL_STATE(26)] = 619,
  [SMALL_STATE(27)] = 631,
  [SMALL_STATE(28)] = 653,
  [SMALL_STATE(29)] = 671,
  [SMALL_STATE(30)] = 683,
  [SMALL_STATE(31)] = 694,
  [SMALL_STATE(32)] = 713,
  [SMALL_STATE(33)] = 724,
  [SMALL_STATE(34)] = 735,
  [SMALL_STATE(35)] = 746,
  [SMALL_STATE(36)] = 757,
  [SMALL_STATE(37)] = 768,
  [SMALL_STATE(38)] = 779,
  [SMALL_STATE(39)] = 794,
  [SMALL_STATE(40)] = 813,
  [SMALL_STATE(41)] = 824,
  [SMALL_STATE(42)] = 835,
  [SMALL_STATE(43)] = 846,
  [SMALL_STATE(44)] = 865,
  [SMALL_STATE(45)] = 876,
  [SMALL_STATE(46)] = 887,
  [SMALL_STATE(47)] = 898,
  [SMALL_STATE(48)] = 909,
  [SMALL_STATE(49)] = 920,
  [SMALL_STATE(50)] = 931,
  [SMALL_STATE(51)] = 946,
  [SMALL_STATE(52)] = 957,
  [SMALL_STATE(53)] = 976,
  [SMALL_STATE(54)] = 987,
  [SMALL_STATE(55)] = 998,
  [SMALL_STATE(56)] = 1009,
  [SMALL_STATE(57)] = 1028,
  [SMALL_STATE(58)] = 1039,
  [SMALL_STATE(59)] = 1050,
  [SMALL_STATE(60)] = 1061,
  [SMALL_STATE(61)] = 1072,
  [SMALL_STATE(62)] = 1083,
  [SMALL_STATE(63)] = 1099,
  [SMALL_STATE(64)] = 1115,
  [SMALL_STATE(65)] = 1131,
  [SMALL_STATE(66)] = 1141,
  [SMALL_STATE(67)] = 1151,
  [SMALL_STATE(68)] = 1161,
  [SMALL_STATE(69)] = 1175,
  [SMALL_STATE(70)] = 1189,
  [SMALL_STATE(71)] = 1203,
  [SMALL_STATE(72)] = 1217,
  [SMALL_STATE(73)] = 1231,
  [SMALL_STATE(74)] = 1241,
  [SMALL_STATE(75)] = 1255,
  [SMALL_STATE(76)] = 1269,
  [SMALL_STATE(77)] = 1283,
  [SMALL_STATE(78)] = 1293,
  [SMALL_STATE(79)] = 1306,
  [SMALL_STATE(80)] = 1319,
  [SMALL_STATE(81)] = 1328,
  [SMALL_STATE(82)] = 1341,
  [SMALL_STATE(83)] = 1354,
  [SMALL_STATE(84)] = 1367,
  [SMALL_STATE(85)] = 1380,
  [SMALL_STATE(86)] = 1393,
  [SMALL_STATE(87)] = 1402,
  [SMALL_STATE(88)] = 1411,
  [SMALL_STATE(89)] = 1424,
  [SMALL_STATE(90)] = 1437,
  [SMALL_STATE(91)] = 1450,
  [SMALL_STATE(92)] = 1459,
  [SMALL_STATE(93)] = 1472,
  [SMALL_STATE(94)] = 1485,
  [SMALL_STATE(95)] = 1498,
  [SMALL_STATE(96)] = 1511,
  [SMALL_STATE(97)] = 1524,
  [SMALL_STATE(98)] = 1533,
  [SMALL_STATE(99)] = 1546,
  [SMALL_STATE(100)] = 1559,
  [SMALL_STATE(101)] = 1572,
  [SMALL_STATE(102)] = 1585,
  [SMALL_STATE(103)] = 1598,
  [SMALL_STATE(104)] = 1611,
  [SMALL_STATE(105)] = 1620,
  [SMALL_STATE(106)] = 1629,
  [SMALL_STATE(107)] = 1642,
  [SMALL_STATE(108)] = 1655,
  [SMALL_STATE(109)] = 1664,
  [SMALL_STATE(110)] = 1677,
  [SMALL_STATE(111)] = 1686,
  [SMALL_STATE(112)] = 1699,
  [SMALL_STATE(113)] = 1712,
  [SMALL_STATE(114)] = 1725,
  [SMALL_STATE(115)] = 1738,
  [SMALL_STATE(116)] = 1751,
  [SMALL_STATE(117)] = 1760,
  [SMALL_STATE(118)] = 1773,
  [SMALL_STATE(119)] = 1786,
  [SMALL_STATE(120)] = 1799,
  [SMALL_STATE(121)] = 1812,
  [SMALL_STATE(122)] = 1825,
  [SMALL_STATE(123)] = 1838,
  [SMALL_STATE(124)] = 1851,
  [SMALL_STATE(125)] = 1864,
  [SMALL_STATE(126)] = 1877,
  [SMALL_STATE(127)] = 1890,
  [SMALL_STATE(128)] = 1903,
  [SMALL_STATE(129)] = 1916,
  [SMALL_STATE(130)] = 1929,
  [SMALL_STATE(131)] = 1942,
  [SMALL_STATE(132)] = 1955,
  [SMALL_STATE(133)] = 1963,
  [SMALL_STATE(134)] = 1973,
  [SMALL_STATE(135)] = 1983,
  [SMALL_STATE(136)] = 1991,
  [SMALL_STATE(137)] = 1999,
  [SMALL_STATE(138)] = 2007,
  [SMALL_STATE(139)] = 2017,
  [SMALL_STATE(140)] = 2025,
  [SMALL_STATE(141)] = 2035,
  [SMALL_STATE(142)] = 2043,
  [SMALL_STATE(143)] = 2053,
  [SMALL_STATE(144)] = 2061,
  [SMALL_STATE(145)] = 2071,
  [SMALL_STATE(146)] = 2081,
  [SMALL_STATE(147)] = 2091,
  [SMALL_STATE(148)] = 2101,
  [SMALL_STATE(149)] = 2109,
  [SMALL_STATE(150)] = 2119,
  [SMALL_STATE(151)] = 2127,
  [SMALL_STATE(152)] = 2137,
  [SMALL_STATE(153)] = 2147,
  [SMALL_STATE(154)] = 2157,
  [SMALL_STATE(155)] = 2167,
  [SMALL_STATE(156)] = 2175,
  [SMALL_STATE(157)] = 2183,
  [SMALL_STATE(158)] = 2193,
  [SMALL_STATE(159)] = 2200,
  [SMALL_STATE(160)] = 2207,
  [SMALL_STATE(161)] = 2214,
  [SMALL_STATE(162)] = 2221,
  [SMALL_STATE(163)] = 2228,
  [SMALL_STATE(164)] = 2235,
  [SMALL_STATE(165)] = 2242,
  [SMALL_STATE(166)] = 2249,
  [SMALL_STATE(167)] = 2256,
  [SMALL_STATE(168)] = 2263,
  [SMALL_STATE(169)] = 2270,
  [SMALL_STATE(170)] = 2277,
  [SMALL_STATE(171)] = 2284,
  [SMALL_STATE(172)] = 2291,
  [SMALL_STATE(173)] = 2298,
  [SMALL_STATE(174)] = 2305,
  [SMALL_STATE(175)] = 2312,
  [SMALL_STATE(176)] = 2319,
  [SMALL_STATE(177)] = 2326,
  [SMALL_STATE(178)] = 2333,
  [SMALL_STATE(179)] = 2340,
  [SMALL_STATE(180)] = 2347,
  [SMALL_STATE(181)] = 2354,
  [SMALL_STATE(182)] = 2361,
  [SMALL_STATE(183)] = 2368,
  [SMALL_STATE(184)] = 2375,
};

static TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(173),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(177),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(176),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(171),
  [15] = {.entry = {.count = 1, .reusable = false}}, SHIFT(20),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(125),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [23] = {.entry = {.count = 1, .reusable = false}}, SHIFT(178),
  [25] = {.entry = {.count = 1, .reusable = false}}, SHIFT(148),
  [27] = {.entry = {.count = 1, .reusable = true}}, SHIFT(148),
  [29] = {.entry = {.count = 1, .reusable = true}}, SHIFT(71),
  [31] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [33] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [35] = {.entry = {.count = 1, .reusable = false}}, SHIFT(126),
  [37] = {.entry = {.count = 1, .reusable = true}}, SHIFT(126),
  [39] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [41] = {.entry = {.count = 1, .reusable = true}}, SHIFT(129),
  [43] = {.entry = {.count = 1, .reusable = false}}, SHIFT(139),
  [45] = {.entry = {.count = 1, .reusable = true}}, SHIFT(139),
  [47] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1),
  [49] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2),
  [51] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(173),
  [54] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(177),
  [57] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(176),
  [60] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(171),
  [63] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [65] = {.entry = {.count = 1, .reusable = true}}, SHIFT(174),
  [67] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [69] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [71] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [73] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query, 2),
  [75] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query, 3, .production_id = 25),
  [77] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_action_declaration_repeat1, 2, .production_id = 29),
  [79] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_action_declaration_repeat1, 2, .production_id = 29), SHIFT_REPEAT(174),
  [82] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_action_declaration_repeat1, 2, .production_id = 29), SHIFT_REPEAT(70),
  [85] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_action_declaration_repeat1, 2, .production_id = 29), SHIFT_REPEAT(72),
  [88] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query, 4, .production_id = 25),
  [90] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [92] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query, 5, .production_id = 44),
  [94] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [96] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_variable, 1, .production_id = 32),
  [98] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [100] = {.entry = {.count = 1, .reusable = true}}, SHIFT(178),
  [102] = {.entry = {.count = 1, .reusable = true}}, SHIFT(175),
  [104] = {.entry = {.count = 1, .reusable = true}}, SHIFT(142),
  [106] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call, 5, .production_id = 42),
  [108] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call, 6, .production_id = 52),
  [110] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call, 4, .production_id = 42),
  [112] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call, 3, .production_id = 33),
  [114] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 6, .production_id = 8),
  [116] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [118] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 9, .production_id = 39),
  [120] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 9, .production_id = 38),
  [122] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 9, .production_id = 30),
  [124] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_action_declaration, 8, .production_id = 37),
  [126] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query_declaration, 6, .production_id = 18),
  [128] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 5, .production_id = 3),
  [130] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_uri, 1, .production_id = 34),
  [132] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [134] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_permission_declaration, 6, .production_id = 14),
  [136] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_permission_declaration, 5, .production_id = 4),
  [138] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 11, .production_id = 51),
  [140] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [142] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 7, .production_id = 8),
  [144] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 8, .production_id = 31),
  [146] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 8, .production_id = 21),
  [148] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query_declaration, 5, .production_id = 4),
  [150] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 8, .production_id = 30),
  [152] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 10, .production_id = 39),
  [154] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_uri_repeat1, 2, .production_id = 43),
  [156] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_uri_repeat1, 2, .production_id = 43), SHIFT_REPEAT(178),
  [159] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_action_declaration, 6, .production_id = 1),
  [161] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 10, .production_id = 48),
  [163] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 4, .production_id = 1),
  [165] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 7, .production_id = 21),
  [167] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_query_declaration_repeat1, 2, .production_id = 19),
  [169] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_query_declaration_repeat1, 2, .production_id = 19), SHIFT_REPEAT(175),
  [172] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_query_declaration_repeat1, 2, .production_id = 19), SHIFT_REPEAT(142),
  [175] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_action_declaration, 9, .production_id = 47),
  [177] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_action_declaration, 7, .production_id = 28),
  [179] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_query_declaration, 7, .production_id = 27),
  [181] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 7, .production_id = 23),
  [183] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 6, .production_id = 3),
  [185] = {.entry = {.count = 1, .reusable = true}}, SHIFT(153),
  [187] = {.entry = {.count = 1, .reusable = true}}, SHIFT(152),
  [189] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [191] = {.entry = {.count = 1, .reusable = true}}, SHIFT(43),
  [193] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_update_statement, 4, .production_id = 46),
  [195] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_uri_repeat1, 2, .production_id = 41),
  [197] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_create_statement, 4, .production_id = 45),
  [199] = {.entry = {.count = 1, .reusable = false}}, SHIFT_EXTRA(),
  [201] = {.entry = {.count = 1, .reusable = false}}, SHIFT(97),
  [203] = {.entry = {.count = 1, .reusable = false}}, SHIFT(75),
  [205] = {.entry = {.count = 1, .reusable = false}}, SHIFT(74),
  [207] = {.entry = {.count = 1, .reusable = true}}, SHIFT(168),
  [209] = {.entry = {.count = 1, .reusable = false}}, SHIFT(108),
  [211] = {.entry = {.count = 1, .reusable = false}}, SHIFT(69),
  [213] = {.entry = {.count = 1, .reusable = true}}, SHIFT(146),
  [215] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_action_declaration_repeat1, 1, .production_id = 20),
  [217] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_string_literal_repeat1, 2),
  [219] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_string_literal_repeat1, 2), SHIFT_REPEAT(74),
  [222] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_string_literal_repeat2, 2),
  [224] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_string_literal_repeat2, 2), SHIFT_REPEAT(75),
  [227] = {.entry = {.count = 1, .reusable = false}}, SHIFT(68),
  [229] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_delete_statement, 3, .production_id = 36),
  [231] = {.entry = {.count = 1, .reusable = true}}, SHIFT(117),
  [233] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [235] = {.entry = {.count = 1, .reusable = true}}, SHIFT(127),
  [237] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [239] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding, 5, .production_id = 54),
  [241] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_binding_repeat1, 2, .production_id = 12), SHIFT_REPEAT(134),
  [244] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_binding_repeat1, 2, .production_id = 12),
  [246] = {.entry = {.count = 1, .reusable = true}}, SHIFT(100),
  [248] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [250] = {.entry = {.count = 1, .reusable = true}}, SHIFT(163),
  [252] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [254] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__parameters, 3, .production_id = 5),
  [256] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__parameters_repeat1, 2, .production_id = 16), SHIFT_REPEAT(157),
  [259] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym__parameters_repeat1, 2, .production_id = 16),
  [261] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding, 4, .production_id = 11),
  [263] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_guard, 2, .production_id = 17),
  [265] = {.entry = {.count = 1, .reusable = true}}, SHIFT(83),
  [267] = {.entry = {.count = 1, .reusable = true}}, SHIFT(86),
  [269] = {.entry = {.count = 1, .reusable = true}}, SHIFT(113),
  [271] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [273] = {.entry = {.count = 1, .reusable = true}}, SHIFT(140),
  [275] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding, 3, .production_id = 11),
  [277] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_type_declaration_repeat2, 2, .production_id = 12), SHIFT_REPEAT(149),
  [280] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_type_declaration_repeat2, 2, .production_id = 12),
  [282] = {.entry = {.count = 1, .reusable = true}}, SHIFT(45),
  [284] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_call_repeat1, 2, .production_id = 50), SHIFT_REPEAT(5),
  [287] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_call_repeat1, 2, .production_id = 50),
  [289] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [291] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string_literal, 3),
  [293] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [295] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [297] = {.entry = {.count = 1, .reusable = true}}, SHIFT(158),
  [299] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [301] = {.entry = {.count = 1, .reusable = true}}, SHIFT(145),
  [303] = {.entry = {.count = 1, .reusable = true}}, SHIFT(118),
  [305] = {.entry = {.count = 1, .reusable = true}}, SHIFT(130),
  [307] = {.entry = {.count = 1, .reusable = true}}, SHIFT(94),
  [309] = {.entry = {.count = 1, .reusable = true}}, SHIFT(91),
  [311] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_guard, 3, .production_id = 26),
  [313] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding, 2),
  [315] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [317] = {.entry = {.count = 1, .reusable = true}}, SHIFT(122),
  [319] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__parameters, 1, .production_id = 2),
  [321] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string_literal, 2),
  [323] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_type_declaration_repeat1, 2, .production_id = 9), SHIFT_REPEAT(172),
  [326] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_type_declaration_repeat1, 2, .production_id = 9),
  [328] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_variable, 2, .production_id = 40),
  [330] = {.entry = {.count = 1, .reusable = true}}, SHIFT(90),
  [332] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [334] = {.entry = {.count = 1, .reusable = true}}, SHIFT(98),
  [336] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [338] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [340] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [342] = {.entry = {.count = 1, .reusable = true}}, SHIFT(124),
  [344] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_query_declaration_repeat1, 1, .production_id = 6),
  [346] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [348] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [350] = {.entry = {.count = 1, .reusable = true}}, SHIFT(120),
  [352] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [354] = {.entry = {.count = 1, .reusable = true}}, SHIFT(84),
  [356] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__parameters, 2, .production_id = 5),
  [358] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__parameters, 2, .production_id = 2),
  [360] = {.entry = {.count = 1, .reusable = true}}, SHIFT(144),
  [362] = {.entry = {.count = 1, .reusable = true}}, SHIFT(114),
  [364] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [366] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [368] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [370] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [372] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [374] = {.entry = {.count = 1, .reusable = true}}, SHIFT(96),
  [376] = {.entry = {.count = 1, .reusable = true}}, SHIFT(105),
  [378] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [380] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_query_repeat1, 2, .production_id = 35), SHIFT_REPEAT(154),
  [383] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_query_repeat1, 2, .production_id = 35),
  [385] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameter, 3, .production_id = 13),
  [387] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_query_repeat1, 2, .production_id = 25),
  [389] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym__parameters_repeat1, 2, .production_id = 15),
  [391] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_binding_repeat1, 2, .production_id = 11),
  [393] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binding_field, 3, .production_id = 53),
  [395] = {.entry = {.count = 1, .reusable = true}}, SHIFT(180),
  [397] = {.entry = {.count = 1, .reusable = true}}, SHIFT(181),
  [399] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_field, 4, .production_id = 22),
  [401] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_type_declaration_repeat1, 2, .production_id = 7),
  [403] = {.entry = {.count = 1, .reusable = true}}, SHIFT(143),
  [405] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [407] = {.entry = {.count = 1, .reusable = true}}, SHIFT(162),
  [409] = {.entry = {.count = 1, .reusable = true}}, SHIFT(99),
  [411] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_call_repeat1, 2, .production_id = 49),
  [413] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameter, 4, .production_id = 24),
  [415] = {.entry = {.count = 1, .reusable = true}}, SHIFT(160),
  [417] = {.entry = {.count = 1, .reusable = true}}, SHIFT(182),
  [419] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_field, 3, .production_id = 10),
  [421] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_type_declaration_repeat2, 2, .production_id = 11),
  [423] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [425] = {.entry = {.count = 1, .reusable = true}}, SHIFT(132),
  [427] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [429] = {.entry = {.count = 1, .reusable = true}}, SHIFT(101),
  [431] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [433] = {.entry = {.count = 1, .reusable = true}}, SHIFT(133),
  [435] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [437] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [439] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [441] = {.entry = {.count = 1, .reusable = true}}, SHIFT(77),
  [443] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [445] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [447] = {.entry = {.count = 1, .reusable = true}}, SHIFT(165),
  [449] = {.entry = {.count = 1, .reusable = true}}, SHIFT(147),
  [451] = {.entry = {.count = 1, .reusable = true}}, SHIFT(151),
  [453] = {.entry = {.count = 1, .reusable = true}}, SHIFT(138),
  [455] = {.entry = {.count = 1, .reusable = true}}, SHIFT(166),
  [457] = {.entry = {.count = 1, .reusable = true}}, SHIFT(167),
  [459] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [461] = {.entry = {.count = 1, .reusable = true}}, SHIFT(141),
  [463] = {.entry = {.count = 1, .reusable = true}}, SHIFT(155),
  [465] = {.entry = {.count = 1, .reusable = true}}, SHIFT(179),
  [467] = {.entry = {.count = 1, .reusable = true}}, SHIFT(183),
  [469] = {.entry = {.count = 1, .reusable = true}}, SHIFT(150),
  [471] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
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
