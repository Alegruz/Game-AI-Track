/* Write a function that evaluates a chess position */

#include <stdio.h>
#include <ctype.h>

int evaluate_position(char board[8][8]);

int main(void) {
    char board[8][8] = {{}};
    board[0][1] = 'B';
    board[1][2] = 'Q';
    board[7][5] = 'q';

    printf("Chess Win Evaluator\n");
    printf("White's Score minus Black's Score is %d.\n", evaluate_position(board));

    return 0;
}

int evaluate_position(char board[8][8]) {
    char piece;
    int white_score = 0, black_score = 0, score;
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            piece = board[y][x];
            switch (toupper(piece)) {
            case 'Q': score = 9; break;
            case 'R': score = 5; break;
            case 'B': case 'N': score = 3; break;
            case 'P': score = 1; break;
            default: score = 0; break;
            }
            if ('b' <= piece && piece <= 'r')
                black_score += score;
            else if ('B' <= piece && piece <= 'R')
                white_score += score;
        }
    }

    return white_score - black_score;
}
