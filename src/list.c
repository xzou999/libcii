#include "cii.h"
#include <stdarg.h>
#include <stddef.h>

//#define T List_T
List_T *List_push(List_T *list, void *x)
{
    List_T *p;
    NEW(p);
    p->first = x;
    p->rest  = list;
    return p;
}

List_T *List_list(void *x, ...)
{
    va_list ap;
    List_T *list;
    List_T **p = &list;
    va_start(ap, x);
    for (; x; x = va_arg(ap, void *))
    {
        NEW(*p);
        (*p)->first = x;
        p           = &(*p)->rest;
    }
    *p = NULL;
    va_end(ap);
    return list;
}

List_T *List_append(List_T *list, List_T *tail)
{
    List_T **p = &list;
    while (*p)
        p = &(*p)->rest;
    *p = tail;
    return list;
}

List_T *List_copy(List_T *list)
{
    List_T *head;
    List_T **p = &head;
    for (; list; list = list->rest)
    {
        NEW(*p);
        (*p)->first = list->first;
        p           = &(*p)->rest;
    }
    *p = NULL;
    return head;
}

List_T *List_pop(List_T *list, void **x)
{
    if (list)
    {
        List_T *head = list->rest;
        if (x)
            *x = list->first;
        FREE(list);
        return head;
    }
    else
        return list;
}

//this will change the input list! should wrap the input list with List_copy!
List_T *List_reverse(List_T *list)
{
    List_T *head = NULL;
    List_T *next;
    for (; list; list = next)
    {
        next       = list->rest;
        list->rest = head;
        head       = list;
    }
    return head;
}

int List_length(List_T *list)
{
    int n;
    for (n = 0; list; list = list->rest)
        n++;
    return n;
}

void List_free(List_T **list)
{
    List_T *next;
    assert(list);
    for (; *list; *list = next)
    {
        next = (*list)->rest;
        FREE(*list);
    }
}

void List_map(List_T *list, void apply(void **x, void *cl), void *cl)
{
    assert(apply);
    for (; list; list = list->rest)
        apply(&list->first, cl);
}

void **List_toArray(List_T *list, void *end)
{
    int i, n = List_length(list);
    void **array = ALLOC((n + 1) * sizeof(*array));
    for (i = 0; i < n; i++)
    {
        array[i] = list->first;
        list     = list->rest;
    }
    array[i] = end;
    return array;
}
