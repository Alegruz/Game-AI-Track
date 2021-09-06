#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void make_empty(void);
bool is_empty(void);
bool push(int ch);
struct node *pop(void);

const int stack_size = 100;

struct node {
    int value;
    struct node *next;
};

struct node *top = NULL;

int len(struct node *list);

int main(void) {
    for (int i = 9; i >= 0; --i) {
        push(i);
    }

    struct node *count = top;
    for (int i = 0; i < len(top); ++i) {
        printf("Node %2d: %d\n", i + 1, count->value);
        count = count->next;
    }

    pop();
    count = top;
    for (int i = 0; i < len(top); ++i) {
        printf("Node %2d: %d\n", i + 1, count->value);
        count = count->next;
    }

    make_empty();

    printf("%d\n", len(top));

    return 0;
}

int len(struct node *list) {
    struct node *p = list;
    int count = 0;
    for (; p != NULL; p = p->next)
        count++;
    return count;
}

/**********************************************************
 * make_empty: Empties the stack by assigning 0 to top    *
 **********************************************************/
void make_empty(void) {
    struct node *temp;
    while (top != NULL) {
        temp = top;
        top = top->next;
        free(temp);
    }
}

/**********************************************************
 * is_empty: Returns whether the stack is empty           *
 **********************************************************/
bool is_empty(void) {
    return top == NULL;
}

/**********************************************************
 * push: When the stack is not full, store ch into        *
 *       stack[top] then increment top.                   *
 **********************************************************/
bool push(int ch) {
    struct node *p = (struct node *) malloc(sizeof (struct node));
    if (p == NULL)
        return false;
    else {
        *p = (struct node) {ch, top};
        top = p;
    }

    return true;
}

/**********************************************************
 * pop: When the stack is not empty, decrement top and    *
 *      return the item in its index                      *
 **********************************************************/
struct node *pop(void) {
    if (is_empty()) {
        printf("Error: empty stack.\n");
        exit(EXIT_FAILURE);
    } else {
        struct node p = *top;
        top = top->next;
        free(top);
        return &p;
    }
}
