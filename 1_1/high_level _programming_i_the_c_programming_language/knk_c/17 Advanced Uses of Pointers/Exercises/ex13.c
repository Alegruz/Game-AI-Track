#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};

int len(struct node *list);
struct node *insert_into_ordered_list(struct node *list, struct node *new_node);

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

    struct node *add;
    add->value = -1;
    add->next = NULL;
    printf("FUNCTION CALL\n");
    list = insert_into_ordered_list(list, add);

    count = list;
    for (int i = 0; i < len(list); ++i) {
        printf("Node %2d: %d\n", i + 1, count->value);
        count = count->next;
    }

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

struct node *insert_into_ordered_list(struct node *list, struct node *new_node) {
    struct node *cur = list, *prev = NULL;
    while (cur != NULL && cur->value <= new_node->value) {
        prev = cur;
        cur = cur->next;
    }

    if (prev == NULL)
        if (cur == NULL)
            list = new_node;
        else {
            list = new_node;
            new_node->next = cur;
        }
    else {
        prev->next = new_node;
        new_node->next = cur;
    }

    return list;
}
