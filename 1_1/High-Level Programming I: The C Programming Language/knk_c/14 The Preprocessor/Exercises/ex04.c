/* Gives an example that illustrates a problem with the macro and show how to fix it */

#include <stdio.h>

#define AVG(x,y) (x+y)/2
#define AREA(x,y) (x)*(y)

int main(void) {
    printf("(a) AVG(2 > 1, 4) = %d\n", AVG(2 > 1, 4));
#undef AVG
#define AVG(x,y) ((x)+(y))/2
    printf("(a) AVG(2 > 1, 4) = %d\n", AVG(2 > 1, 4));
    printf("(b) 360/AREA(2, 6) = %d\n", 360/AREA(2, 6));
#undef AREA
#define AREA(x,y) ((x)*(y))
    printf("(b) 360/AREA(2, 6) = %d\n", 360/AREA(2, 6));

    return 0;
}
