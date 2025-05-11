#ifndef STRUCTS_H
#define STRUCTS_H

#include "enums.h"
#include <stddef.h>
typedef struct Color {
  int r;
  int g;
  int b;
} Color;

typedef struct Point {
  int x;
  int y;
} Point;

typedef struct Line {
  Point start;
  Point end;
  double length;
} Line;

typedef struct Circle {
  Point c;
  int r;
} Circle;

typedef struct Rectangle {
  Point pt1;
  Point pt2;
  Point pt3;
  Point pt4;
} Rectangle;

// typedef struct Command {
//   const char *name;
//   void (*func)(float, float);
//   int argc;
// } Command;

typedef struct AstNode {
  NodeType type;
  union {
    struct { char *expr; } expr; // NODE_EXPR
    struct { char *var; char *expr; } assign; // NODE_ASSIGN
    struct { char *name; char *args; char *expr; } funcdef; // NODE_FUNCDEF
    struct { char *expr; double xmin; double xmax; } plot; // NODE_PLOT
    struct { char *text; } comment; // NODE_COMMENT
  } data;
} AstNode;

typedef struct Token {
  TokenType type;
  char *value;
} Token;

typedef struct Lexer {
  const char *input;
  int pos;
} Lexer;

typedef struct Parser {
  Lexer lexer;
  Token current;
} Parser;

typedef struct Command {
  char *name;
  char *alias;
  char *description;
  int (*callback)(const char *);
} Command;

typedef struct Function {
  char *name;
  char *args;
  char *expr;
} Function;

typedef struct CommandList {
  Command *commands;
  size_t count;
  size_t capacity;
} CommandList;

#endif
