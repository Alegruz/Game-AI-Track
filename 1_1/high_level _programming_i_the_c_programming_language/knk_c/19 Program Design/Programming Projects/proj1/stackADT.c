/* Modify proj1.c from Chapter 10 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stackADT.h"

struct stack_type {
    Item *contents;
    int top;
    int size;
};

static void terminate(const char *message) {
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}

/**********************************************************
 * create: Creates a stack structure.                     *
 **********************************************************/
Stack create(int size) {
    Stack s = (Stack) malloc(sizeof(struct stack_type));
    if (s == NULL)
        terminate("Error in create: Stack could not be created.");

    s->contents = (Item *) malloc(size * sizeof(Item *));
    if (s->contents == NULL) {
        free(s->contents);
        terminate("Error in create: Contents could not be created.");
    }
    s->top = 0;
    s->size = size;
    return s;
}

/**********************************************************
 * destroy: Destroys the stack by freeing the memory      *
 **********************************************************/
void destroy(Stack s) {
    make_empty(s);
    free(s);
}

/**********************************************************
 * make_empty: Empties the stack by assigning 0 to top    *
 **********************************************************/
void make_empty(Stack s) {
    while (!is_empty(s))
        pop(s);
}

/**********************************************************
 * is_empty: Returns whether the stack is empty           *
 **********************************************************/
bool is_empty(Stack s) {
    return s->top == 0;
}

/**********************************************************
 * is_full: Returns whether the stack is full             *
 **********************************************************/
bool is_full(Stack s) {
    return s->size == s->top;
}

/**********************************************************
 * push: When the stack is not full, store ch into        *
 *       stack[top] then increment top.                   *
 **********************************************************/
void push(Stack s, Item i) {
    if (is_full(s))
        stack_overflow(s);

    s->contents[s->top++] = i;
}

/**********************************************************
 * pop: When the stack is not empty, decrement top and    *
 *      return the item in its index                      *
 **********************************************************/
Item pop(Stack s) {
    if (is_empty(s))
        terminate("Error in pop: Stack is empty.");

    return s->contents[--(s->top)];
}

/**********************************************************
 * stack_overflow: Prints warning message that stack is   *
 *                 currently full, unavailable to push    *
 **********************************************************/
Stack stack_overflow(Stack s) {
    printf("Stack is full. Doubling stack size...\n");
    s->size *= 2;
    s = (Stack) realloc(s, s->size * sizeof(struct stack_type));
    return s;
}

/**********************************************************
 * is_in: Checks whether ch is in array a                 *
 **********************************************************/
bool is_in(char a[], int n, Item i) {
    for (int j = 0; j < n; ++j) {
        if (i == a[j])
            return true;
    }
    return false;
}
