#ifndef constantbuffer_h
#define constantbuffer_h

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    int count;

    double* values;
} ConstantBuffer;

void initConstantBuffer(ConstantBuffer* buffer);
void freeConstantBuffer(ConstantBuffer* buffer);
double writeConstantBuffer(ConstantBuffer* buffer, double value);

#endif
