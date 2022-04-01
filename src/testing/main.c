#include <stdio.h>
#include "utest.h"
#include "../euler.c"

UTEST_STATE();

UTEST(Basic, arithmetic) {
    ASSERT_EQ(euler("1+1"), -2);
}

int main(int argc, const char* const  argv[]) {
    euler_main();
    return utest_main(argc, argv);    
}
