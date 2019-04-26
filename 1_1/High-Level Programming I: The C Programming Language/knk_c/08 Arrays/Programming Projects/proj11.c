/* Modify proj04.c of Section 7 */

#include <stdio.h>
#define characters 255

int main(void)
{
    char numberCh[characters] = {};
    int index = 0;
    printf("Enter phone number: ");

    for(;;) {
        numberCh[index] = getchar();
        if (numberCh[index] == '\n')
            break;
        index++;
    }

    for (int x = 0; x < index; ++x) {
        if ((numberCh[x] >= 'A' && numberCh[x] <= 'Z'))
            printf("%d", (numberCh[x] - 59) / 3);
        else
            printf("%c", numberCh[x]);
    }
    printf("\n");

    return 0;
}
