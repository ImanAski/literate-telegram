#ifndef ENUMS_H
#define ENUMS_H

typedef enum {
  TOK_CONST,    // const
  TOK_IMPORT,   // import
  TOK_ATSIGN,   // @
  TOK_AND,      // &&
  TOK_OR,       // ||
  TOK_PIPE,     // |
  TOK_GT,       // >
  TOK_LT,       // <
  TOK_TRUE,     // true
  TOK_FALSE,    // false
  TOK_VOID,     // void
  TOK_QUOTE,    // '
  TOK_DBLQUOTE, // "
  TOK_LET,      // let
  TOK_FN,       // fn
  TOK_PLOT,     // plot
  TOK_IDENT,    // ident
  TOK_NUMBER,   // number
  TOK_RANGE,    // ..
  TOK_ASSIGN,   // =
  TOK_LPAREN,   // (
  TOK_RPAREN,   // )
  TOK_LBRACE,   // [
  TOK_RBRACE,   // ]
  TOK_LCBRACE,  // {
  TOK_RCBRACE,  // }
  TOK_COMMENT,  // #
  TOK_END,      // end
  TOK_PLUS,     // +
  TOK_PLUSEQ,   // +=
  TOK_MINUSEQ,  // -=
  TOK_VAR,      // var
  TOK_WHILE,    // while
  TOK_FOR,      // for
  TOK_IF,       // if
  TOK_ELF,      // elf
  TOK_ELSE,     // else
  TOK_MINUS,    // -
  TOK_MUL,      // *
  TOK_DIV,      // /
  TOK_POW,      // ^
  TOK_SEMI,     // ;
  TOK_COLON,    // ;
  TOK_DOT,      // .
  TOK_IN,       // in
  TOK_DO,       // do
  TOK_EXMARK,   // !
} TokenType;

typedef enum {
  NODE_OP,
  NODE_EXPR,
  NODE_NUMBER,
  NODE_VAR,
  NODE_PLUS,
  NODE_MINUS,
  NODE_MUL,
  NODE_DIV,
  NODE_POW,
  NODE_FUNC,
  NODE_ASSIGN,
  NODE_FUNCDEF,
  NODE_PLOT,
  NODE_COMMENT,
} NodeType;

#endif // !ENUMS_H
