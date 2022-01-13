#include <stdio.h>
#include "ch_01.h"

#define MAXLINE 1000

/* remove trailing blanks */

int main()
{
    int len;
    char line[MAXLINE];

    while ((len = getline_r(line, MAXLINE)) > 0) {
        int i;
        for (i = len - 1; i >= 0 && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'); --i) {
            line[i] = '\0';
        }
        printf("%s\n", line);
    }
    return 0;
}

