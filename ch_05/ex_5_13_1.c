#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ch_01/ch_01.h"

#define MAXLINE     1000

/* tail: prints the last n lines of the input */
int main(int argc, char *argv[])
{
    int i, j, len, n, *sizes;
    char line[MAXLINE], **lines;

    n = 10;
    if (argc == 2 && (*++argv)[0] == '-') {
        n = atoi(++argv[0]);
        if (n <= 0) {
            printf("Usage: tail [-n]\n");
            printf("error: n must be greater than zero\n");
            return 1;
        }
    } else if (argc >= 2) {
        printf("Usage: tail [-n]\n");
        printf("error: n must be greater than zero\n");
        return 1;
    }

    lines = (char **)malloc(n * sizeof(char *));
    for (i = 0; i < n; ++i) {
        lines[i] = NULL;
    }
    sizes = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; ++i) {
        sizes[i] = 0;
    }
    i = 0;
    while ((len = getline_r(line, MAXLINE)) > 0) {
        int pos = i++ % n;
        if (len + 1 > sizes[pos] || len + 1 <= sizes[pos] / 2) {
            if (lines[pos] != NULL) {
                free(lines[pos]);
            }
            lines[pos] = (char *)malloc((len + 1) * sizeof(char));
        }
        strcpy(lines[pos], line);
        sizes[pos] = len + 1;

        // long lines
        if (line[len - 1] != '\n') {
            while ((len = getline_r(line, MAXLINE)) > 0) {
                char *tmp = (char *)malloc((sizes[pos] + len) * sizeof(char));
                strcpy(tmp, lines[pos]);
                strcpy(tmp + sizes[pos] - 1, line);
                free(lines[pos]);
                lines[pos] = tmp;
                sizes[pos] += len;
                if (line[len - 1] == '\n') {
                    break;
                }
            }
        }
    }

    int num = n < i ? n : i;
    for (j = 0; j < num; ++j) {
        printf("%s", lines[(i - num + n + j) % n]);
    }
    return 0;
}

