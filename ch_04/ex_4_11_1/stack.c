#include <stdio.h>
#include "calc.h"

#define MAXVAL      100

static int sp = 0;
static double val[MAXVAL];

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* peek: print the top element of the stack without popping */
double peek(void)
{
    if (sp > 0)
        return val[sp - 1];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* dup: duplicate the top element of the stack */
void dup(void)
{
    push(peek());
}

/* swap: swap the top two elements of the stack */
void swap(void)
{
    double s1 = pop();
    double s2 = pop();
    push(s1);
    push(s2);
}

/* clear: clear the stack */
void clear(void)
{
    sp = 0;
}

