#ifdef WIN32
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include <stdio.h>

#include "cpu_scheduler.h"

#define TEST_PROCESS_COUNT (6ul)

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
#endif

	// test(FCFS, 1u);
	// test(PREEMPTIVE_SJF, 1u);
	// test(ROUND_ROBIN_WITH_TIME_QUANTUM, 3u);

	{
		process_control_block_t* processes[TEST_PROCESS_COUNT] = { NULL, };

		processes[0] = create_process_malloc(~0u, 10u);
		set_process_arrival_time(processes[0], 0u);
		set_process_burst_time(processes[0], 10u);

		processes[1] = create_process_malloc(~0u, 12u);
		set_process_arrival_time(processes[1], 3u);
		set_process_burst_time(processes[1], 12u);

		processes[2] = create_process_malloc(~0u, 4u);
		set_process_arrival_time(processes[2], 7u);
		set_process_burst_time(processes[2], 4u);

		processes[3] = create_process_malloc(~0u, 6u);
		set_process_arrival_time(processes[3], 10u);
		set_process_burst_time(processes[3], 6u);

		processes[4] = create_process_malloc(~0u, 10u);
		set_process_arrival_time(processes[4], 14u);
		set_process_burst_time(processes[4], 8u);

		processes[5] = create_process_malloc(~0u, 10u);
		set_process_arrival_time(processes[5], 15u);
		set_process_burst_time(processes[5], 7u);

		test_with_data(processes, TEST_PROCESS_COUNT, FCFS, 1u);
	}
#ifdef WIN32
	_CrtDumpMemoryLeaks();
#endif
	
	{
		process_control_block_t* processes[TEST_PROCESS_COUNT] = { NULL, };

		processes[0] = create_process_malloc(~0u, 10u);
		set_process_arrival_time(processes[0], 0u);
		set_process_burst_time(processes[0], 10u);

		processes[1] = create_process_malloc(~0u, 12u);
		set_process_arrival_time(processes[1], 3u);
		set_process_burst_time(processes[1], 12u);

		processes[2] = create_process_malloc(~0u, 4u);
		set_process_arrival_time(processes[2], 7u);
		set_process_burst_time(processes[2], 4u);

		processes[3] = create_process_malloc(~0u, 6u);
		set_process_arrival_time(processes[3], 10u);
		set_process_burst_time(processes[3], 6u);

		processes[4] = create_process_malloc(~0u, 10u);
		set_process_arrival_time(processes[4], 14u);
		set_process_burst_time(processes[4], 8u);

		processes[5] = create_process_malloc(~0u, 10u);
		set_process_arrival_time(processes[5], 15u);
		set_process_burst_time(processes[5], 7u);

		test_with_data(processes, TEST_PROCESS_COUNT, PREEMPTIVE_SJF, 1u);
	}
#ifdef WIN32
	_CrtDumpMemoryLeaks();
#endif

	{
		process_control_block_t* processes[TEST_PROCESS_COUNT] = { NULL, };

		processes[0] = create_process_malloc(~0u, 10u);
		set_process_arrival_time(processes[0], 0u);
		set_process_burst_time(processes[0], 10u);

		processes[1] = create_process_malloc(~0u, 12u);
		set_process_arrival_time(processes[1], 3u);
		set_process_burst_time(processes[1], 12u);

		processes[2] = create_process_malloc(~0u, 4u);
		set_process_arrival_time(processes[2], 7u);
		set_process_burst_time(processes[2], 4u);

		processes[3] = create_process_malloc(~0u, 6u);
		set_process_arrival_time(processes[3], 10u);
		set_process_burst_time(processes[3], 6u);

		processes[4] = create_process_malloc(~0u, 10u);
		set_process_arrival_time(processes[4], 14u);
		set_process_burst_time(processes[4], 8u);

		processes[5] = create_process_malloc(~0u, 10u);
		set_process_arrival_time(processes[5], 15u);
		set_process_burst_time(processes[5], 7u);

		test_with_data(processes, TEST_PROCESS_COUNT, ROUND_ROBIN_WITH_TIME_QUANTUM, 3u);
	}
#ifdef WIN32
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}