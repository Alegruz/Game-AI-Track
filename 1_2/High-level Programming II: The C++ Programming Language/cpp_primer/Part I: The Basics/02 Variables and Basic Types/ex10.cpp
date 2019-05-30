// What are the initial values, if any, of each of the following variables?
#include <string>
#include <iostream>

std::string global_str; // default initialization. { /0 }. 
int global_int;         // default initialization. 0.
int main()
{
    int local_int;          // uninitialized.
    std::string local_str;  // class-defined default initialization. { \0 }.

    std::cout << "global: " << global_int << " --- "
                << global_str << std::endl;
    std::cout << "local: " << local_int << " --- "
                << local_str << std::endl;

    return 0;
}