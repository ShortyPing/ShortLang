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
const char weirdCharacters[] = {
        '\n',
        ' ',
        '\t'
};

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

void resetControlVariables(char *buff, unsigned len, unsigned *tokPos) {
    clearBuff(buff, len);
    *tokPos = 0;
}

unsigned isWeirdCharacter(char c) {
    int i = 0;
    while (weirdCharacters[i] != 0) {
        if (weirdCharacters[i] == c) {
            return 1;
        }
        i++;
    }
    return 0;
}

SLANG_TokenType getType(char c) {
    if (isdigit(c)) {
        return INT_LITERAL;
    }
    if (isalpha(c)) {
        return IDENTIFIER;
    }
    if (c == SLANG_Tokenizer_GetToken(LPARENTHESE)) return LPARENTHESE;
    if (c == SLANG_Tokenizer_GetToken(RPARENTHESE)) return RPARENTHESE;
    if (c == SLANG_Tokenizer_GetToken(LBRACE)) return LBRACE;
    if (c == SLANG_Tokenizer_GetToken(RBRACE)) return RBRACE;
    if (c == SLANG_Tokenizer_GetToken(RBRACKET)) return RBRACKET;
    if (c == SLANG_Tokenizer_GetToken(LBRACKET)) return LBRACKET;
    return UNKNOWN;
}

unsigned isSpecialCharacter(SLANG_TokenType type) {
    return type != IDENTIFIER && type != INT_LITERAL && type != STRING_LITERAL;
}

void SLANG_Tokenizer_Analyze(char *str) {
    size_t len = strlen(str);
    const int buffSize = 128;
    char buff[buffSize];
    clearBuff(buff, buffSize);
    unsigned tokPos = 0;
    SLANG_TokenType type = UNKNOWN;
    unsigned line = 1;
    for (int i = 0; i < len; i++) {

        // increment line at newline
        if (str[i] == '\n')
            line++;

        // check if char is string literal
        if (SLANG_Tokenizer_GetToken(STRING_LITERAL) == str[i]) {
            // check if current type is string literal
            // when yes, push token else create new string literal
            if (type == STRING_LITERAL) {
                type = UNKNOWN;
                SLANG_Tokenizer_AddToken(STRING_LITERAL, i, line, buff);
                resetControlVariables(buff, len, &tokPos);
                continue;
            }
            // create new string literal
            type = STRING_LITERAL;
            continue;
        }

        if (type == STRING_LITERAL) {
            buff[tokPos++] = str[i];
            continue;
        }

        if (isWeirdCharacter(str[i])) {
            if (type != UNKNOWN) {
                SLANG_Tokenizer_AddToken(type, i, line, buff);
                resetControlVariables(buff, buffSize, &tokPos);
            }
            continue;
        }

        if (tokPos == 0)
            type = getType(str[i]);

        SLANG_TokenType t = getType(str[i]);
        if ((type == t || (type == IDENTIFIER && t == INT_LITERAL)) && type != UNKNOWN) {
            buff[tokPos++] = str[i];
            if (isSpecialCharacter(type)) {
                SLANG_Tokenizer_AddToken(type, i, line, buff);
                type = UNKNOWN;
                resetControlVariables(buff, buffSize, &tokPos);
                continue;
            }
        } else {
            SLANG_Tokenizer_AddToken(type, i, line, buff);
            type = UNKNOWN;
            clearBuff(buff, buffSize);
            continue;
        }
        if (i + 1 >= len) {
            SLANG_Tokenizer_AddToken(type, i, line, buff);
        }

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
