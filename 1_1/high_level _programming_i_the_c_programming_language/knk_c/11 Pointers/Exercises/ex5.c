/* Write the function split_time(total_sec, &hr, &min, &sec) */

#include <stdio.h>
#include <stdbool.h>

void split_time(long total_sec, int *hr, int *min, int *sec);

int main(void) {
    long total_seconds;
    int hour, minute, second;

    do {
        printf("Enter seconds since midnight: ");
        scanf("%ld", &total_seconds);
        if (total_seconds == -1)
            break;
        else if (total_seconds < 0 || total_seconds >= 24 * 60 * 60)
            continue;

        split_time(total_seconds, &hour, &minute, &second);

        printf("%.2d:%.2d:%.2d\n", hour, minute, second);
    } while (true);

    return 0;
}

void split_time(long total_sec, int *hr, int *min, int *sec) {
    int hours;
    hours = total_sec / (60 * 60);
    *hr = hours;
    total_sec -= hours * 60 * 60;
    *min = total_sec / 60;
    *sec = total_sec % 60;
}
