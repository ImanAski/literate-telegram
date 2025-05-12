#ifndef DEFS_H
#define DEFS_H

#include "enums.h"
#include "funcs.h"
#include "structs.h"

// App specific defines
#define APP_NAME "Plotter"
#define APP_VERSION "v0.0.1"
#define MAX_NODES 64

// Misc defines
#define MAX_INPUT 128
#define MAX_COMMANDS 16
#define MAX_FUNCTIONS 16
#define MAX_TOKENS 64
#define PLOT_WIDTH 64
#define PLOT_HEIGHT 64

// repl.c
#define REPL_EXIT 0;
#define REPL_CONTINUE 1;
#define REPL_NCMD -1;
#define CMD_PREFIX ";"

// Global states
extern Command commands[MAX_COMMANDS];
extern size_t command_count;
extern Function functions[MAX_FUNCTIONS];
extern size_t function_count;
extern double variables[26];
extern Token tokens[MAX_TOKENS];
extern size_t token_count;
extern size_t token_pos;
extern Token math_tokens[MAX_TOKENS];
extern size_t math_token_count;
extern size_t math_token_pos;

#endif // DEFS_H
