// Write a program that uses a do while loop
// to repetitively request two strings from the user
// and report which string is less than the other.
#include <iostream>
#include <string>

int main() {
    std::string str1, str2;

    do {
        std::cout << "Input two separate strings: ";
        if (std::cin >> str1 >> str2)
            std::cout << ((str1.size() < str2.size()) ? str1 : str2) << " is less than " << ((str1.size() < str2.size()) ? str2 : str1) << std::endl;
    } while (std::cin);

    return 0;
}
