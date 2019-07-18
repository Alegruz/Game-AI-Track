/* Prints all temperature readings stored in row i */

#include <stdio.h>

int main(void) {
    int temperatures[7][24];
    int i = 0;

    for (int (*p)[24] = &temperatures[0]; p < &temperatures[7]; ++p)
        printf("%d ", (*p)[i]);

    return 0;
}
