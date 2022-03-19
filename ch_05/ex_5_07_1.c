#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines, char buf[]);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

/* sort input lines */
int main()
{
    int nlines, i;
    char buf[MAXLINES * MAXLEN];

    if ((nlines = readlines(lineptr, MAXLINES, buf)) >= 0) {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

#include "../ch_01/ch_01.h"


int getline_r(char *, int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines, char buf[])
{
    int len, nlines;
    char line[MAXLEN];

    nlines = 0;
    while ((len = getline_r(line, MAXLEN)) > 0) {
        if (nlines >= maxlines) {
            return -1;
        } else {
            line[len - 1] = '\0'; /* delete newline */
            strcpy(buf, line);
            lineptr[nlines++] = buf;
            buf += len;
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

void qsort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);

    if (left >= right) {
        return;
    }
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; ++i) {
        if (strcmp(v[i], v[left]) < 0) {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
    char *tmp;

    tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}

