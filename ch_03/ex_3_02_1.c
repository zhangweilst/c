#include <stdio.h>
#include "../ch_01/ch_01.h"

#define MAXLINE     1000

void escape(char s[], char t[]);
void unescape(char s[], char t[]);

/*
  Compile with:
  gcc ../ch_01/ch_01.c ex_3_02_1.c -o ex_3_02_1
*/
int main()
{
    char s[MAXLINE];
    char t[MAXLINE * 2];
    while ((getline_r(s, MAXLINE)) > 0) {
        escape(s, t);
        printf("%s\n", t);
        unescape(t, s);
        printf("%s", s);
    }
    return 0;
}

/* escape: converts newline and tab into '\n' and '\t' */
void escape(char s[], char t[])
{
    int i, j;

    for (i = 0, j = 0; s[i] != '\0'; ++i) {
        switch (s[i]) {
            case '\n':
                t[j++] = '\\';
                t[j++] = 'n';
                break;
            case '\t':
                t[j++] = '\\';
                t[j++] = 't';
                break;
            default:
                t[j++] = s[i];
                break;
                
        }
    }
    t[j] = '\0';
}

/* unescape: converts '\n' and '\t' back to newline and tab  */
void unescape(char s[], char t[])
{
    int i, j, escaped;

    escaped = 0;
    for (i = 0, j = 0; s[i] != '\0'; ++i) {
        switch (s[i]) {
            case '\\':
                escaped = 1;
                break;
            case 't':
                if (escaped)
                    t[j++] = '\t';
                else
                    t[j++] = 't';
                escaped = 0;
                break;
            case 'n':
                if (escaped)
                    t[j++] = '\n';
                else
                    t[j++] = 'n';
                escaped = 0;
                break;
            default:
                t[j++] = s[i];
                escaped = 0;
                break;
                
        }
    }
    t[j] = '\0';
}

