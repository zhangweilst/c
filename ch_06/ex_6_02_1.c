#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

#define MAXWORD 100

int getword(char *, int);
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);

static int n = 6;

/* word prefix group */
int main(int argc, char *argv[])
{
    if (argc == 2) {
        n = atoi(*++argv);
        if (n <= 0) {
            printf("error: invalid option: %s\n", *argv);
            printf("usage: group [num]\n");
            exit(1);
        }
    }

    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]) && strlen(word) >= n) {
            root = addtree(root, word);
        }
    }
    treeprint(root);

    return 0;
}

struct tnode *talloc(void);

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL) {
        p = talloc();
        p->count = 1;
        p->word = strdup(w);
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        p->count++;
    } else if (cond < 0) {
        p->left = addtree(p->left, w);
    } else {
        p->right = addtree(p->right, w);
    }
    return p;
}

static char *prev = NULL;
/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
    char *strtrn(char *, int);

    if (p != NULL) {
        treeprint(p->left);
        if (prev == NULL || strncmp(p->word, prev, n) != 0) {
            char *prefix = strtrn(p->word, n);
            printf("%s:\n", prefix);
            free(prefix);
        }
        prev = p->word;
        printf("\t%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

/* talloc: make a tnode */
struct tnode *talloc()
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

/* strtrn: truncate string s to strlen of n */
char *strtrn(char *s, int n)
{
    char *d = (char *) malloc((n + 1) * sizeof(char));
    strncpy(d, s, n);
    d[n] = '\0';
    return d;
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

