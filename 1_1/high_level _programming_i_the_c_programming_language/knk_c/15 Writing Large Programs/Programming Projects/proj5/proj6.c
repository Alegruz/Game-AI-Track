/* RPN Expression Calculator */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

/**********************************************************
 * main: Asks the user to enter a series of parentheses   *
 *       and/or braces, then indicates whether or not     *
 *       they're properly nested.                         *
 **********************************************************/
int main(void) {
    char ch;
    const char optr[] = {'+', '-', '*', '/', '='};
    const char operand[] = {'0', '1', '2', '3', '4',
                           '5', '6', '7', '8', '9'};
    int value = 0;

    for (;;) {
        printf("Enter an RPN expression: ");
        for (;;) {
            scanf(" %c", &ch);

            if (is_in(operand, 10, ch)) {
                push(ch - '0');
            } else if (is_in(optr, 5, ch)) {
                int oprnd1 = pop();
                if (ch == '=') {
                    value = oprnd1;
                    break;
                } else {
                    int oprnd2 = pop();
                    switch (ch) {
                    case '+': push(oprnd2 + oprnd1); break;
                    case '-': push(oprnd2 - oprnd1); break;
                    case '*': push(oprnd2 * oprnd1); break;
                    case '/': push(oprnd2 / oprnd1); break;
                    }
                }
            } else
                exit(EXIT_SUCCESS);
        }
        printf("Value of expression: %d\n", value);
    }

    return 0;
}