// Modify our vowel-counting program so that it also counts the number of blank spaces, tabs, and newlines read.
#include <iostream>
#include <string>

int main() {
    std::string text_input;
    unsigned short num_vowel = 0;
    unsigned short num_whitespace = 0;
    while (std::cin >> text_input)
        for (decltype(text_input.size()) i = 0;
                i < text_input.size(); ++i)
            if (text_input[i] == 'a' || text_input[i] == 'e' ||
                text_input[i] == 'i' || text_input[i] == 'o' || text_input[i] == 'u' ||
                text_input[i] == 'A' || text_input[i] == 'E' ||
                text_input[i] == 'I' || text_input[i] == 'O' || text_input[i] == 'U')
                ++num_vowel;
            else if (text_input[i] == ' ' || text_input[i] == '\t' ||
                    text_input[i] == '\n')
                ++num_whitespace;
    
    return 0;
}