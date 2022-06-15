//
// Created by shorty on 6/15/22.
//

#include "parse.h"
#include <stdlib.h>

TokenType currentTokenType;
unsigned consumePosition;
Token *currentToken;
Token *nextToken;
Token *fallbackToken;

void Parser_Init() {
    currentTokenType = UNKNOWN;
    consumePosition = 0;
    fallbackToken = malloc(sizeof (Token));
    fallbackToken->type = UNKNOWN;
    fallbackToken->pos = 0;
    fallbackToken->line = 0;
    fallbackToken->value = "_____FALLBACK_____TOKEN______";

}

void Parser_ConsumeToken() {
    if(consumePosition > posPtr) return;
    currentToken = tokenBuffer[consumePosition++];
    currentTokenType = currentToken->type;
    if(consumePosition == posPtr) {
        nextToken = fallbackToken;
        return;
    }
    nextToken = tokenBuffer[consumePosition];
}

void Parser_Destroy() {
    free(fallbackToken);

}