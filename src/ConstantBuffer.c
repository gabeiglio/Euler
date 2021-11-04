#include "ConstantBuffer.h"

void initConstantBuffer(ConstantBuffer* buffer) {
    buffer->size = 8;
    buffer->count = 0;

    int* tmp = malloc(sizeof(int) * buffer->size);

    if (!tmp) {
        fprintf(stderr, "[ERROR] Could not allocate more memory");
        exit(1);
    }

    buffer->values = tmp;
}

// return the index if the allocated valuer on the constant buffer
int writeConstantBuffer(ConstantBuffer* buffer, int value) {
    if (buffer->size < buffer->count + 1) {
        buffer->size *= 2;

        int* tmp = realloc(buffer->values, sizeof(int) * buffer->size);

        if (!tmp) {
            fprintf(stderr, "[ERROR] Could not allocate more memory");
            exit(1);
        }

        buffer->values = tmp;
    }

    buffer->values[buffer->count] = value;
    buffer->count++;

    //return the index aka the count
    return buffer->count - 1;
}

void freeConstantBuffer(ConstantBuffer* buffer) {
    buffer->size = 0;
    buffer->count = 0;
    free(buffer->values);
}