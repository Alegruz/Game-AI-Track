float dummy1(long l);
int dummy2(double d);
int (*f(float (*)(long), char *))(double);
/* a function with a pointer to a function with a long argument and returns float, a pointer to char as arguments,
   and returns a pointer to a function with a double argument and returns int. */

int main(void) {
    char ch = 'A';
    double n = 1.0;

    int result = f(dummy1, &ch)(n);

    printf("Result when %c, &ld: %d\n", ch, n, result);

    return 0;
}

float dummy1(long l) {
    return l * 1.5f;
}

int dummy2(double d) {
    return d * 3;
}

int (*f(float (*fl)(long), char *ch_ptr))(double) {
    *ch_ptr += fl(6);
    return dummy2;
}