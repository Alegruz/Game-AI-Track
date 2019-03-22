/* Displays the departure and arrival times for the flight whose departure time is closest to that entered by the user */

#include <stdio.h>

int main(void) {
    int hour, minute, time, depart_time, arrive_time;
    bool depart_am = true, arrive_am = true;

    printf("Enter a 24-hour time: ");
    scanf("%2d:%2d", &hour, &minute);
    time = hour * 60 + minute;

    if (time > 11 * 60 + 19) depart_am = false;
    if (time > 9 * 60 + 43) arrive_am = false;

    if (time < 8 * 60) {
        depart_time = 8 * 60;
        arrive_time = 10 * 60 + 16;
    } else if (time < 9 * 60 + 43) {
        depart_time = 9 * 60 + 43;
        arrive_time = 11 * 60 + 52;
    } else if (time < 11 * 60 + 19) {
        depart_time = 11 * 60 + 19;
        arrive_time = 1 * 60 + 31;
    } else if (time < 12 * 60 + 47) {
        depart_time = 12 * 60 + 47;
        arrive_time = 3 * 60;
    } else if (time < 14 * 60) {
        depart_time = 2 * 60;
        arrive_time = 4 * 60 + 8;
    } else if (time < 15 * 60 + 45) {
        depart_time = 3 * 60 + 45;
        arrive_time = 5 * 60 + 55;
    } else if (time < 19 * 60) {
        depart_time = 7 * 60;
        arrive_time = 9 * 60 + 20;
    } else {
        depart_time = 9 * 60 + 45;
        arrive_time = 11 * 60 + 58;
    }

    printf("Closest departure time is %.2d:%.2d ", depart_time / 60, depart_time % 60);
    depart_am ? printf("a") : printf("p");
    printf(".m., arriving at %.2d:%.2d ", arrive_time / 60, arrive_time % 60);
    arrive_am ? printf("a") : printf("p");
    printf(".m.\n");
    return 0;
}
