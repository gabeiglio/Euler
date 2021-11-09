#include "Parser.h"

void initParser(Parser* parser, Lexer* lexer, CodeBuffer* buffer) {
    parser->lexer = lexer;
    parser->currentToken = lexToken(parser->lexer);
    parser->previousToken = parser->currentToken;
    parser->buffer = buffer;
}

static void advanceParser(Parser* parser) {
    parser->previousToken = parser->currentToken;
    parser->currentToken = lexToken(parser->lexer); 
}

static void writeByte(CodeBuffer* buffer, uint8_t byte) {
    writeCodeBuffer(buffer, byte);
}

static void writeBytes(CodeBuffer* buffer, uint8_t byte1, uint8_t byte2) {
    writeByte(buffer, byte1);
    writeByte(buffer, byte2);
}

static int writeConstant(CodeBuffer* buffer, int value) {
    return writeConstantBuffer(&buffer->values, value);
}

static void parseBinary(Parser* parser) {
    
}

static void parseNumber(Parser* parser) {
    int number = atoi(parser->currentToken.start); 
    writeBytes(parser->buffer, OP_CONSTANT, writeConstant(parser->buffer, number));
      
}

void parse(Parser* parser) {
    if (parser->currentToken.type == number)
        parseNumber(parser);
    advanceParser(parser); 
}
