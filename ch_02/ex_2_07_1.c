#include <stdio.h>

unsigned int invert(unsigned int x, int p, int n);
unsigned int setbits(unsigned int x, int p, int n, unsigned int y);

int main()
{
    unsigned int x = 0b01010011;

    printf("invert(0b01010011, 4, 3): %u\n", invert(x, 4, 3));
}

/*
  invert: returns x whth the n bits that begin at position p
  inverted (i.e., 1 changed to 0 and vice versa), leaving the
  others unchanged
*/
unsigned int invert(unsigned int x, int p, int n)
{
    unsigned int y = ~((x >> (p + 1 -n)) & ~(~0 << n));
    return setbits(x, p, n, y);
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

