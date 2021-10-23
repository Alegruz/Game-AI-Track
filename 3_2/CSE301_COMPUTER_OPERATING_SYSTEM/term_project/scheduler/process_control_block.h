#ifndef _PROCESS_CONTROL_BLOCK_H_
#define _PROCESS_CONTROL_BLOCK_H_

#include <stdint.h>

#include "build_settings.h"

typedef unsigned char byte_t;
typedef struct file file_t;
typedef struct io_device io_device_t;
typedef struct program_memory program_memory_t;
typedef struct register_set register_set_t;
typedef struct process_control_block process_control_block_t;

typedef enum
{
	NEW,
	RUNNING,
	WAITING,
	READY,
	TERMINATED,
	COUNT,
} e_process_state_t;

process_control_block_t* create_process_malloc(uint64_t id, uint32_t priority);
void initialize_process(process_control_block_t* process, uint32_t priority, uint32_t burst_time);
void destroy_process(process_control_block_t* process);
void set_process_state(process_control_block_t* process, e_process_state_t state);
uint64_t get_process_id(process_control_block_t* process);
void set_process_id(process_control_block_t* process, uint64_t id);
uint32_t get_process_priority(process_control_block_t* process);
void set_process_priority(process_control_block_t* process, uint32_t priority);
uint32_t get_process_remaining_burst_time(process_control_block_t* process);
void set_process_burst_time(process_control_block_t* process, uint32_t burst_time);
void run_process_for_single_time_step(process_control_block_t* process);
void tick(process_control_block_t* process);
uint32_t get_process_waiting_time(process_control_block_t* process);
uint32_t get_process_arrival_time(process_control_block_t* process);
void set_process_arrival_time(process_control_block_t* process, uint32_t arrival_time);

#ifdef DEBUG
void print_process_debug_information(process_control_block_t* process);
#endif

#endif