/* Returns a pointer to a dynamically allocated int array with n members */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct point { int x, y; };
struct rectangle { struct point upper_left, lower_right; };
struct rectangle *p;

int main(void) {
    struct rectangle *p = (struct rectangle *) malloc(sizeof (*p));

    if (p == NULL) {
        printf("Error: memory full, allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    p->upper_left = (struct point) {10, 25};
    p->lower_right = (struct point) {20, 15};

    return 0;
}
