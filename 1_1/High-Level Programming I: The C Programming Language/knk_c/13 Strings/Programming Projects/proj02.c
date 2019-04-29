/* Improve remind.c */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_REMIND 50   /* maximum number of reminders */
#define MSG_LEN 60      /* max length of reminder message */

int read_line(char str[], int n);

int main(void) {
    char reminders[MAX_REMIND][MSG_LEN+3];
    char month_day_str[6], msg_str[MSG_LEN+1], time_str[7], day_time_str[12];
    int month, day, hour, minute, num_remind = 0, max_days;

    for (;;) {
        if (num_remind == MAX_REMIND) {
            printf("-- No space left --\n");
            break;
        }

        printf("Enter month/day, time (24-hour), and reminder: ");
        scanf("%d/%d", &month, &day);
        if (month == 0)
            break;
        else if (month < 1 || month > 12) {
            printf("Error: month out of range (1 - 12)\n");
            continue;
        }
        switch (month) {
        case 2:
            max_days = 28; break;
        case 4: case 6: case 9: case 11:
            max_days = 30; break;
        default: max_days = 31; break;
        }

        if (day < 0 || day > max_days) {
            printf("Error: day out of range (1 ~ 31)\n");
            continue;
        }
        sprintf(month_day_str, "%.2d/%.2d", month, day);
        scanf("%2d:%2d", &hour, &minute);
        sprintf(time_str, " %.2d:%.2d", hour, minute);
        strcpy(day_time_str, month_day_str);
        strcat(day_time_str, time_str);

        read_line(msg_str, MSG_LEN);

        int i = 0;
        for (; i < num_remind; ++i)
            if (strcmp(day_time_str, reminders[i]) < 0)
                    break;
        for (int j = num_remind; j > i; j--)
            strcpy(reminders[i], reminders[j-1]);

        strcpy(reminders[i], day_time_str);
        strcat(reminders[i], msg_str);

        num_remind++;
    }

    printf("\nDay Reminder\n");
    for (int i = 0; i < num_remind; ++i)
        printf(" %s\n", reminders[i]);

    return 0;
}

int read_line(char str[], int n) {
    int ch, i = 0;
    if ((ch = getchar()) != ' ')
        str[i++] = ' ';
    str[i++] = ch;
    while ((ch = getchar()) != '\n')
        if (i < n)
            str[i++] = ch;

    str[i] = '\0';
    return i;
}
