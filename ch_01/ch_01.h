#ifndef CH_01_H
#define CH_01_H

void copy(char to[], char from[]);

// the gnu libc has defined a version of getline, we use a different name here
int getline_r(char line[], int maxline);

#endif // CH_01_H

