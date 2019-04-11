/* Translates an alphabetic phone number into numberic form */

#include <stdio.h>

int main(void)
{
    char numberCh;
    int number, numberOfType;
    printf("%d %d\n", '0', '9');
    printf("Enter phone number: ");

    for(;;) {
        number = 0;
        numberCh = getchar();
        if ((numberCh >= 'A' && numberCh <= 'Z')) {
            numberOfType = (numberCh - 1) % 3;
            printf("%d", (numberCh - 59) / 3);
        } else if (numberCh == '\n')
            break;
        else
            printf("%c", numberCh);
    }
    printf("\n");

    return 0;
}
