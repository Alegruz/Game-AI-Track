#include "page.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#ifdef DEBUG
    #include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>

page_t* create_page_malloc()
{
    page_t* page = (page_t*) malloc(sizeof(page_t));
    if (page == NULL) {
#ifdef DEBUG
        printf("Not enough memory to allocate page of %llu bytes!!\n", sizeof(page_t));
#endif
        assert(false);
    }
// #ifdef DEBUG
//         printf("Allocated page %p\n", page);
// #endif
    memset(page, 0, sizeof(page_t));

    return page;
}

void destroy_page(page_t* page)
{
    if (page != NULL) {
        free(page);

// #ifdef DEBUG
//         printf("Freed page %p\n", page);
// #endif
    }
}