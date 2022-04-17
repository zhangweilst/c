#include <stdio.h>
#include <stdlib.h>

void filecopy(FILE *, FILE *);

/* cat with page break */
int main(int argc, char *argv[])
{
    FILE *fp;
    void filecopy(FILE *, FILE *);
    char *prog = argv[0];
    int page = 1;

    if (argc == 1) {
        fprintf(stdout, "%s%20d\n", "stdin", page);
        filecopy(stdin, stdout);
    } else {
        while (--argc > 0) {
            if ((fp = fopen(*++argv, "r")) == NULL) {
                fprintf(stderr, "%s: can't open %s\n", prog, *argv);
                exit(1);
            } else {
                fprintf(stdout, "%s%20d\n", *argv, page++);
                filecopy(fp, stdout);
                fprintf(stdout, argc == 1 ? "" : "\f");
                fclose(fp);
            }
        }
    }
    if (ferror(stdout)) {
        fprintf(stderr, "%s: error wrting stdout\n", prog);
        exit(2);
    }
    exit(0);
}

void filecopy(FILE *ifp, FILE *ofp)
{
    int c;

    while ((c = getc(ifp)) != EOF) {
        putc(c, ofp);
    }
}

