//
// Created by shortping on 13.05.22.
//

#include "ast.h"
#include <stdlib.h>
#include "../memory.h"

AbstractSyntaxTree *currentTree;

ASTNode *SLANG_AST_CreateNode() {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->value = nullPtr;
    node->left = nullPtr;
    node->right = nullPtr;
    return node;
}

void SLANG_AST_Create(SLANG_Token** buff) {
    currentTree = malloc(sizeof(AbstractSyntaxTree));
    currentTree->root = nullPtr;
}



void invalidateNode(ASTNode* node) {
    if(node->left != nullPtr)
        invalidateNode(node->left);
    if(node->right != nullPtr)
        invalidateNode(node->right);
    free(node);

}

void SLANG_AST_Invalidate() {
    if(currentTree->root != nullPtr)
        invalidateNode(nullPtr);
}
