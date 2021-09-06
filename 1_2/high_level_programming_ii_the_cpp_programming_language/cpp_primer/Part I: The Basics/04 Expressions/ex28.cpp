// Write a program to print the size of each of the built-in types.
#include <iostream>

int main() {
    std::cout << "char: " << sizeof (char) << '\n'
                << "char16_t: " << sizeof(char16_t) << '\n'
                << "char32_t: " << sizeof(char32_t) << '\n'
                << "wchar_t: " << sizeof(wchar_t) << '\n'
                << "short: " << sizeof(short) << '\n'
                << "int: " << sizeof(int) << '\n'
                << "long: " << sizeof(long) << '\n'
                << "long long: " << sizeof(long long) << '\n'
                << "float: " << sizeof(float) << '\n'
                << "double: " << sizeof(double) << '\n'
                << "long double: " << sizeof(long double) << '\n'
                << "bool: " << sizeof(bool) << '\n'
                << "nullptr: " << sizeof(nullptr) << std::endl;

    return 0;
}