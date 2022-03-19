#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main()
{
    printf("day_of_year(1990, 9, 2) = %d\n", day_of_year(1990, 9, 2));
    printf("day_of_year(1990, 9, 31) = %d\n", day_of_year(1990, 9, 31));
    printf("day_of_year(1990, 2, 29) = %d\n", day_of_year(1990, 2, 29));

    int month, day;
    month_day(1988, 60, &month, &day);
    printf("month_day(1988, 60) = %d, %d\n", month, day);
    month_day(1989, 60, &month, &day);
    printf("month_day(1989, 60) = %d, %d\n", month, day);
    month_day(1989, 365, &month, &day);
    printf("month_day(1989, 365) = %d, %d\n", month, day);
    month_day(1989, 366, &month, &day);
    printf("month_day(1989, 366) = %d, %d\n", month, day);
    return 0;
}

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;

    leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (month < 1 || month > 12 || day < 1 || day > daytab[leap][month]) {
        printf("error: invalid input\n");
        return -1;
    }
    for (i = 1; i < month; ++i) {
        day += daytab[leap][i];
    }
    return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (yearday < 1 || (leap ? yearday > 366 : yearday > 365)) {
        printf("error: invalid input\n");
        *pmonth = -1;
        *pday = -1;
        return;
    }
    for (i = 1; yearday > daytab[leap][i]; ++i) {
        yearday -= daytab[leap][i];
    }
    *pmonth = i;
    *pday = yearday;
}

