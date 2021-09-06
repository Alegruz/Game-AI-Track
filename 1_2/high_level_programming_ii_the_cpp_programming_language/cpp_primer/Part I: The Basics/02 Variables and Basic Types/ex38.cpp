// Describe the differences in type deduction between decltype and auto.
// When the expression to which we apply decltype is a variable, decltype returns the type of that variable, including top-level const and references

// Give an example of an expression where auto and decltype will deduce the same type and an example where they will deduce differing types.

int main() {
    const int a = 3;
    int b;

    auto c = b; // c is int
    decltype(b) d = b;  // d is int

    auto e = a; // c is int
    decltype(a) f = a;  // f is const int

    ++e;
    // ++f;     ERROR!!

    return 0;
}