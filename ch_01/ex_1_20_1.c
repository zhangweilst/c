#include <stdio.h>
#include "ch_01.h"

#define MAXLINE 1000
#define TABSTOP 8

/* detab */
int main()
{
    int len;
    char line[MAXLINE];

    int i = 0;
    while ((len = getline_r(line, MAXLINE)) > 0) {
        for (int j = 0; j < len; ++j) {
            if (line[j] == '\t') {
                int spaces = TABSTOP - i % TABSTOP;
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

