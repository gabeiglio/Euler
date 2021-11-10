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

static void consume(Parser* parser, tok_type type) {
    if (parser->previousToken.type == type) {
        advanceParser(parser);
        return;
    }

    //Change this to explaing semantic errors
    exit(1);
}

static void expression(Parser* parser);

static void parseGrouping(Parser* parser) {
    consume(parser, open_paren);
    expression(parser);
    consume(parser, close_paren);
}

static void parseNumber(Parser* parser) {
    int number = atoi(parser->previousToken.start); 
    writeBytes(parser->buffer, OP_CONSTANT, writeConstant(parser->buffer, number)); 
    advanceParser(parser);
}

static void parseTerminal(Parser* parser) {
    switch (parser->previousToken.type) {
        case number: parseNumber(parser); break;
        case open_paren: parseGrouping(parser); break;
        default: exit(1);
    }
}

static void parseUnary(Parser* parser) {
   if (parser->previousToken.type == op_minus) {
       advanceParser(parser);
       parseTerminal(parser);
       return writeByte(parser->buffer, OP_NEGATE);
   }

   parseTerminal(parser);
}

static void parseTerm(Parser* parser) {
    parseUnary(parser);

    if (parser->previousToken.type == op_times || parser->previousToken.type == op_divide) {
        tok_type operator = parser->previousToken.type;
        advanceParser(parser);
        parseTerm(parser);
        writeByte(parser->buffer, (operator == op_times) ? OP_MULTIPLY : OP_DIVIDE); 
    }
}

static void parseSum(Parser* parser) {
    parseTerm(parser);

    if (parser->previousToken.type == op_plus || parser->previousToken.type == op_minus) {
        tok_type operator = parser->previousToken.type;
        advanceParser(parser);
        parseSum(parser);
        writeByte(parser->buffer, (operator == op_plus) ? OP_ADD : OP_SUBSTRACT);
    }
}

static void expression(Parser* parser) {
    parseSum(parser);
}

void parse(Parser* parser) { 
    advanceParser(parser);
    expression(parser);

    writeByte(parser->buffer, OP_RETURN);
}
