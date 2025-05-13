#include "defs.h"
#include "enums.h"
#include "funcs.h"
#include "structs.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void print_token(Token t) {
  switch (t.type) {
  case TOK_LET:
    printf("{let} with value of %s\n", t.value);
    break;
  case TOK_FN:
    printf("{function} with value of %s\n", t.value);
    break;
  case TOK_PLOT:
    printf("{plot} with value of %s\n", t.value);
    break;
  case TOK_IDENT:
    printf("{identifier} with value of %s\n", t.value);
    break;
  case TOK_NUMBER:
    printf("{number} with value of %s\n", t.value);
    break;
  case TOK_RANGE:
    printf("{range} with value of %s\n", t.value);
    break;
  case TOK_ASSIGN:
    printf("{assign} with value of %s\n", t.value);
    break;
  case TOK_LPAREN:
    printf("{left parenthesis} with value of %s\n", t.value);
    break;
  case TOK_RPAREN:
    printf("{right parenthesis} with value of %s\n", t.value);
    break;
  case TOK_COMMENT:
    printf("{comment} with value of %s\n", t.value);
    break;
  case TOK_END:
    printf("{end} with value of %s\n", t.value);
    break;
  case TOK_PLUS:
    printf("{plus} with value of %s\n", t.value);
    break;
  case TOK_MINUS:
    printf("{minus} with value of %s\n", t.value);
    break;
  case TOK_MUL:
    printf("{multiply} with value of %s\n", t.value);
    break;
  case TOK_DIV:
    printf("{division} with value of %s\n", t.value);
    break;
  case TOK_POW:
    printf("{power} with value of %s\n", t.value);
    break;
  case TOK_SEMI:
    printf("{semicolon} with value of %s\n", t.value);
    break;
  case TOK_LBRACE:
    printf("{l brace} with value of %s\n", t.value);
    break;
  case TOK_RBRACE:
    printf("{r brace} with value of %s\n", t.value);
    break;
  case TOK_LCBRACE:
    printf("{LC brace} with value of %s\n", t.value);
    break;
  case TOK_RCBRACE:
    printf("{RC brace} with value of %s\n", t.value);
    break;
  case TOK_PLUSEQ:
    printf("{plus equal} with value of %s\n", t.value);
    break;
  case TOK_MINUSEQ:
    printf("{minus equal} with value of %s\n", t.value);
    break;
  case TOK_VAR:
    printf("{var} with value of %s\n", t.value);
    break;
  case TOK_WHILE:
    printf("{while} with value of %s\n", t.value);
    break;
  case TOK_FOR:
    printf("{for} with value of %s\n", t.value);
    break;
  case TOK_IF:
    printf("{if} with value of %s\n", t.value);
    break;
  case TOK_ELF:
    printf("{elf} with value of %s\n", t.value);
    break;
  case TOK_ELSE:
    printf("{else} with value of %s\n", t.value);
    break;
  case TOK_COLON:
    printf("{colon} with value of %s\n", t.value);
    break;
  case TOK_DOT:
    printf("{dot} with value of %s\n", t.value);
    break;
    break;
  }
}

Token *current_token() { return &tokens[token_pos]; }

void next_token() {
  if (token_pos < token_count)
    (token_pos)++;
}

void tokenize(const char *input) {
  size_t i = 0;
  while (i < strlen(input) && token_count < MAX_TOKENS) {
    while (isspace(input[i]))
      i++;

    if (input[i] == '\0')
      break;

    Token tok = {0};
    if (input[i] == '#') {
      tok.type = TOK_COMMENT;
      tok.value = strdup(input + i);
      i = strlen(input);
    } else if (strncmp(input + i, "let", 3) == 0 && !isalnum(input[i + 3])) {
      tok.type = TOK_LET;
      tok.value = strdup("let");
      i += 3;
    } else if (strncmp(input + i, "fn", 2) == 0 && !isalnum(input[i + 2])) {
      tok.type = TOK_FN;
      tok.value = strdup("fn");
      i += 2;
    } else if (strncmp(input + i, "plot", 4) == 0 && !isalnum(input[i + 4])) {
      tok.type = TOK_PLOT;
      tok.value = strdup("plot");
      i += 4;
    } else if (strncmp(input + i, "if", 3) == 0 && !isalnum(input[i + 2])) {
      tok.type = TOK_IF;
      tok.value = strdup("if");
      i += 2;
    } else if (strncmp(input + i, "var", 3) == 0 && !isalnum(input[i + 3])) {
      tok.type = TOK_VAR;
      tok.value = strdup("var");
      i += 3;
    } else if (strncmp(input + i, "for", 3) == 0 && !isalnum(input[i + 3])) {
      tok.type = TOK_FOR;
      tok.value = strdup("for");
      i += 3;
    } else if (input[i] == ':') {
      if (input[i + 1] == '=') {
        tok.type = TOK_ASSIGN;
        tok.value = strdup(":=");
        i += 2;
      } else {
        tok.type = TOK_COLON;
        tok.value = strdup(":");
        i++;
      }
    } else if (input[i] == '(') {
      tok.type = TOK_LPAREN;
      tok.value = strdup("(");
      i++;
    } else if (input[i] == ')') {
      tok.type = TOK_RPAREN;
      tok.value = strdup(")");
      i++;
    } else if (input[i] == '[') {
      tok.type = TOK_LBRACE;
      tok.value = strdup("[");
      i++;
    } else if (input[i] == ']') {
      tok.type = TOK_RBRACE;
      tok.value = strdup("]");
      i++;
    } else if (input[i] == '{') {
      tok.type = TOK_LCBRACE;
      tok.value = strdup("{");
      i++;
    } else if (input[i] == '}') {
      tok.type = TOK_RCBRACE;
      tok.value = strdup("}");
      i++;
    } else if (input[i] == ';') {
      tok.type = TOK_SEMI;
      tok.value = strdup(";");
      i++;
    } else if (input[i] == '+') {
      if (input[i + 1] == '=') {
        tok.type = TOK_PLUSEQ;
        tok.value = strdup("+=");
        i += 2;
      } else {
        tok.type = TOK_PLUS;
        tok.value = strdup("+");
        i++;
      }
    } else if (input[i] == '-') {
      if (input[i + 1] == '=') {
        tok.type = TOK_MINUSEQ;
        tok.value = strdup("-=");
        i += 2;
      } else {
        tok.type = TOK_MINUS;
        tok.value = strdup("-");
        i++;
      }
    } else if (input[i] == '*') {
      tok.type = TOK_MUL;
      tok.value = strdup("*");
      i++;
    } else if (input[i] == '/') {
      tok.type = TOK_DIV;
      tok.value = strdup("/");
      i++;
    } else if (input[i] == '^') {
      tok.type = TOK_POW;
      tok.value = strdup("^");
      i++;
    } else if (input[i] == '-' && isdigit(input[i + 1])) {
      size_t start = i;
      while (isdigit(input[i]) || isdigit(input[i + 1]) || input[i] == '.')
        i++;
      tok.type = TOK_NUMBER;
      tok.value = strndup(input + start, i - start);
    } else if (isdigit(input[i])) {
      size_t start = i;
      while (isdigit(input[i]) || input[i] == '.')
        i++;
      tok.type = TOK_NUMBER;
      tok.value = strndup(input + start, i - start);
    } else if (isalnum(input[i])) {
      size_t start = i;
      while (isalnum(input[i]))
        i++;
      tok.type = TOK_IDENT;
      tok.value = strndup(input + start, i - start);
    } else if (input[i] == '.' && input[i + 1] == '.') {
      tok.type = TOK_RANGE;
      tok.value = strdup("..");
      i += 2;
    } else {
      handle_error("Invalid token");
      return;
    }
    tokens[(token_count)++] = tok;
  }
  tokens[token_count].type = TOK_END;
  tokens[token_count].value = NULL;
}
