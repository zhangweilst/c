#include <stdio.h>
#include "ch_01.h"

#define MAXLINE 1000
#define THRESHOLD 80

/* print all input lines longer than 80 characters */

int main()
{
    int len, prev_len;
    int inside_line;
    char line[MAXLINE];

    prev_len = 0;
    inside_line = 0;
    while ((len = getline_r(line, MAXLINE)) > 0) {
        if (inside_line) {
            len = len + prev_len;
        }
        if (line[len - prev_len - 1] == '\n') {
            inside_line = 0;
            prev_len = 0;
        } else {
            // assuming MAXLINE >= THRESHOLD
            printf("%s", line);
            inside_line = 1;
            prev_len = len;
            continue;
        }
        if (len > THRESHOLD) {
            printf("%s", line);
        }
    }
    return 0;
}

