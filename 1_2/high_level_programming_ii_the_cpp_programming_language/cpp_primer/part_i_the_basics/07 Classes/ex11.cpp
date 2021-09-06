// Add constructors to your Sales_data class
// and write a program to use each of the constructors.
#include "ex11.h"

int main() {
    Sales_data sd1;
    write(std::cout, sd1);

    Sales_data sd2("101");
    write(std::cout, sd2);

    Sales_data sd3("101", 25., 150);
    write(std::cout, sd3);

    Sales_data sd4(std::cin);
    write(std::cout, sd4);

    return 0;
}