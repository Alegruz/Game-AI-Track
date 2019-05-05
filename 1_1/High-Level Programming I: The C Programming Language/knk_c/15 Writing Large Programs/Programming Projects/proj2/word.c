#include <stdio.h>
#include "word.h"

const int MAX_WORD_LEN = 20;

int read_char(void) {
    int ch = getchar();

    // if (ch == '\n' || ch == '\t')
    //     return ' ';
    // return ch;
    return (ch == '\n' || ch == '\t') ? ' ' : ch;
}

int read_word(char *word) {
    int ch, pos = 0;

    while ((ch = read_char()) == ' ')
        ;

    while (ch != ' ' && ch != EOF) {
        if (pos < MAX_WORD_LEN + 1)
            word[pos++] = ch;
        ch = read_char();
    }
    if (pos > MAX_WORD_LEN)
        word[MAX_WORD_LEN] = '*'; 

    word[pos] = '\0';
    return pos;
}
