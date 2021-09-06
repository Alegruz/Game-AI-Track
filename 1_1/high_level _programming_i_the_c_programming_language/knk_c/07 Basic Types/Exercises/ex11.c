/* Figure out the type of the converted expression */

#include <stdio.h>

int main(void)
{
    int i = 1;
    float f = 2.5f;
    double d = 3.5;

    printf("The size of the expression i * f / d is %d\n", sizeof (i * f / d));
    printf("The type is double. Size is %d\n", sizeof (double));

    return 0;
}
