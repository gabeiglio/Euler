#include "VM.h"

void initVM(VM* vm) {
    vm->stackTop = vm->stack;
}

static void resetStack(VM* vm) {
    vm->stackTop = vm->stack;
}

static void push(VM* vm, double value) {
    *vm->stackTop = value;
    vm->stackTop++;
}

static double pop(VM* vm) {
    vm->stackTop--;
    return *vm->stackTop;
}

static int peek(VM* vm, int distance) {
    return vm->stackTop[-1 - distance];
}

double interpret(VM* vm, CodeBuffer* buffer) {

    vm->buffer = buffer;
    vm->ip = buffer->data;

#define READ_BYTE() (*vm->ip++)
#define READ_CONSTANT() (vm->buffer->values.values[READ_BYTE()])
    for (;;) {
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                double val = READ_CONSTANT();
                push(vm, val);
                break;
            }
            case OP_NEGATE: {
                push(vm, -pop(vm));
                break;
            }
            case OP_ADD: {
                double rhs = pop(vm);
                double lhs = pop(vm);
                push(vm, lhs + rhs);
                break;
            }
            case OP_SUBSTRACT: {
                double rhs = pop(vm);
                double lhs = pop(vm);
                push(vm, lhs - rhs);
                break;
            }
            case OP_MULTIPLY: {
                double rhs = pop(vm);
                double lhs = pop(vm);
                push(vm, lhs * rhs);
                break;
            } 
            case OP_DIVIDE: {
                double rhs = pop(vm);
                double lhs = pop(vm);
                push(vm, lhs / rhs);
                break;
            }
            case OP_SIN: {
                push(vm, sin(pop(vm)));
                break;
            }
            case OP_COS: {
                push(vm, cos(pop(vm)));
                break;
            }
            case OP_TAN: {
                push(vm, tan(pop(vm)));
                break;
            }
            case OP_RETURN: return pop(vm);
        }
    }
#undef READ_BYTE
#undef READ_CONSTANT
}

