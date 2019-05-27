// Test the previous program by giving multiple transactions
// representing multiple ISBN's. The records for each ISBN should be grouped
// together.

#include <iostream>
#include <vector>
#include "Sales_item.h"

int main() {
    std::vector<Sales_item> book_log;
    Sales_item book;
    bool duplicate;

    while (std::cin >> book) {
        duplicate = false;
        std::cout << "INPUT: " << book << std::endl;
        for (int i = 0; i < book_log.size(); ++i)
            if (book_log[i].isbn() == book.isbn()) {
                duplicate = true;
                book_log[i] += book;
                break;
            }
        
        if (!duplicate)
            book_log.push_back(book);
    }

    for (auto elem: book_log) {
        std::cout << "OUTPUT: " << elem << std::endl;
    }

    return 0;
}