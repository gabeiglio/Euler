#include "Parser.h"

void initParser(Parser* parser, Lexer* lexer, CodeBuffer* buffer, Hashmap* map) {
    parser->lexer = lexer;
    parser->currentToken = lexToken(parser->lexer);
    parser->previousToken = parser->currentToken;
    parser->buffer = buffer;

    parser->map = map;
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

    fprintf(stderr, "[ERROR] Did not expect token of type %i\n", parser->previousToken.type);
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
    fprintf(stderr, "[ERROR]: Function not defined\n");
    exit(1);
}

static void expression(Parser* parser);

static void parseGrouping(Parser* parser) {
    consume(parser, tok_open_paren);
    expression(parser);
    consume(parser, tok_close_paren);
}

static void parseNumber(Parser* parser) {
    writeBytes(parser->buffer, OP_CONSTANT, writeConstant(parser->buffer, NUMBER_CONST(strtod(parser->previousToken.start, NULL )))); 
    advanceParser(parser);
}

static void parseIdentifier(Parser* parser) {
    if (parser->currentToken.type == tok_equals) return;
    
    char lexeme[parser->previousToken.length];
    lexeme[parser->previousToken.length] = '\0';

    for (int i = 0; i < parser->previousToken.length; i++)
        lexeme[i] = parser->previousToken.start[i];

    double value = getEntry(parser->map, lexeme);

    writeBytes(parser->buffer, OP_CONSTANT, writeConstant(parser->buffer, NUMBER_CONST(value)));
    advanceParser(parser);
}

static void parseTerminal(Parser* parser) {
    switch (parser->previousToken.type) {
        case number:     parseNumber(parser); break;
        case identifier: parseIdentifier(parser); break;
        case tok_open_paren: parseGrouping(parser); break;
        default: 
             fprintf(stderr, "[ERROR] Token not recognized\n");
    }
}

static void parseCallOrAssignmentExpr(Parser* parser) {
    if (parser->previousToken.type == identifier) {
        //function call
        if (parser->currentToken.type == tok_open_paren) {
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
    if (parser->previousToken.type == tok_dash) {
        advanceParser(parser);
        parseUnary(parser);
        return writeByte(parser->buffer, OP_NEGATE);
    }
    parseCallOrAssignmentExpr(parser);
}

static void parsePower(Parser* parser) {
    parseUnary(parser);

    if (parser->previousToken.type == tok_power) {
        advanceParser(parser);
        parsePower(parser);
        writeByte(parser->buffer, OP_POWER);
    }
}

static void parseTerm(Parser* parser) {
    parsePower(parser);

    if (parser->previousToken.type == tok_star || parser->previousToken.type == tok_slash) {
        tok_type operator = parser->previousToken.type;
        advanceParser(parser);
        parseTerm(parser);
        writeByte(parser->buffer, (operator == tok_star) ? OP_MULTIPLY : OP_DIVIDE); 
    }
}

static void parseSum(Parser* parser) {
    parseTerm(parser);

    if (parser->previousToken.type == tok_plus || parser->previousToken.type == tok_dash) {
        tok_type operator = parser->previousToken.type;
        advanceParser(parser);
        parseSum(parser);
        writeByte(parser->buffer, (operator == tok_plus) ? OP_ADD : OP_SUBSTRACT);
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
