#ifndef vm_h
#define vm_h

#include "CodeBuffer.h"

#define STACK_MAX 256

typedef struct {
    CodeBuffer* buffer;
    uint8_t* ip;

    int stack[STACK_MAX];
    int* stackTop;
} VM;

void initVM(VM* vm, CodeBuffer* buffer);
int interpret(VM* vm);

#endif
