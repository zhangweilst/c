#include <stdio.h>

#define MAX_CHAR 128

/* histogram of frequencies of ascii characters */
int main()
{
    int c;
    int frequencies[MAX_CHAR];

    for (int i = 0; i < MAX_CHAR; i++)
        frequencies[i] = 0;

    while ((c = getchar()) != EOF) {
        if (c < MAX_CHAR) {
            frequencies[c]++;
        }
    }

    int max_length = 0;
    for (int i = 0; i < MAX_CHAR; i++) {
        if (max_length < frequencies[i]) {
            max_length = frequencies[i];
        }
    }

    for (int i = max_length; i > 0; i--) {
        for (int j = 0; j < MAX_CHAR; j++) {
            if (frequencies[j] >= i)
                printf("__ ");
            else if (frequencies[j] > 0)
                printf("   ");
        }
        putchar('\n');
    }
    for (int i = 0; i < MAX_CHAR; i++) {
        if (frequencies[i] > 0) {
            if (i == '\n')
                printf("\\n ");
            else if (i == '\t')
                printf("\\t ");
            else
                printf("%c  ", i);
        }
    }
    putchar('\n');
}

