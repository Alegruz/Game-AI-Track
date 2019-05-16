/* Modify delete_from_list function */

#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};

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

    list = first;
    struct node *temp;
    while(list != NULL) {
        temp = list;
        list = list->next;
        free(temp);
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
