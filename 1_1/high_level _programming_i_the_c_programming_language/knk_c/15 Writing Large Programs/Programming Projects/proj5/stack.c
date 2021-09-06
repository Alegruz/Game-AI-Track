#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

const int stack_size = 100;
int stack[stack_size];
int top = 0;

/**********************************************************
 * make_empty: Empties the stack by assigning 0 to top    *
 **********************************************************/
void make_empty(void) {
    top = 0;
}

/**********************************************************
 * is_empty: Returns whether the stack is empty           *
 **********************************************************/
bool is_empty(void) {
    return top == 0;
}

/**********************************************************
 * is_full: Returns whether the stack is full             *
 **********************************************************/
bool is_full(void) {
    return top == stack_size;
}

/**********************************************************
 * push: When the stack is not full, store ch into        *
 *       stack[top] then increment top.                   *
 **********************************************************/
void push(int ch) {
    if (is_full())
        stack_overflow();
    else
        stack[top++] = ch;
}

/**********************************************************
 * pop: When the stack is not empty, decrement top and    *
 *      return the item in its index                      *
 **********************************************************/
int pop(void) {
    if (is_empty()) {
        stack_underflow();
    }
    else
        return stack[--top];
}

/**********************************************************
 * stack_overflow: Prints warning message that stack is   *
 *                 currently full, unavailable to push    *
 **********************************************************/
void stack_overflow(void) {
    printf("\nExpression is too complex\n");
    exit(EXIT_SUCCESS);
}

/**********************************************************
 * stack_overflow: Prints warning message that stack is   *
 *                 currently empty, unavailable to pop    *
 **********************************************************/
void stack_underflow(void) {
    printf("\nNot enough operands in expression\n");
    exit(EXIT_SUCCESS);
}

/**********************************************************
 * is_in: Checks whether ch is in array a                 *
 **********************************************************/
bool is_in(const char a[], int n, char ch) {
    for (int i = 0; i < n; ++i) {
        if (ch == a[i])
            return true;
    }
    return false;
}
