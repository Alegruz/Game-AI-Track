#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "process_control_block.h"

#ifdef DEBUG
#include <stdio.h>
#endif

struct file
{
	char name[128];
};

struct io_device
{
	char name[128];
};

struct program_memory
{
	char text[1024];
	byte_t data[256];
	byte_t* initialized_data;
	byte_t* uninitialized_data;
	byte_t heap[1024];
	byte_t stack[1024];
	uint32_t argument_count;
	char* argument_vector;
};

struct register_set
{
	uint64_t eax;
	uint64_t ebx;
	uint64_t ecx;
	uint64_t edx;
};

struct process_control_block
{
	uint64_t id;
	/* process state */
	uint32_t state;
	/* program counter */
	void* program_counter;
	/* cpu registers */
	register_set_t registers;
	/* cpu scheduling information */
	int32_t priority;
	/* memory-management information */
	program_memory_t memory;
	/* accounting information */
	uint32_t cpu_use_count;
	uint32_t process_count;
	uint64_t runtime;
	uint64_t time_limit;
	uint64_t account_count;
	/* i/o status information */
	io_device_t* io_device_head;
	file_t* file_opened;

	uint32_t burst_time;
	uint32_t wait_time;
	uint32_t arrival_time;
};

process_control_block_t* create_process_malloc(uint64_t id, uint32_t priority)
{
	process_control_block_t* process = (process_control_block_t*) malloc(sizeof(process_control_block_t));
	assert(process != NULL);
	initialize_process(process, priority, (uint32_t) rand() % 5 + 1);
	process->id = id;
	
	return process;
}

void initialize_process(process_control_block_t* process, uint32_t priority, uint32_t burst_time)
{
	memset(process, 0, sizeof(process_control_block_t));
	process->state = NEW;
	process->priority = priority;
	process->burst_time = burst_time;
}

void destroy_process(process_control_block_t* process)
{
	free(process);
}

void set_process_state(process_control_block_t* process, e_process_state_t state)
{
	process->state = state;
}

uint64_t get_process_id(process_control_block_t* process)
{
	return process->id;
}

void set_process_id(process_control_block_t* process, uint64_t id)
{
	process->id = id;
}


uint32_t get_process_priority(process_control_block_t* process)
{
	return process->priority;
}

void set_process_priority(process_control_block_t* process, uint32_t priority)
{
	process->priority = priority;
}


uint32_t get_process_remaining_burst_time(process_control_block_t* process)
{
	return process->burst_time;
}

void set_process_burst_time(process_control_block_t* process, uint32_t burst_time)
{
	process->burst_time = burst_time;
}

void run_process_for_single_time_step(process_control_block_t* process)
{
	if (process->burst_time <= 0) {
#ifdef WIN32
		printf("wrong process id: %llu\n", process->id);
#else
		printf("wrong process id: %lu\n", process->id);
#endif
	}
	assert(process->burst_time > 0);
	--process->burst_time;
}

void tick(process_control_block_t* process)
{
	assert(process->burst_time > 0);
	switch (process->state)
	{
	case RUNNING:
		--process->burst_time;
		break;
	case READY:
		/* intentional fallthrough */
	case WAITING:
		++process->wait_time;
		break;
	default:
		break;
	}
}

uint32_t get_process_waiting_time(process_control_block_t* process)
{
	return process->wait_time;
}


uint32_t get_process_arrival_time(process_control_block_t* process)
{
	return process->arrival_time;
}

void set_process_arrival_time(process_control_block_t* process, uint32_t arrival_time)
{
	process->arrival_time = arrival_time;
}

#ifdef DEBUG
void print_process_debug_information(process_control_block_t* process)
{
	printf("========PROCESS INFO========\n");
#ifdef WIN32
	printf("* process id: %5llu        *\n", process->id);
#else
	printf("* process id: %5lu        *\n", process->id);
#endif
	printf("* process priority: %2u     *\n", process->priority);
	printf("* state: ");

	switch (process->state)
	{
	case NEW:
		printf("NEW               *\n");
		break;
	case RUNNING:
		printf("RUNNING           *\n");
		break;
	case WAITING:
		printf("WAITING           *\n");
		break;
	case READY:
		printf("READY             *\n");
		break;
	case TERMINATED:
		printf("TERMINATED        *\n");
		break;
	default:
		printf("INVALID STATE     *\n");
		break;
	}
	
	printf("* remaining time step: %2u  *\n", process->burst_time);
	printf("* waiting time: %2u         *\n", process->wait_time);
	printf("* arrival time: %2u         *\n", process->arrival_time);
	printf("============================\n");
}
#endif