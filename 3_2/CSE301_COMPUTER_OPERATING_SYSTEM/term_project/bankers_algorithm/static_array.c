#include "static_array.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct static_array
{
    uint64_t capacity;
    uint64_t size;
    uint64_t type_size;
    void* items;
};

static_array_t* create_array_malloc(uint64_t type_size, uint64_t capacity)
{
    static_array_t* array = (static_array_t*) malloc(sizeof(static_array_t));
    if (array == NULL) {
        printf("NOT ENOUGH MEMORY! Failed to allocated %llu bytes of memory!!", sizeof(static_array_t));
        assert(false);
    }
    memset(array, 0, sizeof(static_array_t));

    array->capacity = capacity;
    array->type_size = type_size;
    array->items = (void*) malloc(array->type_size * array->capacity);
    if (array->items == NULL) {
        printf("NOT ENOUGH MEMORY! Failed to allocated %llu bytes of memory!!", array->type_size * array->capacity);
        assert(false);
    }
    memset(array->items, 0, array->type_size * array->capacity);

    return array;
}

static_array_t* create_array_from_data_malloc(void* items, uint64_t type_size, uint64_t size)
{
    static_array_t* array = (static_array_t*) malloc(sizeof(static_array_t));
    if (array == NULL) {
        printf("NOT ENOUGH MEMORY! Failed to allocated %llu bytes of memory!!", sizeof(static_array_t));
        assert(false);
    }
    memset(array, 0, sizeof(static_array_t));

    array->capacity = size;
    array->type_size = type_size;
    array->items = (void*) malloc(array->type_size * array->capacity);
    if (array->items == NULL) {
        printf("NOT ENOUGH MEMORY! Failed to allocated %llu bytes of memory!!", array->type_size * array->capacity);
        assert(false);
    }
    memset(array->items, 0, array->type_size * array->capacity);

    for (uint64_t i = 0ul; i < array->capacity; ++i) {
#ifdef WIN32
        memcpy_s(((uint8_t*) array->items) + i * array->type_size, array->type_size, ((uint8_t*) items) + i * type_size, type_size);
#else
        memcpy_s(((uint8_t*) array->items) + i * array->type_size, ((uint8_t*) items) + i * type_size, type_size);
#endif
        ++(array->size);
    }

    return array;
}

void destroy_array(static_array_t* array)
{
    if (array != NULL) {
        if (array->items != NULL) {
            free(array->items);
            array->items = NULL;
        }

        free(array);
    }
}

bool copy_array(static_array_t* destination, static_array_t* source)
{
    if (destination->capacity != source->capacity) {
        return false;
    }

#ifdef WIN32
    memcpy_s(destination->items, destination->type_size * destination->capacity, source->items, source->type_size * source->size);
#else
    memcpy(destination->items, source->items, source->type_size * source->size);
#endif

    destination->type_size = source->type_size;
    destination->size = source->size;

    return true;
}

uint64_t get_capacity(static_array_t* array)
{
    return array->capacity;
}

uint64_t get_size(static_array_t* array)
{
    return array->size;
}

uint64_t get_type_size(static_array_t* array)
{
    return array->type_size;
}

bool is_empty(static_array_t* array)
{
    return array->size == 0ul;
}

bool is_full(static_array_t* array)
{
    return array->size == array->capacity;
}

bool add_item_at(static_array_t* array, void* item, uint64_t index)
{
    if (array->size > array->capacity - 1) {
        return false;
    }

    for (uint64_t i = array->size; i > index; --i) {
        // array->items[i] = array->items[i - 1];
#ifdef WIN32
        memcpy_s(((uint8_t*) array->items) + i * array->type_size, 
                 array->type_size, 
                 ((uint8_t*) array->items) + (i - 1) * array->type_size, 
                 array->type_size);
#else
        memcpy(((uint8_t*) array->items) + i * array->type_size, 
               ((uint8_t*) array->items) + (i - 1) * array->type_size, 
               array->type_size);
#endif
    }
#ifdef WIN32
    memcpy_s(((uint8_t*) array->items) + index * array->type_size, 
                 array->type_size, 
                 item, 
                 array->type_size);
#else
    memcpy(((uint8_t*) array->items) + index * array->type_size, 
           item, 
           array->type_size);
#endif
    ++(array->size);

    return true;
}

bool add_item_in_front(static_array_t* array, void* item)
{
    return add_item_at(array, item, 0ul);
}

bool add_item_at_back(static_array_t* array, void* item)
{
    return add_item_at(array, item, array->size);
}

bool set_item_at(static_array_t* array, void* item, uint64_t index)
{
    assert(array != NULL);

    if (index >= array->size) {
        return false;
    }

#ifdef WIN32
    memcpy_s((void*) (((uint8_t*) array->items) + index * array->type_size), 
             array->type_size, 
             item, 
             array->type_size);
#else
    memcpy((void*) (((uint8_t*) array->items) + index * array->type_size), 
           array->type_size, 
           item, 
           array->type_size);
#endif
    return true;
}

void set_array(static_array_t* array, void* items, uint64_t size)
{
    memset(array->items, 0, array->type_size * array->size);

    array->size = 0;
#ifdef WIN32
    memcpy_s(array->items, array->type_size * array->type_size, items, array->type_size * size);
#else
    memcpy(array->items, items, array->type_size * size);
#endif
    array->size = size;
}

void clear(static_array_t* array)
{
    memset(array->items, 0, array->type_size * array->capacity);
    array->size = 0ul;
}

void* get_item_at(static_array_t* array, uint64_t index)
{
    if (index >= array->size) {
        return NULL;
    }

    // return array->items[index];
    return (void*) (((uint8_t*) array->items) + index * array->type_size);
}

void* remove_item_at(static_array_t* array, uint64_t index)
{
    if (index >= array->size) {
        return NULL;
    }

    void* item = malloc(sizeof(array->type_size));
#ifdef WIN32
        memcpy_s(item, 
                 array->type_size, 
                 ((uint8_t*) array->items) + index * array->type_size, 
                 array->type_size);
#else
        memcpy(item, 
               ((uint8_t*) array->items) + index * array->type_size, 
               array->type_size);
#endif

    for (uint64_t i = index; i < array->size - 1; ++i) {
#ifdef WIN32
        memcpy_s(((uint8_t*) array->items) + i * array->type_size, 
                 array->type_size, 
                 ((uint8_t*) array->items) + (i + 1) * array->type_size, 
                 array->type_size);
#else
        memcpy(((uint8_t*) array->items) + i * array->type_size, 
                ((uint8_t*) array->items) + (i + 1) * array->type_size, 
                array->type_size);
#endif
    }
#ifdef WIN32
        memcpy_s(((uint8_t*) array->items) + (array->size - 1) * array->type_size, 
                 array->type_size, 
                 item, 
                 array->type_size);
#else
        memcpy(((uint8_t*) array->items) + (array->size - 1) * array->type_size, 
               item, 
               array->type_size);
#endif
    --(array->size);

    return (void*) (((uint8_t*) array->items) + array->size * array->type_size);
}

bool is_less_than_ui64(static_array_t* lhs, static_array_t* rhs)
{
    if (get_size(lhs) != get_size(rhs)) {
        return false;
    }

    for (uint64_t i = 0ull; i < get_size(lhs); ++i) {
        if (*((uint64_t*) get_item_at(lhs, i)) >= *((uint64_t*) get_item_at(rhs, i))) {
            return false;
        }
    }

    return true;
}

bool is_equal_to_ui64(static_array_t* lhs, static_array_t* rhs)
{
    if (get_size(lhs) != get_size(rhs)) {
        return false;
    }

    for (uint64_t i = 0ull; i < get_size(lhs); ++i) {
        if (*((uint64_t*) get_item_at(lhs, i)) != *((uint64_t*) get_item_at(rhs, i))) {
            return false;
        }
    }

    return true;
}

bool is_less_or_equal_to_ui64(static_array_t* lhs, static_array_t* rhs)
{
    if (get_size(lhs) != get_size(rhs)) {
        // printf("lhs size: %llu, rhs size: %llu\n", get_size(lhs), get_size(rhs));
        return false;
    }

    for (uint64_t i = 0ull; i < get_size(lhs); ++i) {
        // printf("[%llu] %llu <= %llu\n", i, *((uint64_t*) get_item_at(lhs, i)), *((uint64_t*) get_item_at(rhs, i)));
        if (*((uint64_t*) get_item_at(lhs, i)) > *((uint64_t*) get_item_at(rhs, i))) {
            return false;
        }
    }

    return true;
}

bool add_ui64(static_array_t* destination, static_array_t* other)
{
    if (get_size(destination) != get_size(other)) {
        return false;
    }

    for (uint64_t i = 0ull; i < get_size(destination); ++i) {
        *((uint64_t*) (((uint8_t*) destination->items) + i * destination->type_size)) += *((uint64_t*) (((uint8_t*) other->items) + i * other->type_size));
    }

    return true;
}

bool sub_ui64(static_array_t* destination, static_array_t* other)
{
    if (get_size(destination) != get_size(other)) {
        return false;
    }

    for (uint64_t i = 0ull; i < get_size(destination); ++i) {
        *((uint64_t*) (((uint8_t*) destination->items) + i * destination->type_size)) -= *((uint64_t*) (((uint8_t*) other->items) + i * other->type_size));
    }

    return true;
}

void print_array_ui64(static_array_t* array)
{
    assert(sizeof(uint64_t) == array->type_size);
    printf("array={ capacity=%llu, size=%llu, type_size=%llu, items={\n", array->capacity, array->size, array->type_size);

    for (uint64_t i = 0llu; i < array->size; ++i) {
        printf("\t[%llu]: %llu\n", i, *((uint64_t*) (((uint8_t*) array->items) + i * array->type_size)));
    }
    printf("} }\n");
}