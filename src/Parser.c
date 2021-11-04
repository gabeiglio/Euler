#include "Parser.h"

void initParser(Parser* parser, Lexer* lexer) {
    parser->lexer = lexer;
    parser->currentToken = lexToken(parser->lexer);
    parser->previousToken = parser->currentToken;
}

static void advanceParser(Parser* parser) {
    parser->previousToken = parser->currentToken;
    parser->currentToken = lexToken(parser->lexer); 
}

static int writeConstant(CodeBuffer* buffer, int value) {
    return 0;
}

static void parseBinary() {
    
}

static void parseNumber(Parser* parser) {
    int number = atoi(parser->currentToken.start);   
}

void parse(Parser* parser) {
    while(parser->currentToken.type != tok_eof) {
        printf("%i", parser->currentToken.type);        
        advanceParser(parser);
    }
}
