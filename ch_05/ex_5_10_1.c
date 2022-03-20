#include <stdio.h>
#include <stdlib.h>

void push(double);
double pop(void);
int isnumber(char *);
int isop(char *);

int main(int argc, char *argv[])
{
    double op2;

    if (argc <= 1) {
        printf("Usage: expr reverse polish expression\n");
        return 1;
    }
    while (--argc > 0) {
        if (isnumber(*++argv)) {
            push(atof(*argv));
        } else if (isop(*argv)) {
            switch (**argv) {
            case '+':
                push(pop() + pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case 'x': /* alphabet x */
                push(pop() * pop());
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0) {
                    push(pop() / op2);
                } else {
                    printf("error: zero divisor\n");
                    return 1;
                }
                break;
            case '%':
                op2 = pop();
                if (op2 != 0.0) {
                    push((int) pop() % (int) op2);
                } else {
                    printf("error: zero divisor\n");
                    return 1;
                }
                break;
            default:
                printf("error: invalid argument: %s\n", *argv);
                return 1;
            }
        } else {
            printf("error: invalid argument: %s\n", *argv);
        }
    }
    printf("%.8g\n", pop());
    return 0;
}

#define MAXVAL 100
int sp= 0;
static double val[MAXVAL];

void push(double f)
{
    if (sp < MAXVAL) {
        val[sp++] = f;
    } else {
        printf("error: stack full, can't push %g\n", f);
    }
}

double pop(void)
{
    if (sp > 0) {
        return val[--sp];
    } else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

#include <ctype.h>
#include <string.h>

int isnumber(char *s)
{
    char *s_i;

    s_i = s;
    if (*s_i == '-' || *s_i == '+')
        s_i++;
    while (isdigit(*s_i))
        s_i++;
    if (*s_i == '.')
        s_i++;
    while (isdigit(*s_i))
        s_i++;
    if (*s_i == '\0') {
        if (*s == '-' || *s == '+') {
            return s_i - s > 1;
        } else {
            return s_i - s > 0;
        }
    } else {
        return 0;
    }
}

int isop(char *s)
{
    return strlen(s) == 1 &&
        (*s == '+' || *s == '-' || *s == 'x' || *s == '/' || *s == '%');
}

