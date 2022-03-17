#include <stdio.h>

#define MAXLINE 1000

int getline_r(char *s, int lim);

int main()
{
    char s[MAXLINE];
    int len;
    while ((len = getline_r(s, MAXLINE)) > 0) {
        printf("%s%d\n", s, len);
    }
}

int getline_r(char *s, int lim)
{
    int c;
    char *s_head = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
        *s++ = c;
    }
    if (c == '\n') {
        *s++ = c;
    }
    *s = '\0';
    return s - s_head;
}

