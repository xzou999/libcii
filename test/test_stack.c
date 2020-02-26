#include <stdio.h>
#include <stdbool.h> //new in C99 
#include "cii.h"

void test_stack()
{
    printf("#############test stack module###########\n");

    Stack_T *new_stack = Stack_new();

    bool is_stack_empty = Stack_empty(new_stack);

    printf("new stack is empty?%s\n", is_stack_empty?"yes":"no");

    int x   = 10;
    char y  = 'a';
    float z = 9.6f;
    char *a = "test stack";

    printf("push x:%d,y:%c,z:%f,a:%s\n", x, y, z, a);
    Stack_push(new_stack, &x);
    Stack_push(new_stack, &y);
    Stack_push(new_stack, &z);
    Stack_push(new_stack, a);

    is_stack_empty = Stack_empty(new_stack);
    printf("now new stack is empty?%s\n", is_stack_empty? "yes":"no");

    char *pop_a  = Stack_pop(new_stack);
    float *pop_z = Stack_pop(new_stack);
    char *pop_y  = Stack_pop(new_stack);
    int *pop_x   = Stack_pop(new_stack);

    printf("pop x:%d,y:%c,z:%f,a:%s\n", x, y, z, a);

    //Stack_free(&new_stack);
    is_stack_empty = Stack_empty(new_stack);
    printf("now new stack is empty?%s\n", is_stack_empty?"yes":"no");

    printf("####################end##################\n");
}