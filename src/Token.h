#ifndef token_h
#define token_h

typedef enum {
    number,
    identifier,
    op_plus,
    op_minus,
    op_times,
    op_divide,
    open_paren,
    close_paren,
    tok_eof,
    tok_error
} tok_type;

typedef struct {
    const char* start;
    int length;
    tok_type type;
} Token;

#endif
