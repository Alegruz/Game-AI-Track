/* a */
char (*x1[10])(int);
/* an array of ten function pointers with an int argument that returns char */

/* b */
int (*x2(int))[5];
/* a function with an int argument that returns an array of 5 pointers to int */

/* c */
float *(*x3(void))(int);
/* a function with no arguments that returns a pointer to a function that returns a pointer to a float */

/* d */
void (*x4(int, void (*y)(int)))(int);
/* a function with an int, and a pointer to a function with an int argument that returns nothing as arguments,
   that returns a pointer to a function with an int argument that returns nothing. */