/* Improve power function of Section 9.6 */

#include <stdio.h>

double power(double x, int n);

int main(void) {
    double x;
    int n;

    printf("Enter a number to square: ");
    scanf("%lf", &x);
    printf("Enter a number of times to square: ");
    scanf("%d", &n);

    printf("%.2lf^%d = %.2lf\n", x, n, power(x, n));

    return 0;
}

double power(double x, int n) {
    double result;
    if (n == 0)
        return 1;
    result = (n % 2 == 0) ? power(x, n / 2) * power(x, n / 2) : result = x * power(x, n - 1);
    return result;
}
