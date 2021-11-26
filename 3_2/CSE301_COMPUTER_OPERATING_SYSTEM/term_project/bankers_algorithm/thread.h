#ifndef THREAD_H
#define THREAD_H

#include <stdbool.h>
#include <stdint.h>

#include "static_array.h"

typedef struct
{
    static_array_t* allocation_array;
    static_array_t* max_array;
    static_array_t* need_array;
    uint64_t id;
} thread_t;

thread_t* create_thread_malloc(static_array_t* max_array, static_array_t* need_array);
void destroy_thread(thread_t* thread);

void initialize_needs(thread_t* thread);

bool request_resources(thread_t* thread, static_array_t* request);
bool reverse_request_resources(thread_t* thread, static_array_t* request);

uint64_t get_id(thread_t* thread);

void print_thread(thread_t* thread);

#endif