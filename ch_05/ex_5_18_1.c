#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum {NAME, PARENS, BRACKETS };

int dcl(void);
int dirdcl(void);

int gettoken(void);
int getch(void);
void ungetch(int);
void clearup(void);

int tokentype;              /* type of last token */
char token[MAXTOKEN];       /* last token string */
char name[MAXTOKEN];        /* identifier name */
char datatype[MAXTOKEN];    /* data type = char, int, etc. */
char out[1000];             /* output string */

/* being able to recover from input error */
int main()
{
    while (gettoken() != EOF) {
        /* 1st token on line is the datatype */
        if (tokentype != NAME) {
            printf("error: expected data type\n");
            clearup();
            continue;
        }
        strcpy(datatype, token);
        out[0] = '\0';
        if (dcl()) {
            clearup();
            continue;
        }
        if (tokentype != '\n') {
            printf("syntax error\n");
            clearup();
            continue;
        }
        printf("%s:%s %s\n", name, out, datatype);
    }
    return 0;
}

/* dcl: parse a declarator */
int dcl(void)
{
    int ns;

    for (ns = 0; gettoken() == '*';) {
        ns++;
    }
    if (dirdcl()) {
        return 1;
    }
    while (ns-- > 0) {
        strcat(out, " pointer to");
    }
    return 0;
}

/* dirdcl: parse a direct declarator */
int dirdcl(void)
{
    int type;

    if (tokentype == '(') {
        dcl();
        if (tokentype != ')') {
            printf("error: missing )\n");
            return 1;
        }
    } else if (tokentype == NAME) {
        strcpy(name, token);
    } else {
        printf("error: expected name or (dcl)\n");
        return 1;
    }
    while ((type = gettoken()) == PARENS || type == BRACKETS) {
        if (type == PARENS) {
            strcat(out, " function returning");
        } else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
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

/* clearup: clear up the variables to recover from failure */
void clearup()
{
    // feed the remaining declarator
    if (tokentype != '\n') {
        while (gettoken() != '\n');
    }

    token[0] = name[0] = datatype[0] = out[0] = '\0';
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

