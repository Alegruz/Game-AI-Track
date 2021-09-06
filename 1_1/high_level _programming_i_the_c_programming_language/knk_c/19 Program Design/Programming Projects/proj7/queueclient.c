#include <stdio.h>
#include "queueADT.h"

int main(void) {
    Queue q1, q2;
    int n;

    q1 = create_queue(100);
    q2 = create_queue(100);

    insert_item(q1, 1);
    insert_item(q2, 2);

    n = remove_first_item(q1);
    printf("Popped %d from q1\n", n);
    insert_item(q2, n);
    n = remove_first_item(q1);
    printf("Popped %d from q1\n", n);
    insert_item(q2, n);

    destroy_queue(q1);

    while (!is_empty(q2))
        printf("Popped %d from q2\n", remove_first_item(q2));

    insert_item(q2, 3);
    make_empty(q2);
    if (is_empty(q2))
        printf("q2 is empty, \n");
    else
        printf("q2 is not empty.\n");

    destroy_queue(q2);

    return 0;
}