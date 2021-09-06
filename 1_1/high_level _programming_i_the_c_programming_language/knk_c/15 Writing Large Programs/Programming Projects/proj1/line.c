#include <stdio.h>
#include <string.h>
#include "line.h"

#define MAX_LINE_LEN 60

char line[MAX_LINE_LEN+1];
int line_len = 0;
int num_words = 0;

void clear_line(void) {
    line[0] = '\0';
    line_len = 0;
    num_words = 0;
}

void add_word(const char *word) {
    if (num_words > 0) {
        line[line_len] = ' ';
        line[line_len+1] = '\0';
        line_len++;
    }
    strcat(line, word);
    line_len += strlen(word);
    num_words++;
}

int space_remaining(void) {
    return MAX_LINE_LEN - line_len;
}

void write_line(void) {
    int extra_spaces, space_to_insert, space_locator = 0, just, l_just, r_just;

    extra_spaces = MAX_LINE_LEN - line_len;
    just = extra_spaces % (num_words - 1);
    if (just % 2 == 0) {
        l_just = just / 2;
        r_just = (num_words - 1) - l_just;
    } else {
        l_just = just - 1 / 2;
        r_just = (num_words - 1) - l_just;
    }
    for (int i = 0; i < line_len; i++) {
        if (line[i] != ' ') {
            putchar(line[i]);
        } else {
            space_to_insert = extra_spaces / (num_words - 1);
            for (int j = 1; j <= space_to_insert + 1 + (space_locator < l_just || r_just <= space_locator); j++)
                putchar(' ');
            // extra_spaces -= space_to_insert;
            // num_words--;
            space_locator++;
        }
    }
    putchar('\n');
}

void flush_line(void) {
    if (line_len > 0)
        puts(line);
}
