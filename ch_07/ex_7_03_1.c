#include <stdio.h>
#include <stdarg.h>

void minprintf(char *fmt, ...);

int main()
{
    minprintf("%s said %d + %d = %f\n", "Xiaoming", 1, 1, 2.0);
    int a = 255;
    minprintf("He also said decimal %d is octal %o,"
        " and is hex %x\n", a, a, a);
    minprintf("Variable a is pointed by: %p\n", &a);
    return 0;
}

void minprintf(char *fmt, ...)
{
    va_list ap;
    char *p, *sval, mfmt[3];
    int ival;
    double dval;
    void *pval;

    va_start(ap, fmt);
    for (p = fmt; *p; ++p) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
        case 'd': case 'i': case 'o': case 'x':
        case 'X': case 'u': case 'c':
            mfmt[0] = '%', mfmt[1] = *p, mfmt[2] = '\0';
            ival = va_arg(ap, int);
            printf(mfmt, ival);
            break;
        case 's':
            sval = va_arg(ap, char *);
            printf("%s", sval);
            break;
        case 'f': case 'e': case 'E':
        case 'g': case 'G':
            mfmt[0] = '%', mfmt[1] = *p, mfmt[2] = '\0';
            dval = va_arg(ap, double);
            printf(mfmt, dval);
            break;
        case 'p':
            pval = va_arg(ap, void *);
            printf("%p", pval);
            break;
        default:
            putchar(*p);
            break;
        }
    }
    va_end(ap);
}

