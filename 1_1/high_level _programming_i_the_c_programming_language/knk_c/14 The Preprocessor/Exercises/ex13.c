#include <stdio.h>  /* Lines brought in from stdio.h */

#define N 100   /* Blank Line */

void f(void);

int main(void) {
    f();    /* (b) "N is undefined\n" */
#ifdef N    /* Blank Line */
#undef N    /* Blank Line */
#endif      /* Blank Line */
    return 0;
}

void f(void) {
#if defined (N)             /* Blank Line */
    printf("N is %d\n", N); /* Blank Line */
#else                       /* Blank Line */
    printf("N is undefined\n"); /* Blank Line */
#endif                          /* Blank Line */
}
