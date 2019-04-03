/* Replaces continue by goto */

#include <stdio.h>

int main(void)
{
    int i = 0;

    while (i < 10) {
        printf("%d ", i);
        if (i % 2 == 0) printf("EVEN NUMBER ");
        else {printf("\n"); goto done;}
        printf("ALL HAIL EVENS\n");
        done: i++;
    }

    return 0;
}
