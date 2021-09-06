/* a */
typedef struct
{
    double real, imaginary;
} Complex;

/* c */
Complex make_complex(double real, double imaginary);
/* d */
Complex add_complex(const Complex c1, const Complex c2);

int main(void) {
    /* b */
    Complex c1, c2, c3;
    return 0;
}

/* c */
Complex make_complex(double real, double imaginary) {
    return (Complex) {.real = real, .imaginary = imaginary};
}

/* d */
Complex add_complex(const Complex c1, const Complex c2) {
    return (Complex) {.real = c1.real + c2.real, .imaginary = c1.imaginary + c2.imaginary};
}
