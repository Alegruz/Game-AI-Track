/* Gets three-digit number, prints the digits reversed */

#include <stdio.h>

int main(void) {
    int number, first_digit, second_digit, third_digit;

    printf("Enter a three-digit number: ");
    scanf("%3d", &number);

    first_digit = number / 100;
    second_digit = (number / 10) % 10;
    third_digit = number % 10;

    printf("The reversal is: %1d%1d%1d\n", third_digit, second_digit, first_digit);

    return 0;
}
