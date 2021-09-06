// Write your own versions of the fact.cc and factMain.cc files.
// These files should include your Chapter6.h from the exercises in the previous section.
// Use these files to understand how your compiler supports separate compilation.
#include "Chapter6.h"

int main() {
    std::cout << fact(3) << " " << fact(4) << " " << fact(1) << std::endl;
    return 0;
}

int fact(int val) {
    for (int i = val - 1; i > 0; --i)
        val *= i;
    return val;
}