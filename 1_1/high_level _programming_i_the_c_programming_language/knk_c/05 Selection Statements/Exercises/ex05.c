/* Tell whether the following if statement is legal */

#include <stdio.h>

int main(void) {
    int n = 4;

    if (n >= 1 <= 10)
        printf("n is between 1 and 10\n");

    return 0;
} /* Legal. The controlling expression is always true. */
