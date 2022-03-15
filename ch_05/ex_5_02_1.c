#include <stdio.h>
#include <ctype.h>
#include <math.h>

int getch(void);
void ungetch(int);
int getfloat(double *pn);

int main()
{
    double n;
    while (getfloat(&n) > 0) {
        printf("%.16g\n", n);
    }
    return 0;
}

/* getint: get next integer from input to *pn */
int getfloat(double *pn)
{
    double power, exponent, exponent_power;
    int c, sign, exponent_sign;

    while (isspace(c = getch()));
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
        if (!isdigit(c)) {
            if (c != EOF) {
                ungetch(c);
                ungetch(sign > 0 ? '+' : '-');
                return 0;
            } else {
                return c;
            }
        }
    }
    for (*pn = 0.0; isdigit(c); c = getch())
        *pn = *pn * 10 + (c - '0');
    if (c == '.') {
        c = getch();
    }
    for (power = 1.0; isdigit(c); c = getch()) {
        *pn = *pn * 10 + (c - '0');
        power *= 10.0;
    }

    if (c == 'e' || c == 'E') {
        int tmp = c;
        c = getch();
        if (!isdigit(c) && c != '+' && c != '-') {
            if (c != EOF) {
                ungetch(c);
                ungetch(tmp);
                return 0;
            } else {
                return c;
            }
        }
    } else {
        *pn = sign * *pn / power;
        if (c != EOF) {
            ungetch(c);
        }
        return c;
    }
    exponent_sign = (c == '-') ? -1 : 1;
    if (c == '-' || c == '+') {
        c = getch();
        if (!isdigit(c)) {
            if (c != EOF) {
                ungetch(c);
                ungetch(exponent_sign > 0 ? '+' : '-');
                return 0;
            } else {
                return c;
            }
        }
    }
    for (exponent = 0.0; isdigit(c); c = getch())
        exponent = 10.0 * exponent + (c - '0');
    if (c == '.') {
        c = getch();
    }
    for (exponent_power = 1.0; isdigit(c); c = getch()) {
        exponent = 10.0 * exponent + (c - '0');
        exponent_power *= 10.0;
    }
    *pn = sign * *pn / power * pow(10.0, exponent_sign * exponent / exponent_power);

    if (c != EOF)
        ungetch(c);
    return c;
}

#define BUFSIZE     100

static char buf[BUFSIZE];
static int bufp = 0;
static int eof_encountered = 0;

int getch(void)
{
    if (eof_encountered)
        return EOF;
    int val = (bufp > 0) ? buf[--bufp] : getchar();
    if (val == EOF) {
        eof_encountered = 1;
    }
    return val;
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

