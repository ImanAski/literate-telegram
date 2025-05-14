#include "funcs.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_error(const char *msg) { printf("Error: %s\n", msg); }

char *strdnup(const char *s, size_t n) {
  char *p = malloc(n + 1);
  if (!p) {
    handle_error("Memory allocation failed");
    return NULL;
  }
  strncpy(p, s, n);
  p[n] = '\0';
  return p;
}

char *strdup(const char *s) { return strdnup(s, strlen(s)); }

void free_node(AstNode *node) {
  if (!node)
    return;
  switch (node->type) {
  case NODE_VAR:
    free(node->data.var);
    break;
  case NODE_FUNC:
    free(node->data.func.name);
    free_node(node->data.func.arg);
    break;
  case NODE_ASSIGN:
    free(node->data.assign.var);
    free_node(node->data.assign.expr);
    break;
  case NODE_FUNCDEF:
    free(node->data.funcdef.name);
    free(node->data.funcdef.arg);
    free_node(node->data.funcdef.expr);
    break;
  case NODE_PLOT:
    free_node(node->data.plot.expr);
    break;
  case NODE_COMMENT:
    free(node->data.comment.text);
    break;
  case NODE_NUMBER:
  case NODE_PLUS:
  case NODE_MINUS:
  case NODE_MUL:
  case NODE_DIV:
  case NODE_POW:
    break;
  }
  free_node(node->left);
  free_node(node->right);
  free_node(node->next);
  free(node);
}
