#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int main(void)
{
	stack_t stack = create_malloc();
	assert(stack != NULL);
	assert(length(stack) == 0);
	assert(is_empty(stack));
	int item0 = 0;
	int item1 = 1;
	int item2 = 2;
	int item3 = 3;
	int item4 = 4;

	assert(push_back_malloc(stack, (item_t) &item0));
	assert(length(stack) == 1);
	assert(!is_empty(stack));
	assert(push_back_malloc(stack, (item_t) &item1));
	assert(length(stack) == 2);
	assert(!is_empty(stack));
	assert(push_back_malloc(stack, (item_t) &item2));
	assert(length(stack) == 3);
	assert(!is_empty(stack));
	assert(push_back_malloc(stack, (item_t) &item3));
	assert(length(stack) == 4);
	assert(!is_empty(stack));
	assert(push_back_malloc(stack, (item_t) &item4));
	assert(length(stack) == 5);
	assert(!is_empty(stack));

	destroy(&stack);
	assert(stack == NULL);
	assert(is_empty(stack));
	assert(!delete(stack, (item_t) &item1));

	return 0;
}