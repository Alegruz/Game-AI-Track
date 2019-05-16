#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readline.h"

#ifndef MAX_WORD_LEN
#define MAX_WORD_LEN 20
#endif
#ifndef MAX_WORD_LIST_LEN
#define MAX_WORD_LIST_LEN 100
#endif

int compare_words(const void *p, const void *q);

int main(void) {
    char *word_list[MAX_WORD_LIST_LEN];
    int current_index = 0;
    for (int i = 0; i < MAX_WORD_LIST_LEN; ++i) {
        printf("Enter word: ");
        char *word = (char *) malloc(sizeof(char) * (MAX_WORD_LEN + 1));
        if (word == NULL) {
            printf("Error: memory allocation failed!\n");
            exit(EXIT_FAILURE);
        }
        if (read_line(word, MAX_WORD_LEN) == -1)
            break;
        word_list[current_index] = word;
        current_index++;
    }

    printf("In sorted order: ");
    qsort(word_list, current_index, sizeof(char *), compare_words);
    for (int i = 0; i < current_index; ++i)
        printf("%s ", word_list[i]);
    printf("\b\n");
    return 0;
}

int compare_words(const void *p, const void *q) {
    return strcmp(*(char **) p, *(char **) q);
}