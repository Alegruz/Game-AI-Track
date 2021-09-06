/* Reduces the fraction to lowest terms */

#include <stdio.h>

void reduce(int numerator, int denominator, int *reduced_numerator, int *reduced_denominator);

int main(void)
{
    int numerator, denominator, reduced_numerator, reduce_denominator;

    printf("Enter a fraction: ");
    scanf("%d/%d", &numerator, &denominator);

    reduce(numerator, denominator, &reduced_numerator, &reduce_denominator);

    printf("In lowest terms: %d/%d\n", reduced_numerator, reduce_denominator);

    return 0;
}

void reduce(int numerator, int denominator, int *reduced_numerator, int *reduced_denominator) {
    int remainder, temp_numerator, temp_denominator;
    temp_numerator = numerator;
    temp_denominator = denominator;

    while (temp_denominator) {
        remainder = temp_numerator % temp_denominator;
        temp_numerator = temp_denominator;
        temp_denominator = remainder;
    }

    *reduced_numerator = (numerator / temp_numerator);
    *reduced_denominator = (denominator / temp_numerator);
}
