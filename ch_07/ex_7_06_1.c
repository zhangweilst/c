#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

/* compare two files, printing the first line they differ */
int main(int argc, char *argv[])
{
    FILE *fpl, *fpr;
    char linel[MAXLINE], liner[MAXLINE];
    char *l, *r;

    if (argc != 3) {
        fprintf(stderr, "Usage: diff file1 file2\n");
        return 1;
    }
    
    if ((fpl = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "%s: can't open %s\n", argv[0], argv[1]);
        return 1;
    }
    if ((fpr = fopen(argv[2], "r")) == NULL) {
        fprintf(stderr, "%s: can't open %s\n", argv[0], argv[2]);
        return 1;
    }
    while ((l = fgets(linel, MAXLINE, fpl)) != NULL &&
        (r = fgets(liner, MAXLINE, fpr)) != NULL) {
        if (strcmp(linel, liner)) {
            printf("< %s", linel);
            printf("> %s", liner);
            fclose(fpl);
            fclose(fpr);
            return 0;
        }
    }
    if (l != NULL) {
        printf("< %s", linel);
    }
    if (r != NULL) {
        printf("> %s", liner);
    }
    fclose(fpl);
    fclose(fpr);

    return 0;
}

