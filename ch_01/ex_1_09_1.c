#include <stdio.h>

/* replacing one or more blanks by a single blank */
int main()
{
    int c, prev = EOF;

    while ((c = getchar()) != EOF) {
        if (c != ' ' || prev != ' ')
            putchar(c);
        prev = c;
    }
}

