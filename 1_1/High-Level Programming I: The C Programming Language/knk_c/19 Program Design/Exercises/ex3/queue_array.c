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

void insert_item(Queue q, Item i) {
    if (q->first >= q->size)
        q->first = 0;
    q->contents[q->first++] = i;
}

Item remove_first_item(Queue q) {
    if (q->last == q->first) {
        printf("There is nothing to last.\n");
        return;
    } else if (q->last >= q->size)
        q->last = 0;
    
    return q->contents[q->last++];
}

Item get_first_item(Queue q) {
    return q->contents[q->last];
}

Item get_last_item(Queue q) {
    return q->contents[q->first];
}

bool is_empty(Queue q) {
    return q->first == q->last;
}