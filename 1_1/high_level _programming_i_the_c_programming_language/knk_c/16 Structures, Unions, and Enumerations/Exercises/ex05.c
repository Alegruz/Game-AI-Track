#include <stdbool.h>

struct date
{
    int month, day, year;
};

/* a */
int day_of_year(struct date d);
/* b */
int compare_dates(struct date d1, struct date d2);

int main(void) {
    return 0;
}

/* a */
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

/* b */
int compare_dates(struct date d1, struct date d2) {
    if (day_of_year(d1) < day_of_year(d2) || d1.year < d2.year)
        return -1;
    else if (day_of_year(d1) == day_of_year(d2) || d1.year == d2.year)
            return 0;
    else if (day_of_year(d1) > day_of_year(d2) || d1.year > d2.year)
        return 1;
}
