/* Indicates which date comes earlier on the calendar */

#include <stdio.h>

int main(void)
{
    int first_month, first_day, first_year, first_time,
            second_month, second_day, second_year, second_time;

    printf("Enter first date (mm/dd/yy): ");
    scanf("%d/%d/%d", &first_month, &first_day, &first_year);

    printf("Enter second date (mm/dd/yy): ");
    scanf("%d/%d/%d", &second_month, &second_day, &second_year);

    switch (first_month) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12: first_time = 31; break;
    case 2: first_time = 28; break;
    default: first_time = 30; break;
    }

    switch (second_month) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12: second_time = 31; break;
    case 2: second_time = 28; break;
    default: second_time = 30; break;
    }

    first_time += (first_year > 19) ? first_year * 60 : (100 + first_year) * 60;
    second_time += (second_year > 19) ? second_year * 60 : (100 + second_year) * 60;

    first_time += first_day;
    second_time += second_day;

    if (first_time < second_day) {
        printf("%d/%d/%.2d is earlier than %d/%d/%.2d\n", first_month, first_day, first_year, second_month, second_day, second_year);
    } else {
    printf("%d/%d/%.2d is earlier than %d/%d/%.2d\n", second_month, second_day, second_year, first_month, first_day, first_year);
    }

    return 0;
}
