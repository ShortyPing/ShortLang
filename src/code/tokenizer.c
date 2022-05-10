//
// Created by shortping on 10.05.22.
//

#include "tokenizer.h"
#include "../config.h"
#include <stdlib.h>
#include <stdio.h>

SLANG_Token **tokenBuffer;
unsigned posPtr;
unsigned bufferSize;


void SLANG_Tokenizer_Init() {
    posPtr = 0;
    bufferSize = 10;
    tokenBuffer = malloc(sizeof(SLANG_Token*) * 10);
    if (SLANG_CFG_VerboseMode)
        printf("Initialized Tokenizer (buff_size:%d, pos:%d)\n", bufferSize, posPtr);
    SLANG_Tokenizer_ClearBuffer(0);
}

unsigned SLANG_Tokenizer_AddToken(SLANG_TokenType type, unsigned pos, char *val) {
    if (posPtr == (bufferSize-1)) {
        tokenBuffer = realloc(tokenBuffer, (bufferSize + 10) * sizeof(SLANG_Token));
        bufferSize += 10;
        SLANG_Tokenizer_ClearBuffer(1);
    }


    SLANG_Token *token = tokenBuffer[posPtr++];

    token->pos = pos;
    token->type = type;
    token->value = val;

    return posPtr;
}

void SLANG_Tokenizer_ClearBuffer(unsigned usePos) {

    for (int i = (usePos ? (posPtr+1) : 0); i < bufferSize; i++) {
        tokenBuffer[i] = malloc(sizeof(SLANG_Token));
    }
}

// Frees all memory used by tokenizer
void SLANG_Tokenizer_Invalidate() {
    for (int i = 0; i < bufferSize; i++)
        free(tokenBuffer[i]);
    free(tokenBuffer);
}

// Transfer tokentype to ascii char > returns 0x00 when not found
char SLANG_GetToken(SLANG_TokenType type) {
    switch (type) {
        case RPARENTHESE:
            return 0x29;
        case LPARENTHESE:
            return 0x28;
        case RBRACKET:
            return 0x5D;
        case LBRACKET:
            return 0x5B;
        case RBRACE:
            return 0x7B;
        case LBRACE:
            return 0x7D;
        case COLON:
            return 0x3A;
        case COMMA:
            return 0x2C;
        case DASH:
            return 0x2D;
        case DOT:
            return 0x2C;
        case EQUALS:
            return 0x3D;
        case GREATER:
            return 0x3E;
        case HASHTAG:
            return 0x23;
        case STRING_LITERAL:
            return 0x22;
        case PLUS:
            return 0x2B;
        case QUESTION:
            return 0x3F;
        case SLASH:
            return 0x2F;
        case SMALLER:
            return 0x3C;
        case STAR:
            return 0x2A;
        default:
            return 0x0;
    }
}
