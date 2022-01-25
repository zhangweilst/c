#include <stdio.h>

/* print Celsius-Fahrenheit table, with a header */
int main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    celsius = lower;
    printf("%8s %5s\n", "celsius", "fahr");
    while (celsius <= upper) {
        fahr = (9.0 / 5.0) * celsius + 32.0;
        printf("%8.0f %5.1f\n", celsius, fahr);
        celsius = celsius + step;
    }
}

