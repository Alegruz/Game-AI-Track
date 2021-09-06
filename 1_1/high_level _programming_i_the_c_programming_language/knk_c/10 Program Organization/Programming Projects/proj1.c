/* Modify the stack example of Section 10.2 to store characters instead of integers */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int stack_size = 100;
char stack[stack_size];
int top = 0;

/* prototypes */
void make_empty(void);
bool is_empty(void);
bool is_full(void);
void push(char ch);
char pop(void);
void stack_overflow(void);
void stack_underflow(void);
bool is_in(char a[], int n, char ch);

/**********************************************************
 * main: Asks the user to enter a series of parentheses   *
 *       and/or braces, then indicates whether or not     *
 *       they're properly nested.                         *
 **********************************************************/
int main(void) {
    char ch;
    char open[] = {'(', '[', '{', '<'};
    char close[] = {')', ']', '}', '>'};

    printf("Enter parentheses and/or braces: ");
    for (;;) {
        ch = getchar();
        if (is_in(open, 4, ch))
            push(ch);
        else if (is_in(close, 4, ch)) {
            char temp = pop();
            int brace_index;
            switch (temp) {
            case '(': brace_index = 0; break;
            case '[': brace_index = 1; break;
            case '{': brace_index = 2; break;
            case '<': brace_index = 3; break;
            default:                   break;
            }
            if (close[brace_index] != ch)
                push(temp);
        }

        if (ch == '\n')
            break;
    }

    printf("Parentheses/braces are ");
    if (!is_empty())
            printf("not ");
    printf("nested properly\n");

    return 0;
}

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
void push(char ch) {
    if (is_full())
        stack_overflow();
    else
        stack[top++] = ch;
}

/**********************************************************
 * pop: When the stack is not empty, decrement top and    *
 *      return the item in its index                      *
 **********************************************************/
char pop(void) {
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
    printf("\nTHE STACK IS FULL!! PUSH UNAVAILABLE!! STACK OVERFLOW!!\n");
    exit(EXIT_SUCCESS);
}

/**********************************************************
 * stack_overflow: Prints warning message that stack is   *
 *                 currently empty, unavailable to pop    *
 **********************************************************/
void stack_underflow(void) {
    printf("\nTHE STACK IS EMPTY!! POP UNAVAILABLE!! STACK UNDERFLOW!!\n");
    exit(EXIT_SUCCESS);
}

/**********************************************************
 * is_in: Checks whether ch is in array a                 *
 **********************************************************/
bool is_in(char a[], int n, char ch) {
    for (int i = 0; i < n; ++i) {
        if (ch == a[i])
            return true;
    }
    return false;
}
