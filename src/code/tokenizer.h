//
// Created by shortping on 10.05.22.
//

#ifndef SLANG_TOKENIZER_H
#define SLANG_TOKENIZER_H


typedef enum {

    // General
    UNKNOWN,
    IDENTIFIER,

    // Literals
    STRING_LITERAL,
    INT_LITERAL,
    CHAR_LITERAL,

    // Brackets, Braces and Parentheses
    LPARENTHESE,
    RPARENTHESE,
    LBRACE,
    RBRACE,
    LBRACKET,
    RBRACKET,

    // Symbols
    DASH,
    PLUS,
    STAR,
    SLASH,
    COLON,
    QUESTION,
    GREATER,
    SMALLER,
    EQUALS,
    DOT,
    COMMA,
    HASHTAG,
    SEMICOLON


} SLANG_TokenType;

typedef struct {
    SLANG_TokenType type;
    unsigned pos;
    char* value;
    unsigned line;
} SLANG_Token;


void SLANG_Tokenizer_ClearBuffer(unsigned);
void SLANG_Tokenizer_Init();
void SLANG_Tokenizer_Invalidate();
unsigned SLANG_Tokenizer_AddToken(SLANG_TokenType, unsigned, unsigned, char*);
char SLANG_Tokenizer_GetToken(SLANG_TokenType);
void SLANG_Tokenizer_Analyze(char*);
#endif //SLANG_TOKENIZER_H
