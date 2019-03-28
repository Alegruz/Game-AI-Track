/* Reduces the fraction to lowest terms */

#include <stdio.h>

int main(void)
{
    int numerator, denominator, remainder, temp_numerator, temp_denominator;

    printf("Enter a fraction: ");
    scanf("%d/%d", &numerator, &denominator);

    temp_numerator = numerator;
    temp_denominator = denominator;

    while (temp_denominator) {
        remainder = temp_numerator % temp_denominator;
        temp_numerator = temp_denominator;
        temp_denominator = remainder;
    }

    printf("In lowest terms: %d/%d\n", numerator / temp_numerator, denominator / temp_numerator);

    return 0;
}
