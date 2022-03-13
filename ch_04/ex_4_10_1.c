#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "../ch_01/ch_01.h"

#define MAXLINE     1000
#define MAXOP       100

#define UNKNOWN     INT_MIN
#define NUMBER      (INT_MIN + 1)
#define PEEK        (INT_MIN + 2)
#define DUP         (INT_MIN + 3)
#define SWAP        (INT_MIN + 4)
#define CLEAR       (INT_MIN + 5)
#define SIN         (INT_MIN + 6)
#define COS         (INT_MIN + 7)
#define TAN         (INT_MIN + 8)
#define ASIN        (INT_MIN + 9)
#define ACOS        (INT_MIN + 10)
#define ATAN        (INT_MIN + 11)
#define ATAN2       (INT_MIN + 12)
#define SINH        (INT_MIN + 13)
#define COSH        (INT_MIN + 14)
#define TANH        (INT_MIN + 15)
#define EXP         (INT_MIN + 16)
#define LOG         (INT_MIN + 17)
#define LOG10       (INT_MIN + 18)
#define POW         (INT_MIN + 19)
#define SQRT        (INT_MIN + 20)
#define CEIL        (INT_MIN + 21)
#define FLOOR       (INT_MIN + 22)
#define FABS        (INT_MIN + 23)
#define LDEXP       (INT_MIN + 24)
#define FMOD        (INT_MIN + 25)
#define SETVAR      (INT_MIN + 26)
#define LATESTVAR   (INT_MIN + 27)

int getop(char []);
void push(double);
double pop(void);
double peek(void);
void dup(void);
void swap(void);
void clear(void);


char line[MAXLINE];
int pos;

/*
  Use getline instead of getch and ungetch

  Compile with:
  gcc ../ch_01/ch_01.c ex_4_10_1.c -lm -o ex_4_10_1
*/
int main()
{
    int type;
    double op2;
    char s[MAXOP];
    int running_command = UNKNOWN;

    char variable = '\0';
    double latest_variable = 0.0;
    double variables[26];

    while (getline_r(line, MAXLINE) > 0) {
        pos = 0;
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
            case PEEK: case DUP: case SWAP: case CLEAR: case SETVAR:
                running_command = type;
                break;
            case SIN:
                push(sin(pop()));
                break;
            case COS:
                push(cos(pop()));
                break;
            case TAN:
                push(tan(pop()));
                break;
            case ASIN:
                push(asin(pop()));
                break;
            case ACOS:
                push(acos(pop()));
                break;
            case ATAN:
                push(atan(pop()));
                break;
            case ATAN2:
                op2 = pop();
                push(atan2(pop(), op2));
                break;
            case SINH:
                push(sinh(pop()));
                break;
            case COSH:
                push(cosh(pop()));
                break;
            case TANH:
                push(tanh(pop()));
                break;
            case EXP:
                push(exp(pop()));
                break;
            case LOG:
                push(log(pop()));
                break;
            case LOG10:
                push(log10(pop()));
                break;
            case POW:
                op2 = pop();
                push(pow(pop(), op2));
                break;
            case SQRT:
                push(sqrt(pop()));
                break;
            case CEIL:
                push(ceil(pop()));
                break;
            case FLOOR:
                push(floor(pop()));
                break;
            case FABS:
                push(fabs(pop()));
                break;
            case LDEXP:
                op2 = pop();
                push(ldexp(pop(), op2));
                break;
            case FMOD:
                op2 = pop();
                push(fmod(pop(), op2));
                break;
            case LATESTVAR:
                push(latest_variable);
                break;
            case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
            case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
            case 'o': case 'p': case 'q': case 'r': case 's': case 't':
            case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
                if (running_command == SETVAR) {
                    variable = type;
                } else {
                    push(variables[type - 'a']);
                }
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
                case SETVAR:
                    variables[variable - 'a'] = pop();
                    variable = '\0';
                    break;
                default:
                    latest_variable = pop();
                    printf("\t%.8g\n", latest_variable);
                    break;
                }
                running_command = UNKNOWN;
                break;
            default:
                printf("error: unknown command %s\n", s);
            }
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
int isnumber(char []);

/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i, c;

    while ((s[0] = c = line[pos++]) == ' ' || c == '\t');
    s[1] = '\0';
    if (c == '\n' || c == EOF) {
        return c;
    }
    if (c == '\0') {
        // return EOF as '\0'
        return EOF;
    }
    i = 0;
    while (!isspace(s[++i] = c = line[pos++]) && c != '\0');
    s[i] = '\0';
    --pos;
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
    } else if (strcmp(s, "sin") == 0) {
        return SIN;
    } else if (strcmp(s, "cos") == 0) {
        return COS;
    } else if (strcmp(s, "tan") == 0) {
        return TAN;
    } else if (strcmp(s, "asin") == 0) {
        return ASIN;
    } else if (strcmp(s, "acos") == 0) {
        return ACOS;
    } else if (strcmp(s, "atan") == 0) {
        return ATAN;
    } else if (strcmp(s, "atan2") == 0) {
        return ATAN2;
    } else if (strcmp(s, "sinh") == 0) {
        return SINH;
    } else if (strcmp(s, "cosh") == 0) {
        return COSH;
    } else if (strcmp(s, "tanh") == 0) {
        return TANH;
    } else if (strcmp(s, "exp") == 0) {
        return EXP;
    } else if (strcmp(s, "log") == 0) {
        return LOG;
    } else if (strcmp(s, "log10") == 0) {
        return LOG10;
    } else if (strcmp(s, "pow") == 0) {
        return POW;
    } else if (strcmp(s, "sqrt") == 0) {
        return SQRT;
    } else if (strcmp(s, "ceil") == 0) {
        return CEIL;
    } else if (strcmp(s, "floor") == 0) {
        return FLOOR;
    } else if (strcmp(s, "fabs") == 0) {
        return FABS;
    } else if (strcmp(s, "ldexp") == 0) {
        return LDEXP;
    } else if (strcmp(s, "fmod") == 0) {
        return FMOD;
    } else if (strcmp(s, "setvar") == 0) {
        return SETVAR;
    } else if (strcmp(s, "latest") == 0) {
        return LATESTVAR;
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

