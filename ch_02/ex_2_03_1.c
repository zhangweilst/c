#include <stdio.h>
#include "../ch_01/ch_01.h"

#define MAXLINE     1000

int htoi(char s[]);

/*
  compile with:
  gcc ../ch_01/ch_01.c ex_2_03_1.c -o ex_2_03_1
*/
int main()
{
    char line[MAXLINE];

    while (getline_r(line, MAXLINE) > 0) {
        printf("%d\n", htoi(line));
    }
    return 0;
}

/* hexa-decimal to integer */
int htoi(char s[])
{
    int i, n;

    n = 0;
    for (i = 0; s[i]; ++i) {
        if (s[i] >= '0' && s[i] <= '9') {
            n = n * 16 + s[i] - '0';
        } else if (s[i] >= 'a' && s[i] <= 'f') {
            n = n * 16 + s[i] - 'a' + 10;
        } else if (s[i] >= 'A' && s[i] <= 'F') {
            n = n * 16 + s[i] - 'A' + 10;
        }
    }
    return n;
}

