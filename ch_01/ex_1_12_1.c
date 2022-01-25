#include <stdio.h>

/* print input one word per line */
int main()
{
    int c, prev_c = EOF;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (prev_c != ' ' && prev_c != '\n' &&
                prev_c != '\t' && prev_c != EOF)
                putchar('\n');
        }
        else
            putchar(c);
        prev_c = c;
    }
    if (prev_c != ' ' && prev_c != '\n' &&
        prev_c != '\t' && prev_c != EOF)
        putchar('\n');
}

