#include "Debug.h"

static int printSimpleOpCode(const char* name, int offset) {
    printf("%s", name);
    return offset + 1;
}

static int printConstantOpCode(const char* name, CodeBuffer* buffer, int offset) {
    printf("OP_CONSTANT: %i", buffer->values.values[buffer->data[offset + 1]]);
    return offset + 2;
}

static int disassembleOpCode(CodeBuffer* buffer, int offset) {
    uint8_t opcode = buffer->data[offset];
   
    switch (opcode) {
        case OP_CONSTANT: return printConstantOpCode("OP_CONSTANT", buffer, offset);
        case OP_ADD:      return printSimpleOpCode("OP_ADD", offset);
        case OP_MULTIPLY: return printSimpleOpCode("OP_MULTIPLY", offset);
        case OP_DIVIDE:   return printSimpleOpCode("OP_DIVIDE", offset);
        case OP_SUBSTRACT:return printSimpleOpCode("OP_SUBSTRACT", offset);
        case OP_NEGATE:   return printSimpleOpCode("OP_NEGATE", offset);
        case OP_RETURN:   return printSimpleOpCode("OP_RETURN", offset);
        case OP_SIN:      return printSimpleOpCode("OP_SIN", offset);
        case OP_COS:      return printSimpleOpCode("OP_COS", offset);
        case OP_TAN:      return printSimpleOpCode("OP_TAN", offset);
        default:
            fprintf(stderr, "[ERROR] Unknown upcode: %d", opcode);
            return offset + 1;
    }
}

void disassembleCodeBuffer(CodeBuffer* buffer) {
    printf("\n\n== STACK TRACE ==\n");
    for (int offset = 0; offset < buffer->count;) {
        printf("\n%i -> ", offset);
        offset = disassembleOpCode(buffer, offset);
    }
    printf("\n");
}
