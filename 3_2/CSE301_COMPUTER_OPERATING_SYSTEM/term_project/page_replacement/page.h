#pragma once

#include "build_settings.h"

#include <stdint.h>

#define PAGE_SIZE (32llu)

typedef struct 
{
    uint8_t bytes[PAGE_SIZE];
} page_t;

page_t* create_page_malloc();
void destroy_page(page_t* page);