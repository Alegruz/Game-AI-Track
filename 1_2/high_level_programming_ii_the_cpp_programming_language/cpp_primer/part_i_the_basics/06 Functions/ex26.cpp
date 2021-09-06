// Write a program that accepts the options presented in this section.
// Print the values of the arguments passed to main.
#include <string>
#include <iostream>

int main(int argc, char *argv[]) {
    std::string argv_string;
    
    for (int i = 1; i < argc; ++i)
        argv_string += std::string(argv[i]) + ' ';
    
    std::cout << argv_string << std::endl;

    return 0;
}