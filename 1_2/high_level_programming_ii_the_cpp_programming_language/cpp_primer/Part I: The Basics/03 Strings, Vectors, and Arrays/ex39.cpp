// Write a program to compare two strings.
// Now write a program to compare the values of two C-style character strings.
#include <cstring>
#include <string>
#include <iostream>

int main() {
    const char str1[] = "damn";
    const char str2[] = "darn";

    if (strcmp(str1, str2) < 0)
        std::cout << "str2 is bigger than str1" << std::endl;
    else if (strcmp(str1, str2) > 0)
        std::cout << "str1 is bigger than str2" << std::endl;
    else
        std::cout << "str1 and str2 are equal" << std::endl;
    
    std::string cstr1 = "damn";
    std::string cstr2 = "darn";
    
    if (cstr1 < cstr2)
        std::cout << "str2 is bigger than str1" << std::endl;
    else if (cstr1 > cstr2)
        std::cout << "str1 is bigger than str2" << std::endl;
    else
        std::cout << "str1 and str2 are equal" << std::endl;

    return 0;
}