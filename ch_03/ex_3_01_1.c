#include <stdio.h>

int binsearch_v1(int x, int v[], int n);
int binsearch_v2(int x, int v[], int n);

int main()
{
    int x, r1, r2;
    int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    x = 0;
    r1 = binsearch_v1(x, v, 10);
    r2 = binsearch_v2(x, v, 10);
    printf("r1 = %d, r2 = %d\n", r1, r2);
    return 0;
}

/* binsearch: binary search for sorted array */
int binsearch_v1(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

int binsearch_v2(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high && x != v[mid = (low + high) / 2]) {
        if (x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    if (x == v[mid])
        return mid;
    else
        return -1;
}

