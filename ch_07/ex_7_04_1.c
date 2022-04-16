#include <stdio.h>
#include <stdarg.h>

void minscanf(char *fmt, ...);

int main()
{
    int day, month, year;
    minscanf("%d-%d-%d", &year, &month, &day);
    printf("%d-%d-%d\n", year, month, day);

    float a, b;
    minscanf("%f + %f =", &a, &b);
    printf("%f\n", a + b);
    return 0;
}

void minscanf(char *fmt, ...)
{
    va_list ap;
    char *p, *sp, mfmt[3];
    int *ip;
    float *fp;

    va_start(ap, fmt);
    for (p = fmt; *p; ++p) {
        if (*p != '%') {
            mfmt[0] = *p, mfmt[1] = '\0';
            scanf(mfmt);
            continue;
        }
        switch (*++p) {
        case 'd': case 'i': case 'o': case 'u':
        case 'x': case 'c':
            mfmt[0] = '%', mfmt[1] = *p, mfmt[2] = '\0';
            ip = va_arg(ap, int *);
            scanf(mfmt, ip);
            break;
        case 's':
            sp = va_arg(ap, char *);
            scanf("%s", sp);
            break;
        case 'e': case 'f': case 'g':
            mfmt[0] = '%', mfmt[1] = *p, mfmt[2] = '\0';
            fp = va_arg(ap, float *);
            scanf(mfmt, fp);
            break;
        default:
            mfmt[0] = *p, mfmt[1] = '\0';
            scanf(mfmt);
            break;
        }
    }
    va_end(ap);
}

