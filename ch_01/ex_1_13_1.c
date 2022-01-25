#include <stdio.h>

#define MAX_LENGTH 99

/* histogram of lengths of words */
int main()
{
    int c, prev_c = EOF, length = 0;
    int lengths[MAX_LENGTH];

    for (int i = 0; i < MAX_LENGTH; i++)
        lengths[i] = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (prev_c != ' ' && prev_c != '\n' &&
                prev_c != '\t' && prev_c != EOF) {
                if (length <= MAX_LENGTH) {
                    lengths[length - 1]++;
                    length = 0;
                }
            }
        } else {
            length++;
        }
        prev_c = c;
    }
    if (prev_c != ' ' && prev_c != '\n' &&
        prev_c != '\t' && prev_c != EOF)
        lengths[length >= MAX_LENGTH ? MAX_LENGTH - 1 : length]++;

    for (int i = 0; i < MAX_LENGTH; i++) {
        if (lengths[i] > 0) {
            printf("%2d: ", i + 1);
            for (int j = 0; j < lengths[i]; j++) {
                putchar('|');
            }
            putchar('\n');
        }
    }
}

