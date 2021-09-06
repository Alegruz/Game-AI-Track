#include <stdio.h>

#define DEBUG
#include "debug.h"

int main(void) {
    int i = 1, j = 2, k = 3;


#ifdef DEBUG
    printf("Output if DEBUG is defined:\n");
#else
    printf("Output if DEBUG is not defined:\n");
#endif

    PRINT_DEBUG(i);
    PRINT_DEBUG(j);
    PRINT_DEBUG(k);
    PRINT_DEBUG(i + j);
    PRINT_DEBUG(2 * i + j - k);

    return 0;
}

/* (a)
 * Output
 * Output if DEBUG is defined:
 * Value of i: 1
 * Value of j: 2
 * Value of k: 3
 * Value of i + j: 3
 * Value of 2 * i + j - k: 1
 */

/* (b)
 * Output if DEBUG is not defined:
 */

/* (c)
 * in (a), DEBUG is defined, thus the function PRINT_DEBUG(n) is defined with printf function.
 * in (b), DEBUG is not defined, thus the function PRINT_DEBUG(n) is defined but does nothing.
 */

/* (d)
 * If DEBUG is defined after including debug.h, the output would be following:
 * Output if DEBUG is defined:
 * Thus, in order to make the program work as how we want it to work,
 * yes, we have to define DEBUG before we call debug.h
 */
