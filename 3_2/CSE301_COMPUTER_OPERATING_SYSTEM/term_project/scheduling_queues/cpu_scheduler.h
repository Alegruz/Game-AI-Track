#ifndef _CPU_SCHEDULER_H_
#define _CPU_SCHEDULER_H_

#include "build_settings.h"
#include "process_control_block.h"
#include "queue.h"

typedef struct cpu_scheduler cpu_scheduler_t;

cpu_scheduler_t* create_cpu_scheduler_malloc(job_queue_t* job_queue);
void destroy_cpu_scheduler(cpu_scheduler_t* cpu_scheduler);
void run_process(cpu_scheduler_t* cpu_scheduler);
void exit_process(cpu_scheduler_t* cpu_scheduler);
void save_process(cpu_scheduler_t* cpu_scheduler);
void ready_process(cpu_scheduler_t* cpu_scheduler);
void update(cpu_scheduler_t* cpu_scheduler);

#ifdef _DEBUG_MODE_
void print_cpu_scheduler_debug_information(cpu_scheduler_t* cpu_scheduler);
#endif

#ifdef _TEST_ENABLED_
void test();
#endif

#endif