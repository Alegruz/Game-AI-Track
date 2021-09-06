#include <stdlib.h>

struct {
    union {
        char a, b;
        int c;
    } d;
    int e[5];
} f, *p = &f;

int main(void) {
    /* a */
//    p->b = ' '; /* no member named 'b' */
    p->d.b = ' ';
    /* b */
    p->e[3] = 10;
    /* c */
    (*p).d.a = '*';
    /* d */
//    p->d->c = 20;   /* member reference type 'union' is not a pointer */
    p->d.c = 20;

    return 0;
}
