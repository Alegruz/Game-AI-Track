// Write a program that reads several transactions for the same
// ISBN . Write the sum of all the transactions that were read.
#include <iostream>
#include "Sales_item.h"

int main() {
    Sales_item total, book;
    if (!(std::cin >> total)) {
        std::cerr << "INVALID INPUT" << std::endl;
        return -1;
    }
    while (std::cin >> book)
        total += book;
    
    std::cout << total << std::endl;

    return 0;
}