#include <stdio.h>
#include <limits.h>
#include "../ch_01/ch_01.h"

#define MAXLINE     1000
#define MAXCHARS    (UCHAR_MAX + 1)

void squeeze(char s1[], char s2[]);

/*
  compile with:
  gcc ../ch_01/ch_01.c ex_2_04_1.c -o ex_2_04_1
*/
int main()
{
    char line1[MAXLINE];
    char line2[MAXLINE];

    while (getline_r(line1, MAXLINE) > 0 && getline_r(line2, MAXLINE) > 0) {
        squeeze(line1, line2);
        printf("%s\n", line1);
    }
    return 0;
}

/* squeeze: deletes each character in s1 that matches any character in s2 */
void squeeze(char s1[], char s2[])
{
    int i, j;
    char bucket[MAXCHARS];

    for (i = 0; i < MAXCHARS; ++i) {
        bucket[i] = 0;
    }
    for (i = 0; s2[i] != '\0'; ++i) {
        bucket[(unsigned char)(s2[i])] = 1;
    }
    for (i = 0, j = 0; s1[i] != '\0'; ++i) {
        if (!bucket[(unsigned char)(s1[i])]) {
            s1[j++] = s1[i];
        }
    }
    s1[j] = '\0';
}

