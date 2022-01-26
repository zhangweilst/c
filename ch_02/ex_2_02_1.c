#include <stdio.h>

#define MAXLINE     1000

int getline_r(char s[], int lim);

int main()
{
    char line[MAXLINE];
    while (getline_r(line, MAXLINE) > 0) {
        printf("%s", line);
    }
    return 0;
}

/* getline without '&&' or '||' operator */
int getline_r(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1; ++i) {
        if ((c = getchar()) != EOF)
            if (c != '\n')
                s[i] = c;
            else
                break;
        else
            break;
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

