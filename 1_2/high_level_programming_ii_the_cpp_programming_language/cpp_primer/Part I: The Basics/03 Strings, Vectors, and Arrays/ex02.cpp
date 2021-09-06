// Write a program to read the standard input a line at a time.
// Modify your program to read a word at a time.

#include <iostream>
#include <string>

// int main() {
//     std::string line;
//     while (getline(std::cin, line))
//         std::cout << line << std::endl;

//     return 0;
// }

int main() {
    std::string word;
    while (std::cin >> word)
        std::cout << word << std::endl;

    return 0;
}