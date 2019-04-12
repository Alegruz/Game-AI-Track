#include <stdio.h>

/* convert fahrenheit to celsius */
float fahrToCel(float fahr);

/* receives the input for lower and upper limit */
void lowerAndUpper(int* a);

/* print Fahrenheit-Celsius table
 * for fahr = 0, 20, ..., 300; floating-point version */
main()
{
    float fahr, celsius;
    int lower, upper, step;
    int lowerUpperStep[3];
    lowerAndUpper(lowerUpperStep);

    lower = lowerUpperStep[0];  /* lower limit of temperature table */
    upper = lowerUpperStep[1];  /* upper limit */
    step = lowerUpperStep[2];   /* step size */

    printf("Fahr Celsius\n");

    for (fahr = lower; fahr <= upper; fahr += step) {
        celsius = fahrToCel(fahr);
        printf("%3.0f %6.1f\n", fahr, celsius);
    }
}

float fahrToCel(float fahr) {
    return (5.0/9.0) * (fahr-32.0);
}

void lowerAndUpper(int* a) {
    printf("Enter the lower limit: ");
    scanf("%d", &a[0]);
    printf("Enter the upper limit: ");
    scanf("%d", &a[1]);
    printf("Enter the step size: ");
    scanf("%d", &a[2]);
}
