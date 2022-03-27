#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000
char *lineptr[MAXLINES];
int (**comp)(void *, void *);

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

// use another name to avoid conflicting definition in stdlib.h
void qsort_r(void *lineptr[], int left, int right, char *pattern,
    int (**comp)(void *, void *), int *reverse, int comp_num);
int numcmp(const char *, const char *);
int strcmp_f(const char *, const char *);
int strcmp_d(const char *, const char *);
int strcmp_fd(const char *, const char *);
int (*get_cmpfunc(int, int, int))(void *, void *);
char *exprstr(char *);

/* sort input lines */
int main(int argc, char *argv[])
{
    int nlines, i;
    int numeric = 0, *numeric_f;
    int reverse = 1, *reverse_f;
    int fold = 0, *fold_f;
    int directory = 0, *directory_f;
    int field_num = 0;
    char *pattern;

    i = 0;
    while (--argc > 0 && (*++argv)[0] == '-') {
        i++;
        while (*++argv[0]) {
            switch (*argv[0]) {
            case 'n':
                if (field_num) {
                    numeric_f[i] = 1;
                } else {
                    numeric = 1;
                }
                break;
            case 'r':
                if (field_num) {
                    reverse_f[i] = -1;
                } else {
                    reverse = -1;
                }
                break;
            case 'f':
                if (field_num) {
                    fold_f[i] = 1;
                } else {
                    fold = 1;
                }
                break;
            case 'd':
                if (field_num) {
                    directory_f[i] = 1;
                } else {
                    directory = 1;
                }
                break;
            case 'F':
                field_num = argc;
                numeric_f = (int *)malloc(field_num * sizeof(int));
                reverse_f = (int *)malloc(field_num * sizeof(int));
                fold_f = (int *)malloc(field_num * sizeof(int));
                directory_f = (int *)malloc(field_num * sizeof(int));
                pattern = exprstr(++argv[0]);
                if (strlen(pattern) <= 0) {
                    pattern = " ";
                }

                for (i = 0; i < field_num; ++i) {
                    numeric_f[i] = i == 0 ? numeric : 0;
                    reverse_f[i] = i == 0 ? reverse : 1;
                    fold_f[i] = i == 0 ? fold : 0;
                    directory_f[i] = i == 0 ? directory : 0;
                }
                i = 0;
                while (*++argv[0]);
                --argv[0];
                break;
            default:
                printf("Usage: sort [-n] [-r] [-f] [-d]"
                    " [-Fdelim [opts ...]]\n");
                printf("error: illegal option %c\n", *argv[0]);
                return 1;
            }
        }
    }
    comp = (int (**)(void *, void *))malloc((field_num > 0 ?
        field_num : 1) * sizeof(int (*)(void *, void *)));
    if (field_num == 0) {
        *comp = get_cmpfunc(numeric, fold, directory);
    } else {
        for (i = 0; i < field_num; ++i) {
            comp[i] = get_cmpfunc(numeric_f[i], fold_f[i], directory_f[i]);
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort_r((void **)lineptr, 0, nlines - 1, pattern,
            comp, reverse_f, field_num);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

/* qsort_r: sort v[left]...v[right] into increasing order */
void qsort_r(void *v[], int left, int right, char *pattern,
    int (**comp)(void *, void *), int *reverse, int comp_num)
{
    int i, last;
    void swap(void *v[], int, int);
    int comp_fields(char *, char *, char *,
        int (**)(void *, void*), int *, int);

    if (left >= right) {
        return;
    }
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; ++i) {
        if (comp_fields(v[i], v[left], pattern, comp,
            reverse, comp_num) < 0) {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    qsort_r(v, left, last - 1, pattern, comp, reverse, comp_num);
    qsort_r(v, last + 1, right, pattern, comp, reverse, comp_num);
}

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

/* strcmp_f: strcmp with fold flag */
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

/* strcmp_d: strcmp with directory order */
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

/* strcmp_fd: strcmp with fold flag and directory order */
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

/* swap: swap position i and j in v */
void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* isdirchar: returns whether c is a letter/number/blank */
int isdirchar(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9') || c == ' ' || c == '\t');
}

/* get_cmpfunc: get compare function according to the flags */
int (*get_cmpfunc(int numeric, int fold, int directory))(void *, void *)
{
    int (*comp)(void *, void *) = (int (*)(void *, void *))strcmp;
    if (numeric) {
        comp = (int (*)(void *, void *)) numcmp;
    } else if (fold && directory) {
        comp = (int (*)(void *, void *)) strcmp_fd;
    } else if (fold) {
        comp = (int (*)(void *, void *)) strcmp_f;
    } else if (directory) {
        comp = (int (*)(void *, void *)) strcmp_d;
    }
    return comp;
}

/* exprstr: extract string from option expression, e.g. '\t' returns a tab */
char *exprstr(char *expr)
{
    int escape, i;
    char *result, c;

    escape = 0, i = 0;
    result = (char *)malloc((strlen(expr) + 1) * sizeof(char));
    while (c = *expr++) {
        if (c == '\\') {
            escape = 1;
        } else {
            if (escape) {
                switch (c) {
                case 'n':
                    result[i++] = '\n';
                    break;
                case 't':
                    result[i++] = '\t';
                    break;
                case '\\':
                    result[i++] = '\\';
                    break;
                case '?':
                    result[i++] = '\?';
                    break;
                case '\'':
                    result[i++] = '\'';
                    break;
                case '\"':
                    result[i++] = '\"';
                    break;
                default:
                    printf("error: unknown escape: %c", c);
                    break;
                }
                escape = 0;
            } else {
                result[i++] = c;
            }
        }
    }
    result[i] = '\0';
    return result;
}

/* comp_fields: compare line by fields delimitted by pattern */
int comp_fields(char *s1, char *s2, char *pattern,
    int (**comp)(void *, void*), int *reverse, int comp_num)
{
    char **s1_fields, **s2_fields;
    int s1_field_num, s2_field_num, i, j;
    int split(char *, char *, char ***);

    if (comp_num == 0) {
        return (*comp[0])(s1, s2) * reverse[0];
    }
    s1_field_num = split(s1, pattern, &s1_fields);
    s2_field_num = split(s2, pattern, &s2_fields);
    for (i = 0; i < s1_field_num && i < s2_field_num; ++i) {
        j = i + 1 >= comp_num ? 0 : i + 1;
        int field_comp = (*comp[j])(s1_fields[i], s2_fields[i])
            * reverse[j];
        if (field_comp != 0) {
            return field_comp;
        }
    }
    return s1_field_num - s2_field_num;
}

/* split: C version of string split */
int split(char *line, char *pattern, char ***result)
{
    char *scopy, *start, *end, *token;
    int i, j;

    scopy = (char *)malloc((strlen(line) + 1) * sizeof(char));
    strcpy(scopy, line);

    i = 0;
    start = scopy;
    while ((start = strstr(start, pattern)) != NULL) {
        ++i;
        start += strlen(pattern);
    }
    *result = (char **)malloc((i + 1) * sizeof(char *));

    j = 0;
    start = scopy;
    while ((end = strstr(start, pattern)) != NULL) {
        for (i = 0; i < strlen(pattern); ++i) {
            *end++ = '\0';
        }
        (*result)[j++] = start;
        start = end;
    }
    (*result)[j++] = start;
    
    return j;
}

