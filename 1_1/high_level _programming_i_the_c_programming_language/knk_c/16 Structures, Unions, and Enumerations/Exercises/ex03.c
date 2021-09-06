/* a */
struct complex
{
    double real, imaginary;
};

/* c */
struct complex make_complex(double real, double imaginary);
/* d */
struct complex add_complex(const struct complex c1, const struct complex c2);

int main(void) {
    /* b */
    struct complex c1, c2, c3;
    return 0;
}

/* c */
struct complex make_complex(double real, double imaginary) {
    return (struct complex) {.real = real, .imaginary = imaginary};
}

/* d */
struct complex add_complex(const struct complex c1, const struct complex c2) {
    return (struct complex) {.real = c1.real + c2.real, .imaginary = c1.imaginary + c2.imaginary};
}
