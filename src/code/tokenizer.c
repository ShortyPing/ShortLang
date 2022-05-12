//
// Created by shortping on 10.05.22.
//

#include "tokenizer.h"
#include "../config.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../lifecycle.h"
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
    tokenBuffer = malloc(sizeof(SLANG_Token *) * 50);
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

void parseSyntaxTokens(SLANG_TokenType *type, char c) {
    if (c == SLANG_Tokenizer_GetToken(LPARENTHESE)) *type = LPARENTHESE;
    if (c == SLANG_Tokenizer_GetToken(RPARENTHESE)) *type = RPARENTHESE;
    if (c == SLANG_Tokenizer_GetToken(LBRACKET)) *type = LBRACKET;
    if (c == SLANG_Tokenizer_GetToken(RBRACKET)) *type = RBRACKET;
    if (c == SLANG_Tokenizer_GetToken(LBRACE)) *type = LBRACE;
    if (c == SLANG_Tokenizer_GetToken(RBRACE)) *type = RBRACE;
    if (c == SLANG_Tokenizer_GetToken(COLON)) *type = COLON;
    if (c == SLANG_Tokenizer_GetToken(SEMICOLON)) *type = SEMICOLON;
    if (c == SLANG_Tokenizer_GetToken(EQUALS)) *type = EQUALS;
    if (c == SLANG_Tokenizer_GetToken(STAR)) *type = STAR;
    if (c == SLANG_Tokenizer_GetToken(SLASH)) *type = SLASH;
    if (c == SLANG_Tokenizer_GetToken(DASH)) *type = DASH;
    if (c == SLANG_Tokenizer_GetToken(SMALLER)) *type = SMALLER;
    if (c == SLANG_Tokenizer_GetToken(GREATER)) *type = GREATER;
    if (c == SLANG_Tokenizer_GetToken(PLUS)) *type = PLUS;

}

unsigned isSpecialCharacter(SLANG_TokenType type) {
    return type != IDENTIFIER && type != INT_LITERAL && type != STRING_LITERAL;
}

void SLANG_Tokenizer_Analyze(char *str) {
    size_t len = strlen(str);
    const int buffSize = 2048;
    char buff[buffSize];
    clearBuff(buff, buffSize);
    unsigned tokPos = 0;
    SLANG_TokenType type = UNKNOWN;
    unsigned line = 1;
    for (int i = 0; i < len; i++) {

        // increment line at newline
        if (str[i] == '\n') {
            line++;
            continue;
        }

        // BEGIN: STRING LITERAL TOKENIZING
        if (str[i] == SLANG_Tokenizer_GetToken(STRING_LITERAL)) {
            if(str[i-1] == '\\') {
                buff[tokPos++] = str[i];
                continue;
            }
            if (type == STRING_LITERAL) {
                type = UNKNOWN;
                SLANG_Tokenizer_AddToken(STRING_LITERAL, tokPos, line, buff);
                resetControlVariables(buff, buffSize, &tokPos);
                continue;
            }
            type = STRING_LITERAL;
            continue;
        }


        if (type == STRING_LITERAL) {
            if(str[i] == '\\' && str[i-1] != '\\')
                continue;

            if(str[i+1] == '\0') {
                printf("Error: Trying to tokenize unclosed string literal! Aborting...\n");
                SLANG_LIFECYCLE_Exit(1);
                return;
            }
            buff[tokPos++] = str[i];
            continue;
        }
        // END: STRING LITERAL TOKENIZING

        if (isdigit(str[i]) && (type == UNKNOWN || type == INT_LITERAL)) {
            type = INT_LITERAL;
            buff[tokPos++] = str[i];
            continue;
        }

        if (!isdigit(str[i]) && type == INT_LITERAL) {
            i--;
            SLANG_Tokenizer_AddToken(INT_LITERAL, tokPos, line, buff);
            resetControlVariables(buff, buffSize, &tokPos);
            type = UNKNOWN;
            continue;
        }
        if (str[i] == ' ') {
            buff[tokPos++] = str[i];
            SLANG_Tokenizer_AddToken(UNKNOWN, tokPos, line, buff);
            resetControlVariables(buff, buffSize, &tokPos);
            type = UNKNOWN;
            continue;
        }
        if (type == UNKNOWN) {
            parseSyntaxTokens(&type, str[i]);
            if (type != UNKNOWN) {
                buff[tokPos++] = str[i];
                SLANG_Tokenizer_AddToken(type, tokPos, line, buff);
                resetControlVariables(buff, buffSize, &tokPos);
                type = UNKNOWN;
                continue;
            }
            type = IDENTIFIER;
            buff[tokPos++] = str[i];
            if(!isalpha(str[i+1])) {
                SLANG_Tokenizer_AddToken(type, tokPos, line, buff);
                resetControlVariables(buff, buffSize, &tokPos);
                type = UNKNOWN;
                continue;
            }
            continue;
        }
        type = IDENTIFIER;
        buff[tokPos++] = str[i];
        if(!isalpha(str[i+1])) {
            SLANG_Tokenizer_AddToken(type, tokPos, line, buff);
            resetControlVariables(buff, buffSize, &tokPos);
            type = UNKNOWN;
            continue;
        }

    }
}


unsigned SLANG_Tokenizer_AddToken(SLANG_TokenType type, unsigned pos, unsigned line, char *val) {
    if(type != 0)
        printf("Added token type %d value %s (%d)\n", type, val, line);
    if (posPtr == (bufferSize - 1)) {
        tokenBuffer = realloc(tokenBuffer, (bufferSize + 50) * sizeof(SLANG_Token));
        bufferSize += 50;
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
            return ')';
        case LPARENTHESE:
            return '(';
        case RBRACKET:
            return ']';
        case LBRACKET:
            return '[';
        case RBRACE:
            return '}';
        case LBRACE:
            return '{';
        case COLON:
            return ':';
        case COMMA:
            return ',';
        case DASH:
            return '-';
        case DOT:
            return '.';
        case EQUALS:
            return '=';
        case GREATER:
            return '>';
        case HASHTAG:
            return '#';
        case STRING_LITERAL:
            return '"';
        case PLUS:
            return '+';
        case QUESTION:
            return '?';
        case SLASH:
            return '/';
        case SMALLER:
            return '<';
        case STAR:
            return '*';
        case CHAR_LITERAL:
            return '\'';
        case SEMICOLON:
            return ';';
        default:
            return 0x0;
    }
}
