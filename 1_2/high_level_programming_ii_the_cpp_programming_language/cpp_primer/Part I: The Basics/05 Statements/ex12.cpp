// Modify our vowel-counting program so that
// it counts the number of occurrences of the following two-character sequences:
// ff, fl, and fi.
#include <iostream>
#include <string>

int main() {
    std::string text_input;
    unsigned short num_char = 0;

    while (std::cin >> text_input)
        for (decltype(text_input.size()) i = 0;
                i < text_input.size() - 1; ++i)
            if (text_input[i] == 'f')
                if (text_input[i] == 'f' || text_input[i] == 'l' ||
                    text_input[i] == 'i')
                    ++num_char;
    return 0;
}