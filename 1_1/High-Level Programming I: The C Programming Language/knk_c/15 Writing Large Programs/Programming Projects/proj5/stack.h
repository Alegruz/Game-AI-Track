#if !defined(STACK_H)
#define STACK_H

void make_empty(void);
bool is_empty(void);
bool is_full(void);
void push(int ch);
int pop(void);
void stack_overflow(void);
void stack_underflow(void);
bool is_in(const char a[], int n, char ch);

#endif // STACK_H
