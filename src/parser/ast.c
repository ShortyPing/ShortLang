//
// Created by pwpio on 5/30/2022.
//

#include "ast.h"

#include <stdlib.h>
#include <string.h>

#if !defined(INIT) && !defined(BODY) && !defined(RET)
#   define INIT(t) Node *node = Node_CreateBase(t);
#   define BODY(...) node->body.__VA_ARGS__
#   define RET return node;
#endif

Node *Node_CreateBase(NodeType type) {
    Node *node = malloc(sizeof(Node));
    node->type = type;
    return node;
}

void Node_DestroyRecurse(Node *node) {
    NodeType type = node->type;
    switch (type) {
        case NODE_STRING_LITERAL:
            free(BODY(string_literal.literal));
            break;
        case NODE_INTEGER_LITERAL:
        case NODE_REAL_LITERAL:
            break;
        case NODE_BINARY_EXPRESSION:
            Node_DestroyRecurse(BODY(binary_expression.left));
            Node_DestroyRecurse(BODY(binary_expression.right));
            break;
        default:
            break;
    }
    free(node);
}

Node *Node_CreateStringLiteral(char *s) {
    INIT(NODE_STRING_LITERAL)
        BODY(string_literal.literal) = calloc(strlen(s) + 1, sizeof(char));
        strcpy(BODY(string_literal.literal), s);
    RET;
}

Node *Node_CreateIntegerLiteral(int i) {
    INIT(NODE_INTEGER_LITERAL)
        BODY(integer_literal.literal) = i;
    RET;
}

Node *Node_CreateRealLiteral(double d) {
    INIT(NODE_INTEGER_LITERAL)
        BODY(real_literal.literal) = d;
    RET;
}

Node *Node_CreateBinaryExpression(Node *left, Node *right, BinaryOperator operator) {
    INIT(NODE_BINARY_EXPRESSION)
        BODY(binary_expression.left) = left;
        BODY(binary_expression.right) = right;
        BODY(binary_expression.operator) = operator;
    RET;
}

#if defined(INIT) && defined(BODY) && defined(RET)
#   undef INIT
#   undef BODY
#   undef RET
#endif