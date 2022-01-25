#include <stdio.h>

#define MAX_LENGTH 99

/* histogram of lengths of words, vertical version */
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

    int max_length = 0;
    for (int i = 0; i < MAX_LENGTH; i++) {
        if (max_length < lengths[i]) {
            max_length = lengths[i];
        }
    }

    for (int i = max_length; i > 0; i--) {
        for (int j = 0; j < MAX_LENGTH; j++) {
            if (lengths[j] >= i)
                printf("__ ");
            else if (lengths[j] > 0)
                printf("   ");
        }
        putchar('\n');
    }
    for (int i = 0; i < MAX_LENGTH; i++) {
        if (lengths[i] > 0) {
            printf("%02d ", i + 1);
        }
    }
    putchar('\n');
}

