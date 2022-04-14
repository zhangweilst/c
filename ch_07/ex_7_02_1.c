#include <stdio.h>

#define MAXLINE 80

/* print non-graphic characters in octal or hex, and break long lines */
int main(int argc, char *argv[])
{
    int c, ch, oct, i;

    oct = 0;
    while (--argc > 0) {
        if ((*++argv)[0] == '-') {
            while ((ch = *++argv[0]) != '\0') {
                if (ch == 'o') {
                    oct = 1;
                }
            }
        }
    }

    i = 0;
    while ((c = getchar()) != EOF) {
        // 9: \t, 10: \n, 11: \v, 12: \f, 13: \r
        if (c == '\n') {
            i = 0;
        } else if (i >= MAXLINE) {
            putchar('\n');
            i = 1;
        } else {
            ++i;
        }
        if (c <= 31 && (c <= 8 || c >= 14)) {
            if (oct) {
                printf("'0%o'", c);
            } else {
                printf("'0x%x'", c);
            }
        } else {
            putchar(c);
        }
    }

    return 0;
}

