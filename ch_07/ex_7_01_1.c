#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int c;

    while ((c = getchar()) != EOF) {
        if (strstr(argv[0], "tolower") != NULL) {
            putchar(tolower(c));
        } else if (strstr(argv[0], "toupper") != NULL) {
            putchar(toupper(c));
        } else {
            putchar(c);
        }
    }

    return 0;
}

