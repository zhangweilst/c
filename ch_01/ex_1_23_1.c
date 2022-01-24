#include <stdio.h>
#include <stdlib.h>

#define CODE                0
#define QUOTE_SINGLE        1
#define QUOTE_DOUBLE        2
#define COMMENT_START       3
#define COMMENT_SINGLE      4
#define COMMENT_MULTI       5 
#define COMMENT_MULTI_END   6
#define ESCAPE_SINGLE       7
#define ESCAPE_DOUBLE       8

#define ILLEGAL_STATE       -1

int state = CODE;

void remove_comment_state_machine(char c);

/* 
   remove C comment
 */
int main()
{
    char c;
    while ((c = getchar()) != EOF) {
        remove_comment_state_machine(c);
    }
    return 0;
}

void remove_comment_state_machine(char c)
{
    if (state == CODE) {
        if (c == '/') {
            state = COMMENT_START;
        } else {
            putchar(c);
            if (c == '\'') {
                state = QUOTE_SINGLE;
            } else if (c == '\"') {
                state = QUOTE_DOUBLE;
            }
        }
    } else if (state == QUOTE_SINGLE) {
        putchar(c);
        if (c == '\'') {
            state = CODE;
        } else if (c == '\\') {
            state = ESCAPE_SINGLE;
        }
    } else if (state == QUOTE_DOUBLE) {
        putchar(c);
        if (c == '\"') {
            state = CODE;
        } else if (c == '\\') {
            state = ESCAPE_DOUBLE;
        }
    } else if (state == COMMENT_START) {
        if (c == '/') {
            state = COMMENT_SINGLE;
        } else if (c == '*') {
            state = COMMENT_MULTI;
        } else {
            putchar('/');
            putchar(c);
            state = CODE;
        }
    } else if (state == COMMENT_SINGLE) {
        if (c == '\n') {
            putchar(c);
            state = CODE;
        }
    } else if (state == COMMENT_MULTI) {
        if (c == '*') {
            state = COMMENT_MULTI_END;
        }
    } else if (state == COMMENT_MULTI_END) {
        if (c == '/') {
            state = CODE;
        } else {
            state = COMMENT_MULTI;
        }
    } else if (state == ESCAPE_SINGLE) {
        putchar(c);
        state = QUOTE_SINGLE;
    } else if (state == ESCAPE_DOUBLE) {
        putchar(c);
        state = QUOTE_DOUBLE;
    } else {
        exit(ILLEGAL_STATE);
    }
}

