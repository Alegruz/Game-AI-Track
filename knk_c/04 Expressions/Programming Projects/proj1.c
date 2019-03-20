/* Gets two-digit number, prints the digits reversed */

#include <stdio.h>

int main(void) {
    int number, first_digit, second_digit;

    printf("Enter a two-digit number: ");
    scanf("%2d", &number);

    first_digit = number / 10;
    second_digit = number % 10;

    printf("The reversal is: %1d%1d\n", second_digit, first_digit);

    return 0;
}
