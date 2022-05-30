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


} TokenType;

typedef struct {
    TokenType type;
    unsigned pos;
    char* value;
    unsigned line;
} Token;


void Tokenizer_ClearBuffer(unsigned);
void Tokenizer_Init(void);
void Tokenizer_Invalidate(void);
unsigned Tokenizer_AddToken(TokenType type, unsigned pos, unsigned line, char *val);
char Tokenizer_GetToken(TokenType type);
void Tokenizer_Analyze(char*);
#endif //SLANG_TOKENIZER_H
