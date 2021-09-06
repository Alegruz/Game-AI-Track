/* Modify proj6.c from Chapter 10 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int stack_size = 100;
int stack[stack_size];
int top = 0;
const char optr[] = {'+', '-', '*', '/', '='};
const char operand[] = {'0', '1', '2', '3', '4',
                       '5', '6', '7', '8', '9'};
/* prototypes */
void make_empty(void);
bool is_empty(void);
bool is_full(void);
void push(int ch);
int pop(void);
void stack_overflow(void);
void stack_underflow(void);
bool is_in(const char a[], int n, char ch);
int evaluate_RPN_expression(const char *expression);

/**********************************************************
 * main: Asks the user to enter a series of parentheses   *
 *       and/or braces, then indicates whether or not     *
 *       they're properly nested.                         *
 **********************************************************/
int main(void) {
    char expression[stack_size] = {};

    for (;;) {
        printf("Enter an RPN expression: ");
        int expression_length = 0;
        for (; expression_length < stack_size && (expression[expression_length] = getchar()) != '\n'; ++expression_length)
            ;

        printf("Value of expression: %d\n", evaluate_RPN_expression(expression));
    }

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

/**********************************************************
 * evaluate_RPN_expression: returns the value of the RPN  *
 *                          expression                    *
 **********************************************************/
int evaluate_RPN_expression(const char *expression) {
    int value = 0;
    for (int i = 0; i < strlen(expression); ++i) {
        if (*(expression + i) != ' ')
            if (is_in(operand, 10, *(expression + i))) {
                push(*(expression + i) - '0');
            } else if (is_in(optr, 5, *(expression + i))) {
                int oprnd1 = pop();
                if (*(expression + i) == '=') {
                    value = oprnd1;
                    break;
                } else {
                    int oprnd2 = pop();
                    switch (*(expression + i)) {
                    case '+': push(oprnd2 + oprnd1); break;
                    case '-': push(oprnd2 - oprnd1); break;
                    case '*': push(oprnd2 * oprnd1); break;
                    case '/': push(oprnd2 / oprnd1); break;
                    }
                }
            } else
                exit(EXIT_SUCCESS);
    }
    return value;
}
