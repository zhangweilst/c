#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXOP       100

#define UNKNOWN     INT_MIN
#define NUMBER      (INT_MIN + 1)
#define PEEK        (INT_MIN + 2)
#define DUP         (INT_MIN + 3)
#define SWAP        (INT_MIN + 4)
#define CLEAR       (INT_MIN + 5)

int getop(char []);
void push(double);
double pop(void);
double peek(void);
void dup(void);
void swap(void);
void clear(void);

/* Add commands to manipulate the stack */
int main()
{
    int type;
    double op2;
    char s[MAXOP];
    int running_command = UNKNOWN;

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '*':
            push(pop() * pop());
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
        case '%':
            op2 = pop();
            if (op2 != 0.0)
                push((int) pop() % (int) op2);
            else
                printf("error: zero divisor\n");
            break;
        case PEEK: case DUP: case SWAP: case CLEAR:
            running_command = type;
            break;
        case '\n':
            switch (running_command) {
            case PEEK:
                printf("\t%.8g\n", peek());
                break;
            case DUP:
                dup();
                break;
            case SWAP:
                swap();
                break;
            case CLEAR:
                clear();
                break;
            default:
                printf("\t%.8g\n", pop());
            }
            running_command = UNKNOWN;
            break;
        default:
            printf("error: unknown command %s\n", s);
        }
    }
    return 0;
}

#define MAXVAL      100
int sp = 0;
double val[MAXVAL];

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

#include <ctype.h>
#include <string.h>
int getch(void);
void ungetch(int);
int isnumber(char []);

/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t');
    s[1] = '\0';
    if (c == '\n' || c == EOF) {
        return c;
    }
    i = 0;
    while (!isspace(s[++i] = c = getch()));
    s[i] = '\0';
    ungetch(c);
    if (isnumber(s)) {
        return NUMBER;
    } else if (i == 1) {
        return s[0];
    } else if (strcmp(s, "peek") == 0) {
        return PEEK;
    } else if (strcmp(s, "dup") == 0) {
        return DUP;
    } else if (strcmp(s, "swap") == 0) {
        return SWAP;
    } else if (strcmp(s, "clear") == 0) {
        return CLEAR;
    } else {
        return UNKNOWN;
    }
}

int isnumber(char s[])
{
    int i;

    i = 0;
    if (s[i] == '-' || s[i] == '+')
        ++i;
    while (isdigit(s[i]))
        ++i;
    if (s[i] == '.')
        ++i;
    while (isdigit(s[i]))
        ++i;
    if (s[i] == '\0') {
        if (s[0] == '-' || s[0] == '+') {
            return i > 1;
        } else {
            return i > 0;
        }
    } else {
        return 0;
    }
}

#define BUFSIZE     100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

