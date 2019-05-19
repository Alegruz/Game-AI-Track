#define PI 3.14159

char c = 65;
// static int i = 5, j = i * i;
/* initialization of static variables must be constant.
   i is a static int, so j can't be initialized with an expression containing non-constant i */
double d = 2 * PI;
double angles[] = {0, PI / 2, PI, 3 * PI / 2};