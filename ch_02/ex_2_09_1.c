#include <stdio.h>

int bitcount(unsigned int x);

int main()
{
    unsigned int x = 0b01010011;

    printf("bitcount(0b01010011): %d\n", bitcount(x));
}

/*
  bitcount: count 1 bits in x

  x - 1 will invert the bits from the rightmost 1 to the right position 0:
  x     = 01000100
  x - 1 = 01000011
  As another example:
  x     = 01000101
  x - 1 = 01000100

  After that, x & (x - 1) will clear the bit at the original rightmost
  1 position.
*/
int bitcount(unsigned int x)
{
    int b;

    for (b = 0; x > 0; x &= (x - 1)) {
        ++b;
    }
    return b;
}

