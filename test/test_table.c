#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cii.h"

void test_table()
{
    printf("------------------------test table-------------------------\n");

    Table_T *t1 = Table_new(100, NULL, NULL);
    int len = Table_length(t1);
    printf("original table size:%d\n", len);

    Table_put(t1, "item1", "value1");
    Table_put(t1, "item2", "value2");
    Table_put(t1, "item3", "value3");
    len = Table_length(t1);
    printf("now table size is: %d\n", len);

    char *value1 = Table_get(t1, "item1");
    char *value2 = Table_get(t1, "item2");
    char *value3 = Table_get(t1, "item3");
    printf("value of item1:%s, value of item2:%s, value of item3:%s\n", value1, value2, value3);

    Table_remove(t1, "item2");
    len = Table_length(t1);
    printf("now table size is: %d after remove one item\n", len);

    printf("\n\n");
}