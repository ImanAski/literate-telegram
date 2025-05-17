#include "defs.h"
#include "enums.h"
#include "funcs.h"
#include "structs.h"
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

// Lookup table for token names
static const char *token_names[] = {[TOK_LET] = "let",
                                    [TOK_FN] = "function",
                                    [TOK_IMPORT] = "import",
                                    [TOK_TRUE] = "true",
                                    [TOK_FALSE] = "false",
                                    [TOK_PLOT] = "plot",
                                    [TOK_IDENT] = "identifier",
                                    [TOK_NUMBER] = "number",
                                    [TOK_RANGE] = "range",
                                    [TOK_ASSIGN] = "assign",
                                    [TOK_LPAREN] = "left parenthesis",
                                    [TOK_RPAREN] = "right parenthesis",
                                    [TOK_COMMENT] = "comment",
                                    [TOK_END] = "end",
                                    [TOK_PLUS] = "plus",
                                    [TOK_MINUS] = "minus",
                                    [TOK_MUL] = "multiply",
                                    [TOK_DIV] = "division",
                                    [TOK_POW] = "power",
                                    [TOK_SEMI] = "semicolon",
                                    [TOK_LBRACE] = "l brace",
                                    [TOK_RBRACE] = "r brace",
                                    [TOK_LCBRACE] = "LC brace",
                                    [TOK_RCBRACE] = "RC brace",
                                    [TOK_PLUSEQ] = "plus equal",
                                    [TOK_MINUSEQ] = "minus equal",
                                    [TOK_VAR] = "var",
                                    [TOK_WHILE] = "while",
                                    [TOK_FOR] = "for",
                                    [TOK_IF] = "if",
                                    [TOK_ELF] = "elf",
                                    [TOK_ELSE] = "else",
                                    [TOK_COLON] = "colon",
                                    [TOK_DOT] = "dot",
                                    [TOK_CONST] = "const",
                                    [TOK_PIPE] = "|",
                                    [TOK_GT] = ">",
                                    [TOK_LT] = "<",
                                    [TOK_QUOTE] = "'",
                                    [TOK_DBLQUOTE] = "\"",
                                    [TOK_IN] = "in",
                                    [TOK_DO] = "do",
                                    [TOK_ATSIGN] = "@",
                                    [TOK_EXMARK] = "!"};

void print_token(Token t) {
  if (t.type >= 0 && t.type < sizeof(token_names) / sizeof(token_names[0]) &&
      token_names[t.type]) {
    printf("{%s} with value of %s\n", token_names[t.type], t.value);
  } else {
    printf("{unknonw token with value of %s\n", t.value);
  }
}

Token *current_token() { return &tokens[token_pos]; }

Token *peek_token(void) {
  // peeking token
  return &tokens[token_pos];
}

void next_token() {
  if (token_pos < token_count)
    (token_pos)++;
}

void prev_token() {
  if (token_pos > 0)
    (token_pos)--;
}

int token_end(void) {
  if (token_pos == token_count - 1)
    return 1;

  return 0;
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
    } else if (strncmp(input + i, "while", 5) == 0 && !isalnum(input[i + 5])) {
      tok.type = TOK_FOR;
      tok.value = strdup("while");
      i += 5;
    } else if (strncmp(input + i, "const", 5) == 0 && !isalnum(input[i + 5])) {
      tok.type = TOK_FOR;
      tok.value = strdup("const");
      i += 5;
    } else if (strncmp(input + i, "import", 6) == 0 && !isalnum(input[i + 6])) {
      tok.type = TOK_FOR;
      tok.value = NULL;
      i += 6;
    } else if (strncmp(input + i, "true", 4) == 0 && !isalnum(input[i + 4])) {
      tok.type = TOK_TRUE;
      tok.value = NULL;
      i += 4;
    } else if (strncmp(input + i, "false", 5) == 0 && !isalnum(input[i + 5])) {
      tok.type = TOK_TRUE;
      tok.value = NULL;
      i += 5;
    } else if (strncmp(input + i, "do", 2) == 0 && !isalnum(input[i + 2])) {
      tok.type = TOK_FOR;
      tok.value = strdup("do");
      i += 2;
    } else if (input[i] == ':') {
      if (input[i + 1] == '=') {
        tok.type = TOK_COLONEQ;
        tok.value = strdup(":=");
        i += 2;
      } else {
        tok.type = TOK_COLON;
        tok.value = strdup(":");
        i++;
      }
    } else if (input[i] == '>') {
      tok.type = TOK_GT;
      tok.value = strdup(">");
      i++;
    } else if (input[i] == '<') {
      tok.type = TOK_LT;
      tok.value = strdup("<");
      i++;
    } else if (input[i] == '@') {
      tok.type = TOK_ATSIGN;
      tok.value = strdup("@");
      i++;
    } else if (input[i] == '|') {
      tok.type = TOK_PIPE;
      tok.value = strdup("|");
      i++;
    } else if (input[i] == '\'') {
      tok.type = TOK_QUOTE;
      tok.value = strdup("'");
      i++;
    } else if (input[i] == '"') {
      tok.type = TOK_DBLQUOTE;
      tok.value = strdup("\"");
      i++;
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
      while (isdigit(input[i]) || isdigit(input[i + 1]) || input[i] == '_')
        i++;
      tok.type = TOK_NUMBER;
      tok.value = strndup(input + start, i - start);
    } else if (isdigit(input[i])) {
      size_t start = i;
      while (isdigit(input[i]) || input[i] == '_')
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
