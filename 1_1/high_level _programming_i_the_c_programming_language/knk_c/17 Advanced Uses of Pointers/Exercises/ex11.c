#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};

int count_occurrences(struct node *list, int n);

int count_occurrences(struct node *list, int n) {
    struct node *p = list;
    int count = 0;
    for (; p != NULL; p = p->next)
        if (p->value == n)
            count++;
    return count;
}
