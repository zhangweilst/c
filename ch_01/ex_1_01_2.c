
int main()
{
    printf("hello, world\n");
}

/*

We left out the #include <stdio.h> part. Surprisingly at first, this code can
compile and can run. However, it gives 2 warnings:

1, implicit declaration of function ‘printf’ [-Wimplicit-function-declaration]
This is reasonable, since we didn't declare function 'printf' and ignored
the '#include <stdio.h>' part.

2, incompatible implicit declaration of built-in function ‘printf’
Without explicit declaration, the compiler would reckon that 'printf' can take a
'int' type argument, which is not what we passed on.


The interesting part however is why it still can run without
'#include <stdio.h>'.

If we compile the source with 'gcc -o ex_1_01_2 ex_1_01_2.c', we get the
executable ex_1_01_2. Let's examine what happens here:

readelf -d ex_1_01_2

0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]
...

This prints out the dynamic section of the elf executable. As we can find out,
the first entry is of type NEEDED pointing to 'libc.so.6', which is our GNU C
library. If you know little about the ABI of the x86_64 architecture, that's
OK. It justs says we need a dynamic shared library named 'libc.so.6' to run
this executable.

It turns out the printf resides in this library:

nm -D /usr/lib/x86_64-linux-gnu/libc-2.31.so | grep " printf$"
0000000000064e10 T printf

T means the symbol is in the code section and it's global.

At the same time, there's another function that's important for our executable:

nm -D /usr/lib/x86_64-linux-gnu/libc-2.31.so | grep "__libc_start_main"
0000000000026fc0 T __libc_start_main

'main' function is the C entry point function, but from the perspective of OS,
the entry point is always '_start'. The library function '__libc_start_main'
is needed by the '_start' procedure in our executable, and that's why
'libc.so.6' needs to be linked in the first place.

*/

