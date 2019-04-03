/* Calculates number of digits a number contains */

#include <stdio.h>

int main(void) {
    int number;

    printf("Enter a number: ");
    scanf("%d", &number);

    printf("The number %d has ", number);
    if (number >= 0)
        if (number < 10)
            printf("1");
        else if (number < 100)
            printf("2");
        else if (number < 1000)
            printf("3");
        else
            printf("4");

    printf(" digits\n");

    return 0;
}
