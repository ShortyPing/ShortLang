//
// Created by shortping on 10.05.22.
//

#include "tokenizer.h"
#include "../config.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

SLANG_Token **tokenBuffer;
unsigned posPtr;
unsigned bufferSize;


void SLANG_Tokenizer_Init() {
    posPtr = 0;
    bufferSize = 10;
    tokenBuffer = malloc(sizeof(SLANG_Token *) * 10);
    if (SLANG_CFG_VerboseMode)
        printf("Initialized Tokenizer (buff_size:%d, pos:%d)\n", bufferSize, posPtr);
    SLANG_Tokenizer_ClearBuffer(0);
}

void clearBuff(char *buff, unsigned len) {
    for (int i = 0; i < len; i++) {
        buff[i] = 0x0;
    }
}

void SLANG_Tokenizer_Analyze(char *str) {
    size_t len = strlen(str);
    const int buffSize = 128;
    char buff[buffSize];
    clearBuff(buff, buffSize);
    int tokPos = 0;
    SLANG_TokenType type = UNKNOWN;
    int line = 1;
    for (int i = 0; i < len; i++) {

        if(str[i] == 0x0a) {
            line++;
        }

        // check if current char is string literal (")
        if (str[i] == SLANG_Tokenizer_GetToken(STRING_LITERAL)) {
            // if scope type is string literal it closes current string literal and submits the token to the buffer
            // else it continues to add characters to buffer
            if (type == STRING_LITERAL) {
                type = UNKNOWN;
                SLANG_Tokenizer_AddToken(STRING_LITERAL, i, line, buff);
                tokPos = 0;
                clearBuff(buff, buffSize);
                continue;
            } else {
                type = STRING_LITERAL;
                continue;
            }

        } else {
            if (type == STRING_LITERAL) {
                buff[tokPos++] = str[i];
                continue;
            }
        }

        // Check if is braces or parentheses etc. and submit them as tokens
        if(str[i] == SLANG_Tokenizer_GetToken(LPARENTHESE)) {
            buff[tokPos++] = str[i];
            SLANG_Tokenizer_AddToken(LPARENTHESE, i, line, buff);
            clearBuff(buff, buffSize);
            tokPos = 0;
            continue;
        }
        if(str[i] == SLANG_Tokenizer_GetToken(RPARENTHESE)) {
            buff[tokPos++] = str[i];
            SLANG_Tokenizer_AddToken(RPARENTHESE, i, line, buff);
            clearBuff(buff, buffSize);
            tokPos = 0;
            continue;
        }

        // check if is digit, when there is not int literal start a new one else add to buffer... when it detects a non-digit
        // character in INT_LITERAL scope then terminate the literal and submit the token
        if (isdigit(str[i])) {
            if (type != INT_LITERAL) {
                type = INT_LITERAL;
            }
            buff[tokPos++] = str[i];
            continue;
        } else {
            if(type == INT_LITERAL) {
                type = UNKNOWN;
                SLANG_Tokenizer_AddToken(INT_LITERAL, i, line, buff);
            }
            clearBuff(buff, buffSize);
            tokPos = 0;
        }



        // buffer clear... should not be executed
        // this clears the buffer if anything wrong happens
        clearBuff(buff, buffSize);
        tokPos = 0;
    }
}

unsigned SLANG_Tokenizer_AddToken(SLANG_TokenType type, unsigned pos, unsigned line, char *val) {
    printf("Added token type %d value %s\n", type, val);
    if (posPtr == (bufferSize - 1)) {
        tokenBuffer = realloc(tokenBuffer, (bufferSize + 10) * sizeof(SLANG_Token));
        bufferSize += 10;
        SLANG_Tokenizer_ClearBuffer(1);
    }


    SLANG_Token *token = tokenBuffer[posPtr++];

    token->pos = pos;
    token->type = type;
    token->value = val;
    token->line = line;

    return posPtr;
}


void SLANG_Tokenizer_ClearBuffer(unsigned usePos) {

    for (int i = (usePos ? (posPtr + 1) : 0); i < bufferSize; i++) {
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
char SLANG_Tokenizer_GetToken(SLANG_TokenType type) {
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
