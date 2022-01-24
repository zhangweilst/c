#include <stdio.h>
#include "ch_01.h"

#define MAXLINE     1000
#define MAXWIDTH    80
#define TABSTOP     8

int print_line(char buffer[], int pos);

/* fold, keeping leading and trailing blanks */
int main()
{
    int len;
    char line[MAXLINE];
    char buffer[MAXWIDTH + 2]; // one extra for rewinding, one extra for '\0'

    int i = 0;
    int buffer_pos = 0;
    while ((len = getline_r(line, MAXLINE)) > 0) {
        for (int j = 0; j < len; ++j) {
            char c = line[j];
            buffer[buffer_pos++] = c;
            if (c == '\n') {
                buffer[buffer_pos] = '\0';
                buffer_pos = print_line(buffer, buffer_pos);
                i = 0;
            } else {
                if (c == '\t') {
                    i += TABSTOP - i % TABSTOP;
                } else {
                    ++i;
                }
                if (i > MAXWIDTH) {
                    buffer[buffer_pos] = '\0';
                    buffer_pos = print_line(buffer, buffer_pos - 1);
                    i = 0;
                    while (buffer[i]) {
                        if (buffer[i] == '\t') {
                            i += TABSTOP - i % TABSTOP;
                        } else {
                            ++i;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int print_line(char buffer[], int pos)
{
    int non_blank_pos = -1, end_pos = -1;
    for (int i = 0; i < pos; ++i) {
        if (buffer[i] == '\n') {
            end_pos = i;
        } else if (buffer[i] == ' ' || buffer[i] == '\t') {
            if (non_blank_pos >= 0) {
                end_pos = non_blank_pos;
            }
        } else {
            non_blank_pos = i;
        }
    }
    if (end_pos == -1) {
        end_pos = pos - 1;
    }
    for (int i = 0; i <= end_pos; ++i) {
        putchar(buffer[i]);
    }
    if (buffer[end_pos] != '\n') {
        putchar('\n');
    }
    copy(buffer, buffer + end_pos + 1);
    int new_pos;
    for (new_pos = 0; buffer[new_pos]; ++new_pos);
    return new_pos;
}

