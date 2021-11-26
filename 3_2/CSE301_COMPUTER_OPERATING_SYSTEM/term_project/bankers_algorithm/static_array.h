#ifndef STATIC_ARRAY_H
#define STATIC_ARRAY_H

#include <stdbool.h>
#include <stdint.h>

typedef struct static_array static_array_t;

static_array_t* create_array_malloc(uint64_t type_size, uint64_t capacity);
static_array_t* create_array_from_data_malloc(void* items, uint64_t type_size, uint64_t size);
void destroy_array(static_array_t* array);

bool copy_array(static_array_t* destination, static_array_t* source);

uint64_t get_capacity(static_array_t* array);
uint64_t get_size(static_array_t* array);
uint64_t get_type_size(static_array_t* array);
bool is_empty(static_array_t* array);
bool is_full(static_array_t* array);

bool add_item_at(static_array_t* array, void* item, uint64_t index);
bool add_item_in_front(static_array_t* array, void* item);
bool add_item_at_back(static_array_t* array, void* item);
bool set_item_at(static_array_t* array, void* item, uint64_t index);
void set_array(static_array_t* array, void* items, uint64_t size);
void clear(static_array_t* array);
void* get_item_at(static_array_t* array, uint64_t index);
void* remove_item_at(static_array_t* array, uint64_t index);

bool is_less_than_ui64(static_array_t* lhs, static_array_t* rhs);
bool is_equal_to_ui64(static_array_t* lhs, static_array_t* rhs);
bool is_less_or_equal_to_ui64(static_array_t* lhs, static_array_t* rhs);
bool add_ui64(static_array_t* destination, static_array_t* other);
bool sub_ui64(static_array_t* destination, static_array_t* other);
void negate_ui64(static_array_t* array);

void print_array_ui64(static_array_t* array);

#endif