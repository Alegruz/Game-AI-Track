// Use your Sales_data class to rewrite the exercises in §1.5.1 (p. 22), § 1.5.2 (p. 24), and § 1.6 (p. 25).
// For now, you should define your Sales_data class in the same file as your main function.
#include "ex42.h"
#include <iostream>

int main() {
    Sales_data book1, book2;

    std::cin >> book1.isbn >> book1.price >> book1.units_sold >> book1.revenue >> book2.isbn >> book2.price >> book2.units_sold >> book2.revenue;
    std::cout << book1.isbn << book1.price << book1.units_sold << book1.revenue << std::endl;
    std::cout << book2.isbn << book2.price << book2.units_sold << book2.revenue << std::endl;
    book1.units_sold += book2.units_sold;
    book2.revenue += book2.revenue;
    std::cout << "SUM: " << book1.isbn << book1.price << book1.units_sold << book1.revenue << std::endl;

    return 0;
}