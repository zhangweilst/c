#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE     1000

int itoa(int n, char s[]);

int main()
{
    char s[MAXLINE];
    int n = 0x80000000;
    itoa(n, s);
    printf("%s\n", s);
    return 0;
}

/*
  itoa: convert n to characters in s, recursive version
*/

int itoa(int n, char s[])
{

    if (n < 0) {
        s[0] = '-';
    }
    int i = n < 0 ? 1 : 0;
    if (n / 10) {
        i = itoa(n / 10, s);
    }
    s[i] = abs(n % 10) + '0';
    s[i + 1] = '\0';
    return i + 1;
}

