// Revise the program from the exercise in § 5.5.1 (p. 191)
// so that it looks only for duplicated words that start with an uppercase letter.
#include <iostream>
#include <string>

int main() {
    std::string input_string;
    std::string prev_input_string;

    while (std::cin >> input_string)
        if (prev_input_string.size() > 0 &&
            'A' <= input_string[0] && input_string[0] <= 'Z' &&
            input_string == prev_input_string)
            break;
        else {
            prev_input_string = input_string;
            input_string = EOF;
        }


    std::cout << std::endl;
    if (prev_input_string == input_string)
        std::cout << "The word is: " << prev_input_string << std::endl;
    else
        std::cout << "No repetition." << std::endl;

    return 0;
}
