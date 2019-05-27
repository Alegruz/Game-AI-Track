// Indicate which, if any, of the following output statements are legal:
#include <iostream>

int main() {
    std::cout << "/*";                  /* LEGAL */
    std::cout << "*/";                  /* LEGAL */
    std::cout << /* "*/" */;            /* ILLEGAL */
    std::cout << /*  "*/" /* "/*"  */;  /* LEGAL */
    return 0;
}

// After you’ve predicted what will happen, test your answers by compiling a
// program with each of these statements. Correct any errors you encounter.

// ex08.cpp:7:24: warning: missing terminating " character
//      std::cout << /* "*/" */;            /* ILLEGAL */