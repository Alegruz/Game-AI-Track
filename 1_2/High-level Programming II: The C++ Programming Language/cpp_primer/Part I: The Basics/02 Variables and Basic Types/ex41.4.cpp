// Use your Sales_data class to rewrite the exercises in §1.5.1 (p. 22), § 1.5.2 (p. 24), and § 1.6 (p. 25).
// For now, you should define your Sales_data class in the same file as your main function.
#include "ex42.h"
#include <iostream>

int main() {
    std::cout << "Welcome to book sales transaction manager." << std::endl;
    Sales_data prev_book, book;
    int transaction_count = 0;

    // read ISBN, number of copies sold, and sales price
    if (!(std::cin >> prev_book.isbn >> prev_book.price >> prev_book.units_sold >> prev_book.revenue)) {
        std::cerr << "Error in initial input: NO INPUT" << std::endl;
        return -1;
    }
    std::cout << "INPUT: " << prev_book.isbn << " "
                            << prev_book.price << " "
                            << prev_book.units_sold << " "
                            << prev_book.revenue << std::endl;
    transaction_count = 1;

    while (std::cin >> book.isbn >> book.price >> book.units_sold >> book.revenue) {     
        std::cout << "INPUT: " << book.isbn << " "
                                << book.price << " "
                                << book.units_sold << " "
                                << book.revenue << std::endl;
        
        if (prev_book.isbn == book.isbn) {
            prev_book.units_sold += book.units_sold;
            prev_book.revenue += book.revenue;
            ++transaction_count;
        } else {
            std::cout << "OUTPUT: " << prev_book.isbn << " "
                                    << prev_book.price << " "
                                    << prev_book.units_sold << " "
                                    << prev_book.revenue
                                    << " number of transaction: " << transaction_count << std::endl;
            prev_book = book;
            transaction_count = 1;
        }
    }
    std::cout << "OUTPUT: " << prev_book.isbn << " "
                            << prev_book.price << " "
                            << prev_book.units_sold << " "
                            << prev_book.revenue
                            << " number of transaction: " << transaction_count << std::endl;

    std::clog << "$ Program Terminated" << std::endl;
    return 0;
}