// Explain the behavior of the condition in the following if:

int main() {
    const char *cp = "Hello World";
    if (cp && *cp)  // if pointer cp is null, the logical expression is false.
                    // else, evaluate next operand.
                    // if value of what cp is pointing is not a null character,
                    // the logical expression is true, and vice versa.
    return 0;
}