#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "../ch_01/ch_01.h"

#define MAXLINE     1000

double atof(char s[]);

/*
  Compile with:
  gcc ../ch_01/ch_01.c ex_4_02_1.c -lm -o ex_4_02_1
*/
int main()
{
    char s[MAXLINE];
    while (getline_r(s, MAXLINE) > 0) {
        printf("%lf\n", atof(s));
    }
    return 0;
}

/* atof: ascii to floating point number */
double atof(char s[])
{
    double val, power, exponent, exponent_power;
    int i, sign, exponent_sign;

    for (i = 0; isspace(s[i]); ++i);
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '-' || s[i] == '+')
        ++i;
    for (val = 0.0; isdigit(s[i]); ++i)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        ++i;
    for (power = 1.0; isdigit(s[i]); ++i) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    if (s[i] == 'e' || s[i] == 'E')
        ++i;
    exponent_sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '-' || s[i] == '+')
        ++i;
    for (exponent = 0.0; isdigit(s[i]); ++i)
        exponent = 10.0 * exponent + (s[i] - '0');
    if (s[i] == '.')
        ++i;
    for (exponent_power = 1.0; isdigit(s[i]); ++i) {
        exponent = 10.0 * exponent + (s[i] - '0');
        exponent_power *= 10.0;
    }
    return sign * val / power * pow(10, exponent_sign * exponent / exponent_power);
}

