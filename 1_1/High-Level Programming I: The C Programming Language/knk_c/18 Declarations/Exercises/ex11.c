// int f(int)[];       /* functions can't return arrays */
// int g(int)(int);    /* functions can't return functions */
// int a[10](int); /* array elements can't be functions */

int *f(int);    /* function that returns a pointer to the first element of an int array */
int (*g(int))(int);    /* function that returns a pointer to a function */
int (*a[10])(int);  /* array elements with pointer to a function */