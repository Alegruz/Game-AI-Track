/* Compute the square root of a positive floating-point number by Newton's Method */

//#include <stdio.h>
#include <math.h>

int main(void)
{
    int x;
    double y = 1, average;

    printf("Enter a positive number: ");
    scanf("%d", &x);

    for (;;) {
        average = ((x / y) + y) * 0.5;
        if (fabs(y - average) < y * 0.00001)
            break;
        y = average;
    }

    printf("Square root: %.5lf\n", average);

    return 0;
}
