/* Randomly walks in a 10x10 array */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int main(void) {
    char game_board[10][10] = {{'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                              {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                              {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                              {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                              {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                              {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                              {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                              {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                              {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                              {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'}};
    char trail = 'A';
    const int movement[4][2] = {{0, -1},
                                {0, 1},
                                {-1, 0},
                                {1, 0}};
    int movement_index;
    bool possible_movement[4] = {false};
    int movement_termination;
    int player_pos[2] = {0, 0};
    bool game_loop = true;
    srand((unsigned) time(NULL));


    game_board[player_pos[0]][player_pos[1]] = trail;
    while (game_loop == true) {
        movement_termination = 0;

        /* Checks Collision */
        for (int direction = 0; direction < 4; ++direction) {
            if (player_pos[0] + movement[direction][0] >= 0 && player_pos[0] + movement[direction][0] < 10 &&
                    player_pos[1] + movement[direction][1] >= 0 && player_pos[1] + movement[direction][1] < 10)
                if (game_board[player_pos[0] + movement[direction][0]][player_pos[1] + movement[direction][1]] == '.') {
                    possible_movement[direction] = true;
                    continue;
                }
            possible_movement[direction] = false;
        }

        for (int i = 0; i < 4; ++i)
            movement_termination += possible_movement[i];

        /* Checks Termination */
        if (trail >= 'Z' || movement_termination <= 0)
            break;

        /* Get Movement */
        do {
            movement_index = rand() % 4;
        } while (possible_movement[movement_index] == false);

        player_pos[0] += movement[movement_index][0];
        player_pos[1] += movement[movement_index][1];

        game_board[player_pos[0]][player_pos[1]] = ++trail;
    }

    for (int row = 0; row < 10; ++row) {
        for (int column = 0; column < 10; ++ column)
            printf("%c ", game_board[row][column]);
        printf("\n");
    }

    return 0;
}
