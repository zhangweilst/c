#include <stdio.h>

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

