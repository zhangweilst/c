#include <stdio.h>
#include <ctype.h>
#include "../ch_01/ch_01.h"

#define MAXLINE     1000

void expand(char s1[], char s2[]);

/*
  Compile with:
  gcc ../ch_01/ch_01.c ex_3_03_1.c -o ex_3_03_1
*/
int main()
{
    char s1[MAXLINE];
    char s2[MAXLINE * 10];
    int count;
    while ((count = getline_r(s1, MAXLINE)) > 0) {
        s1[count - 1] = '\0'; // get rid of '\n'
        expand(s1, s2);
        printf("%s\n", s2);
    }
    return 0;
}

/*
  expand: expand shorthand notations like a-z in s1 into complete list
  abc...xyz in s2.
*/
void expand(char s1[], char s2[])
{
    int i, j;
    char start, end, prev;
    int trailing;

    trailing = 0;
    for (i = 0; s1[i] != '\0'; ++i);
    for (j = i - 1; j >= 0 && s1[j] == '-'; --j) {
        ++trailing;
        s1[j] = '\0';
    }
    for (i = 0, j = 0; s1[i] == '-'; ++i)
        s2[j++] = s1[i];

    start = end = '\0';
    for (; s1[i] != '\0'; ++i) {
        if (s1[i] == '-') {
            if (start == '\0')
                start = s1[i - 1];
        } else {
            if (!isalnum(s1[i]))
                break;
            if (start == '\0')
                start = s1[i];
            else {
                end = s1[i];
            }
        }
        if (start != '\0' && end != '\0') {
            if (start > end)
                break;
            if ((islower(start) && islower(end)) ||
                (isupper(start) && isupper(end)) ||
                (isdigit(start) && isdigit(end))) {
                for (char c = start; c <= end; ++c) {
                    s2[j++] = c;
                }
                start = '\0';
                end = '\0';
            } else {
                break;
            }
        }
    }

    for (i = 0; i < trailing; ++i)
        s2[j++] = '-';
    s2[j] = '\0';
}

