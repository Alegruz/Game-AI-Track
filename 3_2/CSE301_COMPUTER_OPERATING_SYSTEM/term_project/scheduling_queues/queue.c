#include <stdlib.h>
#include <string.h>

#include "queue.h"

#ifdef _DEBUG_MODE_
#include <stdio.h>
#endif

struct queue
{
	uint64_t size;
	queue_node_t* front;
	queue_node_t* back;
};

queue_t* create_queue_malloc()
{
	queue_t* queue = (queue_t*) malloc(sizeof(queue_t));
	memset(queue, 0, sizeof(queue_t));

	queue->size = 0;

	return queue;
}

void destroy_queue(queue_t* queue)
{
	while (queue->size > 0) {
		dequeue(queue);
	}

	free(queue);
}

queue_t* copy_queue_malloc(queue_t* lhs, queue_t* rhs)
{
	while (lhs->size > 0) {
		dequeue(lhs);
	}
	for (queue_node_t* node = rhs->front; node != NULL; node = node->next) {
		enqueue(lhs, node->item);
	}

	return lhs;
}


queue_node_t* get_front(queue_t* queue)
{
	return queue->front;
}

queue_node_t* get_back(queue_t* queue)
{
	return queue->back;
}

bool is_queue_empty(queue_t* queue)
{
	return queue->front == NULL && queue->back == NULL;
}

void enqueue(queue_t* queue, void* item)
{
	queue_node_t* node = (queue_node_t*) malloc(sizeof(queue_node_t));
	node->item = item;
	node->next = NULL;

	if (queue->back == NULL) {
		queue->back = node;

		if (queue->front == NULL) {
			queue->front = node; 
		}
	} else {
		queue->back->next = node;
		queue->back = node;
	}
	++queue->size;
}

void* dequeue(queue_t* queue)
{
	if (queue->front == NULL) {
		return NULL;
	}

	void* item = queue->front->item;
	queue_node_t* new_front = queue->front->next;

	free(queue->front);

	queue->front = new_front;
	if (queue->front == NULL) {
		queue->back = NULL;
	}
	--queue->size;

	return item;
}

ready_queue_t* create_ready_queue_malloc()
{
	return create_queue_malloc();
}

void destroy_ready_queue(ready_queue_t* ready_queue)
{
	destroy_queue(ready_queue);
}

ready_queue_t* copy_ready_queue_malloc(ready_queue_t* lhs, ready_queue_t* rhs)
{
	return copy_queue_malloc(lhs, rhs);
}

bool is_ready_queue_empty(ready_queue_t* ready_queue)
{
	return is_queue_empty(ready_queue);
}

void enqueue_process(queue_t* queue, process_control_block_t* process)
{
	enqueue(queue, process);
}

void* dequeue_process(queue_t* queue)
{
	return dequeue(queue);
}

wait_queue_t* create_wait_queue_malloc()
{
	return create_queue_malloc();
}

void destroy_wait_queue(wait_queue_t* wait_queue)
{
	destroy_queue(wait_queue);
}

wait_queue_t* copy_wait_queue_malloc(wait_queue_t* lhs, wait_queue_t* rhs)
{
	return copy_queue_malloc(lhs, rhs);
}

bool is_wait_queue_empty(wait_queue_t* wait_queue)
{
	return is_queue_empty(wait_queue);
}