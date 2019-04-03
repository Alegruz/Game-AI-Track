/* Gets value of constant e */

#include <stdio.h>

int main(void)
{
    int i = 1, j;
    float factorial = 1.0f, epsilon, e = 1.0f;

    printf("Enter an epsilon: ");
    scanf("%f", &epsilon);

    for (i = 1; (1.0f / factorial) > epsilon; ++i) {
        factorial = 1.0f;
        for (j = 1; j <= i; ++j)
            factorial *= j;
        e += (1.0f / factorial);
    }

    printf("Value of e: %.6f\n", e);

    return 0;
}
