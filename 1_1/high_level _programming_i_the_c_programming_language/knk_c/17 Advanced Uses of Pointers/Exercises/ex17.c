#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int int_compare(const void *a, const void *b);

int main(void) {
    int a[100];

    srand((unsigned) time(NULL));

    for (int i = 0; i < 100; i++) {
        a[i] = rand() % 100;
    }

    for (int i = 0; i < 100; i++) {
        printf("a[%d]: %d\n", i, a[i]);
    }

    qsort(&a[50], 50, sizeof (int), int_compare);

    printf("\nSORTED\n");
    for (int i = 0; i < 100; i++) {
        printf("a[%d]: %d\n", i, a[i]);
    }

    return 0;
}

int int_compare(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}
