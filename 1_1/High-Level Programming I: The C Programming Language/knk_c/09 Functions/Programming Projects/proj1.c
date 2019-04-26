/* Sorts an array through selection sort */

#include <stdio.h>


void selection_sort(int a[], int n);

int main(void) {
    int array_size;

    printf("Enter a size of an array: ");
    scanf("%d", &array_size);
    int array[array_size];

    printf("Enter %d numbers: ", array_size);
    for (int i = 0; i < array_size; ++i)
        scanf("%d", &array[i]);

    printf("The array:\t ");
    for (int i = 0; i < array_size; ++i)
        printf("%2d ", array[i]);
    selection_sort(array, array_size);
    printf("\nSorted array:\t ");
    for (int i = 0; i < array_size; ++i)
        printf("%2d ", array[i]);

    return 0;
}

void selection_sort(int a[], int n) {
    if (n > 0) {
        int max = a[0];
        int maxIndex = 0;

        for (int i = 0; i < n; ++i) {
            if (a[i] > max) {
                max = a[i];
                maxIndex = i;
            }
        }

        for (int i = maxIndex; i < n - 1; ++i) {
            int temp = a[i];
            a[i] = a[i + 1];
            a[i + 1] = temp;
        }

        selection_sort(a, n - 1);
    }
}
