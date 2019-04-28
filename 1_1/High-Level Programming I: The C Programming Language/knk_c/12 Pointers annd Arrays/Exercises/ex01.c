/* Prints the value of following expressions */

#include <stdio.h>

int main(void) {
    int a[] = {5, 15, 34, 54, 14, 2, 52, 72};
    int *p = &a[1], *q = &a[5];

    printf("(a) Value of *(p+3):  %d\n"
           "(b) Value of *(q-3):  %d\n"
           "(c) Value of q - p:   %d\n"
           "(d) Value of p < q:   %d\n"
           "(e) Value of *p < *q: %d\n", *(p+3), *(q-3),q-p, p < q, *p < *q);

    return 0;
}
