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
	job_queue_t* job_queue;
	uint64_t next_id;
};

cpu_scheduler_t* create_cpu_scheduler_malloc(job_queue_t* job_queue)
{
	cpu_scheduler_t* cpu_scheduler = (cpu_scheduler_t*) malloc(sizeof(cpu_scheduler_t));
	memset(cpu_scheduler, 0, sizeof(cpu_scheduler_t));

	cpu_scheduler->ready_queue = create_ready_queue_malloc();
	cpu_scheduler->wait_queue = create_wait_queue_malloc();
	cpu_scheduler->job_queue = job_queue;

	return cpu_scheduler;
}

void destroy_cpu_scheduler(cpu_scheduler_t* cpu_scheduler)
{
	destroy_ready_queue(cpu_scheduler->ready_queue);
	destroy_wait_queue(cpu_scheduler->wait_queue);
	destroy_job_queue(cpu_scheduler->job_queue);
	free(cpu_scheduler);
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
	
	return_job(cpu_scheduler->job_queue, cpu_scheduler->current_process);
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

void ready_process(cpu_scheduler_t* cpu_scheduler)
{
	process_control_block_t* process = dequeue_process(cpu_scheduler->wait_queue);
	set_process_state(process, READY);
	enqueue_process(cpu_scheduler->ready_queue, process);
}

void call_process(cpu_scheduler_t* cpu_scheduler, uint64_t index)
{
	uint64_t temp = cpu_scheduler->next_id - get_size_of_queue(cpu_scheduler->wait_queue) - get_size_of_queue(cpu_scheduler->ready_queue);
	temp = (cpu_scheduler->next_id - (temp & ~(temp >> 63)));
	process_control_block_t* process = get_job(cpu_scheduler->job_queue, index, temp);
	if (process != NULL) {
		enqueue_process(cpu_scheduler->ready_queue, process);
		cpu_scheduler->next_id = temp + 1;
	}
}

void update(cpu_scheduler_t* cpu_scheduler)
{
	if (is_ready_queue_empty(cpu_scheduler->ready_queue) && !is_wait_queue_empty(cpu_scheduler->wait_queue)) {
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
			return;
		}
	}
	run_process(cpu_scheduler);
#ifdef _DEBUG_MODE_
	print_cpu_scheduler_debug_information(cpu_scheduler);
#endif

	if (rand() % 5 == 0) {
		exit_process(cpu_scheduler);
	}
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
	job_queue_t* job_queue = create_job_queue_malloc();
	cpu_scheduler_t* cpu_scheduler = create_cpu_scheduler_malloc(job_queue);

	uint64_t call_process_count = (uint64_t) rand() % get_size_of_job_queue(cpu_scheduler->job_queue) + 1;
	for (uint64_t i = 0; i < call_process_count; ++i) {
		call_process(cpu_scheduler, (uint64_t) rand() % get_size_of_job_queue(cpu_scheduler->job_queue));
	}

#ifdef _DEBUG_MODE_
	print_job_queue_debug_information(cpu_scheduler->job_queue);
#endif
#ifdef _DEBUG_MODE_
	print_cpu_scheduler_debug_information(cpu_scheduler);
#endif
	/* test loop */
	do {
		update(cpu_scheduler);
	} while (!is_wait_queue_empty(cpu_scheduler->wait_queue) || !is_ready_queue_empty(cpu_scheduler->ready_queue));

	if (cpu_scheduler->current_process != NULL) {
		exit_process(cpu_scheduler);
	}

#ifdef _DEBUG_MODE_
	print_cpu_scheduler_debug_information(cpu_scheduler);
#endif

	destroy_cpu_scheduler(cpu_scheduler);
	cpu_scheduler = NULL;
}
#endif