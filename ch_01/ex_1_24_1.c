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
#define STACKOVERFLOW       -2
#define STACKUNDERFLOW      -3

#define MAXDEPTH            1000

int state = CODE;
char stack[MAXDEPTH];
int sp = 0;

void push(char c);
char pop();
void rudimentary_c_state_machine(char c);

/* 
   rudimentary syntax errors check 
 */
int main()
{
    char c;
    while ((c = getchar()) != EOF) {
        if (state == CODE) {
            if (c == '{' || c == '[' || c == '(') {
                push(c);
            }
            if (c == '}') {
                if (pop() != '{') {
                    printf("Error: Unmatched }\n");
                    return 1;
                }
            }
            if (c == ']') {
                if (pop() != '[') {
                    printf("Error: Unmatched ]\n");
                    return 1;
                }
            }
            if (c == ')') {
                if (pop() != '(') {
                    printf("Error: Unmatched )\n");
                    return 1;
                }
            }
        }

        rudimentary_c_state_machine(c);
    }
    if ((c = pop()) != STACKUNDERFLOW) {
        printf("Error: Unmatched %c\n", c);
        return 1;
    }
    return 0;
}

void rudimentary_c_state_machine(char c)
{
    if (state == CODE) {
        if (c == '/') {
            state = COMMENT_START;
        } else if (c == '\'') {
            state = QUOTE_SINGLE;
        } else if (c == '\"') {
            state = QUOTE_DOUBLE;
        }
    } else if (state == QUOTE_SINGLE) {
        if (c == '\'') {
            state = CODE;
        } else if (c == '\\') {
            state = ESCAPE_SINGLE;
        }
    } else if (state == QUOTE_DOUBLE) {
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
            state = CODE;
        }
    } else if (state == COMMENT_SINGLE) {
        if (c == '\n') {
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
        state = QUOTE_SINGLE;
    } else if (state == ESCAPE_DOUBLE) {
        state = QUOTE_DOUBLE;
    } else {
        exit(ILLEGAL_STATE);
    }
}

void push(char c)
{
    if (sp < MAXDEPTH) {
        stack[sp++] = c;
    } else {
        exit(STACKOVERFLOW);
    }
}

char pop()
{
    if (sp > 0) {
        return stack[--sp];
    } else {
        return STACKUNDERFLOW;
    }
}

