#include <stdio.h>

#define M 10

int main(void) {
    /* a */
#if M
#define A 1
#else
#define A 0
#endif
    printf("%d\n", A);

    /* b */
#ifdef M
#define B 1
#else
#define B 0
#endif
    printf("%d\n", B);

    /* c */
#ifndef M
#define C 1
#else
#define C 0
#endif
    printf("%d\n", C);

    /* D */
#if defined (M)
#define D 1
#else
#define D 0
#endif
    printf("%d\n", D);

    /* e */
#if !defined (M)
#define E 1
#else
#define E 0
#endif
    printf("%d\n", E);

    return 0;
}
