// Write a program that reads a string of characters including punctuation and writes what was read but with the punctuation removed.
#include <iostream>
#include <string>

int main() {
    std::string s, result;
    if (std::cin >> s) {    // reads a string of characters
        for (decltype(s.size()) i = 0;
            i < s.size(); ++i) {
                if (s[i] == '.' || s[i] == ',' || s[i] == '?' || s[i] == '!')
                    continue;   // ignores punctuations
                result += s[i]; // reads a non-punctuation character
            }
    }

    std::cout << s << std::endl;
    std::cout << result << std::endl;

    return 0;
}