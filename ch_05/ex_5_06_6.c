#include <stdio.h>

int strindex(char *s, char *t);

int main()
{
    char *s1 = "hello, world";
    char *t1 = "world";
    char *t2 = "hello, miss";
    printf("strindex(s1, t1) = %d\n", strindex(s1, t1));
    printf("strindex(s1, t2) = %d\n", strindex(s1, t2));
    return 0;
}

/* return index of t in s, -1 if none */
int strindex(char *s, char *t)
{
    char *s_i, *s_j, *t_k;

    for (s_i = s; *s_i; s_i++) {
        for (s_j = s_i, t_k = t; *t_k && *s_j == *t_k; s_j++, t_k++);
        if (t_k > t && !*t_k)
            return s_i - s;
    }
    return -1;
}

