#include <stdio.h>

/* count blanks, tabs and newlines */
int main()
{
    int c, n1;

    n1 = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ')
            ++n1;
        if (c == '\t')
            ++n1;
        if (c == '\n')
            ++n1;
    }
    printf("%d\n", n1);
}

