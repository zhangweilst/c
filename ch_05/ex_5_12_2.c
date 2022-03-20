#include <stdio.h>
#include <stdlib.h>
#include "../ch_01/ch_01.h"

#define MAXLINE     1000
#define TABSTOP     8

int is_tabstop(int start, int tabstops, int pos);

/* entab, single space takes precedence at tabstop, with tabstop arguments */
int main(int argc, char *argv[])
{
    int i, spaces, len;
    char line[MAXLINE];

    int start = 1; // start defaults to 1
    int tabstops = TABSTOP; // tabstops defaults to TABSTOP
    while (--argc > 0) {
        switch ((*++argv)[0]) {
        case '-':
            start = atoi(++argv[0]);
            if (start <= 0) {
                printf("Usage: entab [-m] [+n] [tablist]\n");
                printf("error: m must be greater than 0\n");
                return 1;
            }
            break;
        case '+':
            tabstops = atoi(++argv[0]);
            if (tabstops <= 0) {
                printf("Usage: entab [-m] [+n] [tablist]\n");
                printf("error: n must be greater than 0\n");
                return 1;
            }
            break;
        default:
            printf("Usage: entab [-m] [+n] [tablist]\n");
            printf("error: illegal option %c\n", (*argv)[0]);
            break;
        }
    }

    i = 0, spaces = 0;
    while ((len = getline_r(line, MAXLINE)) > 0) {
        for (int j = 0; j < len; ++j) {
            if (line[j] == ' ') {
                ++spaces;
                if (is_tabstop(start, tabstops, i)) {
                    putchar(spaces > 1 ? '\t' : ' ');
                    spaces = 0;
                }
                ++i;
            } else {
                if (spaces > 0) {
                    for (int k = 0; k < spaces; ++k) {
                        putchar(' ');
                    }
                }
                putchar(line[j]);
                if (line[j] == '\t') {
                    i += TABSTOP - i % TABSTOP;
                } else if (line[j] == '\n') {
                    i = 0;
                } else {
                    ++i;
                }
                spaces = 0;
            }
        }
    }
    return 0;
}

/* whether position pos is at the tabstop */
int is_tabstop(int start, int tabstops, int pos)
{
    int i;

    if (start <= 0 || tabstops <= 0) {
        return pos % TABSTOP == TABSTOP - 1;
    }
    for (i = start; i - 1 < pos + 1; i += tabstops);
    if (i - 1 == pos + 1) {
        return 1;
    } else {
        return 0;
    }
}

