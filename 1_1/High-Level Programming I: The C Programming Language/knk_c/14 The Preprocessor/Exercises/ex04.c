/* Gives an example that illustrates a problem with the macro and show how to fix it */

#include <stdio.h>

#define AVG(x,y) (x+y)/2
#define AREA(x,y) (x)*(y)

int main(void) {
    printf("(a) AVG(2,6) = %.2lf\n", AVG(2.0, 6.0));
#undef AVG(x,y)
#define AVG(x,y) ((x)+(y))/2
    printf("(a) AVG(2,6) = %.2lf\n", AVG(2.0, 6.0));
    printf("(b) 3/AREA(2, 6) = %.2lf\n", 3/AREA(2, 6));
#undef AREA(x,y)
#define AREA(x,y) ((x)*(y))
    printf("(b) 3/AREA(2, 6) = %.2lf\n", 3/AREA(2, 6));

    return 0;
}
