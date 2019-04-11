/* Prints values of various sizeof(type) */

#include <stdio.h>

int main(void)
{
    printf("Size of int: \t\t%d\n", sizeof (int));
    printf("Size of short: \t\t%d\n", sizeof (short));
    printf("Size of long: \t\t%d\n", sizeof (long));
    printf("Size of float: \t\t%d\n", sizeof (float));
    printf("Size of double: \t%d\n", sizeof (double));
    printf("Size of long double: \t%d\n", sizeof (long double));

    return 0;
}
