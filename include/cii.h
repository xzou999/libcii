#ifndef CII_INCLUDED
#define CII_INCLUDED

#include <setjmp.h>

//////////////////////////////// atomic module ///////////////////////////////
extern int Atom_length(const char *str);
extern const char *Atom_new(const char *str, int len);
extern const char *Atom_string(const char *str);
extern const char *Atom_int(long n);

////////////////////////////// except module /////////////////////////////////
#define RAISE(e) Except_raise(&(e), __FILE__, __LINE__)
#define RERAISE Except_raise(Except_frame.exception, Except_frame.file, Except_frame.line)
#define RETURN                                                                                                         \
    switch (Except_stack = Except_stack->prev, 0)                                                                      \
    default:                                                                                                           \
        return
#define TRY                                                                                                            \
    do                                                                                                                 \
    {                                                                                                                  \
        volatile int Except_flag;                                                                                      \
        Except_Frame Except_frame;                                                                                     \
        Except_frame.prev = Except_stack;                                                                              \
        Except_stack      = &Except_frame;                                                                             \
        Except_flag       = setjmp(Except_frame.env);                                                                  \
        if (Except_flag == Except_entered)                                                                             \
        {
#define EXCEPT(e)                                                                                                      \
    if (Except_flag == Except_entered)                                                                                 \
        Except_stack = Except_stack->prev;                                                                             \
    }                                                                                                                  \
    else if (Except_frame.exception == &(e))                                                                           \
    {                                                                                                                  \
        Except_flag = Except_handled;
#define ELSE                                                                                                           \
    if (Except_flag == Except_entered)                                                                                 \
        Except_stack = Except_stack->prev;                                                                             \
    }                                                                                                                  \
    else                                                                                                               \
    {                                                                                                                  \
        Except_flag = Except_handled;
#define FINALLY                                                                                                        \
    if (Except_flag == Except_entered)                                                                                 \
        Except_stack = Except_stack->prev;                                                                             \
    }                                                                                                                  \
    {                                                                                                                  \
        if (Except_flag == Except_entered)                                                                             \
            Except_flag = Except_finalized;
#define END_TRY                                                                                                        \
    if (Except_flag == Except_entered)                                                                                 \
        Except_stack = Except_stack->prev;                                                                             \
    }                                                                                                                  \
    if (Except_flag == Except_raised)                                                                                  \
        RERAISE;                                                                                                       \
    }                                                                                                                  \
    while (0)

typedef struct _Except_T
{
    char *reason;
} Except_T;

typedef struct _Except_Frame Except_Frame;
struct _Except_Frame
{
    Except_Frame *prev;
    jmp_buf env;
    const char *file;
    int line;
    const Except_T *exception;
};

enum
{
    Except_entered = 0,
    Except_raised,
    Except_handled,
    Except_finalized
};

Except_Frame *Except_stack;
const Except_T Assert_Failed;
void Except_raise(const Except_T *e, const char *file, int line);

/////////////////////////////assert module////////////////////////////
#undef assert
#ifdef NDEBUG
#define assert(e) ((void)0)
#else
//#include "except.h"
extern void assert(int e);
#define assert(e) ((void)((e) || (RAISE(Assert_Failed), 0)))
#endif

///////////////////////////////arith module////////////////////////////
int Arith_max(int x, int y);
int Arith_min(int x, int y);
int Arith_div(int x, int y);
int Arith_mod(int x, int y);
int Arith_ceiling(int x, int y);
int Arith_floor(int x, int y);

//////////////////////////////////mem module///////////////////////////
#define ALLOC(nbytes) Mem_alloc((nbytes), __FILE__, __LINE__)
#define CALLOC(count, nbytes) Mem_calloc((count), (nbytes), __FILE__, __LINE__)
#define NEW(p) ((p) = ALLOC((long)sizeof *(p)))
#define NEW0(p) ((p) = CALLOC(1, (long)sizeof *(p)))
#define FREE(ptr) ((void)(Mem_free((ptr), __FILE__, __LINE__), (ptr) = 0))
#define RESIZE(ptr, nbytes) ((ptr) = Mem_resize((ptr), (nbytes), __FILE__, __LINE__))

extern const Except_T Mem_Failed;

extern void *Mem_alloc(long nbytes, const char *file, int line);
extern void *Mem_calloc(long count, long nbytes, const char *file, int line);
extern void Mem_free(void *ptr, const char *file, int line);
extern void *Mem_resize(void *ptr, long nbytes, const char *file, int line);

///////////////////////////////stack module///////////////////////////////
typedef struct _Stack_T
{
    int count;
    struct elem
    {
        void *x;
        struct elem *link;
    } * head;
} Stack_T;

extern Stack_T *Stack_new(void);
extern int Stack_empty(Stack_T *stk);
extern void Stack_push(Stack_T *stk, void *x);
extern void *Stack_pop(Stack_T *stk);
extern void Stack_free(Stack_T **stk);

///////////////////////list module//////////////////////////////
//#define T List_T
// typedef struct T *T;
// struct T {
// 	T rest;
// 	void *first;
// };
typedef struct _List_T List_T;
struct _List_T
{
    List_T *rest;
    void *first;
};

extern List_T *List_append(List_T *list, List_T *tail);
extern List_T *List_copy(List_T *list);
extern List_T *List_list(void *x, ...);
extern List_T *List_pop(List_T *list, void **x);
extern List_T *List_push(List_T *list, void *x);
extern List_T *List_reverse(List_T *list);
extern int List_length(List_T *list);
extern void List_free(List_T **list);
extern void List_map(List_T *list, void apply(void **x, void *cl), void *cl);
extern void **List_toArray(List_T *list, void *end);
//#undef T

////////////////////////////table module/////////////////////////////
//#define T Table_T
typedef struct _Table_T Table_T;
struct _Table_T
{
    int size;
    int (*cmp)(const void *x, const void *y);
    unsigned (*hash)(const void *key);
    int length;
    unsigned timestamp;
    struct binding
    {
        struct binding *link;
        const void *key;
        void *value;
    } * *buckets;
};

extern Table_T *Table_new(int hint, int cmp(const void *x, const void *y), unsigned hash(const void *key));
extern void Table_free(Table_T **table);
extern int Table_length(Table_T *table);
extern void *Table_put(Table_T *table, const void *key, void *value);
extern void *Table_get(Table_T *table, const void *key);
extern void *Table_remove(Table_T *table, const void *key);
extern void Table_map(Table_T *table, void apply(const void *key, void **value, void *cl), void *cl);
extern void **Table_toArray(Table_T *table, void *end);

#endif // CII_INCLUDED
