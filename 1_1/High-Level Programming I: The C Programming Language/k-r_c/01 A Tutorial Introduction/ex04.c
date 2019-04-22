#include <stdio.h>

/* print Celsius-Fahrenheit table
 * for Celsius = -50, -40, ..., 50; floating-point version */
main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = -50;      /* lower limit of temperature table */
    upper = 50;    /* upper limit */
    step = 10;      /* step size */

    printf("Celsius Fahr\n");

    celsius = lower;
    while (celsius <= upper) {
        fahr = celsius * (9.0/5.0) + 32;
        printf("%5.0f %6.1f\n", celsius, fahr);
        celsius = celsius + step;
    }
}
