/* Write an interface for a queue module in the form
 * of a header file named queue.h                    */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef struct queue *Queue;
typedef int Item;

void insert_item(Queue q, Item i);
Item remove_first_item(Queue q);
Item get_first_item(Queue q);
Item get_last_item(Queue q);
bool is_empty(Queue q);

#endif