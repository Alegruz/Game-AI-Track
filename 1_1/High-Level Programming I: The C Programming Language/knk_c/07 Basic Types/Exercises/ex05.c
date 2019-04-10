/* Shows the legal way to write the number 65 */

#include <stdio.h>

int main(void)
{
    char a = 'A';
    int b = 0b1000001;  /* binary integer literals are a C++14 extension */
    int c = 0101;
    int d = 0x41;


    printf("(a) '%c' -> %d\n", a, a);
    printf("(b) 0b1000001 -> %d\n", b);
    printf("(c) %o -> %d\n", c, c);
    printf("(d) %x -> %d\n", d, d);

    return 0;
}
