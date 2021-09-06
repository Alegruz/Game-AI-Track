/* Prints the decimal value of following integer constants */

#include <stdio.h>

int main(void)
{
    int a, b, c;
    a = 077;
    b = 0x77;
    c = 0XABC;

    printf("Value of a = %o in decimal is %d\n", a, a); /* 7 + 8 * 7 = 63 */
    printf("Value of b = %x in decimal is %d\n", b, b); /* 7 + 16 * 7 = 119 */
    printf("Value of c = %x in decimal is %d\n", c, c); /* 12 + 11 * 7 + 10 * 7 * 7 = 2748 */

    return 0;
}
