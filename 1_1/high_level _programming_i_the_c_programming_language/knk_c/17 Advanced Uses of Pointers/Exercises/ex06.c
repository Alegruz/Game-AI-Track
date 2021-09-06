/* Modify delete_from_list function */

#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};

struct node *delete_from_list(struct node *list, int n);
int len(struct node *list);

int main(void) {
    struct node *list;
    struct node *first = NULL;

    for (int i = 9; i >= 0; --i) {
        list = (struct node *) malloc(sizeof(struct node));
        list->value = i;
        list->next = first;
        first = list;
    }

    struct node *count = list;
    for (int i = 0; i < len(list); ++i) {
        printf("Node %2d: %d\n", i + 1, count->value);
        count = count->next;
    }

    list = delete_from_list(list, 10);
    printf("\nAFTER DELETING %d\n", 10);
    count = list;
    for (int i = 0; i < len(list); ++i) {
        printf("Node %2d: %d\n", i + 1, count->value);
        count = count->next;
    }

    return 0;
}

int len(struct node *list) {
    struct node *p = list;
    int count = 0;
    for (; p != NULL; p = p->next)
        count++;
    return count;
}

struct node *delete_from_list(struct node *list, int n) {
    struct node *p = list;

    while (p != NULL) {
        if (p->next != NULL && p->next->value == n) {
            p->next = p->next->next;
            break;
        }
        p = p->next;
    }

    if (list->value == n)
        list = list->next;
    return list;
}
