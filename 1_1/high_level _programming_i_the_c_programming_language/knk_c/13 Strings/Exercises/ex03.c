/* Show the values of variables */

#include <stdio.h>

int main(void) {
    int i, j;
    char s[10];

    scanf("%d%s%d", &i, s, &j);

    printf("i = %d\ns = %s\nj = %d\n", i, s, j);

    return 0;
}
