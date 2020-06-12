#include <assert.h>
#include <stdlib.h>

#include "stack.h"

struct node_type {
	struct node_type* next;
	item_t item;
};

struct stack_type {
	node_t top;
	node_t front;
	size_t size;
};

stack_t create_malloc(void)
{
	stack_t pa_stack = (stack_t) malloc(sizeof(struct stack_type));
	if (pa_stack == NULL) {
		return NULL;
	}
	pa_stack->top = NULL;
	pa_stack->front = NULL;
	pa_stack->size = 0;
	return pa_stack;
}

void destroy(stack_t* stack)
{
	if (*stack != NULL) {
		make_empty(*stack);
		free(*stack);
		*stack = NULL;
	}
}

bool push_back_malloc(stack_t stack, item_t item)
{
	if (stack == NULL) {
		return false;
	}

	node_t pa_new_node = (node_t) malloc(sizeof(struct node_type));
	if (pa_new_node == NULL) {
		return false;
	}

	if (stack->front == NULL) {
		stack->front = pa_new_node;
	}

	pa_new_node->item = item;
	pa_new_node->next = stack->top;
	stack->top = pa_new_node;
	++stack->size;
	
	return true;
}

item_t pop(stack_t out_stack)
{
	assert(out_stack != NULL);
	if (is_empty(out_stack)) {
		return NULL;
	}

	item_t out_item = out_stack->top->item;
	node_t node_to_delete = out_stack->top;
	out_stack->top = out_stack->top->next;
	if (out_stack->top == NULL) {
		out_stack->front = NULL;
	}
	free(node_to_delete);
	node_to_delete = NULL;
	--out_stack->size;

	return out_item;
}

bool is_empty(stack_t stack)
{
	if (stack == NULL) {
		return true;
	}

	return (stack->size == 0);
}

void make_empty(stack_t stack)
{
	while (!is_empty(stack)) {
		pop(stack);
	}
}

bool delete(stack_t stack, item_t item)
{
	if (stack == NULL) {
		return false;
	}
	
	node_t prev_node = NULL;
	node_t cur_node = stack->top;

	for (; cur_node != NULL; prev_node = cur_node, cur_node= cur_node->next) {
		if (cur_node->item == item) {
			if (prev_node != NULL) {
				prev_node->next = cur_node->next;
				if (cur_node == stack->front) {
					stack->front = prev_node;
				}
			} else {
				stack->top = cur_node->next;
			}

			free(cur_node);
			--stack->size;
			return true;
		}
	}

	return false;
}

bool insert_after_malloc(stack_t stack, node_t node, item_t item)
{
	if (node == NULL || stack == NULL) {
		return false;
	}
	
	node_t prev_node = NULL;
	node_t cur_node = stack->top;

	node_t new_node = (node_t) malloc(sizeof(struct node_type));
	if (new_node == NULL) {
		return false;
	}
	new_node->item = item;

	for (; cur_node != NULL; prev_node = cur_node, cur_node= cur_node->next) {
		if (prev_node == node) {
			if (prev_node != NULL) {
				prev_node->next = new_node;
			}
			new_node->next = cur_node;
			++stack->size;

			return true;
		}
	}

	return false;
}

size_t length(stack_t stack)
{
	if (stack == NULL) {
		return 0;
	}

	return stack->size;
}
