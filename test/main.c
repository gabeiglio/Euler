#include <stdio.h>
#include "utest.h"
#include "../src/euler.c"

UTEST_STATE();

UTEST(Basic, arithmetic) {
    ASSERT_EQ(euler("2 * 23 - -22 / 2"), 57);
}

UTEST(Trig, sin) {

    double test = euler("sin(90)");
    ASSERT_EQ(test, 0.893997);
    ASSERT_EQ(euler("sin(0)"), 0);
}

int main(int argc, const char* const  argv[]) {
    euler_main();
    return utest_main(argc, argv);    
}
