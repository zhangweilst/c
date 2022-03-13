#ifndef _CALC_H_
#define _CALC_H_

#include <limits.h>

#define UNKNOWN     INT_MIN
#define NUMBER      (INT_MIN + 1)
#define PEEK        (INT_MIN + 2)
#define DUP         (INT_MIN + 3)
#define SWAP        (INT_MIN + 4)
#define CLEAR       (INT_MIN + 5)
#define SIN         (INT_MIN + 6)
#define COS         (INT_MIN + 7)
#define TAN         (INT_MIN + 8)
#define ASIN        (INT_MIN + 9)
#define ACOS        (INT_MIN + 10)
#define ATAN        (INT_MIN + 11)
#define ATAN2       (INT_MIN + 12)
#define SINH        (INT_MIN + 13)
#define COSH        (INT_MIN + 14)
#define TANH        (INT_MIN + 15)
#define EXP         (INT_MIN + 16)
#define LOG         (INT_MIN + 17)
#define LOG10       (INT_MIN + 18)
#define POW         (INT_MIN + 19)
#define SQRT        (INT_MIN + 20)
#define CEIL        (INT_MIN + 21)
#define FLOOR       (INT_MIN + 22)
#define FABS        (INT_MIN + 23)
#define LDEXP       (INT_MIN + 24)
#define FMOD        (INT_MIN + 25)
#define SETVAR      (INT_MIN + 26)
#define LATESTVAR   (INT_MIN + 27)

int getop(char []);
void push(double);
double pop(void);
double peek(void);
void dup(void);
void swap(void);
void clear(void);
int getch(void);
void ungetch(int);

#endif // _CALC_H_

