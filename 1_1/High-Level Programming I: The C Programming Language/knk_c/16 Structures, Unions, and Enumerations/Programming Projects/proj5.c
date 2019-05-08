/* Modify proj08.c from Chapter 5 */
/* Displays the departure and arrival times for the flight whose departure time is closest to that entered by the user */

#include <stdio.h>
#include <stdbool.h>

#define FLIGHTS 8

struct time
{
    /* data */
    int departure_time;
    int arrival_time;
};


int main(void) {
    int hour, minute, time, min_flight, min_flight_index;
    bool depart_am = true, arrive_am= true;
    struct time schedule[] = {{480, 616}, {583, 712}, {679, 811}, {767, 900}, 
    {840, 968}, {945, 1075}, {1140, 1280}, {1305, 1438}};

    printf("Enter a 24-hour time: ");
    scanf("%2d:%2d", &hour, &minute);
    time = hour * 60 + minute;
    min_flight = time;

    for (int flight = 0; flight < FLIGHTS; ++flight)
        if (schedule[flight].departure_time - time > 0 && min_flight > schedule[flight].departure_time - time) {
                min_flight = schedule[flight].departure_time - time;
                min_flight_index = flight;
        }

    if (schedule[min_flight_index].departure_time >= 13 * 60) {
        schedule[min_flight_index].departure_time -= 12 * 60;
        depart_am = false;
    }
    if (schedule[min_flight_index].arrival_time >= 13 * 60) {
        schedule[min_flight_index].arrival_time -= 12 * 60;
        arrive_am = false;
    }

    printf("Closest departure time is %.2d:%.2d ", schedule[min_flight_index].departure_time / 60, schedule[min_flight_index].departure_time % 60);
    depart_am ? printf("a") : printf("p");
    printf(".m., arriving at %.2d:%.2d ", schedule[min_flight_index].arrival_time / 60, schedule[min_flight_index].arrival_time % 60);
    arrive_am ? printf("a") : printf("p");
    printf(".m.\n");
}
