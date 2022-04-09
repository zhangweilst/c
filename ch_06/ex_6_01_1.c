#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

static struct key {
    char *word;
    int count;
} keytab[] = {
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "const", 0,
    "continue", 0,
    "default", 0,
    "do", 0,
    "double", 0,
    "else", 0,
    "enum", 0,
    "extern", 0,
    "float", 0,
    "for", 0,
    "goto", 0,
    "if", 0,
    "int", 0,
    "long", 0,
    "register", 0,
    "return", 0,
    "short", 0,
    "signed", 0,
    "sizeof", 0,
    "static", 0,
    "struct", 0,
    "switch", 0,
    "typedef", 0,
    "union", 0,
    "unsigned", 0,
    "void", 0,
    "volatile", 0,
    "while", 0
};

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof keytab[0])

int getword(char *, int);
int binsearch(char *, struct key *, int);

/* count C keywords */
int main()
{
    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            if ((n = binsearch(word, keytab, NKEYS)) >= 0) {
                keytab[n].count++;
            }
        }
    }
    for (n = 0; n < NKEYS; ++n) {
        if (keytab[n].count > 0) {
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
        }
    }
    return 0;
}

/* binsearch: find word in tab[0] ... tab[n - 1] */
int binsearch(char *word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0) {
            high = mid - 1;
        } else if (cond > 0) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}

enum {
    CODE, QUOTE_SINGLE, QUOTE_DOUBLE, COMMENT_START, COMMENT_SINGLE,
    COMMENT_MULTI, COMMENT_MULTI_END, ESCAPE_SINGLE, ESCAPE_DOUBLE,
    PREPROCESSOR, ILLEGAL_STATE

};
static int state = CODE;

/*
  getword: get next word or charactoer from input
*/
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    void c_state_machine(char);
    char *w = word;
    int prev_state = CODE;

    while (isspace(c = getch())) {
        prev_state = state;
        c_state_machine(c);
    }
    prev_state = state;
    c_state_machine(c);
    if (state > CODE) {
        *w = '\0';
        return 0;
    }
    if (c != EOF) {
        *w++ = c;
    }
    if (!isalpha(c) && c != '_') {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++) {
        if (!isalnum(*w = getch()) && *w != '_') {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

void c_state_machine(char c)
{
    if (state == CODE) {
        if (c == '/') {
            state = COMMENT_START;
        } else if (c == '\'') {
            state = QUOTE_SINGLE;
        } else if (c == '\"') {
            state = QUOTE_DOUBLE;
        } else if (c == '#') {
            state = PREPROCESSOR;
        }
    } else if (state == QUOTE_SINGLE) {
        if (c == '\'') {
            state = CODE;
        } else if (c == '\\') {
            state = ESCAPE_SINGLE;
        }
    } else if (state == QUOTE_DOUBLE) {
        if (c == '\"') {
            state = CODE;
        } else if (c == '\\') {
            state = ESCAPE_DOUBLE;
        }
    } else if (state == COMMENT_START) {
        if (c == '/') {
            state = COMMENT_SINGLE;
        } else if (c == '*') {
            state = COMMENT_MULTI;
        } else {
            state = CODE;
        }
    } else if (state == COMMENT_SINGLE) {
        if (c == '\n') {
            state = CODE;
        }
    } else if (state == COMMENT_MULTI) {
        if (c == '*') {
            state = COMMENT_MULTI_END;
        }
    } else if (state == COMMENT_MULTI_END) {
        if (c == '/') {
            state = CODE;
        } else {
            state = COMMENT_MULTI;
        }
    } else if (state == ESCAPE_SINGLE) {
        state = QUOTE_SINGLE;
    } else if (state == ESCAPE_DOUBLE) {
        state = QUOTE_DOUBLE;
    } else if (state == PREPROCESSOR) {
        // after the first space, the following counts as keywords
        if (isspace(c)) {
            state = CODE;
        }
    } else {
        printf("error: illegal input: %c\n", c);
        exit(ILLEGAL_STATE);
    }
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

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

