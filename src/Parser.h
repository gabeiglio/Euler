#ifndef parser_h
#define parser_h

//Debug
#include <stdio.h>

#include "Token.h"
#include "Lexer.h"
#include "CodeBuffer.h"

typedef struct {
    Lexer* lexer;
    Token currentToken;
    Token previousToken;
} Parser;

void initParser(Parser* parser, Lexer* lexer);
void parse(Parser* parser);
#endif
