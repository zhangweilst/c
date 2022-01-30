#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE     1000

void itob(int n, char s[], int b);
void reverse(char s[]);

int main()
{
    int n, b;
    char s[MAXLINE];
    while (scanf("%d, %d", &n, &b) != EOF) {
        itob(n, s, b);
        printf("%s\n", s);
    }
    return 0;
}

/* itob: convert n to base b representation characters in s */
void itob(int n, char s[], int b)
{
    int i, sign;

    i = 0;
    sign = n;
    do {
        char digit = abs(n % b);
        if (digit > 9) {
            digit = digit - 10 + 'a';
        } else {
            digit += '0';
        }
        s[i++] = digit;
    } while ((n /= b) != 0);

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

