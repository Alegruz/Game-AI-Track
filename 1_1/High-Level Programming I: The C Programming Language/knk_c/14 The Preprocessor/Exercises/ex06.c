#include <stdio.h>
#include <math.h>

/* (a) Expands into a call of printf that displays the value
 * of the function f when called with argument x */
#define DISP(f, x) printf(#f "(%g) = %g\n", (x), f(x));

/* (b) Similar to DISP but works for functions with two arguments x */
#define DISP2(f, x, y) printf(#f "(%g, %g) = %g\n", (x), (y), f(x, y));

int main(void) {
    DISP(sqrt, 3.0);
    DISP2(pow, 2.0, 4.0);
    return 0;
}
