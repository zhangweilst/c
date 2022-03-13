#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse(char s[], int left, int right);

int main()
{
    char s[] = "dlrow ,olleh";
    reverse(s, 0, strlen(s) - 1);
    printf("%s\n", s);
    return 0;
}

/* recursive version of reverse */
void reverse(char s[], int left, int right)
{

    if (left < right) {
        char tmp = s[left];
        s[left] = s[right];
        s[right] = tmp;
        reverse(s, left + 1, right - 1);
    }
}

