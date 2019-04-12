/* Declare a 8 x 8 char array and store data by loops */

#include <stdio.h>

int main(void) {
    char chess_board[8][8];

    for (int row = 0; row < 8; ++row) {
        for (int column = 0; column < 8; ++column) {
            chess_board[row][column] = ((row + column) % 2) ? 'R' : 'B';
            printf("%c ", chess_board[row][column]);
        }
        printf("\n");
    }

    return 0;
}
