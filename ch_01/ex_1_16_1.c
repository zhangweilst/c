#include <stdio.h>
#include "ch_01.h"

#define MAXLINE 1000

/* 
  print the longest input line

  compile with:
  gcc ch01.c ex_01_16_1.c -o ex_01_16_1

*/
int main()
{
    int len, prev_len;
    int max;
    int inside_line;
    char line[MAXLINE];
    char longest[MAXLINE];

    prev_len = 0;
    max = 0;
    inside_line = 0;
    while ((len = getline_r(line, MAXLINE)) > 0) {
        if (inside_line) {
            len = len + prev_len;
        }
        if (line[len - prev_len - 1] == '\n') {
            inside_line = 0;
            prev_len = 0;
        } else {
            // copy the longest possible
            if (!inside_line) {
                copy(longest, line);
            }
            inside_line = 1;
            prev_len = len;
            continue;
        }
        if (len > max) {
            max = len;
            // has copied otherwise
            if (len < MAXLINE) {
                copy(longest, line);
            }
        }
    }
    if (max > 0) {
        printf("%d: %s", max, longest);
        if (max >= MAXLINE) {
            putchar('\n');
        }
    }
    return 0;
}

