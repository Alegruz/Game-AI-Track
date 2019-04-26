/* Write a function check(x, y, n) */

#include <stdio.h>

int check(int x, int y, int n);

int main(void) {
    int x, y, n;
    printf("Range Checker\nEnter two integers and a maximum integer n for range (0 ~ n) to check: ");
    scanf("%d%d%d", &x, &y, &n);

    printf("Both %d and %d is ", x, y);
    check(x, y, n) ? printf("") : printf("not");
    printf(" in the range(0 ~ %d).\n", n);

    return 0;
}

int check(int x, int y, int n) {
    return ((0 <= x && x <= n - 1) && (0 <= y && y <= n - 1)) ? 1 : 0 ;
}