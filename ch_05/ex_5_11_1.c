#include <stdio.h>
#include <stdlib.h>
#include "../ch_01/ch_01.h"

#define MAXLINE     1000
#define MAXTABLIST  100
#define TABSTOP     8

int get_tabspaces(int num, int tablist[], int pos);

/* detab, with tabstop arguments */
int main(int argc, char *argv[])
{
    int i, len, num, tablist[MAXTABLIST];
    char line[MAXLINE];

    num = 0;
    while (--argc > 0) {
        if (num >= MAXTABLIST) {
            printf("Usage: detab [tablist]\n");
            printf("error: tablist too long\n");
            return 1;
        }
        tablist[num++] = atoi(*++argv);
    }
    // tablist validation
    for (i = 0; i < num; ++i) {
        if (tablist[i] <= 0) {
            printf("Usage: detab [tablist]\n");
            printf("invalid tablist: must be greater than 0\n");
            return 1;
        }
        if (i > 0 && tablist[i] <= tablist[i - 1]) {
            printf("Usage: detab [tablist]\n");
            printf("invalid tablist: tablist must be in ascending order\n");
            return 1;
        }
    }

    i = 0;
    while ((len = getline_r(line, MAXLINE)) > 0) {
        for (int j = 0; j < len; ++j) {
            if (line[j] == '\t') {
                int spaces = num <= 0 ? (TABSTOP - i % TABSTOP) :
                    get_tabspaces(num, tablist, i);
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

/* get number of spaces according to tablist and character position */
int get_tabspaces(int num, int tablist[], int pos)
{
    int i;

    for (i = 0; i < num; ++i) {
        if (tablist[i] > pos + 1) {
            return tablist[i] - (pos + 1);
        }
    }
    return TABSTOP - pos % TABSTOP;
}

