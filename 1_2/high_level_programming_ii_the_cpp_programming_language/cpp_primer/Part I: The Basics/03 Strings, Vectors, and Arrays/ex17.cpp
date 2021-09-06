// Read a sequence of words from cin and store the values a vector.
// After you’ve read all the words, process the vector and change each word to uppercase.
// Print the transformed elements, eight words to a line.
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string input_string;
    std::vector<std::string> word_vector;
    while (std::cin >> input_string)
        word_vector.push_back(input_string);

    unsigned short newline_count = 0;
    for (auto word : word_vector) {
        for (auto letter : word)
            if ('a' <= letter && letter <= 'z')
                letter = letter - 'a' + 'A';
        if (newline_count % 8 == 0)
            std::cout << '\b' << std::endl;
        std::cout << word << ' ';
        ++newline_count;
    }
    std::cout << std::endl;

    return 0;
}
