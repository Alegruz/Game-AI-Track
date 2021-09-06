/* Computes the value of a polynomial */

#include <stdio.h>

double power(double x, int n);
double f(double x);

int main(void) {
    double x;

    printf("Enter a number: ");
    scanf("%lf", &x);

    printf("3x^5 + 2x^4 - 5x^3 - x^2 + 7x - 6 = %.2lf\n", f(x));
    return 0;
}

double power(double x, int n) {
    double result = x;
    for (int i = 1; i < n; ++i)
        result *= x;
    return result;
}

double f(double x) {
    return 3 * power(x, 5) + 2 * power(x, 4) - 5 * power(x, 3) - power(x, 2) + 7 * x - 6;
}
