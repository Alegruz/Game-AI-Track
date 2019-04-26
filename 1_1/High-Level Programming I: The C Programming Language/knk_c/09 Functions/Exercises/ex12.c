/* Write the function inner_product(a[], b[], n) */

#include <stdio.h>

double inner_product(double a[], double b[], int n);

int main(void) {
    double a[3], b[3];

    printf("Inner Product Calculator\nEnter three numbers of array a: ");
    for (int i = 0; i < 3; ++i)
        scanf("%lf", &a[i]);
    printf("Enter three numbers of array b: ");
    for (int i = 0; i < 3; ++i)
        scanf("%lf", &b[i]);

    printf("The inner product of a and b is %.2lf.\n", inner_product(a, b, 3));

    return 0;
}

double inner_product(double a[], double b[], int n) {
    double inner_product = 0;

    for (int i = 0; i < n; ++i)
        inner_product += a[i] * b[i];

    return inner_product;
}
