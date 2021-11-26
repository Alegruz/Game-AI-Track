#ifdef WIN32
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include <stdio.h>

#include "system.h"
#include "thread.h"

#define NUM_THREADS (5ull)
#define NUM_RESOURCES (3ull)

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

	int n, m, i, j, k;
    n = 5; // Number of processes
    m = 3; // Number of resources
    int alloc[5][3] = { { 0, 1, 0 }, // P0    // Allocation Matrix
                        { 2, 0, 0 }, // P1
                        { 3, 0, 2 }, // P2
                        { 2, 1, 1 }, // P3
                        { 0, 0, 2 } }; // P4
  
    int max[5][3] = { { 7, 5, 3 }, // P0    // MAX Matrix
                      { 3, 2, 2 }, // P1
                      { 9, 0, 2 }, // P2
                      { 2, 2, 2 }, // P3
                      { 4, 3, 3 } }; // P4
  
    int avail[3] = { 3, 3, 2 }; // Available Resources
  
    int f[5], ans[5], ind = 0;
    for (k = 0; k < n; k++) {
        f[k] = 0;
    }
    int need[5][3];
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }
    int y = 0;
    for (k = 0; k < 5; k++) {
        for (i = 0; i < n; i++) {
            if (f[i] == 0) {
  
                int flag = 0;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]){
                        flag = 1;
                         break;
                    }
                }
  
                if (flag == 0) {
                    ans[ind++] = i;
                    for (y = 0; y < m; y++)
                        avail[y] += alloc[i][y];
                    f[i] = 1;
                }
            }
        }
    }
  
    printf("Following is the SAFE Sequence\n");
    for (i = 0; i < n - 1; i++)
        printf(" P%d ->", ans[i]);
    printf(" P%d\n", ans[n - 1]);

	test();
#ifdef WIN32
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}

void test(void)
{
    // {
    //     system_t* system = create_system_malloc(NUM_RESOURCES, NUM_THREADS);
    //     uint64_t available[NUM_RESOURCES] = { 3, 3, 2 };
    //     uint64_t allocations[NUM_THREADS][NUM_RESOURCES] = { { 0, 1, 0 }, 
    //                                                         { 2, 0, 0 }, 
    //                                                         { 3, 0, 2 }, 
    //                                                         { 2, 1, 1 }, 
    //                                                         { 0, 0, 2 } };
    //     uint64_t max[NUM_THREADS][NUM_RESOURCES] = { { 7, 5, 3 }, 
    //                                                 { 3, 2, 2 }, 
    //                                                 { 9, 0, 2 }, 
    //                                                 { 2, 2, 2 }, 
    //                                                 { 4, 3, 3 } };

    //     // initialize available												 
    //     set_available(system, available);

    //     // initialize max and allocation
    //     for (uint64_t threadIdx = 0llu; threadIdx < NUM_THREADS; ++threadIdx) {
    //         set_thread_allocation(system, threadIdx, allocations[threadIdx]);
    //         set_thread_max(system, threadIdx, max[threadIdx]);
    //     }

    //     // initialize need
    //     for (uint64_t threadIdx = 0llu; threadIdx < NUM_THREADS; ++threadIdx) {
    //         initialize_needs(*((thread_t**) get_item_at(system->threads, threadIdx)));
    //     }

    //     // is_system_safe(system);
    //     static_array_t* request_array = create_array_malloc(sizeof(uint64_t), 3llu);
    //     uint64_t item = 1llu;
    //     add_item_at_back(request_array, &item);
    //     item = 0llu;
    //     add_item_at_back(request_array, &item);
    //     item = 2llu;
    //     add_item_at_back(request_array, &item);

    //     if (request_by_index(system, request_array, 1llu)) {
    //         is_system_safe(system);
    //         reverse_request_by_index(system, request_array, 1llu);
    //     }

    //     item = 3llu;
    //     set_item_at(request_array, &item, 0llu);
    //     item = 3llu;
    //     set_item_at(request_array, &item, 1llu);
    //     item = 0llu;
    //     set_item_at(request_array, &item, 2llu);

    //     if (request_by_index(system, request_array, 4llu)) {
    //         is_system_safe(system);
    //         reverse_request_by_index(system, request_array, 4llu);
    //     }

    //     // print_system(system);

    //     item = 0llu;
    //     set_item_at(request_array, &item, 0llu);
    //     item = 2llu;
    //     set_item_at(request_array, &item, 1llu);
    //     item = 0llu;
    //     set_item_at(request_array, &item, 2llu);

    //     if (request_by_index(system, request_array, 0llu)) {
    //         is_system_safe(system);
    //         reverse_request_by_index(system, request_array, 0llu);
    //     }
        
    //     // print_system(system);

    //     destroy_system(system);
    // }

    {
        system_t* system = create_system_malloc(NUM_RESOURCES + 1llu, NUM_THREADS);
        uint64_t available[NUM_RESOURCES + 1llu] = { 3, 2, 1, 1 };
        uint64_t allocations[NUM_THREADS][NUM_RESOURCES + 1llu] = { { 4, 0, 0, 1 }, 
                                                                    { 1, 1, 0, 0 }, 
                                                                    { 1, 2, 5, 4 }, 
                                                                    { 0, 6, 3, 3 }, 
                                                                    { 0, 2, 1, 2 } };
        uint64_t max[NUM_THREADS][NUM_RESOURCES + 1llu] = { { 6, 0, 1, 2 }, 
                                                            { 1, 7, 5, 0 }, 
                                                            { 2, 3, 5, 6 }, 
                                                            { 1, 6, 5, 3 }, 
                                                            { 1, 6, 5, 6 } };

        // initialize available												 
        set_available(system, available);

        // initialize max and allocation
        for (uint64_t threadIdx = 0llu; threadIdx < NUM_THREADS; ++threadIdx) {
            set_thread_allocation(system, threadIdx, allocations[threadIdx]);
            set_thread_max(system, threadIdx, max[threadIdx]);
        }

        // initialize need
        for (uint64_t threadIdx = 0llu; threadIdx < NUM_THREADS; ++threadIdx) {
            initialize_needs(*((thread_t**) get_item_at(system->threads, threadIdx)));
        }

        print_system(system);

        is_system_safe(system);

        static_array_t* request_array = create_array_malloc(sizeof(uint64_t), NUM_RESOURCES + 1llu);
        uint64_t item = 1llu;
        add_item_at_back(request_array, &item);
        item = 2llu;
        add_item_at_back(request_array, &item);
        item = 0llu;
        add_item_at_back(request_array, &item);
        item = 0llu;
        add_item_at_back(request_array, &item);

        if (request_by_index(system, request_array, 4llu)) {
            is_system_safe(system);
            reverse_request_by_index(system, request_array, 4llu);
        }
        
        // print_system(system);

        destroy_system(system);
    }
}