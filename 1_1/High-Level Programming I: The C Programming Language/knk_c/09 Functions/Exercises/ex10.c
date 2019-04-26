/* Write a function */

#include <stdio.h>

int A(int n, int a[]);
double B(int n, int a[]);
int C(int n, int a[]);

int main(void) {
    int n = 10;
    int a[n];
    for (int i = 1; i <= 10; ++i)
        a[i - 1] = -6 + i;

    printf("The highest element in range(-5 ~ 4): %d\n", A(n, a));
    printf("The average of the elements in range (-5 ~ 4): %g\n", B(n, a));
    printf("The number of positive integers in range(-5 ~ 4): %d\n", C(n, a));

    return 0;
}

int A(int n, int a[]) {
    int max = a[0];

    for (int i = 0; i < n; ++i)
        max = a[i] > max ? a[i] : max;

    return max;
}

double B(int n, int a[]) {
    double sum = 0;

    for (int i = 0; i < n; ++i)
        sum += a[i];

    return sum / n;
}

int C(int n, int a[]) {
    int num_positive = 0;

    for (int i = 0; i < n; ++i)
        if (a[i] > 0)
            num_positive++;

    return num_positive;
}
