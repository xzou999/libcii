#include <stdio.h>
#include "cii.h"

extern void test_arith();
extern void test_stack();

int main()
{
    test_arith();

    test_stack();
    
    return 0;
}
