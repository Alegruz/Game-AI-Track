// Write a main function that takes two arguments.
// Concatenate the supplied arguments and print the resulting string.
#include <string>
#include <iostream>

int main(int argc, char *argv[]) {
    std::string argv_string;
    
    for (int i = 1; i < argc; ++i)
        argv_string += std::string(argv[i]) + ' ';
    
    std::cout << argv_string << std::endl;

    return 0;
}