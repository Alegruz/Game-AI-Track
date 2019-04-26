/* Displays the number using seven-segment display */

#include <stdio.h>

#define MAX_DIGITS 10

/* Set up an array of seven-segment numbers */
const int segments[10][7] = {{1, 1, 1, 1, 1, 1, 0},
                             {0, 1, 1, 0, 0, 0, 0},
                             {1, 1, 0, 1, 1, 0, 1},
                             {1, 1, 1, 1, 0, 0, 1},
                             {0, 1, 1, 0, 0, 1, 1},
                             {1, 0, 1, 1, 0, 1, 1},
                             {1, 0, 1, 1, 1, 1, 1},
                             {1, 1, 1, 0, 0, 0, 0},
                             {1, 1, 1, 1, 1, 1, 1},
                             {1, 1, 1, 1, 0, 1, 1}};
char digits[3][MAX_DIGITS * 4];

/* prototypes */
void clear_digits_array(void);
void process_digit(int digit, int position);
void print_digits_array(void);

char char_segment(int, int);

int main(void) {
    char ch;
    char digit[MAX_DIGITS] = {};
    int digit_index = 0;

    clear_digits_array();

    printf("Enter a number: ");
    for (;;) {
        ch = getchar();
        if (ch == '\n' || digit_index >= MAX_DIGITS)
            break;
        if ('0' <= ch && ch <= '9')
            digit[digit_index++] = ch;
    }

    for (int i = 0; i < digit_index; ++i)
        process_digit(digit[i] - '0', i);

    print_digits_array();

    return 0;
}

void clear_digits_array(void) {
    for (int row = 0; row < 3; ++row)
        for (int column = 0; column < MAX_DIGITS * 4; ++column)
            digits[row][column] = ' ';
}

void process_digit(int digit, int position) {
    digits[0][position * 4 + 1] = segments[digit][0] ? '_' : ' ';
    digits[1][position * 4 + 2] = segments[digit][1] ? '|' : ' ';
    digits[2][position * 4 + 2] = segments[digit][2] ? '|' : ' ';
    digits[2][position * 4 + 1] = segments[digit][3] ? '_' : ' ';
    digits[2][position * 4]     = segments[digit][4] ? '|' : ' ';
    digits[1][position * 4]     = segments[digit][5] ? '|' : ' ';
    digits[1][position * 4 + 1] = segments[digit][6] ? '_' : ' ';
}

void print_digits_array(void) {
    for (int row = 0; row < 3; ++row) {
        for (int d = 0; d < MAX_DIGITS; ++d) {
            for (int i = 0; i < 4; ++i)
                printf("%c", digits[row][i + d * 4]);
            printf(" ");
        }
    printf("\n");
    }
}
