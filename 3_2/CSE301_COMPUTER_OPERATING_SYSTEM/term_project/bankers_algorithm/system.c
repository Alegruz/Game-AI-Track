#include "system.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "thread.h"

system_t* create_system_malloc(uint64_t num_resources, uint64_t num_threads)
{
    system_t* system = (system_t*) malloc(sizeof(system_t));
    if (system == NULL) {
        printf("NOT ENOUGH MEMORY! Failed to allocated %llu bytes of memory!!", sizeof(system_t));
        assert(false);
    }
    memset(system, 0, sizeof(system_t));
    system->num_resouces = num_resources;
    system->num_threads = num_threads;

	system->threads = create_array_malloc(sizeof(thread_t*), system->num_threads);
	system->available = create_array_malloc(sizeof(uint64_t), system->num_resouces);

    for (uint64_t threadIdx = 0; threadIdx < system->num_threads; ++threadIdx) {
        thread_t* thread = create_thread_malloc(create_array_malloc(sizeof(uint64_t), system->num_resouces), 
                                               create_array_malloc(sizeof(uint64_t), system->num_resouces)); 
        add_item_at_back(system->threads, 
                         &thread);
    }

	// static_array_t* max_array = create_array_malloc(sizeof(uint64_t), 3ul);
	// static_array_t* need_array = create_array_malloc(sizeof(uint64_t), 3ul);
	// add_item_at_back(system->threads, (void*) create_thread_malloc(max_array, need_array));

	return system;
}

void destroy_system(system_t* system)
{
    for (uint64_t i = get_size(system->threads); i > 0; --i) {
		destroy_thread(*((thread_t**) get_item_at(system->threads, i - 1)));
	}
	destroy_array(system->threads);
	destroy_array(system->available);
}

bool is_system_safe(system_t* system)
{
    // 1
    static_array_t* work = create_array_malloc(sizeof(uint64_t), system->num_resouces);
	static_array_t* finish = create_array_malloc(sizeof(bool), system->num_threads);
    static_array_t* safety_sequence = create_array_malloc(sizeof(thread_t*), system->num_threads);
    bool b_true = true;
    bool b_false = false;

    copy_array(work, system->available);
    for (uint64_t threadIdx = 0llu; threadIdx < system->num_threads; ++threadIdx) {
        add_item_at_back(finish, &b_false);
    }

    // 2
    uint64_t finished_count = 0llu;
    while (finished_count < system->num_threads) {
        uint64_t initial_count = finished_count;
        for (uint64_t threadIdx = 0ul; threadIdx < system->num_threads; ++threadIdx) {
            if (*((bool*) get_item_at(finish, threadIdx)) == false) {
                if (is_less_or_equal_to_ui64((*((thread_t**) get_item_at(system->threads, threadIdx)))->need_array, work)) {
                    // 3
                    add_ui64(work, (*((thread_t**) get_item_at(system->threads, threadIdx)))->allocation_array);
                    uint64_t id = get_id(*((thread_t**) get_item_at(system->threads, threadIdx)));
                    add_item_at_back(safety_sequence, &id);
                    set_item_at(finish, &b_true, threadIdx);
                    ++finished_count;
                }
            }
        }
        
        if (initial_count == finished_count) {
            break;
        }
    }

    // 4
    destroy_array(work);
    destroy_array(finish);

    if (finished_count == system->num_threads) {
        printf("System is in safe state!\n");
        print_array_ui64(safety_sequence);
        destroy_array(safety_sequence);
        return true;
    }
    
    printf("System is in unsafe state!\n");
    destroy_array(safety_sequence);
    return false;
}

void set_available(system_t* system, uint64_t* available)
{
    for (uint64_t i = 0llu; i < get_size(system->available); ++i) {
        set_item_at(system->available, &available[i], i);
    }

    for (uint64_t i = get_size(system->available); i < system->num_resouces; ++i) {
        add_item_at_back(system->available, &available[i]);
    }
}

void set_thread_allocation(system_t* system, uint64_t index, uint64_t* allocation)
{
    set_array((*((thread_t**) get_item_at(system->threads, index)))->allocation_array, allocation, system->num_resouces);
}

void set_thread_max(system_t* system, uint64_t index, uint64_t* allocation)
{
    set_array((*((thread_t**) get_item_at(system->threads, index)))->max_array, allocation, system->num_resouces);
}

bool request_by_index(system_t* system, static_array_t* request, uint64_t threadIdx)
{
    printf("request to [%llu], request array:\n", threadIdx);
    print_array_ui64(request);
    if (request_resources(*((thread_t**) get_item_at(system->threads, threadIdx)), request)) {
        sub_ui64(system->available, request);
        return true;
    }

    return false;
}

bool reverse_request_by_index(system_t* system, static_array_t* request, uint64_t threadIdx)
{
    if (reverse_request_resources(*((thread_t**) get_item_at(system->threads, threadIdx)), request)) {
        add_ui64(system->available, request);
        return true;
    }

    return false;
}

void print_system(system_t* system)
{
    printf("system={ num_resources=%llu, num_threads=%llu, available:\n", system->num_resouces, system->num_threads);
    print_array_ui64(system->available);
    for (uint64_t i = 0llu; i < system->num_threads; ++i) {
        printf("\tthread[%llu]:\n", i);
        print_thread((*(thread_t**) get_item_at(system->threads, i)));
    }
    printf("}\n");
}