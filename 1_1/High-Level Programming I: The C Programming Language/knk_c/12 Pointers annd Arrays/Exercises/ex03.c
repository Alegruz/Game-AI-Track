/* Print the contents of the a array */

#include <stdio.h>

#define N 10

int main(void) {
    int a[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *p = &a[0], *q = &a[N-1], temp;

    printf("Original Array:");
    for (int *p = &a[0]; p < a + N; ++p)
        printf(" %d", *p);
    printf("\n");

    while (p < q) {
        temp = *p;
        *p++ = *q;
        *q-- = temp;
    }

    printf("Changed Array:");
    for (int *p = &a[0]; p < a + N; ++p)
        printf(" %d", *p);
    printf("\n");
}
