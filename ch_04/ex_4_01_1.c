#include <stdio.h>
#include <string.h>

int strrindex(char s[], char t[]);

int main()
{
    char s[] = "couldwouldshould";
    char t[] = "ould";
    int rindex = strrindex(s, t);
    printf("strrindex(%s, %s) = %d\n", s, t, rindex);
    return 0;
}

/* 
  strrindex: return the position of the rightmost occurence of t in s,
  or -1 if there is none.
*/
int strrindex(char s[], char t[])
{
    int i, j, k;

    int rindex = -1;
    for (i = 0; s[i] != '\0'; ++i) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; ++j, ++k);
        if (k > 0 && t[k] == '\0')
            rindex = i;
    }
    return rindex;
}

