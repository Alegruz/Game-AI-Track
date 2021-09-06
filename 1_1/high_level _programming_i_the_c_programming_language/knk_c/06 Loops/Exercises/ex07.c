/* Prints the following program fragment in single for statement */

#include <stdio.h>

int main(void)
{
    int i;
    
    for (i = 9384; i > 0; i /= 10) {
        printf("%d ", i);
    } /* <9384 938 93 9> */

    return 0;
}
