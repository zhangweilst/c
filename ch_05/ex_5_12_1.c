#include <stdio.h>
#include <stdlib.h>
#include "../ch_01/ch_01.h"

#define MAXLINE     1000
#define TABSTOP     8

int get_tabspaces(int start, int tabstops, int pos);

/* detab, with tabstop arguments */
int main(int argc, char *argv[])
{
    int i, len;
    char line[MAXLINE];

    int start = 1; // start defaults to 1
    int tabstops = TABSTOP; // tabstops defaults to TABSTOP
    while (--argc > 0) {
        switch ((*++argv)[0]) {
        case '-':
            start = atoi(++argv[0]);
            if (start <= 0) {
                printf("Usage: detab [-m] [+n] [tablist]\n");
                printf("error: m must be greater than 0\n");
                return 1;
            }
            break;
        case '+':
            tabstops = atoi(++argv[0]);
            if (tabstops <= 0) {
                printf("Usage: detab [-m] [+n] [tablist]\n");
                printf("error: n must be greater than 0\n");
                return 1;
            }
            break;
        default:
            printf("Usage: detab [-m] [+n] [tablist]\n");
            printf("error: illegal option %c\n", (*argv)[0]);
            break;
        }
    }

    i = 0;
    while ((len = getline_r(line, MAXLINE)) > 0) {
        for (int j = 0; j < len; ++j) {
            if (line[j] == '\t') {
                int spaces = get_tabspaces(start, tabstops, i);
                for (int k = 0; k < spaces; ++k) {
                    putchar(' ');
                }
                i += spaces;
            } else {
                putchar(line[j]);
                ++i;
                if (line[j] == '\n') {
                    i = 0;
                }
            }
        }
    }
    return 0;
}

/* get number of spaces according to tab start and stop */
int get_tabspaces(int start, int tabstops, int pos)
{
    int i;

    if (start > 0 && tabstops > 0) {
        for (i = start; i <= pos + 1; i += tabstops);
        return i - (pos + 1);
    }
    return TABSTOP - pos % TABSTOP;
}

