/* Finds the aliases for i */

#include <stdio.h>

int main(void) {
    int i, *p = &i;
    *p = 3;

    printf("(a): %d\t\t(c): %d\t(e): *i\t\t(g): %d\n", *p, *&p, *&i);
    printf("(b): %d\t(d): %d\t(f): %d\t(h): &*i\n", &p, &*p, &i);

    return 0;
}
