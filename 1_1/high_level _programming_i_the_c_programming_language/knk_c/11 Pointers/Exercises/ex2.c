/* Finds the legal assignment */

#include <stdio.h>

int main (void) {
    int i, *p, *q;
    p = &i;
    q = &i;

    /* (a) */
//    p = i;
    /* assigning int to (int *) */

    /* (b) */
//    *p = &i;

    /* assigning (int *) to int */

    /* (c) */
//    &p = q;
    /* assigining (int *) to (int **) */

    /* (d) */
//    p = &q;
    /* assigining (int **) to (int *) */

    /* (e) */
    p = *&q;

    /* (f) */
    p = q;

    /* (g) */
//    p = *q;
    /* assigining (int) to (int *) */

    /* (h) */
//    *p = q;
    /* assigining (int *) to (int) */

    /* (i) */
    *p = *q;

    return 0;
}
