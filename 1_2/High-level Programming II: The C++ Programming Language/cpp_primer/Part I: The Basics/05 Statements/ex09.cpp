// Write a program using a series of if statements to count the number of vowels in text read from cin.
#include <iostream>
#include <string>

int main() {
    std::string text_input;
    unsigned short num_vowel = 0;
    while (std::cin >> text_input)
        for (decltype(text_input.size()) i = 0;
                i < text_input.size(); ++i) {
            if (text_input[i] == 'a' || text_input[i] == 'e' ||
                text_input[i] == 'i' || text_input[i] == 'o' || text_input[i] == 'u')
                ++num_vowel;
            if (text_input[i] == 'A' || text_input[i] == 'E' ||
                text_input[i] == 'I' || text_input[i] == 'O' || text_input[i] == 'U')
                ++num_vowel;
        }
    
    return 0;
}