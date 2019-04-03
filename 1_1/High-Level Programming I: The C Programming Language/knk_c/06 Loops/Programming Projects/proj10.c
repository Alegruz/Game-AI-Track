/* Indicates which date comes earlier on the calendar */

#include <stdio.h>

int main(void)
{
    int month, day, year, time,
            earlier_month, earlier_day, earlier_year, earlier_time;

    earlier_time = 200 * 365;
    while (1) {
        time = 0;
        printf("Enter a date (mm/dd/yy): ");
        scanf("%d/%d/%d", &month, &day, &year);
        if (!year) break;

        switch (month) {
        case 12: time += 31;
        case 11: time += 30;
        case 10: time += 31;
        case 9: time += 30;
        case 8: time += 31;
        case 7: time += 31;
        case 6: time += 30;
        case 5: time += 31;
        case 4: time += 30;
        case 3: time += 31;
        case 2: time += 28;
        case 1: time += 31;
        }

        time += (year > 19) ? year * 365 : (100 + year) * 365;
        time += day;
        printf("earlier_time: %d\n", earlier_time);
        printf("time: %d\n", time);
        if (earlier_time > time) {
            earlier_time = time;
            earlier_day = day;
            earlier_year = year;
            earlier_month = month;
        }
    }

    printf("%d/%d/%.2d is the earliest date\n", earlier_month, earlier_day, earlier_year);

    return 0;
}
