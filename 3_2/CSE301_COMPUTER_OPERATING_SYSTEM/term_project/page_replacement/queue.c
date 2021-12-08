#include "queue.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#ifdef DEBUG
    #include <stdio.h>
#endif
#include <string.h>

#ifndef INVALID_INDEX
    #define INVALID_INDEX (0xffffffffffffffffllu)
#endif

#ifndef INVALID_BYTE
    #define INVALID_BYTE (0xff)
#endif

page_queue_t* create_page_queue_malloc()
{
    page_queue_t* page_queue = (page_queue_t*) malloc(sizeof(page_queue_t));
    if (page_queue == NULL) {
#ifdef DEBUG
        printf("Not enough memory to allocate page queue of %llu bytes!!\n", sizeof(page_queue_t));
#endif
        assert(false);
    }
// #ifdef DEBUG
//         printf("Allocated page queue %p\n", page_queue);
// #endif
    memset(page_queue, 0, sizeof(page_queue_t));

    return page_queue;
}

void destroy_page_queue(page_queue_t* page_queue)
{
    if (page_queue != NULL) {
        while (page_queue->size > 0llu) {
            dequeue_page(page_queue);
            // printf("destroy_page_queue::size=%llu\n", page_queue->size);
        }
        free(page_queue);

// #ifdef DEBUG
//         printf("Freed page queue %p\n", page_queue);
// #endif
    }
}

void enqueue_page(page_queue_t* page_queue, page_t* page)
{
    assert(page_queue != NULL && page != NULL);

    page_queue_node_t* node = (page_queue_node_t*) malloc(sizeof(page_queue_node_t));
    if (node == NULL) {
#ifdef DEBUG
        printf("Not enough memory to allocate page queue node of %llu bytes!!\n", sizeof(page_queue_node_t));
#endif
        assert(false);
    }
    memset(node, 0, sizeof(page_queue_node_t));
    node->page = page;
// #ifdef DEBUG
//         printf("Allocated page queue node %p with page %p\n", node, node->page);
// #endif

    if (page_queue->tail != NULL) {
        page_queue->tail->next = node;
    }
    page_queue->tail = node;

    if (page_queue->head == NULL) {
        page_queue->head = node;
    }
    ++(page_queue->size);
}

page_t* dequeue_page(page_queue_t* page_queue)
{
    assert(page_queue != NULL);

    page_queue_node_t* page_node_to_dequeue = page_queue->head;
    page_t* page_to_dequeue = page_node_to_dequeue->page;

    page_queue->head = page_node_to_dequeue->next;
    --(page_queue->size);

    free(page_node_to_dequeue);

// #ifdef DEBUG
//     printf("dequeue_page::Freed page queue node %p\n", page_node_to_dequeue);
// #endif

    return page_to_dequeue;
}

void clear_page_queue(page_queue_t* page_queue)
{
    while (page_queue->size > 0) {
        dequeue_page(page_queue);
    }
}

// index queue

index_queue_t* create_index_queue_malloc()
{
    index_queue_t* index_queue = (index_queue_t*) malloc(sizeof(index_queue_t));
    if (index_queue == NULL) {
#ifdef DEBUG
        printf("Not enough memory to allocate index queue of %llu bytes!!\n", sizeof(index_queue_t));
#endif
        assert(false);
    }
    memset(index_queue, 0, sizeof(index_queue_t));

    return index_queue;
}

void destroy_index_queue(index_queue_t* index_queue)
{
    if (index_queue != NULL) {
        while (index_queue->size > 0llu) {
            dequeue_index(index_queue);
        }
        free(index_queue);
    }
}

void enqueue_index(index_queue_t* index_queue, uint64_t index)
{
    assert(index_queue != NULL && index != INVALID_INDEX);

    index_queue_node_t* node = (index_queue_node_t*) malloc(sizeof(index_queue_node_t));
    if (node == NULL) {
#ifdef DEBUG
        printf("Not enough memory to allocate index queue node of %llu bytes!!\n", sizeof(index_queue_node_t));
#endif
        assert(false);
    }
// #ifdef DEBUG
//     printf("Allocated index queue node %p\n", node);
// #endif
    memset(node, 0, sizeof(index_queue_node_t));
    node->index = index;

    if (index_queue->tail != NULL) {
        index_queue->tail->next = node;
    }
    index_queue->tail = node;

    if (index_queue->head == NULL) {
        index_queue->head = node;
    }
    ++(index_queue->size);
}

uint64_t dequeue_index(index_queue_t* index_queue)
{
    assert(index_queue != NULL);

    index_queue_node_t* index_node_to_dequeue = index_queue->head;
    uint64_t index_to_dequeue = index_node_to_dequeue->index;

    index_queue->head = index_node_to_dequeue->next;
    --(index_queue->size);

    free(index_node_to_dequeue);
// #ifdef DEBUG
//     printf("Freed index queue node %p\n", index_node_to_dequeue);
// #endif

    return index_to_dequeue;
}

void clear_index_queue(index_queue_t* index_queue)
{
    while (index_queue->size > 0) {
        dequeue_index(index_queue);
    }
}

#ifdef DEBUG
void print_index_queue(index_queue_t* index_queue)
{
    index_queue_node_t* iter = index_queue->head;
    printf("INDEX QUEUE: \n");
    while (iter != NULL) {
        printf(" -> [%llu]", iter->index);
        iter = iter->next;
    }
    printf("\n");
}
#endif

page_t* remove_page_from_queue_by_index(page_queue_t* page_queue, index_queue_t* index_queue, uint64_t index)
{
    assert(page_queue->size == index_queue->size);

    page_queue_node_t* page_iter_node = page_queue->head;
    index_queue_node_t* index_iter_node = index_queue->head;

    if (index_iter_node->index == index) {
        dequeue_index(index_queue);
        return dequeue_page(page_queue);
    }

    page_t* page_to_return = NULL;
    while (index_iter_node->next != NULL) {
        assert(page_iter_node->next != NULL);
        if (index_iter_node->next->index == index) {
            page_queue_node_t* page_node_to_remove = page_iter_node->next;
            index_queue_node_t* index_node_to_remove = index_iter_node->next;
            page_iter_node->next = page_node_to_remove->next;
            index_iter_node->next = index_node_to_remove->next;
            page_to_return = page_node_to_remove->page;
            free(page_node_to_remove);
            free(index_node_to_remove);
// #ifdef DEBUG
//             printf("remove_page_from_queue_by_index::Freed page queue node %p\n", page_node_to_remove);
//             printf("remove_page_from_queue_by_index::Freed index queue node %p\n", index_node_to_remove);
// #endif

            break;
        }

        page_iter_node = page_iter_node->next;
        index_iter_node = index_iter_node->next;
    }

    return page_to_return;
}