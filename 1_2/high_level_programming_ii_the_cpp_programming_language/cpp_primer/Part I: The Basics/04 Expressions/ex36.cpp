// Assuming i is an int and d is a double
// write the expression i *= d so that
// it does integral, rather than floating-point, multiplication.

int main() {
    int i;
    double d;

    i *= static_cast<int>(d);

    return 0;
}