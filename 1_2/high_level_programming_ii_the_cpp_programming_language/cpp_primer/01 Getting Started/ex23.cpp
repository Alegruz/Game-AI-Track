// Write a program that reads several transactions and counts
// how many transactions occur for each ISBN .
#include <iostream>
#include "Sales_item.h"

int main() {
    std::cout << "Welcome to book sales transaction manager." << std::endl;
    Sales_item prev_book, book;
    int transaction_count = 0;

    // read ISBN, number of copies sold, and sales price
    if (!(std::cin >> prev_book)) {
        std::cerr << "Error in initial input: NO INPUT" << std::endl;
        return -1;
    }
    std::cout << "INPUT: " << prev_book << std::endl;
    transaction_count = 1;

    while (std::cin >> book) {     
        std::cout << "INPUT: " << book << std::endl;
        
        if (prev_book.isbn() == book.isbn()) {
            prev_book += book;
            ++transaction_count;
        } else {
            std::cout << "OUTPUT: " << prev_book << " number of transaction: " << transaction_count << std::endl;
            prev_book = book;
            transaction_count = 1;
        }
    }
    std::cout << "OUTPUT: " << prev_book <<  " number of transaction: " << transaction_count << std::endl;

    std::clog << "$ Program Terminated" << std::endl;
    return 0;
}