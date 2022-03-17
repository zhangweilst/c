#include <stdio.h>

void strncpy_r(char *s, char *t, int n);
void strncat_r(char *s, char *t, int n);
int strncmp_r(char *s, char *t, int n);

int main()
{
    char s1[13];
    char t1[] = "hello, world";
    strncpy_r(s1, t1, 5);
    printf("strncpy_r(s1, t1, 5): %s\n", s1);

    char s2_1[13] = "hello, ";
    char s2_2[13] = "hello, ";
    char t2[] = "world";
    strncat_r(s2_1, t2, 3);
    printf("strncat_r(s2_1, t2, 3): %s\n", s2_1);
    strncat_r(s2_2, t2, 5);
    printf("strncat_r(s2_2, t2, 5): %s\n", s2_2);

    char *s3 = "hello";
    char *t3_1 = "hell";
    char *t3_2 = "world";
    printf("strncmp_r(s3, t3_1, 4) = %d\n", strncmp_r(s3, t3_1, 4));
    printf("strncmp_r(s3, t3_1, 5) = %d\n", strncmp_r(s3, t3_1, 5));
    printf("strncmp_r(s3, t3_1, 6) = %d\n", strncmp_r(s3, t3_1, 6));
    printf("strncmp_r(s3, t3_2, 6) = %d\n", strncmp_r(s3, t3_2, 6));
    return 0;
}

void strncpy_r(char *s, char *t, int n) {
    while (n-- > 0 && (*s++ = *t++));
    *s = '\0';
}

void strncat_r(char *s, char *t, int n) {
    while (*s)
        s++;
    while (n-- > 0 && (*s++ = *t++));
    *s = '\0';
}

int strncmp_r(char *s, char *t, int n) {
    for (; n-- > 0 && *s == *t; s++, t++)
        if (*s == '\0')
            return 0;
    if (n < 0) {
        return 0;
    }
    return *s - *t;
}

