/* Finds the largest in a series of numbers */

#include <stdio.h>

int main(void)
{
    float number, max = 0.0f;

    do {
        printf("Enter a number: ");
        scanf("%f", &number);
        max = max > number ? max : number;
    } while (number);

    printf("The largest number entered was %.2f\n", max);

    return 0;
}
