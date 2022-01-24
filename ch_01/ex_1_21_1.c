#include <stdio.h>
#include "ch_01.h"

#define MAXLINE 1000
#define TABSTOP 8

/* entab, single space takes precedence at tabstop */
int main()
{
    int len;
    char line[MAXLINE];

    int i = 0;
    int spaces = 0;
    while ((len = getline_r(line, MAXLINE)) > 0) {
        for (int j = 0; j < len; ++j) {
            if (line[j] == ' ') {
                ++spaces;
                if (i % TABSTOP == TABSTOP - 1) {
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

