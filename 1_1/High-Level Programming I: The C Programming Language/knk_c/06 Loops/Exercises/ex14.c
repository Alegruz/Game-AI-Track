/* Find and fix the error */

#include <stdio.h>

int main(void)
{
    int n = 4;

    if (n % 2 == 0)/*;*/
        printf("%d is even\n", n); /* "n is even\n" */
    return 0;
}
