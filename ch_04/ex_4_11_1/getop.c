#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "calc.h"

int isnumber(char[]);

/* getop without ungetch */
int getop(char s[])
{
    int i, c;
    static int pushback = UNKNOWN;

    if (pushback != UNKNOWN) {
        if (pushback != ' ' && pushback != '\t') {
            s[0] = c = pushback;
        } else {
            while ((s[0] = c = getch()) == ' ' || c == '\t');
        }
        pushback = UNKNOWN;
    } else {
        while ((s[0] = c = getch()) == ' ' || c == '\t');
    }

    s[1] = '\0';
    if (c == '\n' || c == EOF) {
        return c;
    }
    i = 0;
    while (!isspace(s[++i] = c = getch()));
    s[i] = '\0';
    pushback = c;
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

