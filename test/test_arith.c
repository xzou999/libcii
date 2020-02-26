#include "cii.h"
#include <stdio.h>

void test_arith()
{
    printf("#############test arith module###########\n");

    int x = 97;
    int y = 9;

    int max     = Arith_max(x, y);
    int min     = Arith_min(x, y);
    int div     = Arith_div(x, y);
    int mod     = Arith_mod(x, y);
    int floor   = Arith_floor(x, y);
    int ceiling = Arith_ceiling(x, y);

    printf("for x=%d and y=%d, max=%d\n", x, y, max);
    printf("for x=%d and y=%d, min=%d\n", x, y, min);
    printf("for x=%d and y=%d, div=%d\n", x, y, div);
    printf("for x=%d and y=%d, mod=%d\n", x, y, mod);
    printf("for x=%d and y=%d, floor=%d\n", x, y, floor);
    printf("for x=%d and y=%d, ceiling=%d\n", x, y, ceiling);

    printf("##################end####################\n");
}