// Write programs that contain the common errors discussed in
// the box on page 16. Familiarize yourself with the messages the compiler
// generates.
#include <iostream>

// error: missing ) in parameter list for main
int main(
{
    int sum = 0;
    for (int val = 1; val <= 10; ++val)
        sum += val;
    // error: missing quotes around string literal
    std::cout << Sum of 1 to 10 inclusive is ;
    // error: used colon, not a semicolon, after the string
    std::cout << sum:
    // error: second output operator is missing
    std::cout << "." std::endl;

    // error: missing ; on return statement
    return 0
}