#ifndef _CPU_SCHEDULER_H_
#define _CPU_SCHEDULER_H_

#include "build_settings.h"
#include "process_control_block.h"
#include "queue.h"

typedef enum
{
    FCFS,
    PREEMPTIVE_SJF,
    ROUND_ROBIN_WITH_TIME_QUANTUM,
    PRIORITY,
    SCHEDULING_ALGORITHM_COUNT,
} e_scheduling_algorithm_t;

typedef enum
{
    IDLE_PRIORITY_CLASS = 4,
    BELOW_NORMAL_PRIORITY_CLASS = 6,
    NORMAL_PRIORITY_CLASS = 8,
    ABOVE_NORMAL_PRIORITY_CLASS = 10,
    HIGH_PRIORITY_CLASS = 13,
    REAL_TIME_PRIORITY_CLASS = 24,
    PRIORITY_CLASS_COUNT = 6,
} e_priority_class_t;

typedef enum
{
    IDLE,
    LOWEST,
    BELOW_NORMAL,
    NORMAL,
    ABOVE_NORMAL,
    HIGHEST,
    TIME_CRITICAL, 
    RELATIVE_PRIORITY_COUNT,
} e_relative_priority_t;

extern const e_priority_class_t g_priority_classes[PRIORITY_CLASS_COUNT];
extern const e_relative_priority_t g_relative_priorities[RELATIVE_PRIORITY_COUNT];

typedef struct cpu_scheduler cpu_scheduler_t;

uint32_t get_priority(const e_priority_class_t priority_class, const e_relative_priority_t relative_priority);

cpu_scheduler_t* create_cpu_scheduler_malloc(job_queue_t* job_queue);
void destroy_cpu_scheduler(cpu_scheduler_t* cpu_scheduler);
void run_process(cpu_scheduler_t* cpu_scheduler);
void exit_process(cpu_scheduler_t* cpu_scheduler);
void save_process(cpu_scheduler_t* cpu_scheduler);
void ready_process(cpu_scheduler_t* cpu_scheduler);
void call_process(cpu_scheduler_t* cpu_scheduler, uint64_t index, uint32_t priority);
void sort_process(cpu_scheduler_t* cpu_scheduler);
void update(cpu_scheduler_t* cpu_scheduler);
void update_by_test_data(cpu_scheduler_t* cpu_scheduler, uint32_t* arrival_times, uint64_t data_size);
e_scheduling_algorithm_t get_scheduling_algorithms(cpu_scheduler_t* cpu_scheduler);
void set_scheduling_algorithms(cpu_scheduler_t* cpu_scheduler, e_scheduling_algorithm_t scheduling_algorithm);
void set_time_quantum(cpu_scheduler_t* cpu_scheduler, uint32_t time_quantum);
uint32_t get_time_quantum(cpu_scheduler_t* cpu_scheduler);

#ifdef DEBUG
void print_cpu_scheduler_debug_information(cpu_scheduler_t* cpu_scheduler);
#endif

#ifdef _TEST_ENABLED_
void test(e_scheduling_algorithm_t scheduling_algorithm, uint32_t time_quantum);
void test_with_data(process_control_block_t** test_set, uint64_t data_size, e_scheduling_algorithm_t scheduling_algorithm, uint32_t time_quantum);
#endif

#endif