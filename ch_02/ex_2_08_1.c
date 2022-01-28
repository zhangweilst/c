#include <stdio.h>

unsigned int rightrot(unsigned int x, int n);

int main()
{
    unsigned int x = 0b01010011;

    printf("rightrot(0b01010011, 3): %u\n", rightrot(x, 3));
}

/* rotate x to the right by n bit positions */
unsigned int rightrot(unsigned int x, int n)
{
    return (x >> n) | (x << (((sizeof(unsigned int)) << 3) - n));
}

