/* Design a structure type that occupies 32 bits,
 * with bit-field members corresponding to the sign(1), exponent(8), and fraction(23). */

#include <stdio.h>

struct float_type {
    unsigned int fraction: 23;
    unsigned int exponent: 8;
    unsigned int sign: 1;

};

union {
    unsigned int f;
    struct float_type f_t;
} u;

int main(void) {
    u.f_t.sign = 1;
    u.f_t.exponent = 0;
    u.f_t.fraction = 23;

    printf("%d\n", u.f);

    return 0;
}
