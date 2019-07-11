// Write a function that returns 0 when it is first called
// and then generates numbers in sequence each time it is called again.
#include <iostream>

int sequenceGenerator() {
    static int callCount = 0;
    for (int i = 0; i <= callCount; ++i)
        std::cout << i << " ";
    std::cout << '\b' << std::endl;
}