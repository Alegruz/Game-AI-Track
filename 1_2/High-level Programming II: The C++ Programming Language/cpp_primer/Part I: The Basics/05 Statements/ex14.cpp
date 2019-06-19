// Write a program to read strings from standard input looking for duplicated words.
// The program should find places in the input where one word is followed immediately by itself.
// Keep track of the largest number of times a single repetition occurs and which word is repeated.
// Print the maximum number of duplicates, or else print a message saying that no word was repeated.
// For example, if the input is
// how now now now brown cow cow
// the output should indicate that the word now occurred three times.
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> string_tracker;
    std::vector<int> string_count;
    decltype(string_tracker.size()) i;

    std::string input_string;
    while (std::cin >> input_string) {
        for (i = 0; i < string_tracker.size(); ++i)
            if (string_tracker[i] == input_string) {
                ++string_count[i];
                break;
            }

        if (i == string_tracker.size()) {
            string_tracker.push_back(input_string);
            string_count.push_back(1);
        }
    }

    int max = string_count[0];
    decltype(string_tracker.size()) max_index = 0;
    for (i = 0; i < string_count.size(); ++i)
        if (max < string_count[i]) {
            max = string_count[i];
            max_index = i;
        }

    std::cout << std::endl;
    std::cout << "word \"" << string_tracker[max_index] << "\" now occurred "
                << string_count[max_index] << " times." << std::endl;

    return 0;
}
