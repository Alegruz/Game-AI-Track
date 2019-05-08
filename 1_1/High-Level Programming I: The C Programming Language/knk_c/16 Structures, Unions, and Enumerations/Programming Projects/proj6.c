/* Modify proj09.c from Chapter 5 */
/* Indicates which date comes earlier on the calendar */

#include <stdio.h>
#include <stdbool.h>

struct date
{
    int month, day, year;
};

int day_of_year(struct date d);
int compare_dates(struct date d1, struct date d2);

int main(void)
{
    struct date first_date, second_date;

    printf("Enter first date (mm/dd/yy): ");
    scanf("%d/%d/%d", &first_date.month, &first_date.day, &first_date.year);

    printf("Enter second date (mm/dd/yy): ");
    scanf("%d/%d/%d", &second_date.month, &second_date.day, &second_date.year);

    if (compare_dates(first_date, second_date) < 0) {
        printf("%d/%d/%.2d is earlier than %d/%d/%.2d\n", 
        first_date.month, first_date.day, first_date.year, second_date.month, second_date.day, second_date.year);
    } else if (compare_dates(first_date, second_date) > 0) {
    printf("%d/%d/%.2d is earlier than %d/%d/%.2d\n", 
    second_date.month, second_date.day, second_date.year, first_date.month, first_date.day, first_date.year);
    } else {
        printf("%d/%d/%.2d is the same date as %d/%d/%.2d\n", 
        first_date.month, first_date.day, first_date.year, second_date.month, second_date.day, second_date.year);
    }

    return 0;
}

int day_of_year(struct date d) {
    bool is_lunar_year = (d.year % 4) == 0;

    /* days */
    int day_of_year = d.day;

    /* months */
    int month_count = d.month;
    for (int month = month_count; month >= 1; month--) {
        switch (month) {
        case 2:
            day_of_year += (28 + is_lunar_year);
            break;
        case 4: case 6: case 9: case 11:
            day_of_year += 30;
            break;
        default:
            day_of_year += 31;
            break;
        }
    }

    if (1 > day_of_year || day_of_year > 365 + is_lunar_year)
        return -1;

    return day_of_year;
}

int compare_dates(struct date d1, struct date d2) {
    if (day_of_year(d1) < day_of_year(d2) || d1.year < d2.year)
        return -1;
    else if (day_of_year(d1) == day_of_year(d2) || d1.year == d2.year)
            return 0;
    else if (day_of_year(d1) > day_of_year(d2) || d1.year > d2.year)
        return 1;
}