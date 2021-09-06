// Repeat the previous program but read strings this time.
#include <iostream>
#include <vector>
#include <string>

int main() {
    std::string s;
    std::vector<std::string> svec;
    while (std::cin >> s)   // reads a string
        svec.push_back(s);  // stores the string in a vector

    return 0;
}