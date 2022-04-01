#include "Lexer.h"

void initLexer(Lexer* lexer, const char* input) {
    lexer->source = input;
    lexer->start = lexer->source;
    lexer->current = lexer->source;
}

static int getLexemeLength(Lexer* lexer) {
    return (int)(lexer->current - lexer->start);
}

static Token createToken(Lexer* lexer, tok_type type) {
    Token token = {lexer->start, getLexemeLength(lexer), type};

    //reset the lexer indicators
    lexer->start = lexer->current;
    return token;
}

Token lexToken(Lexer* lexer) {
    while (*lexer->current == ' ' || *lexer->current == '\t')
        lexer->current++;
    lexer->start = lexer->current;
    
    if (isdigit(*lexer->current)) {
        while (isdigit(*lexer->current) || *lexer->current == '.')
            lexer->current++;

        return createToken(lexer, number);
    }

    //Check for identifier
    if (isalpha(*lexer->current)) {
        while (isalpha(*lexer->current))
            lexer->current++;

        return createToken(lexer, identifier);
    }

    switch (*lexer->current++) {
        case '+':  return createToken(lexer, tok_plus);
        case '-':  return createToken(lexer, tok_dash);
        case '*':  return createToken(lexer, tok_star);
        case '/':  return createToken(lexer, tok_slash);
        case ')':  return createToken(lexer, tok_close_paren);
        case '(':  return createToken(lexer, tok_open_paren);
        case '=':  return createToken(lexer, tok_equals);
        case '\0':
        case '\n': return createToken(lexer, tok_eof);
        default:   return createToken(lexer, tok_error);
    }
}
