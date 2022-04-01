#include "VM.h"

void initVM(VM* vm, Hashmap* map) {
    vm->stackTop = vm->stack;

    //Init hashtable and load constants
    vm->map = map;
    setEntry(vm->map, "pi", M_PI);
    setEntry(vm->map, "e", M_E);

    //printf("[Hashmap in vm] Getting pi: %f\n", getEntry(vm->map, "pi"));
}

static void resetStack(VM* vm) {
    vm->stackTop = vm->stack;
}

static void push(VM* vm, Constant value) {
    *vm->stackTop = value;
    vm->stackTop++;
}

static Constant pop(VM* vm) {
    vm->stackTop--;
    return *vm->stackTop;
}

static Constant peek(VM* vm, int distance) {
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
                Constant currentConst = READ_CONSTANT();
                
                if (IS_NUMBER(currentConst)) {
                    push(vm, currentConst);
                    break;
                }

                if (IS_IDENTIFIER(currentConst)) {
                    String* str = AS_IDENTIFIER(currentConst);
                   
                    char key[str->length];
                    key[str->length] = '\0';

                    for (int i = 0; i < str->length; i++)
                        key[i] = str->start[i];

                    double result = getEntry(vm->map, key);

                    if (result != -1)
                        push(vm, NUMBER_CONST(result));
                }
                break;
            }
            case OP_NEGATE: {
                push(vm, NUMBER_CONST(-AS_NUMBER(pop(vm))));
                break;
            }
            case OP_ADD: {
                double rhs = AS_NUMBER(pop(vm));
                double lhs = AS_NUMBER(pop(vm));
                push(vm, NUMBER_CONST(lhs + rhs));
                break;
            }
            case OP_SUBSTRACT: {
                double rhs = AS_NUMBER(pop(vm));
                double lhs = AS_NUMBER(pop(vm));
                push(vm, NUMBER_CONST(lhs - rhs));
                break;
            }
            case OP_MULTIPLY: {
                double rhs = AS_NUMBER(pop(vm));
                double lhs = AS_NUMBER(pop(vm));
                push(vm, NUMBER_CONST(lhs * rhs));
                break;
            } 
            case OP_DIVIDE: {
                double rhs = AS_NUMBER(pop(vm));
                double lhs = AS_NUMBER(pop(vm));
                push(vm, NUMBER_CONST(lhs / rhs));
                break;
            }
            case OP_SIN: {
                push(vm, NUMBER_CONST(sin(AS_NUMBER(pop(vm)))));
                break;
            }
            case OP_COS: {
                push(vm, NUMBER_CONST(cos(AS_NUMBER(pop(vm)))));
                break;
            }
            case OP_TAN: {
                push(vm, NUMBER_CONST(tan(AS_NUMBER(pop(vm)))));
                break;
            }
            case OP_RETURN: return AS_NUMBER(pop(vm));
        }
    }
#undef READ_BYTE
#undef READ_CONSTANT
}

