/* Write a macro NELEMS(a) that computes the number of elements in a one-dimensional array a */

#include <stdio.h>

#define NELEMS(a) sizeof(a) / sizeof(a[0])

int main(void) {
    int a[] = {1, 2, 3, 4};

    printf("NELEMS(a): %d\n", NELEMS(a));

    return 0;
}
