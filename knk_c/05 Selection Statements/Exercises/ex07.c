/* Tell whether the following if statement is legal */

#include <stdio.h>

int main(void) {
    int i = 17;

    printf("i is 17, %d\n", i >= 0 ? i : -i); /* <i is 17, 17> */

    i *= -1;
    printf("i is -17, %d\n", i >= 0 ? i : -i); /* <i is -17, 17> */

    return 0;
}
