/* Reads an integer and displays it in octal */

#include <stdio.h>

int main(void) {
    unsigned int decimal_number, octal_1, octal_2, octal_3, octal_4, octal_5;
    octal_1 = octal_2 = octal_3 = octal_4 = octal_5 = 0;

    printf("Enter a number between 0 and 32767: ");
    scanf("%d", &decimal_number);

    octal_5 = decimal_number % 8;
    decimal_number = (decimal_number - octal_5) / 8;
    octal_4 = decimal_number % 8;
    decimal_number = (decimal_number - octal_4) / 8;
    octal_3 = decimal_number % 8;
    decimal_number = (decimal_number - octal_3) / 8;
    octal_2 = decimal_number % 8;
    decimal_number = (decimal_number - octal_2) / 8;
    octal_1 = decimal_number % 8;

    printf("In octal, your number is: %1d%1d%1d%1d%1d\n", octal_1, octal_2, octal_3, octal_4, octal_5);

    return 0;
}
