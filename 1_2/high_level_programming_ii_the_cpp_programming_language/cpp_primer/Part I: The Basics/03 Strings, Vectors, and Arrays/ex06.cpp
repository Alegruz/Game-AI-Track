// Use a range for to change all the characters in a string to X.
#include <iostream>
#include <string>

int main() {
    std::string s;
    std::cin >> s;
    for (auto &c : s)
        c = 'X';

    std::cout << s << std::endl;

    return 0;
}