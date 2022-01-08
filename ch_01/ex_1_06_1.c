#include <stdio.h>

/* verify value of expression getchar() != EOF */
int main()
{
    int c, r;

    // type crtl-d to send EOF
    while (r = ((c = getchar()) != EOF)) {
        printf("Value of (getchar() != EOF): %d\n", r);
    }
    printf("Value of (getchar() != EOF): %d\n", r);
}

