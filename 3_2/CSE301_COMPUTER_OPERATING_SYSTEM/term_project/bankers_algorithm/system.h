#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>

#include "static_array.h"

typedef struct
{
    uint64_t num_resouces;
    uint64_t num_threads;
    static_array_t* available;
    static_array_t* threads;
} system_t;

system_t* create_system_malloc(uint64_t num_resources, uint64_t num_threads);
void destroy_system(system_t* system);

bool is_system_safe(system_t* system);

void set_available(system_t* system, uint64_t* available);
void set_thread_allocation(system_t* system, uint64_t index, uint64_t* allocation);
void set_thread_max(system_t* system, uint64_t index, uint64_t* allocation);

bool request_by_index(system_t* system, static_array_t* request, uint64_t threadIdx);
bool reverse_request_by_index(system_t* system, static_array_t* request, uint64_t threadIdx);

void print_system(system_t* system);

#endif