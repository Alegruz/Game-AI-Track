#ifndef STACKADT_H
#define STACKADT_H

#include <stdbool.h>

typedef struct stack_type *Stack;
typedef char Item;
int top = 0;

/* prototypes */
Stack create(int size);
void destroy(Stack s);
void make_empty(Stack s);
bool is_empty(Stack s);
bool is_full(Stack s);
void push(Stack s, Item i);
Item pop(Stack s);
Stack stack_overflow(Stack s);
bool is_in(char a[], int n, Item i);

#endif