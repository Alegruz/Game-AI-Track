#include <stdio.h>
#include <ctype.h>

enum {NORTH, SOUTH, EAST, WEST} direction;

int main(void) {
    char ch, input;
    int x = 0, y = 0;

    printf("You are currently in (%d, %d)\n", x, y);
    for (;;) {
        printf("Make your move (wasd): ");
        while ((ch = getchar()) != '\n')
            input = ch;
        if (input == 'q')
            break;
        switch (toupper(input)) {
        case 'W':
            y++;
            break;
        case 'A':
            x--;
            break;
        case 'S':
            y--;
            break;
        case 'D':
            x++;
            break;
        }
        printf("You are currently in (%d, %d)\n", x, y);
    }

    return 0;
}
