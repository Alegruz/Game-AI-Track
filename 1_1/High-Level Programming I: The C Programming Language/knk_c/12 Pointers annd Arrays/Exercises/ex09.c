/* Write the function inner_product(a, b, n) */

double inner_product(const double *a, const double *b, int n) {
    double product = 0;
    for(double const *p = a, *q = b; p < a + n && q < b + n; p++, q++)
        product += (*p) * (*q);
    return product;
}
