#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);
int getint(int *pn);

int main()
{
    int n;
    while (getint(&n) > 0) {
        printf("%d\n", n);
    }
    return 0;
}

/* getint: get next integer from input to *pn */
int getint(int *pn)
{
    int c, sign;

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
    for (*pn = 0; isdigit(c); c = getch())
        *pn = *pn * 10 + (c - '0');
    *pn *= sign;
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

