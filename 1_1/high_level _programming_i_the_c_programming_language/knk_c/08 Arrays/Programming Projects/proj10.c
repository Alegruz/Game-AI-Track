/* Modify proj08.c of Section 5 */

#include <stdio.h>
#include <stdbool.h>
#define FLIGHTS 8

int main(void) {
    int hour, minute, time, min_flight, min_flight_index;
    bool depart_am = true, arrive_am= true;
    const int departure[FLIGHTS] = {480, 583, 679, 767, 840, 945, 1140, 1305},
            arrival[FLIGHTS] = {616, 712, 811, 900, 968, 1075, 1280, 1438};

    printf("Enter a 24-hour time: ");
    scanf("%2d:%2d", &hour, &minute);
    time = hour * 60 + minute;
    min_flight = time;

    for (int flight = 0; flight < FLIGHTS; ++flight)
        if (departure[flight] - time > 0 && min_flight > departure[flight] - time) {
                min_flight = departure[flight] - time;
                min_flight_index = flight;
        }

    if (departure[min_flight_index] >= 13 * 60) {
        departure[min_flight_index] -= 12 * 60;
        depart_am = false;
    }
    if (arrival[min_flight_index] >= 13 * 60) {
        arrival[min_flight_index] -= 12 * 60;
        arrive_am = false;
    }

    printf("Closest departure time is %.2d:%.2d ", departure[min_flight_index] / 60, departure[min_flight_index] % 60);
    depart_am ? printf("a") : printf("p");
    printf(".m., arriving at %.2d:%.2d ", arrival[min_flight_index] / 60, arrival[min_flight_index] % 60);
    arrive_am ? printf("a") : printf("p");
    printf(".m.\n");
    return 0;
}
