#include <stdlib.h>
#include <string.h>

#include "cpu_scheduler.h"

#ifdef _DEBUG_MODE_
#include <stdio.h>
#endif

struct cpu_scheduler
{
	process_control_block_t* current_process;
	ready_queue_t* ready_queue;
	wait_queue_t* wait_queue;
};

cpu_scheduler_t* create_cpu_scheduler_malloc(ready_queue_t* ready_queue, wait_queue_t* wait_queue)
{
	cpu_scheduler_t* cpu_scheduler = (cpu_scheduler_t*) malloc(sizeof(cpu_scheduler_t));
	memset(cpu_scheduler, 0, sizeof(cpu_scheduler_t));

	cpu_scheduler->ready_queue = ready_queue;
	cpu_scheduler->wait_queue = wait_queue;

	return cpu_scheduler;
}

void destroy_cpu_scheduler(cpu_scheduler_t* cpu_scheduler)
{
	free(cpu_scheduler);
}


void set_ready_queue(cpu_scheduler_t* cpu_scheduler, ready_queue_t* ready_queue)
{
	cpu_scheduler->ready_queue = ready_queue;
}

void set_wait_queue(cpu_scheduler_t* cpu_scheduler, wait_queue_t* wait_queue)
{
	cpu_scheduler->wait_queue = wait_queue;
}

void run_process(cpu_scheduler_t* cpu_scheduler)
{
	save_process(cpu_scheduler);

	cpu_scheduler->current_process = dequeue_process(cpu_scheduler->ready_queue);
	set_process_state(cpu_scheduler->current_process, RUNNING);
}

void exit_process(cpu_scheduler_t* cpu_scheduler)
{
	set_process_state(cpu_scheduler->current_process, TERMINATED);
#ifdef _DEBUG_MODE_
	print_process_debug_information(cpu_scheduler->current_process);
#endif
	destroy_process(cpu_scheduler->current_process);
	cpu_scheduler->current_process = NULL;
}

void save_process(cpu_scheduler_t* cpu_scheduler)
{
	if (cpu_scheduler->current_process != NULL) {
		enqueue_process(cpu_scheduler->wait_queue, cpu_scheduler->current_process);
		set_process_state(cpu_scheduler->current_process, WAITING);
		cpu_scheduler->current_process = NULL;
	}
}

void reload_process(cpu_scheduler_t* cpu_scheduler)
{
	run_process(cpu_scheduler);
}

void add_process(cpu_scheduler_t* cpu_scheduler, process_control_block_t* process)
{
	enqueue_process(cpu_scheduler->wait_queue, process);
}

void ready_process(cpu_scheduler_t* cpu_scheduler)
{
	process_control_block_t* process = dequeue_process(cpu_scheduler->wait_queue);
	set_process_state(process, READY);
	enqueue_process(cpu_scheduler->ready_queue, process);
}

#ifdef _DEBUG_MODE_
#include <string.h>

void print_cpu_scheduler_debug_information(cpu_scheduler_t* cpu_scheduler)
{
	printf("============CPU INFO============\n");
	if (cpu_scheduler->current_process != NULL) {
		printf("* CURRENT PROCESS:         *\n");
		print_process_debug_information(cpu_scheduler->current_process);
	}
	if (!is_ready_queue_empty(cpu_scheduler->ready_queue)) {
		printf("* READY QUEUE:             *\n");
		uint64_t counter = 0;
		int length = 0;
		char line[27] = { '\0', };
		for (queue_node_t* iter = get_front(cpu_scheduler->ready_queue); iter != NULL; iter = iter->next, ++counter) {
			if (counter % 3 == 0) {
				strncpy(line, "* ", 3);
				length = 2;
			}
			length += sprintf(line + length, "%5ld ->", get_process_id((process_control_block_t*) iter->item));
			// printf("\ncoutner: %ld, length: %d, string: %s\n", counter, length, line);
			if (counter % 3 == 2) {
				printf("%s", line);
				printf(" *\n");
				memset(line, 0, 29);
				length = 0;
			}
		}
		if (counter % 3 != 0) {
			printf("%s", line);
			for (int i = 0; i < 27 - length; ++i) {
				printf(" ");
			}
			printf("*\n");
		}
	}
	if (!is_wait_queue_empty(cpu_scheduler->wait_queue)) {
		printf("* WAIT QUEUE:              *\n");
		uint64_t counter = 0;
		int length = 0;
		char line[27] = { '\0', };
		for (queue_node_t* iter = get_front(cpu_scheduler->wait_queue); iter != NULL; iter = iter->next, ++counter) {
			if (counter % 3 == 0) {
				strncpy(line, "* ", 3);
				length = 2;
			}
			length += sprintf(line + length, "%5ld ->", get_process_id((process_control_block_t*) iter->item));
			// printf("\ncoutner: %ld, length: %d, string: %s\n", counter, length, line);
			if (counter % 3 == 2) {
				printf("%s", line);
				printf(" *\n");
				memset(line, 0, 29);
				length = 0;
			}
		}
		if (counter % 3 != 0) {
			printf("%s", line);
			for (int i = 0; i < 27 - length; ++i) {
				printf(" ");
			}
			printf("*\n");
		}
	}
	printf("================================\n");
}
#endif

#ifdef _TEST_ENABLED_
#include <stdio.h>
#include <time.h>

void test()
{
	wait_queue_t* wait_queue = create_wait_queue_malloc();
	ready_queue_t* ready_queue = create_ready_queue_malloc();
	cpu_scheduler_t* cpu_scheduler = create_cpu_scheduler_malloc(ready_queue, wait_queue);

	srand(time(NULL));
	uint32_t process_count = (uint32_t) rand() % 256 + 1;

	for (uint32_t i = 0; i < process_count; ++i) {
		printf("adding processes %u/%u\n", (i + 1), process_count);
		process_control_block_t* process = create_process((uint64_t) i);
		add_process(cpu_scheduler, process);
	}

	/* test loop */
	uint64_t process_run_count = 0;
	while (process_run_count < 256) {
		if (is_ready_queue_empty(cpu_scheduler->ready_queue)) {
			int wait_to_ready_count = rand() % 8 + 1;
			for (int i = 0; i < wait_to_ready_count; ++i) {
				process_control_block_t* process = dequeue_process(cpu_scheduler->wait_queue);
				if (process == NULL) {
					break;
				}
				set_process_state(process, READY);

				enqueue_process(cpu_scheduler->ready_queue, process);
			}

			if (is_ready_queue_empty(cpu_scheduler->ready_queue)) {
				break;
			}
		}

		run_process(cpu_scheduler);
#ifdef _DEBUG_MODE_
		print_cpu_scheduler_debug_information(cpu_scheduler);
#endif

		if (rand() % 5 == 0) {
			exit_process(cpu_scheduler);
			++process_count;
		}
	}

	if (cpu_scheduler->current_process != NULL) {
		exit_process(cpu_scheduler);
	}

#ifdef _DEBUG_MODE_
	print_cpu_scheduler_debug_information(cpu_scheduler);
#endif

	while (!is_wait_queue_empty(cpu_scheduler->wait_queue)) {
		destroy_process(dequeue_process(cpu_scheduler->wait_queue));
	}
	destroy_wait_queue(cpu_scheduler->wait_queue);
	cpu_scheduler->wait_queue = NULL;

	while (!is_ready_queue_empty(cpu_scheduler->ready_queue)) {
		destroy_process(dequeue_process(cpu_scheduler->ready_queue));
	}
	destroy_ready_queue(cpu_scheduler->ready_queue);
	cpu_scheduler->ready_queue = NULL;

	destroy_cpu_scheduler(cpu_scheduler);
	cpu_scheduler = NULL;
}
#endif