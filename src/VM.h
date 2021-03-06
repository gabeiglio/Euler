#ifndef vm_h
#define vm_h

#include <math.h>

#include "Hashmap.h"
#include "CodeBuffer.h"

#define STACK_MAX 256

typedef struct {
    CodeBuffer* buffer;
    uint8_t* ip;

    Constant stack[STACK_MAX];
    Constant* stackTop;

    Hashmap* map;
} VM;

void initVM(VM* vm, Hashmap* map);
double interpret(VM* vm, CodeBuffer* buffer);

#endif
