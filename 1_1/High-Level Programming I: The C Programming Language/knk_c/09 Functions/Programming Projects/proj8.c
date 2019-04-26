/* Randomly walks in a 10x10 array using functions */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int die_roll(void);
bool play_game(void);

int win = 0, lose = 0;

int main(void) {
    bool game_loop = true;
    srand((unsigned) time(NULL));

    do {
        game_loop = play_game();
    } while (game_loop);

    printf("Wins: %d\tLosses: %d\n", win, lose);

    return 0;
}

int die_roll(void) {
    int first_dice, second_dice;
    first_dice = (rand() % 6) + 1;
    second_dice = (rand() % 6) + 1;
    printf("You rolled: %d\n", first_dice + second_dice);
    return first_dice + second_dice;
}
bool play_game(void) {
    int roll, point;
    bool has_point = false, is_game = true, is_player_win, is_player_lose;
    while (is_game) {
        is_player_win = false;
        is_player_lose = false;
        roll = die_roll();

        if (!has_point) {
            switch (roll) {
            case 7: case 11:
                is_player_win = true; break;
            case 2: case 3: case 12:
                is_player_lose = true; break;
            default:
                point = roll; has_point = true;
                printf("Your point is %d\n", point); break;
            }
        } else {
            if (point == roll)
                is_player_win = true;
            else if (roll == 7)
                is_player_lose = true;
        }

        if (is_player_win || is_player_lose) {
            printf("You ");
            is_game = false;
            if (is_player_win) {
                printf("win!\n");
                win++;
            } else {
                printf("lose!\n");
                lose++;
            }
        }
    }

    char ch;
    bool again = false, is_input = false;
    printf("\nPlay again? ");

    for (;;) {
        ch = getchar();
        if (is_input && ch == '\n')
            break;
        if (ch == 'y' || ch == 'n') {
            again = (ch == 'y');
            is_input = true;
        }
    }
    printf("\n");
    return again;
}
