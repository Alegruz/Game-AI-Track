/* Figure out the type of the converted expression */

#include <stdio.h>

int main(void)
{
    int i = 1;
    long j = 2L;
    unsigned k = 3;

    printf("The size of the expression i + (int) j * k is %d\n", sizeof (i + (int) j * k));
    printf("The type is int. Size is %d\n", sizeof (int));

    return 0;
}
