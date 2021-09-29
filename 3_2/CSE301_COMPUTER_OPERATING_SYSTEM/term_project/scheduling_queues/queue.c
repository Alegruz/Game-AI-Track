#include <assert.h>
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

typedef struct id_node
{
	uint64_t id;
	uint64_t index;
	struct id_node* next;
} id_node_t;

struct job_queue
{
	process_control_block_t* jobs[256];
	id_node_t* pid_to_index[256];
	uint64_t size;
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

uint64_t get_size_of_queue(queue_t* queue)
{
	return queue->size;
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

id_node_t* create_id_node_malloc(uint64_t index, uint64_t id)
{
	id_node_t* node = (id_node_t*) malloc(sizeof(id_node_t));
	memset(node, 0, sizeof(id_node_t));
	node->id = id;
	node->index = index;

	return node;
}

job_queue_t* create_job_queue_malloc()
{
	job_queue_t* queue = (job_queue_t*) malloc(sizeof(job_queue_t));
	memset(queue, 0, sizeof(job_queue_t));
	queue->size = (uint64_t) rand() % 256 + 1;

	for (uint64_t i = 0; i < queue->size; ++i) {
		queue->jobs[i] = create_process_malloc(~0u);
	}

	return queue;
}

void destroy_job_queue(job_queue_t* queue)
{
	for (uint64_t i = 0; i < sizeof(queue->pid_to_index) / sizeof(queue->pid_to_index[0]); ++i) {
		id_node_t* iter = queue->pid_to_index[i];

		while (iter != NULL) {
			id_node_t* node_to_free = iter;
			iter = iter->next;
			free(node_to_free);
		}
	}

	for (uint32_t i = 0; i < queue->size; ++i) {
		destroy_process(queue->jobs[i]);
	}

	free(queue);
}

process_control_block_t* get_job(job_queue_t* queue, uint64_t index, uint64_t id)
{
	if (get_process_id(queue->jobs[index]) != ~0u) {
		return NULL;
	}

	uint64_t id_node_index = id % 256;

	id_node_t* iter = queue->pid_to_index[id_node_index];
	if (iter == NULL) {
		iter = queue->pid_to_index[id_node_index] = create_id_node_malloc(index, id);
	} else {
		while (iter->next != NULL) {
			iter = iter->next;
		}

		iter->next = create_id_node_malloc(index, id);
	}

	set_process_id(queue->jobs[index], id);

	return queue->jobs[index];
}

void return_job(job_queue_t* queue, process_control_block_t* job)
{
	uint64_t id_node_index = get_process_id(job) % 256;

	id_node_t* iter = queue->pid_to_index[id_node_index];
	id_node_t* prev = NULL;

	while (iter != NULL && iter->id != get_process_id(job)) {
		prev = iter;
		iter = iter->next;
	}
	
	assert(iter != NULL);

	if (prev != NULL) {
		prev->next = iter->next;
	} else {
		queue->pid_to_index[id_node_index] = iter->next;
	}

	free(iter);
}

uint64_t get_size_of_job_queue(job_queue_t* queue)
{
	return queue->size;
}

#ifdef _DEBUG_MODE_
void print_job_queue_debug_information(job_queue_t* queue)
{
	for (uint32_t i = 0; i < 256; ++i)
	{
		id_node_t* node = queue->pid_to_index[i];
		if (node != NULL) {
			printf("BUCKET[%u]:", i);
		}
		while (node != NULL) {
			printf(" -> (id: %lu, index: %lu)", node->id, node->index);
			node = node->next;
		}
		if (queue->pid_to_index[i] != NULL) {
			printf("\n");
		}
	}
}
#endif