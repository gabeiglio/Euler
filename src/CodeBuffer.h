#ifndef codebuffer_h
#define codebuffer_h

#include <stdio.h>
#include <stdlib.h>

#include "ConstantBuffer.h"

typedef enum {
    OP_CONSTANT,
    OP_ADD,
    OP_SUBSTRACT,
    OP_DIVIDE,
    OP_MULTIPLY,
    OP_NEGATE,
    OP_SIN,
    OP_COS,
    OP_TAN,
    OP_RETURN
} op_code;

typedef struct {
    int size;
    int count;

    uint8_t* data;
    ConstantBuffer values;    
} CodeBuffer;

void initCodeBuffer(CodeBuffer* b);
void writeCodeBuffer(CodeBuffer* b, uint8_t byte);
void freeCodeBuffer(CodeBuffer* b);

#endif
