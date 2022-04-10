#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASHSIZE 101
#define MAXWORD 100

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

enum {
    CODE, QUOTE_SINGLE, QUOTE_DOUBLE, COMMENT_START, COMMENT_SINGLE,
    COMMENT_MULTI, COMMENT_MULTI_END, ESCAPE_SINGLE, ESCAPE_DOUBLE,
    PREPROCESSOR, ILLEGAL_STATE
};

unsigned hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
void c_state_machine(char);
int getch(void);
char *stripe(char *);

static struct nlist *hashtab[HASHSIZE];
static int state = CODE;

/* simple #define preprocessor */
int main()
{
    char c, word[3][MAXWORD];
    int i, j;

    i = 0, j = 0;
    while ((c = getch()) != EOF) {
        if (c == '_' || isalnum(c)) {
            word[i][j++] = c;
        } else {
            word[i][j] = '\0';
            if (state == PREPROCESSOR) {
                if (i == 2) {
                    if (c == '\n') {
                        if (strcmp("define", word[0]) == 0) {
                            install(word[1], stripe(word[2]));
                        }
                        printf("%s", word[i]);
                        putchar(c);
                        i = j = 0;
                    } else {
                        word[i][j++] = c;
                    }
                } else {
                    printf("%s", word[i]);
                    putchar(c);
                    if (j > 0) {
                        ++i;
                        j = 0;
                    }
                }
            } else {
                if (state == CODE) {
                    struct nlist *node = lookup(word[0]);
                    if (node != NULL) {
                        printf("%s", node->defn);
                    } else {
                        printf("%s", word[0]);
                    }
                } else {
                    printf("%s", word[0]);
                }
                j = 0;
                putchar(c);
            }
        }
        c_state_machine(c);
    }
    return 0;
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL) {
            return NULL;
        }
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free((void *)np->defn);
    }
    if ((np->defn = strdup(defn)) == NULL) {
        return NULL;
    }
    return np;
}

/* hash: form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++) {
        hashval = *s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0) {
            return np;
        }
    }
    return NULL;
}

/* stripe leading and suffix spaces in string s */
char *stripe(char *s)
{
    int i;

    while (isspace(*s)) {
        s++;
    }
    for (i = strlen(s) - 1; i >= 0 && isspace(s[i]); --i) {
        s[i] = '\0';
    }
    
    return s;
}

/* c_state_machine: state machine for C code */
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
        if (c == '\n') {
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

