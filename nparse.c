#include "defs.h"
#include "enums.h"
#include "funcs.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to get NodeType as string
const char *node_type_to_string(NodeType type) {
  switch (type) {
  case NODE_PROGRAM:
    return "PROGRAM";
  case NODE_ASSIGN:
    return "ASSIGN";
  case NODE_FUNC:
    return "FUNC";
  case NODE_FUNCDEF:
    return "FUNCDEF";
  case NODE_PLOT:
    return "PLOT";
  case NODE_COMMENT:
    return "COMMENT";
  case NODE_NUMBER:
    return "NUMBER";
  case NODE_VAR:
    return "VAR";
  case NODE_LET:
    return "LET";
  default:
    return "UNKNOWN";
  }
}

void expect(TokenType type, char *msg) {
  next_token();
  if (current_token()->type != type) {
    handle_error(msg);
    exit(1);
  }
  prev_token();
}

AstNode *new_node(NodeType type) {
  AstNode *node = malloc(sizeof(AstNode));
  if (!node) {
    handle_error("Memory allocation failed");
    exit(1);
  }
  node->type = type;
  node->left = node->right = node->next = NULL;
  return node;
}

AstNode *nparse_comment(void) {
  Token *tok = current_token();
  AstNode *node = new_node(NODE_COMMENT);
  node->data.comment.text = strdup(tok->value);
  next_token();
  return node;
}

// let {ident} := {value}{semicolon}
// this shoud have tree like this
// NODE_LET
// |
// |---{NODE_IDENT}
// |
// |___{NODE_EXPRESSION}
AstNode *parse_let_assign(void) {
  expect(TOK_IDENT, "Expected identifier after let");
  next_token();
  Token *ident = current_token();
  AstNode *node = new_node(NODE_LET);
  AstNode *ident_node = new_node(NODE_IDENT);
  ident_node->data.ident = strdup(ident->value);
  node->left = ident_node;
  // node->data.let_assign.ident = strdup(ident->value);
  expect(TOK_COLONEQ, "Expected ':=' after identifier");
  next_token();
  // skipping ':=' and reaching the value of the let expression
  next_token();
  AstNode *expr_node = new_node(NODE_EXPR);
  expr_node->data.expr = nparse_expression();
  node->right = expr_node;
  // node->data.let_assign.expr = nparse_expression();
  expect(TOK_SEMI, "Expected ';' after assignment");
  next_token();
  return node;
}

void print_node(AstNode *node, int indent) {
  // printig nodes
  if (node == NULL) {
    printf("<----END---->\n");
    return;
  }
  printf("node type is %d\n", node->type);
  // print_tabs(indent);

  // left braench
  // print_tabs(indent);
  printf("left:\n");
  print_node(node->left, indent + 1);

  // right branch
  // print_tabs(indent);
  printf("right:\n");
  print_node(node->right, indent + 1);
}

void print_tabs(int nums) {
  for (int i = 0; i < nums; i++) {
    printf("\t");
  }
}

void print_ast(AstNode *node) {
  // printing nodes with intial 1 indention
  print_node(node, 0);
}

AstNode *nparse_expression(void) {
  AstNode *expr_node = new_node(NODE_EXPR);
  return expr_node;
}

AstNode *nparse_statement() {
  Token *tok = current_token();

  switch (tok->type) {
  case TOK_LET:
    AstNode *ln = parse_let_assign();
    return ln;
  case TOK_FN:
  case TOK_PLOT:
  case TOK_COMMENT:
    AstNode *cn = nparse_comment();
    return cn;
  case TOK_END:
    return NULL;
  default:
    print_token(*current_token());
    AstNode *node = new_node(NODE_EXPR);
    expect(TOK_SEMI, "Expected ';' after expression");
    return node;
  }
}

// should be something like this
// [PROGRAM]
// |
// |
// |----{NODE}
// |
// |
// |----{NODE}
void nparse(void) {
  AstNode *root = new_node(NODE_PROGRAM);
  AstNode *current = root;

  while (token_end() != 1) {
    AstNode *stmt = nparse_statement();
    if (stmt == NULL) {
      break;
    }
    current->next = stmt;
    current = stmt;
    next_token();
  }
  print_ast(current);
}
