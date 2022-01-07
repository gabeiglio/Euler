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

static int writeConstant(CodeBuffer* buffer, Constant value) {
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

static op_code getFunctionOpCode(Token token) {
    char lexeme[token.length];
    lexeme[token.length] = '\0';

    for (int i = 0; i < token.length; i++)
        lexeme[i] = token.start[i];
    
    if (strcmp(lexeme, "sin") == 0) return OP_SIN;
    if (strcmp(lexeme, "cos") == 0) return OP_COS;
    if (strcmp(lexeme, "tan") == 0) return OP_TAN;
    
    //This should not happen
    exit(2);
}

static void expression(Parser* parser);

static void parseGrouping(Parser* parser) {
    consume(parser, open_paren);
    expression(parser);
    consume(parser, close_paren);
}

static void parseNumber(Parser* parser) {
    writeBytes(parser->buffer, OP_CONSTANT, writeConstant(parser->buffer, NUMBER_CONST(strtod(parser->previousToken.start, NULL )))); 
    advanceParser(parser);
}

static void parseIdentifier(Parser* parser) {
    //Create key until lexeme length, if not it will copy the rest of the source
    char key[parser->previousToken.length];
    key[parser->previousToken.length] = '\0';

    for (int i = 0; i < parser->previousToken.length; i++) {
        key[i] = parser->previousToken.start[i];
    }

    printf("parser key: %s, made key: %s\n", parser->previousToken.start, key);
    writeBytes(parser->buffer, OP_CONSTANT, writeConstant(parser->buffer, IDENTIFIER_CONST(key)));
    advanceParser(parser);
}

static void parseTerminal(Parser* parser) {
    switch (parser->previousToken.type) {
        case number:     parseNumber(parser); break;
        case identifier: parseIdentifier(parser); break;
        case open_paren: parseGrouping(parser); break;
        default: exit(1);
    }
}

static void parseCallOrAssignmentExpr(Parser* parser) {
    if (parser->previousToken.type == identifier) {
        //function call
        if (parser->currentToken.type == open_paren) {
            uint8_t opcode = getFunctionOpCode(parser->previousToken);
            advanceParser(parser);
            parseCallOrAssignmentExpr(parser);
            return writeByte(parser->buffer, opcode);
        }

        //assignment expr, not yet implemented
        if (parser->previousToken.type == tok_equals) {
            consume(parser, tok_equals);
        }
    }

    parseTerminal(parser);
}

static void parseUnary(Parser* parser) {   
    if (parser->previousToken.type == op_minus) {
        advanceParser(parser);
        parseUnary(parser);
        return writeByte(parser->buffer, OP_NEGATE);
    }
    parseCallOrAssignmentExpr(parser);
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
