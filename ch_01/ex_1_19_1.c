#include <stdio.h>
#include "ch_01.h"

#define MAXLINE 1000

void reverse(char s[]);

/* reverse */
int main()
{
    int len;
    char line[MAXLINE];

    while ((len = getline_r(line, MAXLINE)) > 0) {
        if (line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        reverse(line);
        printf("%s\n", line);
    }
    return 0;
}

/* reverse string s in place */
void reverse(char s[])
{
    int n = 0;
    while (s[n]) {
        n++;
    }

    int i = 0, j = n - 1;
    while (i < j) {
        char tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
        ++i;
        --j;
    }
}

