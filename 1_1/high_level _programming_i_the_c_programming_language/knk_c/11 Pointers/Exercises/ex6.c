/* Write the function find_two_largest(a, n, &largest, &second_largest) */

#include <stdio.h>

void find_two_largest(int a[], int n, int *largest, int *second_largest);

int main(void) {
    int b[10] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int max1, max2;

    find_two_largest(b, 10, &max1, &max2);

    printf("Largest element: %d, Second largest element: %d\n", max1, max2);

    return 0;
}

void find_two_largest(int a[], int n, int *largest, int *second_largest) {
    *largest = a[0];
    *second_largest = a[n - 1];
    for (int i = 0; i < n; ++i) {
        if (*largest < a[i]) {
            *second_largest = *largest;
            *largest = a[i];
        } else if (*second_largest < a[i] && a[i] < *largest)
            *second_largest = a[i];
    }
}
