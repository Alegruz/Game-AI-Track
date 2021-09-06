// What would happen if you define the loop control variable in the previous exercise as type char?
// Predict the results and then change your program to use a char to see if you were right.
#include <iostream>
#include <string>

int main() {
    std::string s;
    std::cin >> s;
    for (char c : s)
        c = 'X';    // does nothing to the string

    std::cout << s << std::endl;

    return 0;
}