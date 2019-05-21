#include <stdio.h>
#include "stackADT3.h"

int main(void) {
    Stack s1, s2;
    int n;

    s1 = create();
    s2 = create();

    push(s1, 1);
    push(s2, 2);

    n = pop(s1);
    printf("Popped %d from s1. Length of s1: %d\n", n, length(s1));
    push(s2, n);
    printf("Pushed %d, length of s2: %d", n, length(s2));
    n = pop(s1);
    printf("Popped %d from s1. Length of s1: %d\n", n, length(s1));
    push(s2, n);
    printf("Pushed %d, length of s2: %d", n, length(s2));

    destroy(s1);

    while (!is_empty(s2))
        printf("Popped %d from s2. Length of s2: %d\n", pop(s2), length(s2));

    push(s2, 3);
    printf("Pushed %d, length of s2: %d", 3, length(s2));
    make_empty(s2);
    printf("s2 emptied, length of s2: %d", length(s2));
    if (is_empty(s2))
        printf("s2 is empty, \n");
    else
        printf("s2 is not empty.\n");

    destroy(s2);

    return 0;
}