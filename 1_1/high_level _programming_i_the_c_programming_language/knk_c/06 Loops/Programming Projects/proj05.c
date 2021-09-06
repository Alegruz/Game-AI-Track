/* Reverses the digits */

#include <stdio.h>

int main(void) {
    int number, digit;

    printf("Enter number: ");
    scanf("%d", &number);

    printf("The reversal is: ");

    do {
        digit = number % 10;
        printf("%d", digit);
        number /= 10;
    } while (number);

    printf("\n");

    return 0;
}
