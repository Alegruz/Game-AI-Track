/* Displays 12-hour form into 24-hour form */

#include <stdio.h>
#include <ctype.h>

int main(void)
{
    int hour, minute;
    char isAm;

    printf("Enter a 12-hour time: ");
    scanf("%d:%d", &hour, &minute);

    for (;;) {
        isAm = getchar();
        if (isAm == '\n')
            break;
        else if (toupper(isAm) == 'P')
            hour += (hour < 12) ? 12 : 0;
        else if (toupper(isAm) == 'A')
            hour -= (hour == 12) ? 12 : 0;
    }

    printf("Equivalent 24-hour time: %.2d:%.2d\n", hour, minute);

    return 0;
}
