// Use your Sales_data class to rewrite the exercises in §1.5.1 (p. 22), § 1.5.2 (p. 24), and § 1.6 (p. 25).
// For now, you should define your Sales_data class in the same file as your main function.
#include "ex42.h"
#include <iostream>
#include <vector>

int main() {
    std::vector<Sales_data> book_log;
    Sales_data book;
    bool duplicate;

    while (std::cin >> book.isbn >> book.price >> book.units_sold >> book.revenue) {
        duplicate = false;
        std::cout << "INPUT: " << book.isbn << " "
                                << book.price << " "
                                << book.units_sold << " "
                                << book.revenue << std::endl;
        for (int i = 0; i < book_log.size(); ++i)
            if (book_log[i].isbn == book.isbn) {
                duplicate = true;
                book_log[i].units_sold += book.units_sold;
                book_log[i].revenue += book.revenue;
                break;
            }
        
        if (!duplicate)
            book_log.push_back(book);
    }

    for (auto elem: book_log) {
        std::cout << "OUTPUT: " << elem.isbn << " "
                                << elem.price << " "
                                << elem.units_sold << " "
                                << elem.revenue << std::endl;
    }

    return 0;
}
}