#ifndef lexer_h
#define lexer_h

#include <ctype.h>
#include "Token.h"

typedef struct {
    const char* source;
    const char* start;
    const char* current;
} Lexer;

void initLexer(Lexer* lexer, const char* input);
Token lexToken(Lexer* lexer);

#endif