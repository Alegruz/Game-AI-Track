#pragma once

#include "build_settings.h"

#include <stdint.h>
#include <stdlib.h>

#include "page.h"

typedef struct page_queue_node page_queue_node_t;
typedef struct index_queue_node index_queue_node_t;

struct page_queue_node
{
    page_t* page;
    page_queue_node_t* next;
};

struct index_queue_node
{
    uint64_t index;
    index_queue_node_t* next;
};

typedef struct 
{
    uint64_t size;
    page_queue_node_t* head;
    page_queue_node_t* tail;
} page_queue_t;

typedef struct 
{
    uint64_t size;
    index_queue_node_t* head;
    index_queue_node_t* tail;
} index_queue_t;

page_queue_t* create_page_queue_malloc();
void destroy_page_queue(page_queue_t* page_queue);
void enqueue_page(page_queue_t* page_queue, page_t* page);
page_t* dequeue_page(page_queue_t* page_queue);
void clear_page_queue(page_queue_t* page_queue);

index_queue_t* create_index_queue_malloc();
void destroy_index_queue(index_queue_t* index_queue);
void enqueue_index(index_queue_t* index_queue, uint64_t index);
uint64_t dequeue_index(index_queue_t* index_queue);
void clear_index_queue(index_queue_t* index_queue);
#ifdef DEBUG
void print_index_queue(index_queue_t* index_queue);
#endif

page_t* remove_page_from_queue_by_index(page_queue_t* page_queue, index_queue_t* index_queue, uint64_t index);