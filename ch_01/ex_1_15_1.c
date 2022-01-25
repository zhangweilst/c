#include <stdio.h>

float fahr_to_celsius(float fahr)
{
    return (5.0 / 9.0) * (fahr - 32.0);
}

float celsius_to_fahr(float celsius)
{
    return (9.0 / 5.0) * celsius + 32.0;
}

/* temporature conversion with a function call */
int main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    printf("%4s %8s\n", "fahr", "celsius");
    while (fahr <= upper) {
        celsius = fahr_to_celsius(fahr);
        printf("%4.0f %8.1f\n", fahr, celsius);
        fahr = fahr + step;
    }

    lower = 0;
    upper = 300;
    step = 20;

    celsius = lower;
    printf("%8s %5s\n", "celsius", "fahr");
    while (celsius <= upper) {
        fahr = celsius_to_fahr(celsius);
        printf("%8.0f %5.1f\n", celsius, fahr);
        celsius = celsius + step;
    }

}

