#include <stdio.h>
#include "cii.h"

extern void test_arith();
extern void test_stack();
extern void test_list();
extern void test_table();

int main()
{
    test_arith();

    test_stack();
    
    test_list();

    test_table();

    return 0;
}
