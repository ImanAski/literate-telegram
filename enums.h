#ifndef ENUMS_H
#define ENUMS_H

typedef enum {
  // Commands
  T_MAKE,
  T_PLOT,
  T_EXIT,

  // Operators
  T_PLUS,
  T_MINUS,
  T_MULTIPLY,
  T_DIVIDE,
  T_POWER,

  // Misc
  T_LPAREN,
  T_RPAREN,
  T_IDENT,
  T_EOF,

  // Error
  T_ERROR,

  // Types
  T_INTLIT
} TokenType;

#endif // !ENUMS_H
