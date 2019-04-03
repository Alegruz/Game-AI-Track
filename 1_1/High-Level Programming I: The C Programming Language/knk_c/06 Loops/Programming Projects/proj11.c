/* Gets value of constant e */

#include <stdio.h>

int main(void)
{
    int i, j, n;
    float factorial, e = 1.0f;

    printf("Enter a number: ");
    scanf("%d", &n);

    for (i = 1; i <= n; ++i) {
        factorial = 1.0f;
        for (j = 1; j <= i; ++j)
            factorial *= j;
        e += (1.0f / factorial);
    }

    printf("Value of e: %.6f\n", e);

    return 0;
}
