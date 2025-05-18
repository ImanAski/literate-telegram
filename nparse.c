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
  case NODE_OP:
    return "OPERATION";
  case NODE_IDENT:
    return "IDNETIFIER";
  case NODE_EXPR:
    return "EXPRESSION";
  case NODE_PLUS:
    return "PLUS";
  case NODE_MINUS:
    return "MINUS";
  case NODE_MUL:
    return "MULTIPLY";
  case NODE_DIV:
    return "DIVISION";
  case NODE_POW:
    return "POWER";
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

AstNode *parse_var_assign() {
  expect(TOK_IDENT, "Expected identifier after var");
  next_token();
  Token *ident = current_token();
  AstNode *node = new_node(NODE_VAR);
  AstNode *ident_node = new_node(NODE_IDENT);

  ident_node->data.ident = strdup(ident->value);
  node->left = ident_node;

  expect(TOK_IDENT, "Expected `type` after identidier");
  next_token();

  Token *type_tok = current_token();
  AstNode *type_node = new_node(NODE_IDENT);
  type_node->data.ident = strdup(type_tok->value);
  node->right = type_node;

  expect(TOK_SEMI, "Expected ';' after assignment");
  next_token();
  return node;
}

AstNode *parse_fn() {
  expect(TOK_IDENT, "Expected identifier after fn");
  next_token();

  // root node for function
  AstNode *root = new_node(NODE_FUNC);

  // function name as identifier
  AstNode *fn_name = new_node(NODE_IDENT);
  fn_name->data.ident = strdup(current_token()->value);
  root->left = fn_name;

  // TODO: should add the arguments between LPAREN and RPAREN for fn arguments
  expect(TOK_LPAREN, "expected '(' for function");
  next_token();
  expect(TOK_RPAREN, "expected ')' for function");
  next_token();

  // TODO: should add the body between LCBRACE and RCBRACE for fn body
  expect(TOK_LCBRACE, "expected '{' for function body");
  next_token();
  expect(TOK_RCBRACE, "expected '}' for function body");
  next_token();

  expect(TOK_SEMI, "expected ';' for end of statement");
  next_token();
  return root;
}

void print_node(AstNode *node, int indent) {
  // printig nodes
  if (node == NULL) {
    print_tabs(indent);
    printf("<----EMPTY---->\n");
    return;
  }

  print_tabs(indent);
  printf("node type is {%s}\n", node_type_to_string(node->type));

  // left braench
  print_tabs(indent);
  printf("left:\n");
  print_node(node->left, indent + 1);

  // right branch
  print_tabs(indent);
  printf("right:\n");
  print_node(node->right, indent + 1);
  print_tabs(indent);
  printf("done\n");
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
    AstNode *fn = parse_fn();
    return fn;
  case TOK_VAR:
    print_token(*tok);
    AstNode *vn = parse_var_assign();
    return vn;
  case TOK_PLOT:
    return NULL;
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
