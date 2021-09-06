struct fraction
{
    int numerator, denominator;
};

struct fraction reduce_fraction(struct fraction f);
struct fraction add_fractions(const struct fraction f1, const struct fraction f2);
struct fraction subtract_fractions(const struct fraction f1, const struct fraction f2);
struct fraction multiply_fractions(const struct fraction f1, const struct fraction f2);
struct fraction divide_fractions(const struct fraction f1, const struct fraction f2);

/* a */
struct fraction reduce_fraction(struct fraction f) {
    int reduced_numerator = f.numerator, reduced_denominator = f.denominator, remainder;

    while (reduced_denominator) {
        remainder = reduced_numerator % reduced_denominator;
        reduced_numerator = reduced_denominator;
        reduced_denominator = remainder;
    }
    reduced_numerator = f.numerator / reduced_numerator;
    reduced_denominator = f.denominator / reduced_numerator;

    return (struct fraction) {.numerator = reduced_numerator, .denominator = reduced_denominator};
}

/* b */
struct fraction add_fractions(const struct fraction f1, const struct fraction f2) {
    return reduce_fraction((struct fraction) {.numerator = f1.numerator * f2.denominator + f2.numerator * f1.denominator, .denominator = f1.denominator * f2.denominator});
}

/* c */
struct fraction subtract_fractions(const struct fraction f1, const struct fraction f2) {
    return reduce_fraction((struct fraction) {.numerator = f1.numerator * f2.denominator - f2.numerator * f1.denominator, .denominator = f1.denominator * f2.denominator});
}

/* d */
struct fraction multiply_fractions(const struct fraction f1, const struct fraction f2) {
    return reduce_fraction((struct fraction) {.numerator = f1.numerator *  f2.denominator, .denominator = f1.denominator * f2.numerator});
}
