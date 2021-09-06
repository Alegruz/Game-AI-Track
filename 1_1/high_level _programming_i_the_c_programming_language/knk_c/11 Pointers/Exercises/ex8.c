/* Write the function find_largest(a, n) */

#include <stdio.h>

int *find_largest(int a[], int n);

int main(void) {
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    printf("The largest element: %d\n", *find_largest(a, 10));

    return 0;
}

int *find_largest(int a[], int n) {
    int *maxIndex = &a[0];
    for (int i = 0; i < n; ++i)
        if (*maxIndex < a[i])
            maxIndex = &a[i];
    return maxIndex;
}
