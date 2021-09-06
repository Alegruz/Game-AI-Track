/* Determine the smallest n that causes failure */

#include <stdio.h>

int main(void)
{
    int i, n;

//    n = 46341;
//    for (i = 1; i <= n; i++) {
//        printf("%10d%15d\n", i, i * i);
//    }

//    n = 182;
//    for (short i = 1; i <= n; i++) {
//        printf("%10hd%15hd\n", i, i * i);
//    }

    long nLONG = 3037000499;
    for (long i = 1; i <= nLONG; i++) {
        printf("%15ld%20ld\n", i, i * i);
    }

    return 0;
}
