/* Evaluates an expression */

#include <stdio.h>
#include <ctype.h>

int main(void)
{
    float number = 0, rightOprnd = 0, leftOprnd = 0;
    int digit = 0;
    char ch, oprtr;
    bool isOprtr = false;
    bool isFloating = false;

    printf("Enter an expression: ");
    for (;;) {
        ch = getchar();
        if (ch >= '0' && ch <= '9') {
            number = ch - '0';
            if (isFloating) {
                for (int i = 0; i < digit; ++i) {
                    number *= 0.1f;
                }
                digit++;
            } else {
                rightOprnd *= 10;
            }
            rightOprnd += number;
        } else {
            digit = 0;
            isFloating = false;

            if (ch == '.') {
                isFloating = true;
                digit = 1;
            } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '\n') {
                if (isOprtr) {
                    switch (oprtr) {
                    case '+':
                        leftOprnd += rightOprnd;
                        break;
                    case '-':
                        leftOprnd -= rightOprnd;
                        break;
                    case '*':
                        leftOprnd *= rightOprnd;
                        break;
                    case '/':
                        leftOprnd /= rightOprnd;
                        break;
                    }
                    oprtr = ch;
                } else {
                    isOprtr = true;
                    oprtr = ch;
                    leftOprnd = rightOprnd;
                }

                rightOprnd = 0;
                if (ch == '\n')
                    break;
            } else if (ch == '\n') {
                break;
            }
        }
    }

    printf("Value of expression: %.2f\n", leftOprnd);

    return 0;
}
