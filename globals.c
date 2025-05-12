#include "defs.h"
#include "structs.h"

Command commands[MAX_COMMANDS];
size_t command_count;
Function functions[MAX_FUNCTIONS];
size_t function_count;
double variables[26];
Token tokens[MAX_TOKENS];
size_t token_count;
size_t token_pos;
Token math_tokens[MAX_TOKENS];
size_t math_token_count;
size_t math_token_pos;
