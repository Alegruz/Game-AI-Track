#include "thread.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint64_t g_id_count = 0ul;

thread_t* create_thread_malloc(static_array_t* max_array, static_array_t* need_array)
{
    thread_t* thread = (thread_t*) malloc(sizeof(thread_t));
    if (thread == NULL) {
        printf("NOT ENOUGH MEMORY! Failed to allocated %llu bytes of memory!!", sizeof(thread_t));
        assert(false);
    }
    memset(thread, 0, sizeof(thread_t));

    thread->allocation_array = create_array_malloc(sizeof(uint64_t), get_capacity(max_array));
    thread->max_array = max_array;
    thread->need_array = need_array;
    thread->id = g_id_count++;

    return thread;
}

void destroy_thread(thread_t* thread)
{
    if (thread != NULL) {
        if (thread->allocation_array != NULL) {
            destroy_array(thread->allocation_array);
            thread->allocation_array = NULL;
        }
        if (thread->max_array != NULL) {
            destroy_array(thread->max_array);
            thread->max_array = NULL;
        }
        if (thread->need_array != NULL) {
            destroy_array(thread->need_array);
            thread->need_array = NULL;
        }

        free(thread);
    }
}

void initialize_needs(thread_t* thread)
{
    for (uint64_t resourceIdx = 0llu; resourceIdx < get_capacity(thread->need_array); ++resourceIdx) {
        uint64_t max = *((uint64_t*) get_item_at(thread->max_array, resourceIdx));
        uint64_t allocation = *((uint64_t*) get_item_at(thread->allocation_array, resourceIdx));
        uint64_t need = max - allocation;
        add_item_at_back(thread->need_array, (void*) &need);
    }
}

bool request_resources(thread_t* thread, static_array_t* request)
{
    if (is_less_or_equal_to_ui64(request, thread->need_array)) {
        add_ui64(thread->allocation_array, request);
        sub_ui64(thread->need_array, request);
        // print_array_ui64(thread->allocation_array);
        // print_array_ui64(thread->need_array);
        // print_array_ui64(request);

        return true;
    }
    
    return false;
}

bool reverse_request_resources(thread_t* thread, static_array_t* request)
{
    if (is_less_or_equal_to_ui64(request, thread->allocation_array)) {
        sub_ui64(thread->allocation_array, request);
        add_ui64(thread->need_array, request);
        return true;
    }
    
    return false;
}

uint64_t get_id(thread_t* thread)
{
    return thread->id;
}

void print_thread(thread_t* thread)
{
    printf("thread={ allocation array:\n");
    print_array_ui64(thread->allocation_array);
    printf("\tmax array:\n");
    print_array_ui64(thread->max_array);
    printf("\tneed array:\n");
    print_array_ui64(thread->need_array);
    printf("}\n");
}