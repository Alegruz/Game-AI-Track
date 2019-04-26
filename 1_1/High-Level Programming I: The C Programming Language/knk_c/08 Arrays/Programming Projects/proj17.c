/* Prints an n x n magic square */

#include <stdio.h>

int main(void) {
    int magic_square_size, row = 0, column, number = 1;

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
    column = magic_square_size / 2;
    magic_square[row][column] = number;


    for (;;) {
        row = (row + magic_square_size - 1) % magic_square_size;
        column = (column + 1) % magic_square_size;
        number++;
        if (number > magic_square_size * magic_square_size)
            break;
        if (magic_square[row][column] != 0) {
            row = (row + 2) % magic_square_size;
            column = (column + magic_square_size - 1) % magic_square_size;
        }
        magic_square[row][column] = number;
    }

    for (int y = 0; y < magic_square_size; ++y) {
        for (int x = 0; x < magic_square_size; ++x)
            printf("%4d ", magic_square[y][x]);
        printf("\n");
    }

    return 0;
}
