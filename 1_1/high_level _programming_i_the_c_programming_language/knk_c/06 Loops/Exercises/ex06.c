/* Prints the following program fragment in for statement */

#include <stdio.h>

int main(void)
{
    int i;
    
    for (i = 1; i <= 128; i *= 2) {
        printf("%d ", i);
    } /* <1 2 4 8 16 32 64 128> */

    return 0;
}
