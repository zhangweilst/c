#include <stdio.h>

/* verify value of expression getchar() != EOF */
int main()
{
    int r;

    // press CRTL-D to send EOF
    while (r = (getchar() != EOF)) {
        printf("Value of (getchar() != EOF): %d\n", r);
    }
    printf("Value of (getchar() != EOF): %d\n", r);
}

