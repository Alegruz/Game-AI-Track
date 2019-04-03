/* Prints the ex08.c but while statement */

#include <stdio.h>

int main(void)
{
    int i;

    i = 10;
    while (i >= 1) {
        printf("%d ", i++);
        i /= 2;
    } /* <10 5 3 1 1 1 1 1 1 ...> */

    return 0;
}
