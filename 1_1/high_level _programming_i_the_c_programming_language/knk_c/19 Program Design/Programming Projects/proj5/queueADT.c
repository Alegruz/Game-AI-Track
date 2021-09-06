#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "queueADT.h"

#define QUEUE_SIZE 100

struct queue {
    int contents[QUEUE_SIZE];
    int first;
    int last;
};

static void terminate(const char *message) {
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}

Queue create_queue(void) {
    Queue q = (Queue) malloc(sizeof(struct queue));
    if (q == NULL)
        terminate("Error in create_queue: queue could not be created.\n");

    q->first = 0;
    q->last = 0;
    return q;
}

void destroy_queue(Queue q) {
    make_empty(q);
    free(q);
}

void make_empty(Queue q) {
    while(!is_empty(q))
        remove_first_item(q);
}

void insert_item(Queue q, Item i) {
    if (q->first >= QUEUE_SIZE)
        q->first = 0;
    q->contents[q->first++] = i;
}

Item remove_first_item(Queue q) {
    if (is_empty(q))
        terminate("Error in remove_first_item: Queue is empty.");
    else if (q->last >= QUEUE_SIZE)
        q->last = 0;
    
    return q->contents[q->last++];
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