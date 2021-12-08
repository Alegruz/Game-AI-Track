#include "build_settings.h"

#ifdef WIN32
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <windows.h>
#include <profileapi.h>
#else
#define __USE_POSIX199309
#include <time.h>
#endif

#include <stdio.h>

#include "memory.h"
#include "page.h"
#include "queue.h"

#ifndef WIN32
struct timespec get_time_difference(struct timespec start, struct timespec end);
#endif
void test(void);

int main(void)
{
	printf("PLATFORM: ");
#ifdef WIN32
	printf("WIN32\n");
#elif defined(UNIX)
	printf("UNIX\n");
#endif

	printf("COMPILER: ");
#ifdef MSVC
	printf("Microsoft Visual C++\n");
#elif CMAKE_COMPILER_IS_GNUCC
	printf("GCC\n");
#endif

	printf("BUILD SETTING: ");
#ifdef DEBUG
	printf("Debug Mode\n");
#else
	printf("Release Mode\n");
#endif
	
	test();

#ifdef WIN32
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}

#ifndef WIN32
struct timespec get_time_difference(struct timespec start, struct timespec end)
{
	struct timespec temp;
	if ((end.tv_nsec - start.tv_nsec) <0) {
		temp.tv_sec = end.tv_sec-start.tv_sec - 1;
		temp.tv_nsec = 1000000000+end.tv_nsec - start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec - start.tv_sec;
		temp.tv_nsec = end.tv_nsec - start.tv_nsec;
	}
	return temp;
}
#endif

void test()
{
#ifdef DEBUG
    printf("size of memory: %llu\n", sizeof(memory_t));
	printf("size of page: %llu\n", sizeof(page_t));
	printf("size of page queue: %llu\n", sizeof(page_queue_t));
	printf("size of index queue: %llu\n", sizeof(index_queue_t));
#endif

	// uint64_t reference_string[] = { 7llu, 0llu, 1llu, 2llu, 
	// 								0llu, 3llu, 0llu, 4llu, 
	// 								2llu, 3llu, 0llu, 3llu, 
	// 								2llu, 1llu, 2llu, 0llu, 
	// 								1llu, 7llu, 0llu, 1llu };
	uint64_t reference_string[] = { 0llu, 1llu, 0llu, 3llu, 
									4llu, 5llu, 2llu, 3llu,
									5llu, 2llu, 6llu, 2llu,
									0llu, 4llu, 2llu, 6llu, 
									2llu, 3llu, 1llu, 3llu, 
									0llu, 3llu, 4llu, 0llu, };
	uint64_t main_memory_frame_count = 3llu;
	uint64_t secondary_storage_frame_count = 8llu;
	uint64_t reference_string_size = sizeof(reference_string) / sizeof(reference_string[0]);
	uint64_t references_count = 7llu;
	page_t** pages = (page_t**) malloc(sizeof(page_t*) * references_count);
	for (uint64_t page_idx = 0llu; page_idx < references_count; ++page_idx) {
		pages[page_idx] = create_page_malloc();
	}

	memory_t* main_memory = create_memory_malloc(main_memory_frame_count);
	memory_t* secondary_storage = create_memory_malloc(secondary_storage_frame_count);
	for (uint64_t page_idx = 0llu; page_idx < references_count; ++page_idx) {
		add_page(secondary_storage, pages[page_idx], page_idx);
	}

	print_memory_debug_information(secondary_storage);
	// FIFO
#ifdef FIFO_REPLACEMENT
	{
#ifdef WIN32
		LARGE_INTEGER starting_time;
		LARGE_INTEGER ending_time;
		LARGE_INTEGER elapsed_microseconds;
		LARGE_INTEGER frequency;
#else
		struct timespec starting_time;
		struct timespec ending_time;
#endif
		printf("FIFO Page Replacement\n");
#ifdef WIN32
		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&starting_time);
#else
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &starting_time);
#endif
		uint64_t page_fault_count = 0llu;
		for (uint64_t reference_idx = 0llu; reference_idx < reference_string_size; ++reference_idx) {
			if (add_page_by_fifo(main_memory, secondary_storage, reference_string[reference_idx])) {
				++page_fault_count;
				print_memory_debug_information(main_memory);
			}
		}
#ifdef WIN32
		QueryPerformanceCounter(&ending_time);
		elapsed_microseconds.QuadPart = ending_time.QuadPart - starting_time.QuadPart;
		elapsed_microseconds.QuadPart *= 1000000;
		elapsed_microseconds.QuadPart /= frequency.QuadPart;
		printf("Total Page Faults: %llu, %lld ms elapsed\n", page_fault_count, elapsed_microseconds.QuadPart);
#else
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ending_time);
		printf("Total Page Faults: %llu, %lld ms elapsed\n", page_fault_count, get_time_difference(starting_time, ending_time));
#endif
		clear_memory(main_memory);
	}
#endif
#ifdef OPTIMAL_REPLACEMENT
	{
#ifdef WIN32
		LARGE_INTEGER starting_time;
		LARGE_INTEGER ending_time;
		LARGE_INTEGER elapsed_microseconds;
		LARGE_INTEGER frequency;
#else
		struct timespec starting_time;
		struct timespec ending_time;
#endif
		printf("Optimal Page Replacement\n");
#ifdef WIN32
		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&starting_time);
#else
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &starting_time);
#endif
		index_queue_t** reference_index_queues = (index_queue_t**) malloc(sizeof(index_queue_t*) * references_count);
		for (uint64_t reference_index_queue_idx = 0llu; reference_index_queue_idx < references_count; ++reference_index_queue_idx) {
			reference_index_queues[reference_index_queue_idx] = create_index_queue_malloc();
		}
		for (uint64_t reference_string_idx = 0llu; reference_string_idx < reference_string_size; ++reference_string_idx) {
			// printf("[%llu]: enqueueing %llu\n", reference_string[reference_string_idx], reference_string_idx);
			// printf("before enqueueing: \n");
			// print_index_queue(reference_index_queues[reference_string[reference_string_idx]]);
			enqueue_index(reference_index_queues[reference_string[reference_string_idx]], reference_string_idx);
		}
		
		uint64_t page_fault_count = 0llu;
		for (uint64_t reference_idx = 0llu; reference_idx < reference_string_size; ++reference_idx) {
			dequeue_index(reference_index_queues[reference_string[reference_idx]]);
			// printf("[%llu]: \n", reference_string[reference_idx]);
			// print_index_queue(reference_index_queues[reference_string[reference_idx]]);
			if (add_page_by_optimal(main_memory, secondary_storage, reference_string[reference_idx], reference_index_queues[reference_string[reference_idx]])) {
				++page_fault_count;
				print_memory_debug_information(main_memory);
			}
		}
#ifdef WIN32
		QueryPerformanceCounter(&ending_time);
		elapsed_microseconds.QuadPart = ending_time.QuadPart - starting_time.QuadPart;
		elapsed_microseconds.QuadPart *= 1000000;
		elapsed_microseconds.QuadPart /= frequency.QuadPart;
		printf("Total Page Faults: %llu, %lld ms elapsed\n", page_fault_count, elapsed_microseconds.QuadPart);
#else
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ending_time);
		printf("Total Page Faults: %llu, %lld ms elapsed\n", page_fault_count, get_time_difference(starting_time, ending_time));
#endif
		clear_memory(main_memory);


		for (uint64_t reference_index_queue_idx = 0llu; reference_index_queue_idx < references_count; ++reference_index_queue_idx) {
			destroy_index_queue(reference_index_queues[reference_index_queue_idx]);
		}
		free(reference_index_queues);
	}
#endif
#ifdef LRU_REPLACEMENT
	{
#ifdef WIN32
		LARGE_INTEGER starting_time;
		LARGE_INTEGER ending_time;
		LARGE_INTEGER elapsed_microseconds;
		LARGE_INTEGER frequency;
#else
		struct timespec starting_time;
		struct timespec ending_time;
#endif
		printf("LRU Page Replacement\n");
#ifdef WIN32
		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&starting_time);
#else
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &starting_time);
#endif
		uint64_t page_fault_count = 0llu;
		for (uint64_t reference_idx = 0llu; reference_idx < reference_string_size; ++reference_idx) {
			if (add_page_by_lru(main_memory, secondary_storage, reference_string[reference_idx])) {
				++page_fault_count;
				print_memory_debug_information(main_memory);
			}
		}
#ifdef WIN32
		QueryPerformanceCounter(&ending_time);
		elapsed_microseconds.QuadPart = ending_time.QuadPart - starting_time.QuadPart;
		elapsed_microseconds.QuadPart *= 1000000;
		elapsed_microseconds.QuadPart /= frequency.QuadPart;
		printf("Total Page Faults: %llu, %lld ms elapsed\n", page_fault_count, elapsed_microseconds.QuadPart);
#else
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ending_time);
		printf("Total Page Faults: %llu, %lld ms elapsed\n", page_fault_count, get_time_difference(starting_time, ending_time));
#endif
		clear_memory(main_memory);
	}
#endif

	destroy_memory(secondary_storage);
	destroy_memory(main_memory);

	for (uint64_t page_idx = 0llu; page_idx < secondary_storage_frame_count; ++page_idx) {
		destroy_page(pages[page_idx]);
	}
	free(pages);
}