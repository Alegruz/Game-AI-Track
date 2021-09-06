/* Displays a calendar */

#include <stdio.h>

int main(void) {
    int month_length, start_day, i;

    printf("Enter number of days in month: ");
    scanf("%d", &month_length);

    printf("Enter starting day of the week (1=Sun, 7=Sat): ");
    scanf("%d", &start_day);

    for (i = 1; i < start_day; ++i) {
        printf("   ");
    }

    for (i = 1; i <= month_length; ++i) {
        printf("%2d ", i);
        (i + start_day - 1) % 7 == 0 ? printf("\n"):printf("");
    }

    printf("\n");

    return 0;
}
