// Use your Sales_data class to rewrite the exercises in §1.5.1 (p. 22), § 1.5.2 (p. 24), and § 1.6 (p. 25).
// For now, you should define your Sales_data class in the same file as your main function.
#include "ex42.h"
#include <iostream>

int main() {
    Sales_data total, book;
    if (!(std::cin >> total.isbn >> total.price >> total.units_sold >> total.revenue)) {
        std::cerr << "INVALID INPUT" << std::endl;
        return -1;
    }
    while (std::cin >> book.isbn >> book.price >> book.units_sold >> book.revenue) {
        total.units_sold += book.units_sold;
        total.revenue += book.revenue;
    }
    
    std::cout << total.isbn << total.price << total.units_sold << total.revenue << std::endl;

    return 0;
}