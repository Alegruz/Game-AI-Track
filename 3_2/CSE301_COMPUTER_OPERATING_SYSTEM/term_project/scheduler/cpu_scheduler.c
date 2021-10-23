#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "cpu_scheduler.h"

#ifdef DEBUG
#include <stdio.h>
#endif

const e_priority_class_t g_priority_classes[PRIORITY_CLASS_COUNT] = { IDLE_PRIORITY_CLASS,
												   BELOW_NORMAL_PRIORITY_CLASS,
												   NORMAL_PRIORITY_CLASS,
												   ABOVE_NORMAL_PRIORITY_CLASS,
												   HIGH_PRIORITY_CLASS,
												   REAL_TIME_PRIORITY_CLASS, };
const e_relative_priority_t g_relative_priorities[RELATIVE_PRIORITY_COUNT] = { IDLE,
																			   LOWEST,
																			   BELOW_NORMAL,
																			   NORMAL,
																			   ABOVE_NORMAL,
																			   HIGHEST,
																			   TIME_CRITICAL, };

struct cpu_scheduler
{
	process_control_block_t* current_process;
	ready_queue_t* ready_queue;
	wait_queue_t* wait_queue;
	job_queue_t* job_queue;
	uint64_t next_id;
	e_scheduling_algorithm_t scheduling_algorithm;
	uint32_t time_quantum;
	uint32_t quantum_timer;
	uint32_t timer;
	uint32_t total_waiting_time;
};

static uint64_t g_next_arrival_time_index = 0u;

uint32_t get_priority(const e_priority_class_t priority_class, const e_relative_priority_t relative_priority)
{
	switch (relative_priority) {
	case NORMAL:
		return (uint32_t) priority_class;
	case TIME_CRITICAL:
		if (priority_class == REAL_TIME_PRIORITY_CLASS) {
			return 31u;
		}
		return 15u;
	case HIGHEST:
		switch (priority_class) {
		case REAL_TIME_PRIORITY_CLASS:
			return 26u;
		case HIGH_PRIORITY_CLASS:
			return 15u;
		case ABOVE_NORMAL_PRIORITY_CLASS:
			return 12u;
		case NORMAL_PRIORITY_CLASS:
			return 10u;
		case BELOW_NORMAL_PRIORITY_CLASS:
			return 8u;
		case IDLE_PRIORITY_CLASS:
			return 6u;
		default:
			break;
		}
	case ABOVE_NORMAL:
		switch (priority_class) {
		case REAL_TIME_PRIORITY_CLASS:
			return 25u;
		case HIGH_PRIORITY_CLASS:
			return 14u;
		case ABOVE_NORMAL_PRIORITY_CLASS:
			return 11u;
		case NORMAL_PRIORITY_CLASS:
			return 9u;
		case BELOW_NORMAL_PRIORITY_CLASS:
			return 7u;
		case IDLE_PRIORITY_CLASS:
			return 5u;
		default:
			break;
		}
	case BELOW_NORMAL:
		switch (priority_class) {
		case REAL_TIME_PRIORITY_CLASS:
			return 23u;
		case HIGH_PRIORITY_CLASS:
			return 12u;
		case ABOVE_NORMAL_PRIORITY_CLASS:
			return 9u;
		case NORMAL_PRIORITY_CLASS:
			return 7u;
		case BELOW_NORMAL_PRIORITY_CLASS:
			return 5u;
		case IDLE_PRIORITY_CLASS:
			return 3u;
		default:
			break;
		}
	case LOWEST:
		switch (priority_class) {
		case REAL_TIME_PRIORITY_CLASS:
			return 22u;
		case HIGH_PRIORITY_CLASS:
			return 11u;
		case ABOVE_NORMAL_PRIORITY_CLASS:
			return 8u;
		case NORMAL_PRIORITY_CLASS:
			return 6u;
		case BELOW_NORMAL_PRIORITY_CLASS:
			return 4u;
		case IDLE_PRIORITY_CLASS:
			return 2u;
		default:
			break;
		}
	case IDLE:
		switch (priority_class) {
		case REAL_TIME_PRIORITY_CLASS:
			return 16u;
		case HIGH_PRIORITY_CLASS:
			return 1u;
		case ABOVE_NORMAL_PRIORITY_CLASS:
			return 1u;
		case NORMAL_PRIORITY_CLASS:
			return 1u;
		case BELOW_NORMAL_PRIORITY_CLASS:
			return 1u;
		case IDLE_PRIORITY_CLASS:
			return 1u;
		default:
			break;
		}
	default:
		break;
	}

	return 0u;
}

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
	
	bool b_should_preempt = true;
	if (cpu_scheduler->current_process != NULL) {
		b_should_preempt = get_process_remaining_burst_time(cpu_scheduler->current_process) == 0;
		if (!b_should_preempt) {
			switch (cpu_scheduler->scheduling_algorithm)
			{
			case PREEMPTIVE_SJF:
				if (!is_ready_queue_empty(cpu_scheduler->ready_queue)) {
					uint32_t next_process_burst_time = get_process_remaining_burst_time((process_control_block_t*) get_front(cpu_scheduler->ready_queue)->item);
					uint32_t current_process_burst_time = get_process_remaining_burst_time(cpu_scheduler->current_process);
					b_should_preempt = current_process_burst_time > next_process_burst_time;
				} else {
					b_should_preempt = false;
				}
				break;
			case PRIORITY:
				if (!is_ready_queue_empty(cpu_scheduler->ready_queue)) {
					uint32_t next_process_priority = get_process_priority((process_control_block_t*) get_front(cpu_scheduler->ready_queue)->item);
					uint32_t current_process_priority = get_process_priority(cpu_scheduler->current_process);
					b_should_preempt = next_process_priority > current_process_priority;
				} else {
					b_should_preempt = false;
				}
				break;
			case FCFS:
				break;
			case ROUND_ROBIN_WITH_TIME_QUANTUM:
				b_should_preempt = 0 == cpu_scheduler->quantum_timer;
				break;
			default:
				break;
			}
		}
	}
	
	if (b_should_preempt) {
		if (cpu_scheduler->current_process != NULL) {
			if (get_process_remaining_burst_time(cpu_scheduler->current_process) <= 0) {
				exit_process(cpu_scheduler);
			} else {
				save_process(cpu_scheduler);
			}
		}

		cpu_scheduler->current_process = dequeue_process(cpu_scheduler->ready_queue);
		if (cpu_scheduler->current_process == NULL) {
			return;
		}
		set_process_state(cpu_scheduler->current_process, RUNNING);
	}

	run_process_for_single_time_step(cpu_scheduler->current_process);
}

void exit_process(cpu_scheduler_t* cpu_scheduler)
{
	set_process_state(cpu_scheduler->current_process, TERMINATED);

	cpu_scheduler->total_waiting_time += get_process_waiting_time(cpu_scheduler->current_process);
	
	return_job(cpu_scheduler->job_queue, cpu_scheduler->current_process);
	cpu_scheduler->current_process = NULL;
}

void save_process(cpu_scheduler_t* cpu_scheduler)
{
	if (cpu_scheduler->current_process != NULL) {
		switch (cpu_scheduler->scheduling_algorithm) {
		case FCFS:
			/* intentional fallthrough */
		case ROUND_ROBIN_WITH_TIME_QUANTUM:
			enqueue_process(cpu_scheduler->wait_queue, cpu_scheduler->current_process);
			break;
		case PREEMPTIVE_SJF:
			enqueue_process_by_sjf(cpu_scheduler->wait_queue, cpu_scheduler->current_process);
			break;
		default:
			assert(false);
			break;
		}
		set_process_state(cpu_scheduler->current_process, WAITING);
		cpu_scheduler->current_process = NULL;
	}
}

void ready_process(cpu_scheduler_t* cpu_scheduler)
{
	process_control_block_t* process = dequeue_process(cpu_scheduler->wait_queue);
	set_process_state(process, READY);
	switch (cpu_scheduler->scheduling_algorithm) {
	case FCFS:
		/* intentional fallthrough */
	case ROUND_ROBIN_WITH_TIME_QUANTUM:
		enqueue_process(cpu_scheduler->ready_queue, process);
		break;
	case PREEMPTIVE_SJF:
		enqueue_process_by_sjf(cpu_scheduler->ready_queue, process);
		break;
	default:
		assert(false);
		break;
	}
}

void call_process(cpu_scheduler_t* cpu_scheduler, uint64_t index, uint32_t priority)
{
	// uint64_t temp = cpu_scheduler->next_id - get_size_of_queue(cpu_scheduler->wait_queue) - get_size_of_queue(cpu_scheduler->ready_queue);
	/* clamp temp to 0 */
	// temp = (cpu_scheduler->next_id - (temp & ~(temp >> 63)));
	// printf("temp: %llu, next id=%llu\n", temp, cpu_scheduler->next_id);
	// process_control_block_t* process = get_job(cpu_scheduler->job_queue, index, temp);
	process_control_block_t* process = get_job(cpu_scheduler->job_queue, index, cpu_scheduler->next_id);
	if (process != NULL) {
		set_process_priority(process, priority);
		set_process_arrival_time(process, cpu_scheduler->timer);
		
		switch (cpu_scheduler->scheduling_algorithm) {
		case FCFS:
			/* intentional fallthrough */
		case ROUND_ROBIN_WITH_TIME_QUANTUM:
			enqueue_process(cpu_scheduler->ready_queue, process);
			break;
		case PREEMPTIVE_SJF:
			enqueue_process_by_sjf(cpu_scheduler->ready_queue, process);
			break;
		default:
			assert(false);
			break;
		}
		set_process_state(process, READY);
		++cpu_scheduler->next_id;
	}
}

void sort_process(cpu_scheduler_t* cpu_scheduler)
{
	switch (cpu_scheduler->scheduling_algorithm)
	{
	case FCFS:
		/* intentional breakthrough */
	case ROUND_ROBIN_WITH_TIME_QUANTUM:
		/* do nothing */
		break;
	case PREEMPTIVE_SJF:
		break;
	default:
		break;
	}
}

void update(cpu_scheduler_t* cpu_scheduler)
{
	if (is_ready_queue_empty(cpu_scheduler->ready_queue)) {
		if (!is_wait_queue_empty(cpu_scheduler->wait_queue)) {
			int wait_to_ready_count = rand() % 8 + 1;
			for (int i = 0; i < wait_to_ready_count; ++i) {
				process_control_block_t* process = dequeue_process(cpu_scheduler->wait_queue);
				if (process == NULL) {
					break;
				}
				set_process_state(process, READY);

				switch (cpu_scheduler->scheduling_algorithm) {
				case FCFS:
					/* intentional fallthrough */
				case ROUND_ROBIN_WITH_TIME_QUANTUM:
					enqueue_process(cpu_scheduler->ready_queue, process);
					break;
				case PREEMPTIVE_SJF:
					enqueue_process_by_sjf(cpu_scheduler->ready_queue, process);
					break;
				default:
					assert(false);
					break;
				}
			}

			if (is_ready_queue_empty(cpu_scheduler->ready_queue)) {
				return; 
			}
		}
	}
	
	if (rand() % 10 == 0) {
		uint32_t priority = get_priority(g_priority_classes[rand() % PRIORITY_CLASS_COUNT], g_relative_priorities[rand() % RELATIVE_PRIORITY_COUNT]);
		call_process(cpu_scheduler, (uint64_t) rand() % get_size_of_job_queue(cpu_scheduler->job_queue), priority);
	}

	run_process(cpu_scheduler);

	for (queue_node_t* iter_node = get_front(cpu_scheduler->ready_queue); iter_node != NULL; iter_node = iter_node->next) {
		tick((process_control_block_t*) iter_node->item);
	}

	for (queue_node_t* iter_node = get_front(cpu_scheduler->wait_queue); iter_node != NULL; iter_node = iter_node->next) {
		tick((process_control_block_t*) iter_node->item);
	}

#ifdef DEBUG
	print_cpu_scheduler_debug_information(cpu_scheduler);
#endif
	cpu_scheduler->quantum_timer = (cpu_scheduler->quantum_timer + 1) % cpu_scheduler->time_quantum;
	++cpu_scheduler->timer;
}

void update_by_test_data(cpu_scheduler_t* cpu_scheduler, uint32_t* arrival_times, uint64_t data_size)
{
	if (is_ready_queue_empty(cpu_scheduler->ready_queue)) {
		if (!is_wait_queue_empty(cpu_scheduler->wait_queue)) {
			int wait_to_ready_count = rand() % 8 + 1;
			for (int i = 0; i < wait_to_ready_count; ++i) {
				process_control_block_t* process = dequeue_process(cpu_scheduler->wait_queue);
				if (process == NULL) {
					break;
				}
				set_process_state(process, READY);

				switch (cpu_scheduler->scheduling_algorithm) {
				case FCFS:
					/* intentional fallthrough */
				case ROUND_ROBIN_WITH_TIME_QUANTUM:
					enqueue_process(cpu_scheduler->ready_queue, process);
					break;
				case PREEMPTIVE_SJF:
					enqueue_process_by_sjf(cpu_scheduler->ready_queue, process);
					break;
				default:
					assert(false);
					break;
				}
			}

			if (is_ready_queue_empty(cpu_scheduler->ready_queue)) {
				return; 
			}
		}
	}
	
	if (g_next_arrival_time_index < data_size && arrival_times[g_next_arrival_time_index] == cpu_scheduler->timer) {
		uint32_t priority = get_priority(g_priority_classes[rand() % PRIORITY_CLASS_COUNT], g_relative_priorities[rand() % RELATIVE_PRIORITY_COUNT]);
		call_process(cpu_scheduler, g_next_arrival_time_index, priority);
		++g_next_arrival_time_index;
	}

	run_process(cpu_scheduler);

	for (queue_node_t* iter_node = get_front(cpu_scheduler->ready_queue); iter_node != NULL; iter_node = iter_node->next) {
		tick((process_control_block_t*) iter_node->item);
	}

	for (queue_node_t* iter_node = get_front(cpu_scheduler->wait_queue); iter_node != NULL; iter_node = iter_node->next) {
		tick((process_control_block_t*) iter_node->item);
	}

#ifdef DEBUG
	print_cpu_scheduler_debug_information(cpu_scheduler);
#endif
	cpu_scheduler->quantum_timer = (cpu_scheduler->quantum_timer + 1) % cpu_scheduler->time_quantum;
	++cpu_scheduler->timer;
}

e_scheduling_algorithm_t get_scheduling_algorithms(cpu_scheduler_t* cpu_scheduler)
{
	return cpu_scheduler->scheduling_algorithm;
}

void set_scheduling_algorithms(cpu_scheduler_t* cpu_scheduler, e_scheduling_algorithm_t scheduling_algorithm)
{
	cpu_scheduler->scheduling_algorithm = scheduling_algorithm;
}

void set_time_quantum(cpu_scheduler_t* cpu_scheduler, uint32_t time_quantum)
{
	cpu_scheduler->time_quantum = time_quantum;
}

uint32_t get_time_quantum(cpu_scheduler_t* cpu_scheduler)
{
	return cpu_scheduler->time_quantum;
}

#ifdef DEBUG
#include <string.h>

void print_cpu_scheduler_debug_information(cpu_scheduler_t* cpu_scheduler)
{
	printf("============CPU INFO============\n");
	printf("* TIMER: %4u %2u/%2u        *\n", cpu_scheduler->timer, cpu_scheduler->quantum_timer, cpu_scheduler->time_quantum);
	if (cpu_scheduler->current_process != NULL) {
		printf("* CURRENT PROCESS:         *\n");
		print_process_debug_information(cpu_scheduler->current_process);
	}
	if (!is_ready_queue_empty(cpu_scheduler->ready_queue)) {
		printf("* NEXT PROCESS:            *\n");
		print_process_debug_information((process_control_block_t*) get_front(cpu_scheduler->ready_queue)->item);
		printf("* READY QUEUE:             *\n");
		uint64_t counter = 0;
		int length = 0;
		char line[27] = { '\0', };
 		for (queue_node_t* iter = get_front(cpu_scheduler->ready_queue); iter != NULL; iter = iter->next, ++counter) {
			if (counter % 3 == 0) {
#ifdef WIN32
				strncpy_s(line, sizeof(line), "* ", 3);
#else
				strncpy(line, "* ", 3);
#endif
				length = 2;
			}
#ifdef WIN32
			length += sprintf_s(line + length, sizeof(line) - length, "%5llu ->", get_process_id((process_control_block_t*) iter->item));
#else
			length += sprintf(line + length, "%5llu ->", get_process_id((process_control_block_t*) iter->item));
#endif
			// printf("\ncoutner: %ld, length: %d, string: %s\n", counter, length, line);
			if (counter % 3 == 2) {
				printf("%s", line);
				printf(" *\n");
				memset(line, 0, sizeof(line) / sizeof(line[0]));
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
#ifdef WIN32
				strncpy_s(line, sizeof(line), "* ", 3);
#else
				strncpy(line, "* ", 3);
#endif
				length = 2;
			}
#ifdef WIN32
			length += sprintf_s(line + length, sizeof(line) - length, "%5llu ->", get_process_id((process_control_block_t*) iter->item));
#else
			length += sprintf(line + length, "%5llu ->", get_process_id((process_control_block_t*) iter->item));
#endif
			// printf("\ncoutner: %ld, length: %d, string: %s\n", counter, length, line);
			if (counter % 3 == 2) {
				printf("%s", line);
				printf(" *\n");
				memset(line, 0, sizeof(line) / sizeof(line[0]));
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

void test(e_scheduling_algorithm_t scheduling_algorithm, uint32_t time_quantum)
{
	srand((unsigned int) time(NULL));

	job_queue_t* job_queue = create_job_queue_malloc();
	cpu_scheduler_t* cpu_scheduler = create_cpu_scheduler_malloc(job_queue);
	set_scheduling_algorithms(cpu_scheduler, scheduling_algorithm);
	set_time_quantum(cpu_scheduler, time_quantum);

	uint64_t call_process_count = (uint64_t) rand() % get_size_of_job_queue(cpu_scheduler->job_queue) + 1;
	for (uint64_t i = 0; i < call_process_count; ++i) {
		uint32_t priority = get_priority(g_priority_classes[rand() % PRIORITY_CLASS_COUNT], g_relative_priorities[rand() % RELATIVE_PRIORITY_COUNT]);
		call_process(cpu_scheduler, (uint64_t) rand() % get_size_of_job_queue(cpu_scheduler->job_queue), priority);
	}

	printf("SCHEDULING ALGORITHM: ");
	switch (scheduling_algorithm)
	{
	case FCFS:
		printf("First Come, First Served (FCFS)\n");
		break;
	case PREEMPTIVE_SJF:
		printf("Preemptive Shortest Job First (SJF)\n");
		break;
	case ROUND_ROBIN_WITH_TIME_QUANTUM:
		printf("Round Robin with Time Quantum = %u\n", time_quantum);
		break;
	default:
		assert(false);
		break;
	}
	printf("PROCESS COUNT: %llu\n", call_process_count);
#ifdef DEBUG
	print_job_queue_debug_information(cpu_scheduler->job_queue);
	print_cpu_scheduler_debug_information(cpu_scheduler);
#endif
	/* test loop */
	do {
		update(cpu_scheduler);
	} while (!is_wait_queue_empty(cpu_scheduler->wait_queue) || !is_ready_queue_empty(cpu_scheduler->ready_queue));

	if (cpu_scheduler->current_process != NULL) {
		exit_process(cpu_scheduler);
	}

#ifdef DEBUG
	print_cpu_scheduler_debug_information(cpu_scheduler);
#endif

	printf("Average Waiting Time: %f\n", (float) cpu_scheduler->total_waiting_time / (float) call_process_count);
	destroy_cpu_scheduler(cpu_scheduler);
	cpu_scheduler = NULL;
}

void test_with_data(process_control_block_t** test_set, uint64_t data_size, e_scheduling_algorithm_t scheduling_algorithm, uint32_t time_quantum)
{
	srand((unsigned int) time(NULL));

	g_next_arrival_time_index = 0u;
	uint32_t* arrival_times = (uint32_t*) malloc(sizeof(uint32_t) * data_size);
	for (uint64_t i = 0; i < data_size; ++i) {
		arrival_times[i] = get_process_arrival_time(test_set[i]);
	}

	job_queue_t* job_queue = create_job_queue_with_data_malloc(test_set, data_size);
	cpu_scheduler_t* cpu_scheduler = create_cpu_scheduler_malloc(job_queue);
	set_scheduling_algorithms(cpu_scheduler, scheduling_algorithm);
	set_time_quantum(cpu_scheduler, time_quantum);

	printf("SCHEDULING ALGORITHM: ");
	switch (scheduling_algorithm)
	{
	case FCFS:
		printf("First Come, First Served (FCFS)\n");
		break;
	case PREEMPTIVE_SJF:
		printf("Preemptive Shortest Job First (SJF)\n");
		break;
	case ROUND_ROBIN_WITH_TIME_QUANTUM:
		printf("Round Robin with Time Quantum = %u\n", time_quantum);
		break;
	default:
		assert(false);
		break;
	}
	printf("PROCESS COUNT: %llu\n", data_size);
#ifdef DEBUG
	print_job_queue_debug_information(cpu_scheduler->job_queue);
	print_cpu_scheduler_debug_information(cpu_scheduler);
#endif
	/* test loop */
	do {
		update_by_test_data(cpu_scheduler, arrival_times, data_size);
	} while (cpu_scheduler->current_process != NULL || (!is_wait_queue_empty(cpu_scheduler->wait_queue) || !is_ready_queue_empty(cpu_scheduler->ready_queue)));

	if (cpu_scheduler->current_process != NULL) {
		exit_process(cpu_scheduler);
	}

#ifdef DEBUG
	print_cpu_scheduler_debug_information(cpu_scheduler);
#endif

	printf("Average Waiting Time: %f\n", (float) cpu_scheduler->total_waiting_time / (float) data_size);
	destroy_cpu_scheduler(cpu_scheduler);
	cpu_scheduler = NULL;
}
#endif