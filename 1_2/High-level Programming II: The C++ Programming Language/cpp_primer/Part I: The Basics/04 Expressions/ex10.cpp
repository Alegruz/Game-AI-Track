// Write the condition for a while loop that would read ints from the standard input and stop when the value read is equal to 42.
#include <iostream>

int main() {
    int int_input;
    while (std::cin >> int_input && int_input != 42)
        ;
    return 0;
}