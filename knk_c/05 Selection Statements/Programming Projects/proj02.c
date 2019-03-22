/* Displays 24-hour time into 12-hour form */

#include <stdio.h>

int main(void) {
    int hour_24, minute, hour_12;

    printf("Enter a 24-hour time: ");
    scanf("%2d:%2d", &hour_24, &minute);

    hour_12 = hour_24 - (12 * (hour_24 / 12));

    printf("Equivalent 12-hour time: %.2d:%.2d ", hour_12, minute);

    (hour_24 - 1) / 12? printf("P") : printf("A");
    printf("M\n");

    return 0;
}
