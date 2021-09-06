/* Write a function day_of_year(month, day, year) */

#include <stdio.h>

int day_of_year(int month, int day, int year);

int main(void) {
    int month, day, year;
    
    printf("Number of Days Calculator\nEnter a date (mm/dd/yyyy): ");
    scanf("%d/%d/%d", &month, &day, &year);

    printf("%d/%.2d/%.4d has %d days.\n", month, day, year, day_of_year(month, day, year));

    return 0;
}

int day_of_year(int month, int day, int year) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        month = 31; break;
        case 2:
        month = 28; break;
        default:
        month = 30; break;
    }

    year = year * 365 + (year / 4 + 1);

    return day + month + year;
}