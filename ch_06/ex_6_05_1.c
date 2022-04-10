#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

unsigned hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
void undef(char *);

static struct nlist *hashtab[HASHSIZE];

int main()
{
    if (install("A", "100") == NULL) {
        return 1;
    }
    if (install("B", "200") == NULL) {
        return 1;
    }
    printf("A: %s\n", lookup("A")->defn);
    printf("B: %s\n", lookup("B")->defn);

    undef("C");
    undef("A");
    printf("B: %s\n", lookup("B")->defn);
    if (lookup("A") != NULL) {
        printf("undef fail\n");
        return 1;
    }
    undef("B");
    if (lookup("B") != NULL) {
        printf("undef fail\n");
        return 1;
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

/* undef: remove name in hashtab */
void undef(char *s)
{
    int hashval;
    struct nlist *prev, *curr;

    hashval = hash(s);
    prev = NULL;
    for (curr = hashtab[hashval]; curr != NULL;
        prev = curr, curr = curr->next) {
        if (strcmp(s, curr->name) == 0) {
            if (prev == NULL) {
                hashtab[hashval] = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr->name);
            free(curr->defn);
            free(curr);
        }
    }
}

