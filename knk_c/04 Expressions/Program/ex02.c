/* Justify whether given positive integers i and j, (-i)/j and -(i/j) always have the same value */

#include <stdio.h>

int main(void) {
    int i, j;

    i = 9; j = 2;
    printf("i is %d, and j is %d. (-i)/j: %d, -(i/j): %d\n", i, j, (-i)/j, -(i/j));

    i = 4; j = 4;
    printf("i is %d, and j is %d. (-i)/j: %d, -(i/j): %d\n", i, j, (-i)/j, -(i/j));

    i = 3; j = 5;
    printf("i is %d, and j is %d. (-i)/j: %d, -(i/j): %d\n", i, j, (-i)/j, -(i/j));

    printf("In C99, (-i)/j is equal to -(i/j)\n");

    return 0;
}
