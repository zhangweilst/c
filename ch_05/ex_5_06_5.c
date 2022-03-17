#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse(char *s);

int main()
{
    char s[13] = "dlrow ,olleh";
    reverse(s);
    printf("%s\n", s);
    return 0;
}

void reverse(char *s)
{
    int i, j;

    for (i = 0, j = strlen(s) - 1; i < j;  ++i, --j) {
        char tmp = *(s + i);
        *(s + i) = *(s + j);
        *(s + j) = tmp;
    }
}

