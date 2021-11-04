#ifndef constantbuffer_h
#define constantbuffer_h

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    int count;

    int* values;
} ConstantBuffer;

void initConstantBuffer(ConstantBuffer* buffer);
void freeConstantBuffer(ConstantBuffer* buffer);
int writeConstantBuffer(ConstantBuffer* buffer, int value);

#endif