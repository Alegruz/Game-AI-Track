/* Tell whether the expressions are true */

#include <stdio.h>

int main(void) {
    int a[10] = {}, *p;
    p = a;

    printf("(a) Value of p    ==  a[0]: %ld\n"
           "(b) Value pf p    == &a[0]: %ld\n"
           "(c) Value of *p   ==  a[0]: %ld\n"
           "(d) Value of p[0] ==  a[0]: %ld\n", (long) p==a[0], p==&a[0], *p==a[0], p[0]==a[0]);

    return 0;
}
