/* Prints an n x n magic square using functions */

#include <stdio.h>

void create_magic_square(int n, int magic_square[n][n]);
void print_magic_square(int n, int magic_square[n][n]);

int main(void) {
    int magic_square_size;

    printf("This program creates a magic square of a specified size.\n"
           "The size must be an odd number between 1 and 99.\n"
           "Enter size of magic square: ");

    scanf("%d", &magic_square_size);
    while (magic_square_size % 2 == 0) {
        printf("The size of a magic square must be an odd number!!\n"
               "Enter size of magic square: ");
        scanf("%d", &magic_square_size);
    }

    int magic_square[magic_square_size][magic_square_size];
    for (int y = 0; y < magic_square_size; ++y)
        for (int x = 0; x < magic_square_size; ++x)
            magic_square[y][x] = 0;

    create_magic_square(magic_square_size, magic_square);
    print_magic_square(magic_square_size, magic_square);

    return 0;
}

void create_magic_square(int n, int magic_square[n][n]) {
    int row = 0, column, number = 1;
    column = n / 2;
    magic_square[row][column] = number;

    for (;;) {
        row = (row + n - 1) % n;
        column = (column + 1) % n;
        number++;
        if (number > n * n)
            break;
        if (magic_square[row][column] != 0) {
            row = (row + 2) % n;
            column = (column + n - 1) % n;
        }
        magic_square[row][column] = number;
    }
}

void print_magic_square(int n, int magic_square[n][n]) {
    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < n; ++x)
            printf("%4d ", magic_square[y][x]);
        printf("\n");
    }
}
