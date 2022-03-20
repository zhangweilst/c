#include <stdio.h>
#include <stdlib.h>
#include "../ch_01/ch_01.h"

#define MAXLINE     1000
#define MAXTABLIST  100
#define TABSTOP     8

int is_tabstop(int num, int tablist[], int pos);

/* entab, single space takes precedence at tabstop, with tabstop arguments */
int main(int argc, char *argv[])
{
    int i, spaces, len, num, tablist[MAXTABLIST];
    char line[MAXLINE];

    num = 0;
    while (--argc > 0) {
        if (num >= MAXTABLIST) {
            printf("Usage: entab [tablist]\n");
            printf("error: tablist too long\n");
            return 1;
        }
        tablist[num++] = atoi(*++argv);
    }
    // tablist validation
    for (i = 0; i < num; ++i) {
        if (tablist[i] <= 0) {
            printf("Usage: entab [tablist]\n");
            printf("invalid tablist: must be greater than 0\n");
            return 1;
        }
        if (i > 0 && tablist[i] <= tablist[i - 1]) {
            printf("Usage: entab [tablist]\n");
            printf("invalid tablist: tablist must be in ascending order\n");
            return 1;
        }
    }

    i = 0, spaces = 0;
    while ((len = getline_r(line, MAXLINE)) > 0) {
        for (int j = 0; j < len; ++j) {
            if (line[j] == ' ') {
                ++spaces;
                if ((num <= 0 && i % TABSTOP == TABSTOP - 1) ||
                    (num > 0 && is_tabstop(num, tablist, i))) {
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
int is_tabstop(int num, int tablist[], int pos)
{
    int i;

    for (i = 0; i < num; ++i) {
        if (pos + 1 == tablist[i] - 1) {
            return 1;
        }
        if (pos + 1 < tablist[i] - 1) {
            return 0;
        }
    }
    return pos % TABSTOP == TABSTOP - 1;
}

