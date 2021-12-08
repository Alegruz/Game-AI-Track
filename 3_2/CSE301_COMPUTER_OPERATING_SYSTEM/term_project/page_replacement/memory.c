#include "memory.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#ifdef DEBUG
    #include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>

memory_t* create_memory_malloc(uint64_t capacity)
{
    memory_t* memory = (memory_t*) malloc(sizeof(memory_t));
    if (memory == NULL) {
#ifdef DEBUG
        printf("Not enough memory to allocate memory of %llu bytes!!\n", sizeof(memory));
#endif
        assert(false);
    }
// #ifdef DEBUG
//         printf("Allocated memory %p\n", memory);
// #endif
    memset(memory, 0, sizeof(memory_t));
    memory->capacity = capacity;
    memory->pages = (page_t*) malloc(sizeof(page_t) * memory->capacity);
    if (memory->pages == NULL) {
#ifdef DEBUG
        printf("Not enough memory to allocate memory pages of %llu bytes!!\n", sizeof(page_t) * memory->capacity);
#endif
        assert(false);
    }
// #ifdef DEBUG
//         printf("Allocated memory pages %p\n", memory->pages);
// #endif
    memset(memory->pages, 0, sizeof(page_t) * memory->capacity);
    memory->indice = (uint64_t*) malloc(sizeof(uint64_t) * memory->capacity);
    if (memory->indice == NULL) {
#ifdef DEBUG
        printf("Not enough memory to allocate memory indice of %llu bytes!!\n", sizeof(uint64_t) * memory->capacity);
#endif
        assert(false);
    }
// #ifdef DEBUG
//         printf("Allocated memory indice %p\n", memory->indice);
// #endif
    memset(memory->indice, INVALID_BYTE, sizeof(uint64_t) * memory->capacity);
#ifdef FIFO_REPLACEMENT
    memory->page_queue = create_page_queue_malloc();
    memory->index_queue = create_index_queue_malloc();
#endif

#ifdef OPTIMAL_REPLACEMENT
    memory->next_index_data = (index_queue_t**) malloc(sizeof(index_queue_t*) * memory->capacity);
    if (memory->next_index_data == NULL) {
#ifdef DEBUG
        printf("Not enough memory to allocate memory next index data of %llu bytes!!\n", sizeof(index_queue_t*) * memory->capacity);
#endif
        assert(false);
    }
    memset(memory->next_index_data, 0, sizeof(index_queue_t*) * memory->capacity);
#endif
#ifdef WIN32
    memory->timers = (LARGE_INTEGER*) malloc(sizeof(LARGE_INTEGER) * memory->capacity);
    if (memory->timers == NULL) {
#ifdef DEBUG
        printf("Not enough memory to allocate memory timer of %llu bytes!!\n", sizeof(LARGE_INTEGER) * memory->capacity);
#endif
        assert(false);
    }
    memset(memory->timers, 0, sizeof(LARGE_INTEGER) * memory->capacity);
    QueryPerformanceFrequency(&memory->frequency);
#endif

    return memory;
}

void destroy_memory(memory_t* memory)
{
    if (memory != NULL) {
#ifdef FIFO_REPLACEMENT
        destroy_index_queue(memory->index_queue);
        destroy_page_queue(memory->page_queue);
#endif
#ifdef OPTIMAL_REPLACEMENT
        free(memory->next_index_data);
#endif
#ifdef LRU_REPLACEMENT
#ifdef WIN32
        free(memory->timers);
#endif
#endif
        free(memory->indice);
        free(memory->pages);
        free(memory);

// #ifdef DEBUG
//         printf("Freed memory indice %p\n", memory->indice);
//         printf("Freed memory pages %p\n", memory->pages);
//         printf("Freed memory %p\n", memory);
// #endif
    }
}

page_t* get_page_by_index(memory_t* memory, uint64_t index)
{
    for (uint64_t page_idx = 0llu; page_idx < memory->capacity; ++page_idx) {
        if (memory->indice[page_idx] == index) {
            return &memory->pages[page_idx];
        }
    }

    return NULL;
}

bool add_page(memory_t* memory, page_t* page, uint64_t index)
{
    for (uint64_t page_idx = 0llu; page_idx < memory->capacity; ++page_idx) {
        if (memory->indice[page_idx] == INVALID_INDEX) {
#ifdef WIN32
            memcpy_s(&memory->pages[page_idx], sizeof(page_t), page, sizeof(page_t));
#else
            memcpy(&memory->pages[page_idx], page, sizeof(page_t));
#endif
            memory->indice[page_idx] = index;
#ifdef FIFO_REPLACEMENT
            enqueue_page(memory->page_queue, &memory->pages[page_idx]);
            enqueue_index(memory->index_queue, index);
#endif
// #ifdef DEBUG
//             printf("adding page index %llu to physical frame index %llu\n", index, page_idx);
// #endif
            ++(memory->size);
            return true;
        }
    }

    return false;
}

bool add_page_from_memory_by_index(memory_t* destination_memory, memory_t* source_memory, uint64_t index)
{
    for (uint64_t page_idx = 0llu; page_idx < destination_memory->capacity; ++page_idx) {
        if (destination_memory->indice[page_idx] == INVALID_INDEX) {
#ifdef WIN32
            memcpy_s(&destination_memory->pages[page_idx], sizeof(page_t), get_page_by_index(source_memory, index), sizeof(page_t));
#else
            memcpy(&destination_memory->pages[page_idx], get_page_by_index(source_memory, index), sizeof(page_t));
#endif
            destination_memory->indice[page_idx] = index;
#ifdef FIFO_REPLACEMENT
            enqueue_page(destination_memory->page_queue, &destination_memory->pages[page_idx]);
            enqueue_index(destination_memory->index_queue, index);
#endif
            ++(destination_memory->size);
            return true;
        }
    }

    return false;
}

#ifdef FIFO_REPLACEMENT
bool add_page_by_fifo(memory_t* destination_memory, memory_t* source_memory, uint64_t index)
{
    bool b_has_index = false;
    for (uint64_t page_idx = 0llu; page_idx < destination_memory->capacity; ++page_idx) {
        if (destination_memory->indice[page_idx] == index) {
            b_has_index = true;
            break;
        }
    }

    if (b_has_index) {
        return false;
    }
    
    if (destination_memory->size < destination_memory->capacity) {
        for (uint64_t page_idx = 0llu; page_idx < destination_memory->capacity; ++page_idx) {
            if (destination_memory->indice[page_idx] == INVALID_INDEX) {
#ifdef WIN32
                memcpy_s(&destination_memory->pages[page_idx], sizeof(page_t), get_page_by_index(source_memory, index), sizeof(page_t));
#else
                memcpy(&destination_memory->pages[page_idx], get_page_by_index(source_memory, index), sizeof(page_t));
#endif
                destination_memory->indice[page_idx] = index;

                enqueue_page(destination_memory->page_queue, &destination_memory->pages[page_idx]);
                enqueue_index(destination_memory->index_queue, index);
                ++(destination_memory->size);

                return true;
            }
        }
    } else {
        uint64_t index_to_remove = dequeue_index(destination_memory->index_queue);
        dequeue_page(destination_memory->page_queue);
        uint64_t page_index = remove_page_by_index(destination_memory, index_to_remove);
        
#ifdef WIN32
        memcpy_s(&destination_memory->pages[page_index], sizeof(page_t), get_page_by_index(source_memory, index), sizeof(page_t));
#else
        memcpy(&destination_memory->pages[page_index], get_page_by_index(source_memory, index), sizeof(page_t));
#endif
        destination_memory->indice[page_index] = index;

        enqueue_page(destination_memory->page_queue, &destination_memory->pages[page_index]);
        enqueue_index(destination_memory->index_queue, index);

#ifdef DEBUG
        printf("index_to_remove: %llu, page_index: %llu, index: %llu\n", index_to_remove, page_index, index);
#endif

        return true;
    }

    return false;
}
#endif

#ifdef OPTIMAL_REPLACEMENT
bool add_page_by_optimal(memory_t* destination_memory, memory_t* source_memory, uint64_t index, index_queue_t* index_queue)
{
    bool b_has_index = false;
    for (uint64_t page_idx = 0llu; page_idx < destination_memory->capacity; ++page_idx) {
        if (destination_memory->indice[page_idx] == index) {
            b_has_index = true;
            break;
        }
    }

    if (b_has_index) {
        return false;
    }
    
    if (destination_memory->size < destination_memory->capacity) {
        for (uint64_t page_idx = 0llu; page_idx < destination_memory->capacity; ++page_idx) {
            if (destination_memory->indice[page_idx] == INVALID_INDEX) {
#ifdef WIN32
                memcpy_s(&destination_memory->pages[page_idx], sizeof(page_t), get_page_by_index(source_memory, index), sizeof(page_t));
#else
                memcpy(&destination_memory->pages[page_idx], get_page_by_index(source_memory, index), sizeof(page_t));
#endif
                destination_memory->indice[page_idx] = index;
                destination_memory->next_index_data[page_idx] = index_queue;
                ++(destination_memory->size);
                return true;
            }
        }
    } else {
        uint64_t max_index = 0llu;
        uint64_t max_next_index = destination_memory->next_index_data[max_index]->size > 0 ? destination_memory->next_index_data[max_index]->head->index : UINT64_MAX;
        uint64_t max_page_index = destination_memory->indice[max_index];
        
        // printf("checking [%llu]: ", max_index);
        // print_index_queue(destination_memory->next_index_data[max_index]);
        for (uint64_t next_index_idx = max_index + 1llu; next_index_idx < destination_memory->capacity; ++next_index_idx) {
            // printf("checking [%llu]: ", next_index_idx);
            // print_index_queue(destination_memory->next_index_data[next_index_idx]);
            uint64_t next_index = destination_memory->next_index_data[next_index_idx]->size > 0 ? destination_memory->next_index_data[next_index_idx]->head->index : UINT64_MAX;
            if (max_next_index < next_index) {
                max_index = next_index_idx;
                max_next_index = next_index;
                max_page_index = destination_memory->indice[max_index];
            }
        }

        assert(remove_page_by_index(destination_memory, max_page_index) == max_index);
#ifdef WIN32
        memcpy_s(&destination_memory->pages[max_index], sizeof(page_t), get_page_by_index(source_memory, index), sizeof(page_t));
#else
        memcpy(&destination_memory->pages[max_index], get_page_by_index(source_memory, index), sizeof(page_t));
#endif
        destination_memory->indice[max_index] = index;
        destination_memory->next_index_data[max_index] = index_queue;
        ++(destination_memory->size); 

#ifdef DEBUG
        printf("max_page_index: %llu, max_index: %llu, index: %llu\n", max_page_index, max_index, index);
#endif

        return true;
    }

    return false;
}
#endif
#ifdef LRU_REPLACEMENT
bool add_page_by_lru(memory_t* destination_memory, memory_t* source_memory, uint64_t index)
{
    bool b_has_index = false;
    uint64_t least_recently_used_idx = 0llu;
#ifdef WIN32
    LONGLONG min_lru = MAXLONGLONG;
#endif        
    for (uint64_t page_idx = 0llu; page_idx < destination_memory->capacity; ++page_idx) {
        // printf("[%llu]: lru: %lld\n", page_idx, destination_memory->timers[page_idx].QuadPart);
        if (destination_memory->indice[page_idx] == index) {
            b_has_index = true;
            QueryPerformanceCounter(&destination_memory->timers[page_idx]);
            break;
        } else if (destination_memory->timers[page_idx].QuadPart < min_lru) {
            least_recently_used_idx = page_idx;
            min_lru = destination_memory->timers[least_recently_used_idx].QuadPart;
        }
    }

    if (b_has_index) {
        return false;
    }
    
    if (destination_memory->size < destination_memory->capacity) {
        for (uint64_t page_idx = 0llu; page_idx < destination_memory->capacity; ++page_idx) {
            if (destination_memory->indice[page_idx] == INVALID_INDEX) {
#ifdef WIN32
                memcpy_s(&destination_memory->pages[page_idx], sizeof(page_t), get_page_by_index(source_memory, index), sizeof(page_t));
#else
                memcpy(&destination_memory->pages[page_idx], get_page_by_index(source_memory, index), sizeof(page_t));
#endif
                destination_memory->indice[page_idx] = index;

#ifdef WIN32
                QueryPerformanceCounter(&destination_memory->timers[page_idx]);
#endif

                ++(destination_memory->size);

                return true;
            }
        }
    } else {
#ifdef WIN32
        memcpy_s(&destination_memory->pages[least_recently_used_idx], sizeof(page_t), get_page_by_index(source_memory, index), sizeof(page_t));
#else
        memcpy(&destination_memory->pages[least_recently_used_idx], get_page_by_index(source_memory, index), sizeof(page_t));
#endif
        destination_memory->indice[least_recently_used_idx] = index;

#ifdef WIN32
        QueryPerformanceCounter(&destination_memory->timers[least_recently_used_idx]);
#endif
        return true;
    }

    return false;
}
#endif

uint64_t remove_page_by_index(memory_t* memory, uint64_t index)
{
    for (uint64_t page_idx = 0llu; page_idx < memory->capacity; ++page_idx) {
        if (memory->indice[page_idx] == index) {
            memset(&memory->pages[page_idx], INVALID_BYTE, sizeof(page_t));
#ifdef FIFO_REPLACEMENT
            remove_page_from_queue_by_index(memory->page_queue, memory->index_queue, index);
#endif
            --(memory->size);
            return page_idx;
        }
    }

    return INVALID_INDEX;
}

void clear_memory(memory_t* memory)
{
#ifdef FIFO_REPLACEMENT
    clear_page_queue(memory->page_queue);
    clear_index_queue(memory->index_queue);
#endif
    memset(memory->pages, 0, sizeof(page_t) * memory->capacity);
    memset(memory->indice, INVALID_BYTE, sizeof(uint64_t) * memory->capacity);
    memory->size = 0llu;
}

#ifdef DEBUG
void print_memory_debug_information(memory_t* memory)
{
    printf("====MEMORY DEBUG INFORMATION====\n");
    for (uint64_t i = 0llu; i < memory->capacity; ++i) {
        printf("FRAME[%llu] = %llu\n", i, memory->indice[i]);
    }
    printf("=================================\n");
}
#endif