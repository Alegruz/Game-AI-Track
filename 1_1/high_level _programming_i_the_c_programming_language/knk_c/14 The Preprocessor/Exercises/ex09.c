#include <stdio.h>

#define CHECK(x, y, n) (0<=x&&x<=n-1&&0<=y&&y<=n-1)?1:0
#define MEDIAN(x, y, z) ((y<=x&&x<=z)||(z<=x&&x<=y))?x:((x<=y&&y<=z)||(z<=y&&y<=x))?y:z
#define POLYNOMIAL(x) (3*(x)*(x)*(x)*(x)*(x)+2*(x)*(x)*(x)*(x)-5*(x)*(x)*(x)-(x)*(x)+7*(x)-6)

int main(void) {
    printf("CHECK(%d, %d, %d) = %d\n", 1, 3, 4, CHECK(1, 3, 4));
    printf("CHECK(%d, %d, %d) = %d\n", 1, 5, 4, CHECK(1, 5, 4));
    printf("MEDIAN(%d, %d, %d) = %d\n", 3, 5, 7, MEDIAN(3, 5, 7));
    printf("MEDIAN(%d, %d, %d) = %d\n", 9, 5, 7, MEDIAN(9, 5, 7));
    printf("MEDIAN(%d, %d, %d) = %d\n", 3, 5, 1, MEDIAN(3, 5, 1));
    printf("POLYNOMIAL(%d) = %d\n", 1, POLYNOMIAL(1));
    printf("POLYNOMIAL(%d) = %d\n", 1 + 1, POLYNOMIAL(1 + 1));

    return 0;
}
