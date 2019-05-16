#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "line.h"

#define MAX_LINE_LEN 60

struct node {
    struct node *next;
    char word[];
};

struct node *cur_line = NULL;
int line_len = 0;
int num_words = 0;

void clear_line(void) {
    cur_line = NULL;
    line_len = 0;
    num_words = 0;
}

void add_word(const char *word) {
    if (num_words > 0)
        line_len++;

    struct node *new_word = (struct node *) malloc(sizeof(struct node) + strlen(word) + 1);
    if (new_word == NULL) {
        printf("Error: memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    strcpy(new_word->word, word);
    new_word->next = NULL;
    
    struct node **pp = &cur_line;
    struct node *last = *pp;
    if (*pp == NULL) {
        *pp = new_word;
    } else {
        for (; last->next != NULL; last=last->next)
            ;
        last->next = new_word;
    }
    line_len += strlen(new_word->word);
    num_words++;
}

int space_remaining(void) {
    return MAX_LINE_LEN - line_len;
}

void write_line(void) {
    int extra_spaces, space_to_insert;

    extra_spaces = MAX_LINE_LEN - line_len;
    for (struct node *p = cur_line; p != NULL; p=p->next) {
        if (p != cur_line) {
            space_to_insert = extra_spaces / (num_words - 1);
            for (int i = 1; i <= space_to_insert + 1; i++)
                putchar(' ');
            extra_spaces -= space_to_insert;
            num_words--;
        }
        printf("%s", p->word);
    }
    putchar('\n');
}

void flush_line(void) {
    if (line_len > 0) {
        for (struct node *p = cur_line; p != NULL; p=p->next) {
            printf("%s ", p->word);
        }
        printf("\b\n");
    }
}
