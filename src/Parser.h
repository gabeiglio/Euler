#ifndef parser_h
#define parser_h

//Debug
#include <stdio.h>

#include "Token.h"
#include "Lexer.h"
#include "CodeBuffer.h"
#include "ConstantBuffer.h"

typedef struct {
    Lexer* lexer;
    Token currentToken;
    Token previousToken;

    CodeBuffer* buffer;
} Parser;

void initParser(Parser* parser, Lexer* lexer, CodeBuffer* buffer);
void parse(Parser* parser);
#endif
