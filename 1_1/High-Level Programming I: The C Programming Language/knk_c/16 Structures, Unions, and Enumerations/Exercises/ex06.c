#include <stdio.h>

struct time
{
    int hours, minutes, seconds;
};

struct time split_time(long total_seconds);

int main(void) {
    long t1 = 1, t2 = 86399, t3 = 9030;

    struct time T1, T2, T3;
    T1 = split_time(t1);
    T2 = split_time(t2);
    T3 = split_time(t3);

    printf("t1: %ld, T1: %.2d:%.2d:%.2d\n", t1, T1.hours, T1.minutes, T1.seconds);
    printf("t2: %ld, T2: %.2d:%.2d:%.2d\n", t2, T2.hours, T2.minutes, T2.seconds);
    printf("t3: %ld, T3: %.2d:%.2d:%.2d\n", t3, T3.hours, T3.minutes, T3.seconds);

    return 0;
}

struct time split_time(long total_seconds) {
    int hours = 0, minutes = 0, seconds = 0;

    /* seconds */
    seconds = total_seconds % 60;
    total_seconds -= (long) seconds;

    /* minutes */
    minutes = (int) total_seconds / 60;
    /* hours */
    if (minutes >= 60)
        hours = minutes / 60;
    minutes -= hours * 60;

    return (struct time) {.hours = hours, .minutes = minutes, .seconds = seconds};
}
