#include <stdio.h>

int strend(char *s, char* t);

int main()
{
    char *s = "world";
    char *t1 = "world";
    char *t2 = "rld";
    char *t3 = "wo";
    char *t4 = "hello, world";

    printf("strend(\"%s\", \"%s\") = %d\n", s, t1, strend(s, t1));
    printf("strend(\"%s\", \"%s\") = %d\n", s, t2, strend(s, t2));
    printf("strend(\"%s\", \"%s\") = %d\n", s, t3, strend(s, t3));
    printf("strend(\"%s\", \"%s\") = %d\n", s, t4, strend(s, t4));
    return 0;
}

int strend(char *s, char* t)
{
    char *s_head = s;
    char *t_head = t;

    while (*s++);
    while (*t++);
    --s, --t;
    while (s >= s_head && t >= t_head) {
        if (*s-- != *t--) {
            return 0;
        }
    }
    if (t < t_head) {
        return 1;
    } else {
        return 0;
    }
}

