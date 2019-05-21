#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "queue.h"

struct queue {
    int *contents;
    int first;
    int last;
    int size;
};

static void terminate(const char *message) {
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}

Queue create_queue(int size) {
    Queue q = (Queue) malloc(sizeof(struct queue));
    if (q == NULL)
        terminate("Error in create_queue: queue could not be created.\n");
    
    q->contents = (Item *) malloc(size * sizeof(Item));
    if (q->contents == NULL) {
        free(q->contents);
        terminate("Error in create_queue: queue could not be created.\n");
    }
    q->first = 0;
    q->last = 0;
    q->size = size;
    return q;
}

void destroy_queue(Queue q) {
    free(q->contents);
    free(q);
}

void make_empty(Queue q) {
    while(!is_empty(q))
        remove_first_item(q);
}

void insert_item(Queue q, Item i) {
    if (q->last >= q->size)
        q->last = 0;
    q->contents[q->last++] = i;
}

Item remove_first_item(Queue q) {
    if (is_empty(q))
        terminate("Error in remove_first_item: Queue is empty.");
    else if (q->first >= q->size)
        q->first = 0;
    
    return q->contents[q->first++];
}

Item get_first_item(Queue q) {
    if (is_empty(q))
        terminate("Error in get_first_item: Queue empty.");
    return q->contents[q->last];
}

Item get_last_item(Queue q) {
    if (is_empty(q))
        terminate("Error in get_first_item: Queue empty.");
    return q->contents[q->first];
}

bool is_empty(Queue q) {
    return q->first == q->last;
}