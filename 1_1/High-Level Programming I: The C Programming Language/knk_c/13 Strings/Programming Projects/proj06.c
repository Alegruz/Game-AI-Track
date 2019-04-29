/* Checks planet names */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUM_PLANETS 9

int main(int argc, char *argv[]) {
    char *planets[] = {"Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune", "Pluto"};

    int i, j, case_count;

    for (i = 1; i < argc; ++i) {
        case_count = 0;
        for (j = 0; j < NUM_PLANETS; ++j) {
            for (int k = 0; k < strlen(argv[i]) && toupper(*(planets[j] + k)) == toupper(*(argv[i] + k)); ++k) 
                case_count++;
            if (case_count == strlen(argv[i])) {
                printf("%s is planet %d\n", argv[i], j + 1);
                break;
            }
        }
        if (j == NUM_PLANETS)
            printf("%s is not a planet\n", argv[i]);
    }

    return 0;
}
