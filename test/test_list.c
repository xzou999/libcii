#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cii.h"

//TODO: Atom_string need definition.
static void mkatom(void **x, void *cl)
{
    char **str = (char **)x;
    FILE *fp = cl;

    *str = Atom_string(*str);
    fprintf(fp, "%s\n", *str);
}

static int compare(void *x, void *y)
{
    return strcmp(*(char **)x, *(char **)y);
}

void test_list()
{
    printf("####################test list######################\n");

    List_T *p1, *p2;
    p1 = List_list(NULL);
    p2 = List_list("Atom", "Mem", "Arena", "List", NULL);
    List_T *iter = p2;
    while(iter)
    {
        printf("item of list:\n");
        printf("item:%s\n", iter->first);
        iter = iter->rest;
    }

    p1 = List_push(NULL, "List");
    p1 = List_push(p1, "Arena");
    p1 = List_push(p1, "Mem");
    p1 = List_push(p1, "Atom");
    iter = p1;
    while(iter)
    {
        printf("item of list after push:\n");
        printf("item:%s\n", iter->first);
        iter = iter->rest;
    }

    List_T *p3;
    p3 = List_append(p1, p2);
    iter = p3;
    while(p3)
    {
        printf("item of list after append:\n");
        printf("item:%s\n", iter->first);
        iter = iter->rest;
    }

    List_T *p4;
    p4 = List_reverse(p3);
    iter = p4;
    while(iter)
    {
        printf("item of list after reverse:\n");
        printf("item:%s\n", iter->first);
        iter = iter->rest;
    }

    printf("item of list after map:\n");
    List_map(p4, mkatom, stderr);

    //TODO: function compare need definition
    printf("item of list after to array:\n");
    char **array = (char **)List_toArray(p3, NULL);
    qsort((void **)array, List_length(p3), sizeof(*array),(int (*)(const void*, const void*))compare);
    for (int i = 0; array[i]; i++)
        printf("%s\n", array[i]);
    FREE(array);




    printf("######################end##########################\n");
}