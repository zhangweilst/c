#include <stdio.h>

int atoi(char *s);

int main()
{
    char *s;
    s = "1234";
    printf("%d\n", atoi(s));
    s = "-1234";
    printf("%d\n", atoi(s));
    s = "-7654123";
    printf("%d\n", atoi(s));
    return 0;
}

/* atoi: ascii to integer, pointer version */
int atoi(char *s)
{
    int n = 0, sign;

    sign = *s == '-' ? -1 : 1;
    if (*s == '-' || *s == '+') {
        s++;
    }
    while (*s >= '0' && *s <= '9') {
        n = 10 * n + (*s - '0');
        s++;
    }
    return sign * n;
}

