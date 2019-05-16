struct temp {
    int a;
};

int main(void) {
    struct temp x;
    x.a = 10;
    (&x)->a = 10;
    /* true */

    return 0;
}
