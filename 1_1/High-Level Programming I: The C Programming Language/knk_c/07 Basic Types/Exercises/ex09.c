/* Figure out the type of the converted expression */

#include <stdio.h>

int main(void)
{
    int i = 3, j = 2;

    printf("The size of the expression i / j + 'a' is %d\n", sizeof (i / j + 'a'));
    printf("The type of the expression is int. Size of int is %d\n", sizeof (int));

    return 0;
}
