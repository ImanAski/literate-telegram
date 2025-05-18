#ifndef FUNCS_H
#define FUNCS_H

#include "enums.h"
#include "structs.h"

// point.c
Point *make_point(int x, int y);
char *point_to_string(Point);

// line.c
Line *make_line(Point start, Point end);
int line_length(Line ln);
char *line_to_string(Line ln);

// circle.c
Circle *make_circle(Point c, int r);
char *circle_to_string(Circle cr);

// rect.c
Rectangle *make_rectangle(Point pts[]);

// repl.c
void init_repl(void);
int process_input(const char *input);
void init_command_list(size_t inittial_capacity);
void free_command_list(void);
void register_command(const char *name, const char *alias,
                      const char *description, int (*callback)(const char *));
int execute_command(const char *input);
void register_commands(void);

// commands.c
int command_quit(const char *args);
int command_ping(const char *args);
int command_set(const char *args);
int command_help(const char *args);

// ast.c
AstNode *alloc_node(void);
void free_ast(void);
AstNode *parse_atom(int *);

// lex.c
void lexer_init(Lexer *l, const char *input);
void skip_whitespace(Lexer *l);

// token.c
void tokenize(const char *input);
Token *current_token(void);
void next_token(void);
void prev_token(void);
int token_end(void);
void print_token(Token t);

// nparse.c
void expect(TokenType type, char *msg);
void nparse(void);
AstNode *nparse_statement(void);
AstNode *new_node(NodeType type);
AstNode *parse_let_assign(void);
AstNode *parse_var_assign(void);
AstNode *parse_fn(void);
AstNode *nparse_comment(void);
AstNode *nparse_expression(void);
void print_node(AstNode *node, int indent);
void print_ast(AstNode *node);
void print_tabs(int nums);

// parser.c
AstNode *parse(void);
AstNode *parse_factor(void);
AstNode *parse_power(void);
AstNode *parse_term(void);
AstNode *parse_expression(void);
AstNode *parse_statement(void);

// utils.c
void handle_error(const char *msg);
char *strdup(const char *s);
char *strdnup(const char *s, size_t n);
void free_node(AstNode *node);

#endif
