/* Write parameterized macros */

#include <stdio.h>

#define cube(x) x * x * x
#define remainder_4(n) n % 4
#define product(x, y) x * y < 100 ? 1 : 0

int main(void) {
    printf("cube(4) = %d\n", cube(4));
    printf("remainder_4(5): %d\n", remainder_4(5));
    printf("product(2, 100): %d\n", product(2, 100));

    return 0;
}
