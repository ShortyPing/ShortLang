//
// Created by shortping on 10.05.22.
//

#include "tokenizer.h"
#include "../config.h"
#include "../lifecycle.h"
#include "../parser/ast.h"
#include "../const.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

Token **tokenBuffer;
unsigned posPtr;
unsigned bufferSize;
const char weirdCharacters[] = {
        '\n',
        ' ',
        '\t'
};



#define _(x) case x: return #x;

char *TokenType_ToString(TokenType t) {
	switch (t) {
		_(UNKNOWN);
		_(IDENTIFIER);
		_(STRING_LITERAL);
		_(INT_LITERAL);
		_(CHAR_LITERAL);
		_(LPARENTHESE);
		_(RPARENTHESE);
		_(LBRACE);
		_(RBRACE);
		_(LBRACKET);
		_(RBRACKET);
		_(DASH);
		_(PLUS);
		_(STAR);
		_(SLASH);
		_(COLON);
		_(QUESTION);
		_(GREATER);
		_(SMALLER);
		_(EQUALS);
		_(DOT);
		_(COMMA);
		_(HASHTAG);
		_(SEMICOLON);
	}
}

#undef _

void Tokenizer_Init() {
    posPtr = 0;
    bufferSize = 10;
    tokenBuffer = malloc(sizeof(Token *) * 50);
    DEBUG("Initialized Tokenizer (buff_size:%d, pos:%d)\n", bufferSize, posPtr);
    Tokenizer_ClearBuffer(0);
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

void parseSyntaxTokens(TokenType *type, char c) {
    if (c == Tokenizer_GetToken(LPARENTHESE)) *type = LPARENTHESE;
    if (c == Tokenizer_GetToken(RPARENTHESE)) *type = RPARENTHESE;
    if (c == Tokenizer_GetToken(LBRACKET)) *type = LBRACKET;
    if (c == Tokenizer_GetToken(RBRACKET)) *type = RBRACKET;
    if (c == Tokenizer_GetToken(LBRACE)) *type = LBRACE;
    if (c == Tokenizer_GetToken(RBRACE)) *type = RBRACE;
    if (c == Tokenizer_GetToken(COLON)) *type = COLON;
    if (c == Tokenizer_GetToken(SEMICOLON)) *type = SEMICOLON;
    if (c == Tokenizer_GetToken(EQUALS)) *type = EQUALS;
    if (c == Tokenizer_GetToken(STAR)) *type = STAR;
    if (c == Tokenizer_GetToken(SLASH)) *type = SLASH;
    if (c == Tokenizer_GetToken(DASH)) *type = DASH;
    if (c == Tokenizer_GetToken(SMALLER)) *type = SMALLER;
    if (c == Tokenizer_GetToken(GREATER)) *type = GREATER;
    if (c == Tokenizer_GetToken(PLUS)) *type = PLUS;
    if (c == Tokenizer_GetToken(COMMA)) *type = COMMA;

}

unsigned isSpecialCharacter(TokenType type) {
    return type != IDENTIFIER && type != INT_LITERAL && type != STRING_LITERAL;
}

void Tokenizer_Analyze(char *str) {
    size_t len = strlen(str);
    const int buffSize = 2048;
    char buff[buffSize];
    clearBuff(buff, buffSize);
    unsigned tokPos = 0;
    TokenType type = UNKNOWN;
    unsigned line = 1;
    for (int i = 0; i < len; i++) {

        // increment line at newline
        if (str[i] == '\n') {
            line++;
            continue;
        }
		
        // BEGIN: STRING LITERAL TOKENIZING
        if (str[i] == Tokenizer_GetToken(STRING_LITERAL)) {
            if(str[i-1] == '\\') {
                buff[tokPos++] = str[i];
                continue;
            }
            if (type == STRING_LITERAL) {
                type = UNKNOWN;
                Tokenizer_AddToken(STRING_LITERAL, tokPos, line, buff);
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
                LifeCycle_Exit(1);
                return;
            }
            buff[tokPos++] = str[i];
            continue;
        }
        // END: STRING LITERAL TOKENIZING
	
	// Check for some weird whitespace characters
	if(str[i] == ' ' || str[i] == '\t')
		continue;

        if (isdigit(str[i]) && (type == UNKNOWN || type == INT_LITERAL)) {
            type = INT_LITERAL;
            buff[tokPos++] = str[i];
            continue;
        }

        if (!isdigit(str[i]) && type == INT_LITERAL) {
            i--;
            Tokenizer_AddToken(INT_LITERAL, tokPos, line, buff);
            resetControlVariables(buff, buffSize, &tokPos);
            type = UNKNOWN;
            continue;
        }
        if (str[i] == ' ') {
            buff[tokPos++] = str[i];
            Tokenizer_AddToken(UNKNOWN, tokPos, line, buff);
            resetControlVariables(buff, buffSize, &tokPos);
            type = UNKNOWN;
            continue;
        }
        if (type == UNKNOWN) {
            parseSyntaxTokens(&type, str[i]);
            if (type != UNKNOWN) {
                buff[tokPos++] = str[i];
                Tokenizer_AddToken(type, tokPos, line, buff);
                resetControlVariables(buff, buffSize, &tokPos);
                type = UNKNOWN;
                continue;
            }
            type = IDENTIFIER;
            buff[tokPos++] = str[i];
            if(!isalpha(str[i+1]) && str[i+1] != '_') {
                Tokenizer_AddToken(type, tokPos, line, buff);
                resetControlVariables(buff, buffSize, &tokPos);
                type = UNKNOWN;
                continue;
            }
            continue;
        }
        type = IDENTIFIER;
        buff[tokPos++] = str[i];
        if(!isalpha(str[i+1]) && str[i + 1] != '_') {
            Tokenizer_AddToken(type, tokPos, line, buff);
            resetControlVariables(buff, buffSize, &tokPos);
            type = UNKNOWN;
            continue;
        }

    }
    // tokenizing finished, use tokenBuffer* to pass into parser

}


unsigned Tokenizer_AddToken(TokenType type, unsigned pos, unsigned line, char *val) {
    if(type != 0)
        DEBUG("Added token type %s value %s (%d)\n", TokenType_ToString(type), val, line);
    if (posPtr == (bufferSize - 1)) {
        tokenBuffer = realloc(tokenBuffer, (bufferSize + 50) * sizeof(Token));
        bufferSize += 50;
        Tokenizer_ClearBuffer(1);
    }

    Token *token = tokenBuffer[posPtr++];

    token->pos = pos;
    token->type = type;
    token->value = val;
    token->line = line;

    return posPtr;
}


void Tokenizer_ClearBuffer(unsigned usePos) {
    for (unsigned i = (usePos ? (posPtr + 1) : 0); i < bufferSize; i++) {
        tokenBuffer[i] = malloc(sizeof(Token));
    }
}

// Frees all memory used by tokenizer
void Tokenizer_Invalidate() {
    for (int i = 0; i < bufferSize; i++)
        free(tokenBuffer[i]);
    free(tokenBuffer);
}

#define _(t, c) case t: return c;

// Convert TokenType to an ASCII character; Return 0, if no match is found.
char Tokenizer_GetToken(TokenType type) {
    switch (type) {
        _(RPARENTHESE, ')')
        _(LPARENTHESE, '(')
        _(RBRACKET, ']')
        _(LBRACKET, '[')
        _(RBRACE, '}')
        _(LBRACE, '{')
        _(COLON, ':')
        _(COMMA, ',')
        _(DASH, '-')
        _(DOT, '.')
        _(EQUALS, '=')
        _(GREATER, '>')
        _(SMALLER, '<')
        _(HASHTAG, '#')
        _(STRING_LITERAL, '"')
        _(PLUS, '+')
        _(QUESTION, '?')
        _(SLASH, '/')
        _(STAR, '*')
        _(CHAR_LITERAL, '\'')
        _(SEMICOLON, ';')
        default:
            return '\0';
    }
}

#undef _
