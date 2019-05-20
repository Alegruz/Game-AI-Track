#include <stdbool.h>
#include <stdlib.h>
#include "queue.h"

struct node {
    Item data;
    struct node *next;
};

struct queue {
    struct node *first;
    struct node *last;
};

static void terminate(const char *message) {
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}

Queue create_queue(int size) {
    Queue q = (Queue) malloc(sizeof(struct queue));
    if (q == NULL)
        terminate("Error in create_queue: queue could not be created.\n");
    q->first = NULL;
    q->last = NULL;
    return q;
}

void insert_item(Queue q, Item i) {
    struct node *new_node = (struct node *) malloc(sizeof(struct node));
    if (new_node == NULL)
        terminate("Error in insert_item: queue is full");
    
    new_node->data = i;
    new_node->next = q->last;
    q->last = new_node;
}

Item remove_first_item(Queue q) {
    struct node *old_first;
    Item i;

    if (is_empty(q))
        terminate("Error in remove_first_item: queue is empty.");
    
    old_first = q->first;
    i = old_first->data;
    q->first = old_first->next;
    free(old_first);
    return i;
}

Item get_first_item(Queue q) {
    return q->first->data;
}

Item get_last_item(Queue q) {
    return q->last->data;
}

bool is_empty(Queue q) {
    return q->first == NULL && q->last == NULL;
}