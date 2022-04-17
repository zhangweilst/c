#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

/* find: pattern finding taking input from files */
int main(int argc, char *argv[])
{
    char line[MAXLINE], *pattern;
    long lineno;
    int c, except = 0, number = 0, found = 0;
    FILE *fp;

    while (--argc > 0 && (*++argv)[0] == '-') {
        while (c = *++argv[0]) {
            switch (c) {
            case 'x':
                except = 1;
                break;
            case 'n':
                number = 1;
                break;
            default:
                fprintf(stderr, "find: illegal option %c\n", c);
                argc = 0;
                found = -1;
                break;
            }
        }
    }
    if (argc < 1) {
        fprintf(stderr, "Usage: find [-x] [-n] pattern [file ...]\n");
    } else {
        pattern = *argv++;
        if (*argv) {
            if ((fp = fopen(*argv, "r")) == NULL) {
                fprintf(stderr, "find: cannot open file %s\n", *argv);
                return -1;
            }
        } else {
            fp = stdin;
        }
        do {
            lineno = 0;
            while (fgets(line, MAXLINE, fp) != NULL) {
                ++lineno;
                if ((strstr(line, pattern) != NULL) != except) {
                    printf("%s", *argv ? *argv : "stdin");
                    if (number) {
                        printf("#%ld", lineno);
                    }
                    printf(":%s", line);
                    found++;
                }
            }
            if (*argv) {
                fclose(fp);
                argv++;
            }
        } while (*argv && (fp = fopen(*argv, "r")) != NULL);
        if (fp == NULL) {
            fprintf(stderr, "find: cannot open file %s\n",
                *argv ? *argv : "stdin");
            return -1;
        }
    }

    return found;
}

