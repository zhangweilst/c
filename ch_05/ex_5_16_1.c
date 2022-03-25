#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

// use another name to avoid conflicting definition in stdlib.h
void qsort_r(void *lineptr[], int left, int right,
    int (*comp)(void *, void *), int reverse);
int numcmp(const char *, const char *);
int strcmp_f(const char *, const char *);
int strcmp_d(const char *, const char *);
int strcmp_fd(const char *, const char *);

/* sort input lines */
int main(int argc, char *argv[])
{
    int nlines;
    int numeric = 0;
    int reverse = 1;
    int fold = 0;
    int directory = 0;

    while (--argc > 0 && (*++argv)[0] == '-') {
        while (*++argv[0]) {
            switch (*argv[0]) {
            case 'n':
                numeric = 1;
                break;
            case 'r':
                reverse = -1;
                break;
            case 'f':
                fold = 1;
                break;
            case 'd':
                directory = 1;
                break;
            default:
                printf("Usage: sort [-n] [-r] [-f] [-d]\n");
                printf("error: illegal option %c\n", *argv[0]);
                return 1;
            }
        }
    }
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        int (*comp)(void *, void *) = (int (*)(void *, void *)) strcmp;
        if (numeric) {
            comp = (int (*)(void *, void *)) numcmp;
        } else if (fold && directory) {
            comp = (int (*)(void *, void *)) strcmp_fd;
        } else if (fold) {
            comp = (int (*)(void *, void *)) strcmp_f;
        } else if (directory) {
            comp = (int (*)(void *, void *)) strcmp_d;
        }
        qsort_r((void **)lineptr, 0, nlines - 1, comp, reverse);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

/* qsort_r: sort v[left]...v[right] into increasing order */
void qsort_r(void *v[], int left, int right,
    int (*comp)(void *, void *), int reverse)
{
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right) {
        return;
    }
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; ++i) {
        if ((*comp)(v[i], v[left]) * reverse < 0) {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    qsort_r(v, left, last - 1, comp, reverse);
    qsort_r(v, last + 1, right, comp, reverse);
}

#include <stdlib.h>
#include "../ch_01/ch_01.h"

#define MAXLEN 1000

int getline_r(char *, int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = getline_r(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = malloc(len)) == NULL) {
            return -1;
        } else {
            line[len - 1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

/* writelines: write output line */
void writelines(char *lineptr[], int nlines)
{
    int i;

    while (nlines-- > 0) {
        printf("%s\n", *lineptr++);
    }
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(const char *s1, const char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2) {
        return -1;
    } else if (v1 > v2) {
        return 1;
    } else {
        return 0;
    }
}

#include <ctype.h>

int strcmp_f(const char *s1, const char *s2)
{
    for (; tolower(*s1) == tolower(*s2); s1++, s2++) {
        if (*s1 == '\0') {
            return 0;
        }
    }
    return tolower(*s1) - tolower(*s2);
}

int isdirchar(char c);

int strcmp_d(const char *s1, const char *s2)
{
    for (; *s1 && *s2; s1++, s2++) {
        while (!isdirchar(*s1)) {
            s1++;
        }
        while (!isdirchar(*s2)) {
            s2++;
        }
        if (*s1 != *s2) {
            return *s1 - *s2;
        }
    }
    return *s1 - *s2;
}

int strcmp_fd(const char *s1, const char *s2)
{
    for (; *s1 && *s2; s1++, s2++) {
        while (!isdirchar(*s1)) {
            s1++;
        }
        while (!isdirchar(*s2)) {
            s2++;
        }
        if (tolower(*s1) != tolower(*s2)) {
            return tolower(*s1) - tolower(*s2);
        }
    }
    return tolower(*s1) - tolower(*s2);
}

void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int isdirchar(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9') || c == ' ');
}

