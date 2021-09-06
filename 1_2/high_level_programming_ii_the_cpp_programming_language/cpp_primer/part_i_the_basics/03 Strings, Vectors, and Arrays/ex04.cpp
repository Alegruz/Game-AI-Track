// Write a program to read two strings and report whether the strings are equal.
// If not, report which of the two is larger.
// Now, change the program to report whether the strings have the same length, and if not, report which is longer.
#include <iostream>
#include <string>

int main() {
    std::string s1, s2;
    std::cin >> s1 >> s2;   // read two strings
    if (s1 == s2)
        std::cout << "strings are equal" << std::endl;  // report whether the strings are equal
    else if (s1 < s2)
            std::cout << "s2 is larger than s1" << std::endl;
        else
            std::cout << "s1 is larger than s2" << std::endl;   // report which of the two is larger
    
    if (s1.size() == s2.size())
        std::cout << "strings have the same length" << std::endl;   // report whether the strings have the same length
    else if (s1.size() < s2.size())
            std::cout << "s2 is longer than s1" << std::endl;
        else
            std::cout << "s1 is longer than s2" << std::endl;   // report which is longer

    return 0;
}