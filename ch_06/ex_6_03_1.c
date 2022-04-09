#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct tnode {
    char *word;
    int count;
    int *lines;
    struct tnode *left;
    struct tnode *right;
};

/* sorted list of excluded words */
static char *noises[] = {
    "a", "an", "and", "be", "in", "is", "on", "the", "to"
};

#define MAXWORD 100
#define NNOISES (sizeof noises / sizeof noises[0])

int getword(char *, int);
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int binsearch(char *, char *[], int);

static int line = 1;

/* cross referencer to print all words with line number list */
int main(int argc, char *argv[])
{
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]) && binsearch(word, noises, NNOISES) < 0) {
            root = addtree(root, word);
        }
    }
    treeprint(root);

    return 0;
}

struct tnode *talloc(void);
int *addline(int *, int);

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL) {
        p = talloc();
        p->count = 1;
        p->lines = addline(NULL, p->count - 1);
        p->word = strdup(w);
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        p->count++;
        p->lines = addline(p->lines, p->count - 1);
    } else if (cond < 0) {
        p->left = addtree(p->left, w);
    } else {
        p->right = addtree(p->right, w);
    }
    return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
    int i;

    if (p != NULL) {
        treeprint(p->left);
        printf("%s\t\t", p->word);
        for (i = 0; i < p->count; ++i) {
            printf("%d%c", p->lines[i], i == p->count - 1 ? '\n' : ',');
        }
        treeprint(p->right);
    }
}

/* binsearch: find word in tab[0] ... tab[n - 1] */
int binsearch(char *word, char *tab[], int n)
{
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid])) < 0) {
            high = mid - 1;
        } else if (cond > 0) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}

/* talloc: make a tnode */
struct tnode *talloc()
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

#include <math.h>
/* addline: manage lines list and add line number into lines */
int *addline(int *lines, int n)
{
    if (lines == NULL || n <= 0) {
        // init
        lines = (int *) malloc(sizeof(int));
    } else if (ceil(log2(n)) == floor(log2(n))) {
        // n is power of 2, the list is full
        int *tmp = (int *) malloc(n * 2 * sizeof(int)), i;
        for (i = 0; i < n; ++i) {
            tmp[i] = lines[i];
        }
        free(lines);
        lines = tmp;
    }
    lines[n] = line;

    return lines;
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
        if (c == '\n') {
            line++;
        }
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

