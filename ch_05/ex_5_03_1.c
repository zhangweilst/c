#include <stdio.h>

void strcat_r(char *s, char *t);

int main()
{
    char s[13] = "hello, ";
    char t[] = "world";
    strcat_r(s, t);
    printf("%s\n", s);
    return 0;
}

/* strcat: pointer version */
void strcat_r(char *s, char *t)
{
    while (*s)
        s++;
    while (*s++ = *t++);
}

