#ifndef euler_c
#define euler_c

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "ConstantBuffer.h"
#include "CodeBuffer.h"
#include "Token.h"
#include "Lexer.h"
#include "Parser.h"
#include "VM.h"
#include "Debug.h"
#include "Hashmap.h"

Hashmap map;
VM vm; 

void euler_main() {
    initMap(&map);
    initVM(&vm, &map);
}

double run(VM* vm, const char* source) {

    //Initialize lexer
    Lexer lexer;
    initLexer(&lexer, source);
   
    //Initialize code buffer for storing the outputs outputed by the parser
    CodeBuffer codeBuffer;
    initCodeBuffer(&codeBuffer);

    //Here the parser should have to take care of getting the tokens and translating it to IR
    Parser parser;
    initParser(&parser, &lexer, &codeBuffer, vm->map);            
    parse(&parser);

    //disassembleCodeBuffer(&codeBuffer); 

    // Now for the fun part Virtual machine
    double result = interpret(vm, &codeBuffer);
    freeCodeBuffer(&codeBuffer);

    return result;
}

double euler(const char* source) {
    return run(&vm, source);
}

#endif
