#include <stdio.h>

unsigned int setbits(unsigned int x, int p, int n, unsigned int y);

int main()
{
    unsigned int x = 0b01010011;
    unsigned int y = 0b11010010;

    printf("setbits(0b01010011, 4, 3, 0b11010010): %u\n",
        setbits(x, 4, 3, y));
}

/*
  setbits: x with the n bits that begin at p set to 
  the rightmost n bits of y
*/
unsigned int setbits(unsigned int x, int p, int n, unsigned int y)
{
    return (x & ~(~(~0 << n) << (p + 1 - n))) |
        ((y & ~(~0 << n)) << (p + 1 - n));
}

