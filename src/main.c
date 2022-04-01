#include <stdio.h>
#include "euler.c"

#define MAX_INPUT 100

int main(int argc, char* argv[]) {
    euler_main();

    char input[MAX_INPUT];

    while (1) {
        
        //Input
        printf("\n> ");
        fgets(input, MAX_INPUT, stdin);
        
        //remove trailing new line
        input[strlen(input) - 1] = '\0';

        //Output
        printf("%f\n",euler(input));
    }
}
