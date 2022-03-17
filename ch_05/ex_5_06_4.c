#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE     1000

char *itoa(int n, char *s);

int main()
{
    char s[MAXLINE];
    int n = 0x80000000;
    itoa(n, s);
    printf("%s\n", s);
    return 0;
}

/*
  itoa: convert n to characters in s, recursive with pointer version
*/

char *itoa(int n, char *s)
{

    if (n < 0) {
        *s++ = '-';
    }
    int next = n / 10;
    if (next) {
        s = itoa(next > 0 ? next : -next, s);
    }
    *s++ = abs(n % 10) + '0';
    *s= '\0';
    return s;
}

