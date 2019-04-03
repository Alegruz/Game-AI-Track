/* Prints the following for statement */

#include <stdio.h>

int main(void)
{
    int i;

    for (i = 10; i >= 1; i /= 2) {
        printf("%d ", i++);
    } /* <10 5 3 1 1 1 1 1 1 ...> */

    return 0;
}
