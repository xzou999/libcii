#ifndef CII_INCLUDED
#define CII_INCLUDED

#include <setjmp.h>

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

#endif //CII_INCLUDED