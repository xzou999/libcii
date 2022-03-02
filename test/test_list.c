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
    printf("---------------------test list--------------------------\n");

    List_T *p1, *p2;
    p1 = List_list(NULL);
    p2 = List_list("Atom-p2", "Mem-p2", "Arena-p2", "List-p2", NULL);
    List_T *iter = p2;
    printf("item of list p2:\n");
    while(iter != NULL)
    {
        printf("item:%s\n", iter->first);
        iter = iter->rest;
    }

    p1 = List_push(NULL, "List-p1");
    p1 = List_push(p1, "Arena-p1");
    p1 = List_push(p1, "Mem-p1");
    p1 = List_push(p1, "Atom-p1");
    iter = p1;
    printf("item of list p1 after push:\n");
    while(iter != NULL)
    {
        printf("item:%s\n", iter->first);
        iter = iter->rest;
    }

    List_T *p3;
    p3 = List_append(p1, p2);
    iter = p3;
    printf("item of list p3 after append:\n");
    while(iter != NULL)
    {
        printf("item:%s\n", iter->first);
        iter = iter->rest;
    }

    List_T *p4;
    p4 = List_reverse(List_copy(p3));
    iter = p4;
    printf("item of list p4 after reverse:\n");
    while(iter != NULL)
    {
        printf("item:%s\n", iter->first);
        iter = iter->rest;
    }

    printf("item of list p4 after map:\n");
    List_map(p4, mkatom, stderr);

    //TODO: function compare need definition
    //printf("item of list p3 after to array:\n");
    char **array = (char **)List_toArray(p3, NULL);
    printf("before qsort, array of p3 is:\n");
    for(int i = 0; array[i]; i++)
        printf("%s\n", array[i]);
    qsort((void **)array, List_length(p3), sizeof(*array),(int (*)(const void*, const void*))compare);
    printf("after qsort, array of p3 is:\n");
    for (int i = 0; array[i]; i++)
        printf("%s\n", array[i]);
    FREE(array);

    printf("\n\n");
}
