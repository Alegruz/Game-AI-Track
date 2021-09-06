/* Prints the highest temperature */

#include <stdio.h>


int find_largest(int *a, int n);

int main(void) {
    int temperatures[7][24];
    int i = 0;

    printf("Hottest temperature: %d\n", find_largest(*temperatures, 7 * 24));

    return 0;
}


int find_largest(int *a, int n) {
    int max = *a;
    for (int *p = a; p < a + n; p++)
        if (*p > max)
            max = *p;
    return max;
}
