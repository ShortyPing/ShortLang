//
// Created by pwpio on 13.05.22.
//

#ifndef SLANG_AST_H
#define SLANG_AST_H

#include "../tokenizer/tokenizer.h"

typedef enum {
    NODE_STRING_LITERAL,
    NODE_INTEGER_LITERAL,
    NODE_REAL_LITERAL,
    NODE_BINARY_EXPRESSION,
    NODE_COMPLEX_INITIALIZER,
    // ...
} NodeType;

typedef enum {
    BOP_ADD,
    BOP_SUB,
    BOP_MUL,
    BOP_DIV,
    BOP_SHL,    // Bit-shift left
    BOP_SHR     // Bit-shift right
} BinaryOperator;

typedef struct Node Node;

struct Node {
    NodeType type;
    union {
        struct {    char   *literal;   } string_literal;
        struct {    int    literal;    } integer_literal;
        struct {    double literal;    } real_literal;
        struct {
            Node *left;
            Node *right;
            BinaryOperator operator;
        } binary_expression;
    } body;
};

/**
 * Reserves memory for the base structure (and sets its type).
 * Not intended to be use outside of /ast.c/
 * @return
 */
Node *Node_CreateBase(NodeType);

/**
 * Destroy a full node tree structure, rather than a single node
 */
void Node_DestroyRecurse(Node *);

Node *Node_CreateStringLiteral(char *);
Node *Node_CreateIntegerLiteral(int);
Node *Node_CreateRealLiteral(double);
Node *Node_CreateBinaryExpression(Node *, Node *, BinaryOperator);

#endif //SLANG_AST_H
