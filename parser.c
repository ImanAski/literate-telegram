#include "defs.h"
#include "enums.h"
#include "funcs.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AstNode *parse(void) {
  AstNode *head = NULL, *tail = NULL;
  while (token_pos < token_count && current_token()->type != TOK_END) {
    AstNode *node = parse_statement();
    if (!node) {
      // free_node(head);
      return NULL;
    }
    if (head == NULL) {
      head = tail = node;
    } else {
      tail->next = node;
      tail = node;
    }
    if (current_token()->type == TOK_SEMI) {
      next_token();
    }
  }
  return head;
};

AstNode *parse_factor(void) {
  Token *tok = current_token();
  AstNode *node = malloc(sizeof(AstNode));

  if (tok->type == TOK_NUMBER) {
    node->type = NODE_NUMBER;
    node->data.number = atof(tok->value);
    node->left = node->right = node->next = NULL;
    next_token();
  } else if (tok->type == TOK_IDENT) {
    char *name = tok->value;
    next_token();
    if (current_token()->type == TOK_LPAREN) {
      node->type = NODE_FUNC;
      node->data.func.name = strdup(name);
      next_token();
      node->data.func.arg = parse_factor();
      if (current_token()->type != TOK_RPAREN) {
        handle_error("Expected )");
        // free_node(node);
        return NULL;
      }
      next_token();
      node->left = node->right = node->next = NULL;
    } else {
      node->type = NODE_VAR;
      node->data.var = strdup(name);
      node->left = node->right = node->next = NULL;
    }
  } else if (tok->type == TOK_MINUS) { // Unary minus
    next_token();
    node->type = NODE_MINUS;
    node->left = NULL;
    node->right = parse_factor();
    node->next = NULL;
  } else if (tok->type == TOK_LPAREN) {
    next_token();
    node = parse_expression();
    if (current_token()->type != TOK_RPAREN) {
      handle_error("Expected )");
      // free_node(node);
      return NULL;
    }
    next_token();
  } else {
    handle_error("Invalid factor");
    free(node);
    return NULL;
  }
  return node;
}

AstNode *parse_power(void) {
  AstNode *node = parse_factor();
  while (current_token()->type == TOK_POW) {
    AstNode *op_node = malloc(sizeof(AstNode));
    op_node->type = NODE_POW;
    op_node->left = node;
    next_token();
    op_node->right = parse_factor();
    op_node->next = NULL;
    node = op_node;
  }
  return node;
}

AstNode *parse_term(void) {
  AstNode *node = parse_power();
  while (1) {
    Token *tok = current_token();
    if (tok->type != TOK_MUL && tok->type != TOK_DIV)
      break;
    AstNode *op_node = malloc(sizeof(AstNode));
    op_node->type = tok->type == TOK_MUL ? NODE_MUL : NODE_DIV;
    op_node->left = node;
    next_token();
    op_node->right = parse_power();
    op_node->next = NULL;
  }
  return node;
}

AstNode *parse_expression(void) {
  AstNode *node = parse_term();
  while (1) {
    Token *tok = current_token();
    if (tok->type != TOK_PLUS && tok->type != TOK_MINUS)
      break;
    AstNode *op_node = malloc(sizeof(AstNode));
    op_node->type = tok->type == TOK_PLUS ? NODE_PLUS : NODE_MINUS;
    op_node->left = node;
    next_token();
    op_node->right = parse_term();
    op_node->next = NULL;
    node = op_node;
  }
  return node;
}

AstNode *parse_statement(void) {
  Token *tok = current_token();
  AstNode *node = NULL;

  if (tok->type == TOK_LET) {
    next_token();
    Token *var_tok = current_token();
    if (var_tok->type != TOK_IDENT || strlen(var_tok->value) < 1) {
      handle_error("Wrong assignment");
      return NULL;
    }

    next_token();
    if (current_token()->type != TOK_ASSIGN) {
      handle_error("Expected :=");
      return NULL;
    }

    next_token();
    node = malloc(sizeof(AstNode));
    node->type = NODE_ASSIGN;
    node->data.assign.var = strdup(var_tok->value);
    node->data.assign.expr = parse_expression();
    node->left = node->right = node->next = NULL;
  } else if (tok->type == TOK_FN) {
    next_token();
    Token *name_tok = current_token();
    if (name_tok->type != TOK_IDENT) {
      handle_error("Expected function name");
      return NULL;
    }
    next_token();
    if (current_token()->type != TOK_LPAREN) {
      handle_error("Expected (");
      return NULL;
    }
    next_token();
    Token *arg_tok = current_token();
    if (arg_tok->type != TOK_IDENT) {
      handle_error("Expected argument name");
      return NULL;
    }
    next_token();
    if (current_token()->type != TOK_RPAREN) {
      handle_error("Expected )");
      return NULL;
    }
    next_token();
    if (current_token()->type != TOK_ASSIGN) {
      handle_error("Expected :=");
      return NULL;
    }
    next_token();
    node = malloc(sizeof(AstNode));
    node->type = NODE_FUNCDEF;
    node->data.funcdef.name = strdup(name_tok->value);
    node->data.funcdef.arg = strdup(arg_tok->value);
    node->data.funcdef.expr = parse_expression();
    node->left = node->right = node->next = NULL;
  } else {
    node = parse_expression();
  }
  return node;
}
