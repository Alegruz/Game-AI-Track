// Write and test your own version of fact.
#include <iostream>

int fact(int val);

int main() {
    int i = 3, j = 4, k = 1;

    std::cout << "I: " << i << " fact: " << fact(i) << '\n'
                << "J: " << j << " fact: " << fact(j) << '\n'
                << "K: " << k << " k: " << fact(k) << std::endl;

    return 0;
}

int fact(int val) {
    for (int i = val - 1; i > 0; --i)
        val *= i;
    return val;
}