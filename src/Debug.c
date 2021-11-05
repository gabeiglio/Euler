#include "Debug.h"

void disassembleCodeBuffer(CodeBuffer* buffer) {

}

int disassembleOpCode(CodeBuffer* buffer, int offset) {
    uint8_t opcode = buffer->data[offset];
    
    switch (opcode) {
        case OP_CONSTANT: break;
        case OP_ADD: break;
        default:
            fprintf(stderr, "[ERROR] Unknown upcode: %d", opcode);
            return offset + 1;
    }
    return 0;
}

