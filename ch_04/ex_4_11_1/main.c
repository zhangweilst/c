#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calc.h"

#define MAXOP       100

/*
   Add commands for handling variables
   and a variable for latest printed value

   Compile with: gcc stack.c getch.c getop.c main.c -lm -o ex_4_11_1
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
    return 0;
}

