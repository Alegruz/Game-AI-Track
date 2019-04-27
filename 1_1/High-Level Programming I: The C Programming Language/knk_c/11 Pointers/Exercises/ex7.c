/* Write the function split_date(day_of_year, &year, *month, *day) */

#include <stdio.h>
#include <stdbool.h>

void split_date(int day_of_year, int *year, int *month, int *day);

int main(void) {
    int day_of_year, year, month, day;
    printf("Enter a day of year: ");
    scanf("%d", &day_of_year);

    split_date(day_of_year, &year, &month, &day);

    printf("Date: %2d/%.2d/%.4d\n", month, day, year);

    return 0;
}

void split_date(int day_of_year, int *year, int *month, int *day) {
    int lunar_repeatance;
    bool lunar_year = false;
    lunar_repeatance = day_of_year / (365 * 4 + 1);
    *year = 4 * lunar_repeatance;
    day_of_year -= lunar_repeatance * (365 * 4 + 1);
    switch ((day_of_year - 2) / 365) {
    case 0: lunar_year = true;              break;
    case 3: *year += 1;    day_of_year -= 365;
    case 2: *year += 1;    day_of_year -= 365;
    case 1: *year += 1;    day_of_year -= 366; break;
    default:                                break;
    }

    if (day_of_year <= 31)
        *month = 1;
    else if (day_of_year <= 28 + 31 + lunar_year)
        *month = 2;
    else if (day_of_year <= 31*2 + 28 + lunar_year)
        *month = 3;
    else if (day_of_year <= 31*2 + 30 + 28 + lunar_year)
        *month = 4;
    else if (day_of_year <= 31*3 + 30 + 28 + lunar_year)
        *month = 5;
    else if (day_of_year <= 31*3 + 30*2 + 28 + lunar_year)
        *month = 6;
    else if (day_of_year <= 31*4 + 30*2 + 28 + lunar_year)
        *month = 7;
    else if (day_of_year <= 31*5 + 30*2 + 28 + lunar_year)
        *month = 8;
    else if (day_of_year <= 31*5 + 30*3 + 28 + lunar_year)
        *month = 9;
    else if (day_of_year <= 31*6 + 30*3 + 28 + lunar_year)
        *month = 10;
    else if (day_of_year <= 31*6 + 30*4 + 28 + lunar_year)
        *month = 11;
    else
        *month = 12;

    int mon = 0;
    switch (*month) {
    case 12: mon += 30;
    case 11: mon += 31;
    case 10: mon += 30;
    case 9:  mon += 31;
    case 8:  mon += 31;
    case 7:  mon += 30;
    case 6:  mon += 31;
    case 5:  mon += 30;
    case 4:  mon += 31;
    case 3:  mon += (28 + lunar_year);
    case 2:  mon += 31; break;
    }

    *day = (day_of_year - mon);
}
