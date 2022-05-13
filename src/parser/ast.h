//
// Created by shortping on 13.05.22.
//

#ifndef SLANG_AST_H
#define SLANG_AST_H
#include "../code/tokenizer.h"



extern AbstractSyntaxTree *currentTree;
typedef struct {
    char* value;
    void* left; // this should be type ASTNode* but cannot define itself, so its a void pointer
    void* right; // also for here
} ASTNode;

typedef struct {
    ASTNode *root;
} AbstractSyntaxTree;


void SLANG_AST_Create(SLANG_Token**);
ASTNode *SLANG_AST_CreateNode(void);

void SLANG_AST_Invalidate(void);

#endif //SLANG_AST_H
