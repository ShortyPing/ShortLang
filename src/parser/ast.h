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

#endif //SLANG_AST_H
