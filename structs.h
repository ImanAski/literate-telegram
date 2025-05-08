#ifndef STRUCTS_H
#define STRUCTS_H

#include "enums.h"
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

typedef struct Command {
  const char *name;
  void (*func)(float, float);
  int argc;
} Command;

typedef struct AstNode {
  int type;
  union {
    float number;
    char constant[16];
    struct {
      char op;
      struct AstNode *left, *right;
    } binary;
    struct {
      char func[16];
      struct AstNode *arg;
    } function;
  } data;
} AstNode;

typedef struct Token {
  TokenType type;
  float value;
  char ident[16];
} Token;

typedef struct Lexer {
  const char *input;
  int pos;
} Lexer;

typedef struct Parser {
  Lexer lexer;
  Token current;
} Parser;

#endif
