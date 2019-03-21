/* A single expression whose value is either -1, 0, or +1, depending on relation between i and j */

#include <stdio.h>

int main(void) {
    int i, j, value;

    printf("value of i and j: ");
    scanf("%d %d", &i, &j);

    value = (i > j) - (i < j);

    printf("i is %d, j is %d\n", i, j);
    printf("value is %d\n", value);

    return 0;
}
