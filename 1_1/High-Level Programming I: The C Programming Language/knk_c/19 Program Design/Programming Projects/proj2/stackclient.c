/* Modify proj6.c from Chapter 10 */

#include <stdio.h>
#include <stdlib.h>
#include "stackADT.h"

/**********************************************************
 * main: Asks the user to enter a series of parentheses   *
 *       and/or braces, then indicates whether or not     *
 *       they're properly nested.                         *
 **********************************************************/
int main(void) {
    Item ch;
    const Item optr[] = {'+', '-', '*', '/', '='};
    const Item operand[] = {'0', '1', '2', '3', '4',
                           '5', '6', '7', '8', '9'};
    int value = 0;

    Stack s = create(100);

    for (;;) {
        printf("Enter an RPN expression: ");
        for (;;) {
            scanf(" %c", &ch);

            if (is_in(operand, 10, ch)) {
                push(s, ch - '0');
            } else if (is_in(optr, 5, ch)) {
                int oprnd1 = pop(s);
                if (ch == '=') {
                    value = oprnd1;
                    break;
                } else {
                    int oprnd2 = pop(s);
                    switch (ch) {
                    case '+': push(s, oprnd2 + oprnd1); break;
                    case '-': push(s, oprnd2 - oprnd1); break;
                    case '*': push(s, oprnd2 * oprnd1); break;
                    case '/': push(s, oprnd2 / oprnd1); break;
                    }
                }
            } else
                exit(EXIT_SUCCESS);
        }
        printf("Value of expression: %d\n", value);
    }

    return 0;
}