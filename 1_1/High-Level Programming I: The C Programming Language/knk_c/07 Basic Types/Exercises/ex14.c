/* Computes the fractional part of f */

#include <stdio.h>

int main(void)
{
    float f = 3.5f, frac_part = f - (int) f;

    printf("The fractional part of %.2f is %.2f\n", f, frac_part);
    /* The program will not work if the value of f exceeds the largest value of int */

    return 0;
}
