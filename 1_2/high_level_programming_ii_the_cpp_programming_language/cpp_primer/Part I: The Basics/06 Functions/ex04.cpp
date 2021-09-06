// Write a function that interacts with the user,
// asking for a number and generating the factorial of that number.
// Call this function from main.
#include <iostream>

// Functions
int fact(int val);
bool getFact();

int main() {
    while (getFact())
        ;

    return 0;
}

int fact(int val) {
    for (int i = val - 1; i > 0; --i)
        val *= i;
    return val;
}

bool getFact() {
    int val = 0;
    std::cout << "Enter a number to factorialize (0 to exit): ";
    while (!(std::cin >> val))
        ;
    if (val == 0)
        return false;
    std::cout << "Factorial of " << val << " is " << fact(val) << std::endl;
    return true;
}