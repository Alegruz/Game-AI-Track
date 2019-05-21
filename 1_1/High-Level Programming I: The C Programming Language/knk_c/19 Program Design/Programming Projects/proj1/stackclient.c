#include <stdio.h>
#include <stdlib.h>
#include "stackADT.h"

/**********************************************************
 * main: Asks the user to enter a series of parentheses   *
 *       and/or braces, then indicates whether or not     *
 *       they're properly nested.                         *
 **********************************************************/
int main(void) {
    char ch;
    char open[] = {'(', '[', '{', '<'};
    char close[] = {')', ']', '}', '>'};
    Stack s = create(100);

    printf("Enter parentheses and/or braces: ");
    for (;;) {
        ch = getchar();
        if (is_in(open, 4, ch))
            push(s, ch);
        else if (is_in(close, 4, ch)) {
            char temp = pop(s);
            int brace_index;
            switch (temp) {
            case '(': brace_index = 0; break;
            case '[': brace_index = 1; break;
            case '{': brace_index = 2; break;
            case '<': brace_index = 3; break;
            default:                   break;
            }
            if (close[brace_index] != ch)
                push(s, temp);
        }

        if (ch == '\n')
            break;
    }

    printf("Parentheses/braces are ");
    if (!is_empty(s))
            printf("not ");
    printf("nested properly\n");

    return 0;
}