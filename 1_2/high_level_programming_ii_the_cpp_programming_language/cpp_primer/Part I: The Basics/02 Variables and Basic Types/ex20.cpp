// What does the following program do?

int main() {
    int i = 42;
    int *p1 = &i;       // *p1 == 42
    *p1 = *p1 * *p1;    // i = i * i; i == 42 * 42;
    return 0;
}