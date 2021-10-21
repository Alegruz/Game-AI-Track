#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>
#include <stdint.h>

#include "build_settings.h"
#include "process_control_block.h"

typedef struct queue_node
{
	void* item;
	struct queue_node* next;
} queue_node_t;

typedef struct queue queue_t;

typedef struct queue ready_queue_t;
typedef struct queue wait_queue_t;

typedef struct job_queue job_queue_t;

queue_t* create_queue_malloc();
void destroy_queue(queue_t* queue);
queue_t* copy_queue_malloc(queue_t* lhs, queue_t* rhs);
queue_node_t* get_front(queue_t* queue);
queue_node_t* get_back(queue_t* queue);
bool is_queue_empty(queue_t* queue);
uint64_t get_size_of_queue(queue_t* queue);
void enqueue(queue_t* queue, void* item);
void* dequeue(queue_t* queue);

ready_queue_t* create_ready_queue_malloc();
void destroy_ready_queue(ready_queue_t* ready_queue);
ready_queue_t* copy_ready_queue_malloc(ready_queue_t* lhs, ready_queue_t* rhs);
bool is_ready_queue_empty(ready_queue_t* ready_queue);
void enqueue_process(queue_t* queue, process_control_block_t* process);
void* dequeue_process(queue_t* queue);

wait_queue_t* create_wait_queue_malloc();
void destroy_wait_queue(wait_queue_t* wait_queue);
wait_queue_t* copy_wait_queue_malloc(wait_queue_t* lhs, wait_queue_t* rhs);
bool is_wait_queue_empty(wait_queue_t* wait_queue);

job_queue_t* create_job_queue_malloc();
void destroy_job_queue(job_queue_t* queue);
process_control_block_t* get_job(job_queue_t* queue, uint64_t index, uint64_t id);
void return_job(job_queue_t* queue, process_control_block_t* job);
uint64_t get_size_of_job_queue(job_queue_t* queue);
#ifdef _DEBUG_MODE_
	void print_job_queue_debug_information(job_queue_t* queue);
#endif

#endif