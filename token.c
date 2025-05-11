#include "funcs.h"
#include "enums.h"
#include "structs.h"
#include "defs.h"
#include <string.h>
#include <ctype.h>


void tokenize(const char *input, Token *tokens, size_t *token_count, size_t max_tokens) {
  *token_count = 0;
  size_t i = 0;
  while (i < strlen(input) && *token_count < max_tokens) {
    while (isspace(input[i])) i++;
    if (input[i] == '\0') break;

    printf("%c", input[i]);
    Token tok = {0};
    if (input[i] == '#') {
      tok.type = TOK_COMMENT;
      tok.value = strdup(input+i);
      i = strlen(input);
    } else if (strncmp(input+i, "let", 3) == 0 && !isalnum(input[i + 3])) {
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
    } else if (input[i] == ':') {
      if (input[i + i] == '=') {
        tok.type = TOK_ASSIGN;
        tok.value = strdup(":=");
        i += 2;
      } else {
        handle_error("Invalid token");
        return;
      }
    } else if (input[i] == '(') {
      tok.type = TOK_LPAREN;
      tok.value = strdup("(");
    } else if (input[i] == ')') {
      tok.type = TOK_RPAREN;
      tok.value = strdup(")");
    } else if (input[i] == '-' && isdigit(input[i + 1])) {
      size_t start;
      while (isdigit(input[i]) || input[i] == '.') i++;
      tok.type = TOK_NUMBER;
      tok.value = strndup(input + start, i - start);
    } else if (isdigit(input[i])) { 
      size_t start = i;
      while (isdigit(input[i]) || input[i] == '.') i++;
      tok.type = TOK_NUMBER;
      tok.value = strndup(input + start, i - start);
    } else if (isalnum(input[i])) {
      size_t start = i;
      while (isalnum(input[i])) i++;
      tok.type = TOK_IDENT;
      tok.value = strndup(input + start, i - start);
    } else if (input[i] == '.' && input[i + 1] == '.') {
      tok.type = TOK_RANGE;
      tok.value = strdup("..");
      i += 2;
    }
    else {
      handle_error("Invalid token");
      return;
    }
    tokens[(*token_count)++] = tok;
  }
  tokens[*token_count].type = TOK_END;
  tokens[*token_count].value = NULL;
}
