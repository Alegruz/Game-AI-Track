/* Find the legal statements */

int f(int a, int b);

int main(void) {
    int i;
    double x;

    /* a */
    i = f(83, 12);
    /* b */
    x = f(83, 12);
    /* c */
    i = f(3.15, 9.28);
    /* d */
    x = f(3.15, 9.28);
    /* e */
    f(83, 12);
    /* Above statements are all legal */

    return 0;
}

int f(int a, int b) {}
