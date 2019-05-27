// http://www.informit.com/title/032174113 contains a copy of
// Sales_item.h in the Chapter 1 code directory. Copy that file to your
// working directory. Use it to write a program that reads a set of book sales
// transactions, writing each transaction to the standard output.
#include <iostream>
#include "Sales_item.h"

int main() {
    std::cout << "Welcome to book sales transaction manager." << std::endl;
    Sales_item prev_book;

    // read ISBN, number of copies sold, and sales price
    if (!(std::cin >> prev_book)) {
        std::cerr << "INVALID INPUT" << std::endl;
        return -1;
    }
    std::cout << "INPUT: " << prev_book << std::endl;

    Sales_item book;
    while (std::cin >> book) {
        std::cout << "INPUT: " << book << std::endl;
        
        if (prev_book.isbn() == book.isbn())
            prev_book += book;
        else {
            std::cout << "OUTPUT: " << prev_book << std::endl;
            prev_book = book;
        }
    }
    std::cout << "OUTPUT: " << prev_book << std::endl;


    std::cout << "Program Terminated" << std::endl;
    return 0;
}