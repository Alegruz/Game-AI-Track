/* Displays the corresponding Beaufort scale description */

#include <stdio.h>

int main(void) {
    int wind_speed;

    printf("Enter a speed (knots) of the wind: ");
    scanf("%d", &wind_speed);

    printf("The wind condition is ");
    if (wind_speed > 63) printf("Hurricane");
    else if (wind_speed >= 48) printf("Storm");
    else if (wind_speed >= 28) printf("Gale");
    else if (wind_speed >= 4) printf("Breeze");
    else if (wind_speed >= 1) printf("Light air");
    else printf("Calm");

    printf(".\n");

    return 0;
}
