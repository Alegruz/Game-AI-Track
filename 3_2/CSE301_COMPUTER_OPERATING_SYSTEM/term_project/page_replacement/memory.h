#pragma once

#include "build_settings.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef WIN32
#include <windows.h>
#include <profileapi.h>
#endif

#include "page.h"
#if defined(FIFO_REPLACEMENT) || defined(OPTIMAL_REPLACEMENT)
#include "queue.h"
#endif

#ifndef INVALID_INDEX
#define INVALID_INDEX (0xffffffffffffffffllu)
#endif

#ifndef INVALID_BYTE
#define INVALID_BYTE (0xff)
#endif

typedef struct
{
    uint64_t capacity;
    uint64_t size;
    page_t* pages;
    uint64_t* indice;
#ifdef FIFO_REPLACEMENT
    page_queue_t* page_queue;
    index_queue_t* index_queue;
#endif
#ifdef OPTIMAL_REPLACEMENT
    index_queue_t** next_index_data;
#endif
#ifdef LRU_REPLACEMENT
#ifdef WIN32
    LARGE_INTEGER* timers;
    LARGE_INTEGER frequency;
#endif
#endif
} memory_t;

memory_t* create_memory_malloc(uint64_t capacity);
void destroy_memory(memory_t* memory);

page_t* get_page_by_index(memory_t* memory, uint64_t index);

bool add_page(memory_t* memory, page_t* page, uint64_t index);
bool add_page_from_memory_by_index(memory_t* destination_memory, memory_t* source_memory, uint64_t index);
#ifdef FIFO_REPLACEMENT
bool add_page_by_fifo(memory_t* destination_memory, memory_t* source_memory, uint64_t index);
#endif
#ifdef OPTIMAL_REPLACEMENT
bool add_page_by_optimal(memory_t* destination_memory, memory_t* source_memory, uint64_t index, index_queue_t* index_queue);
#endif
#ifdef LRU_REPLACEMENT
bool add_page_by_lru(memory_t* destination_memory, memory_t* source_memory, uint64_t index);
#endif
uint64_t remove_page_by_index(memory_t* memory, uint64_t index);
void clear_memory(memory_t* memory);

#ifdef DEBUG
void print_memory_debug_information(memory_t* memory);
#endif