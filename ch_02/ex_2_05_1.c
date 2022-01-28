#include <stdio.h>
#include <limits.h>

#define MAXCHARS    (UCHAR_MAX + 1)

int any(char s1[], char s2[]);

int main()
{
    char s1[] = "abcdefghijklmn";
    char s2[] = "ihg";
    printf("s1: %s, s2: %s, any(s1, s2): %d\n", s1, s2, any(s1, s2));
    return 0;
}

/* any: returns first location in s1 where any character in s2 occurs */
int any(char s1[], char s2[])
{
    int i;
    char bucket[MAXCHARS];

    for (i = 0; i < MAXCHARS; ++i) {
        bucket[i] = 0;
    }
    for (i = 0; s2[i] != '\0'; ++i) {
        bucket[(unsigned char)(s2[i])] = 1;
    }
    for (i = 0; s1[i] != '\0'; ++i) {
        if (bucket[(unsigned char)(s1[i])]) {
            return i;
        }
    }
    return -1;
}

