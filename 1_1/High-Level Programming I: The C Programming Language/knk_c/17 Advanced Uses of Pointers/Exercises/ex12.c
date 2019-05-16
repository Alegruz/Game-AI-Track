#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};

struct node *find_last(struct node *list, int n);

struct node *find_last(struct node *list, int n) {
    struct node *container, *p;
    container = NULL;

    for (p = list; p != NULL; p = p->next) {
        if (p->value == n)
            container = p;
    }

    return container;
}
