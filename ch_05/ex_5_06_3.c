#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE     1000

void itoa(int n, char *s);
void reverse(char s[]);

int main()
{
    char s[MAXLINE];
    int n = 0x80000000;
    itoa(n, s);
    printf("%s\n", s);
    return 0;
}

/* itoa: convert n to characters in s, pointer version */
void itoa(int n, char *s)
{
    int sign;
    char *s_head = s;

    sign = n;
    do {
        *s++ = abs(n % 10) + '0';
    } while ((n /= 10) != 0);

    if (sign < 0)
        *s++ = '-';
    *s = '\0';
    reverse(s_head);
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

