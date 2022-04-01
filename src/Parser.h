#ifndef parser_h
#define parser_h

//Debug
#include <string.h>

#include "Token.h"
#include "Lexer.h"
#include "CodeBuffer.h"
#include "ConstantBuffer.h"
#include "Hashmap.h"

typedef struct {
    Lexer* lexer;
    Token currentToken;
    Token previousToken;

    Hashmap* map;
    CodeBuffer* buffer;
} Parser;

void initParser(Parser* parser, Lexer* lexer, CodeBuffer* buffer, Hashmap* map);
void parse(Parser* parser);
#endif
