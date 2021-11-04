#include "CodeBuffer.h"

void initCodeBuffer(CodeBuffer* b) {
    b->size = 8;
    b->count = 0;
    
    uint8_t* tmp = malloc(sizeof(uint8_t) * b->size);

    if (!tmp) {
        fprintf(stderr, "[ERROR] Could not allocate more memory");
        exit(1);
    }

    b->data = tmp;
    initConstantBuffer(&b->values);
}

void writeCodeBuffer(CodeBuffer* b, uint8_t byte) {
    if (b->size < b->count + 1) {
        b->size *= 2;

        uint8_t* tmp = realloc(b->data, sizeof(uint8_t) * b->size);

        if (!tmp) {
            fprintf(stderr, "[ERROR] Could not allocate more memory");
            exit(1);
        }

        b->data = tmp;
    }

    b->data[b->count] = byte;
    b->count++;
}

void freeCodeBuffer(CodeBuffer* b) {
    b->size = 0;
    b->count = 0;
    free(b->data);
    freeConstantBuffer(&b->values);
}
