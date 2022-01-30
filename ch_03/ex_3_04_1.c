#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE     1000

void itoa(int n, char s[]);
void reverse(char s[]);

int main()
{
    char s[MAXLINE];
    int n = 0x80000000;
    itoa(n, s);
    printf("%s\n", s);
    return 0;
}

/*
  itoa: convert n to characters in s

  '%' behavior with negative numbers are implementation defined in C89,
  as stated previously in this book.
  However with C99, it is clearly spelled that '%' is the remainder of
  division truncating to zero, i.e. -6 / 10 = 0, and -6 % 10 = -6.
  We hereby use C99 defined '%' operator.
*/
void itoa(int n, char s[])
{
    int i, sign;

    i = 0;
    sign = n;
    do {
        s[i++] = abs(n % 10) + '0';
    } while ((n /= 10) != 0);

    if (sign < 0)
        s[i++] = '-';
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

