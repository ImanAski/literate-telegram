#ifndef FUNCS_H
#define FUNCS_H

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
// void init_command_list(size_t inittial_capacity);
void free_command_list(void);

// ast.c
AstNode *alloc_node(void);
void free_ast(void);
AstNode *parse_atom(int *);

// lex.c
void lexer_init(Lexer *l, const char *input);
void skip_whitespace(Lexer *l);

#endif
