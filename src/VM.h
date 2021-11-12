#ifndef vm_h
#define vm_h

#include <math.h>
#include "CodeBuffer.h"

#define STACK_MAX 256

typedef struct {
    CodeBuffer* buffer;
    uint8_t* ip;

    double stack[STACK_MAX];
    double* stackTop;
} VM;

void initVM(VM* vm, CodeBuffer* buffer);
double interpret(VM* vm);

#endif
