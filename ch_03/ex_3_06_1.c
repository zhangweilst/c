#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE     1000

void itob(int n, char s[], int w);
void reverse(char s[]);

int main()
{
    int n, w;
    char s[MAXLINE];
    while (scanf("%d, %d", &n, &w) != EOF) {
        itob(n, s, w);
        printf("%s\n", s);
    }
    return 0;
}

/* itob: convert n to base b representation characters in s */
void itob(int n, char s[], int w)
{
    int i, sign;

    i = 0;
    sign = n;
    do {
        s[i++] = abs(n % 10) + '0';
    } while ((n /= 10) != 0);

    if (sign < 0)
        s[i++] = '-';
    while (i < w) {
        s[i++] = ' ';
    }
    s[i] = '\0';
    reverse(s);
}

void reverse(char s[])
{
    int i, j;

    for (i = 0, j = strlen(s) - 1; i < j;  ++i, --j) {
        char tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
}

