#include <stdio.h>

unsigned int f(unsigned int i, int m, int n);

int main(void) {
    return 0;
}

unsigned int f(unsigned int i, int m, int n) {
    return (i >> (m + 1 - n)) & ~(~0 << n);
}

/* a. value of ~(~0 << n) */
/* ...000..0011..111, with n 1's */

/* b. what does this function do? */
/* this function gets the bit-field of (m + 1 -n) + n to (m + 1 - n) */
/* first, get rid of all the bits which has lower position than (m + 1 - n) */
/* then get 00...00011..11 with n bits of 1's, and use & operator */
/* this returns the bit-field from (m + 1 - n), to (m + 1 - n) + n */
