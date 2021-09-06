/* Translates an alphabetic phone number into numberic form */

#include <stdio.h>

int main(void)
{
    char numberCh;
    printf("Enter phone number: ");

    for(;;) {
        numberCh = getchar();
        if ((numberCh >= 'A' && numberCh <= 'Z'))
            printf("%d", (numberCh - 59) / 3);
        else if (numberCh == '\n')
            break;
        else
            printf("%c", numberCh);
    }
    printf("\n");

    return 0;
}

