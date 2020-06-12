#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef void* item_t;
typedef struct node_type* node_t;
typedef struct stack_type* stack_t;

stack_t create_malloc(void);
void destroy(stack_t* stack);
bool push_back_malloc(stack_t stack, item_t item);
item_t pop(stack_t out_stack);
bool is_empty(stack_t stack);
void make_empty(stack_t stack);
bool delete(stack_t stack, item_t item);
bool insert_after_malloc(stack_t stack, node_t node, item_t item);
size_t length(stack_t stack);

#endif	/* STACK_H */