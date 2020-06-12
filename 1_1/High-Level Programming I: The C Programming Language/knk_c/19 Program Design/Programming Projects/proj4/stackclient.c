#include <stdio.h>
#include "stackADT3.h"

int main(void) {
    Stack s1, s2;
    int* n;

    s1 = create();
    s2 = create();

	int item0 = 1;
	int item1 = 2;
    push(s1, (Item) &item0);
    push(s2, (Item) &item1);

    n = pop(s1);
    printf("Popped %d from s1\n", *n);
    push(s1, n);
    n = pop(s2);
    printf("Popped %d from s2\n", *n);
    push(s2, n);

    destroy(s1);

    while (!is_empty(s2))
        printf("Popped %d from s2\n", *((int*) pop(s2)));

	int item2 = 3;
    push(s2, (Item) &item2);
    make_empty(s2);
    if (is_empty(s2))
        printf("s2 is empty, \n");
    else
        printf("s2 is not empty.\n");

    destroy(s2);

    return 0;
}