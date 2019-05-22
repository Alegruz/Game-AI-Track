/* Design a union that makes it possible to view a 32-bit
value as either a float or the structure described in ex14.c */

#include <stdio.h>

union IEEE_float {
    float f;
    struct {
        unsigned int fraction: 23;
        unsigned int exponent: 8;
        unsigned int sign: 1;
    } s_f;
};

int main(void) {
    union IEEE_float u;
    u.s_f.sign = 0;
    u.s_f.exponent = 127;
    u.s_f.fraction = 800000000;

    printf("%.2g\n", u.f);

    return 0;
}
