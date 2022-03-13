#include <stdio.h>

#define swap(t, x, y) { \
    t tmp = x; \
    x = y; \
    y = tmp; \
}

int main()
{
    int x1 = 1, y1 = 2;
    double x2 = 1.1, y2 = 2.2;

    swap(int, x1, y1);
    printf("x1 = %d, y1 = %d\n", x1, y1);
    swap(double, x2, y2);
    printf("x2 = %f, y2 = %f\n", x2, y2);

    return 0;
}

