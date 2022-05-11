//
// Created by shortping on 10.05.22.
//

#ifndef SLANG_TOKENIZER_H
#define SLANG_TOKENIZER_H


typedef enum {

    // General
    UNKNOWN = 0x0000,
    IDENTIFIER = 0x0001,

    // Literals
    STRING_LITERAL = 0x0002,
    INT_LITERAL = 0x0003,

    // Brackets, Braces and Parentheses
    LPARENTHESE = 0x0004,
    RPARENTHESE = 0x0005,
    LBRACE = 0x0006,
    RBRACE = 0x0007,
    LBRACKET = 0x0008,
    RBRACKET = 0x0009,

    // Symbols
    DASH = 0x000A,
    PLUS = 0x000B,
    STAR = 0x000C,
    SLASH = 0x000D,
    COLON = 0x000E,
    QUESTION = 0x000F,
    GREATER = 0x0010,
    SMALLER = 0x0011,
    EQUALS = 0x0012,
    DOT = 0x0013,
    COMMA = 0x0014,
    HASHTAG = 0x0015


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
