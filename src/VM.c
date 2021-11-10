#include "VM.h"
#include <stdio.h>

void initVM(VM* vm, CodeBuffer* buffer) {
    vm->buffer = buffer;
    vm->ip = buffer->data;
    vm->stackTop = vm->stack;
}

static void resetStack(VM* vm) {
    vm->stackTop = vm->stack;
}

static void push(VM* vm, int value) {
    *vm->stackTop = value;
    vm->stackTop++;
}

static int pop(VM* vm) {
    vm->stackTop--;
    return *vm->stackTop;
}

static int peek(VM* vm, int distance) {
    return vm->stackTop[-1 - distance];
}

int interpret(VM* vm) {
#define READ_BYTE() (*vm->ip++)
#define READ_CONSTANT() (vm->buffer->values.values[READ_BYTE()])
    for (;;) {
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                int val = READ_CONSTANT();
                push(vm, val);
                break;
            }
            case OP_NEGATE: {
                push(vm, -pop(vm));
                break;
            }
            case OP_ADD: {
                int rhs = pop(vm);
                int lhs = pop(vm);
                push(vm, lhs + rhs);
                break;
            }
            case OP_SUBSTRACT: {
                int rhs = pop(vm);
                int lhs = pop(vm);
                push(vm, lhs - rhs);
                break;
            }
            case OP_MULTIPLY: {
                int rhs = pop(vm);
                int lhs = pop(vm);
                push(vm, lhs * rhs);
                break;
            } 
            case OP_DIVIDE: {
                int rhs = pop(vm);
                int lhs = pop(vm);
                push(vm, lhs / rhs);
                break;
            } 
            case OP_RETURN: return pop(vm);
        }
    }
#undef READ_BYTE
#undef READ_CONSTANT
}

