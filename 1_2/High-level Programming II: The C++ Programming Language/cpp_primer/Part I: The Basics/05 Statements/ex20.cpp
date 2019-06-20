// Write a program to read a sequence of strings from the standard input
// until either the same word occurs twice in succession or all the words have been read.
// Use a while loop to read the text one word at a time.
// Use the break statement to terminate the loop if a word occurs twice in succession.
// Print the word if it occurs twice in succession,
// or else print a message saying that no word was repeated.
#include <iostream>
#include <vector>
#include <string>

int main() {
    std::string input_string;
    std::string prev_input_string;

    while (std::cin >> input_string)
        if (prev_input_string.size() > 0 && input_string == prev_input_string)
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
