#ifndef token_h
#define token_h

typedef enum {
    number,
    identifier,
    tok_plus,
    tok_dash,
    tok_star,
    tok_slash,
    tok_open_paren,
    tok_close_paren,
    tok_equals,
    tok_eof,
    tok_error
} tok_type;

typedef struct {
    const char* start;
    int length;
    tok_type type;
} Token;

#endif
