#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>

/* ranges of C types */
int main()
{
    printf("char range:\t\t\t[%d, %d]\n", CHAR_MIN, CHAR_MAX);
    printf("unsigned char range:\t\t[%u, %u]\n", 0, UCHAR_MAX);
    printf("signed char range:\t\t[%d, %d]\n", SCHAR_MIN, SCHAR_MAX);
    printf("short int range:\t\t[%d, %d]\n", SHRT_MIN, SHRT_MAX);
    printf("unsigned short int range:\t[%u, %u]\n", 0, USHRT_MAX);
    printf("int range:\t\t\t[%d, %d]\n", INT_MIN, INT_MAX);
    printf("unsigned int range:\t\t[%u, %u]\n", 0, UINT_MAX);
    printf("long int range:\t\t\t[%ld, %ld]\n", LONG_MIN, LONG_MAX);
    printf("unsigned long int range:\t[%lu, %lu]\n", 0UL, ULONG_MAX);
    printf("long long int range:\t\t[%lld, %lld]\n", LLONG_MIN, LLONG_MAX);
    printf("unsigned long long int range:\t[%llu, %llu]\n", 0ULL, ULLONG_MAX);

    // FLT_MIN = pow(FLT_RADIX, FLT_MIN_EXP - 1)
    // FLT_MAX = (1 - pow(FLT_RADIX, -FLT_MANT_DIG)) * pow(FLT_RADIX, FLT_MAX_EXP)
    printf("float range:\t\t\t[%.10e, %.10e]\n", FLT_MIN, FLT_MAX);
    printf("double range:\t\t\t[%.20e, %.20e]\n", DBL_MIN, DBL_MAX);
    printf("long double range:\t\t[%.40Le, %.40Le]\n", LDBL_MIN, LDBL_MAX);
}

