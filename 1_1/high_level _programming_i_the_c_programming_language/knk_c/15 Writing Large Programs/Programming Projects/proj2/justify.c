/* Modify the justify program */
/* Formats a file of text */

#include "line.h"
#include "word.h"

int main(void) {
    extern int MAX_WORD_LEN;
    char word[MAX_WORD_LEN + 2];
    int word_len;

    clear_line();
    for (;;) {
        word_len = read_word(word);
        if (word_len == 0) {
            flush_line();
            return 0;
        }
        if (word_len > MAX_WORD_LEN)
            word[MAX_WORD_LEN] = '*';
        if (word_len + 1 > space_remaining()) {
            write_line();
            clear_line();
        }
        add_word(word);
    }
}
