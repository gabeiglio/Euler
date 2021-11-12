#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "ConstantBuffer.h"
#include "CodeBuffer.h"
#include "Token.h"
#include "Lexer.h"
#include "Parser.h"
#include "VM.h"
#include "Debug.h"

#define MAX_INPUT 100

void run(const char* source) {

    //Initialize lexer
    Lexer lexer;
    initLexer(&lexer, source);
   
    //Initialize code buffer for storing the outputs outputed by the parser
    CodeBuffer codeBuffer;
    initCodeBuffer(&codeBuffer);

    //Here the parser should have to take care of getting the tokens and translating it to IR
    Parser parser;
    initParser(&parser, &lexer, &codeBuffer);        
    parse(&parser);

    disassembleCodeBuffer(&codeBuffer); 

    // Now for the fun part Virtual machine
    VM vm;
    initVM(&vm, &codeBuffer);
    printf("%f\n", interpret(&vm));
   
    freeCodeBuffer(&codeBuffer);
}

int main(int argc, char* argv[]) {
    char input[MAX_INPUT];

    while (1) {
        
        //Input
        printf("\n> ");
        fgets(input, MAX_INPUT, stdin);

        //Output
        run(input);
    }
}
