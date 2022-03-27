#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum {NAME, PARENS, BRACKETS };

int gettoken(void);
int getch(void);
void ungetch(int);
void rmredunparens(char *, int);

int tokentype;              /* type of last token */
char token[MAXTOKEN];       /* last token string */
char name[MAXTOKEN];        /* identifier name */
char datatype[MAXTOKEN];    /* data type = char, int, etc. */
char out[1000];             /* output string */

/* 
  undcl: convert word description to declaration,
  remove redundant parentheses
*/
int main()
{
    int type, prev_type;
    char temp[MAXTOKEN + 1000];

    while (gettoken() != EOF) {
        strcpy(out, token);
        prev_type = -1;
        while ((type = gettoken()) != '\n') {
            if (type == PARENS || type == BRACKETS) {
                strcat(out, token);
            } else if (type == '*') {
                rmredunparens(out, prev_type);
                sprintf(temp, "(*%s)", out);
                strcpy(out, temp);
            } else if (type == NAME) {
                rmredunparens(out, prev_type);
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            } else {
                printf("invalid input at %s\n", token);
            }
            prev_type = type;
        }
        printf("%s\n", out);
    }
    return 0;
}

/* gettoken: finds the next token in the input */
int gettoken(void)
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t');
    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']';);
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch());) {
            *p++ = c;
        }
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else {
        return tokentype = c;
    }
}

void rmredunparens(char *s, int prev_type)
{
    int i;

    if (prev_type == '*') {
        int len = strlen(s);
        for (i = 1; i < len; ++i) {
            s[i - 1] = s[i];
        }
        s[len - 2] = '\0';
    }
}

#define BUFSIZE     100

static char buf[BUFSIZE];
static int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

