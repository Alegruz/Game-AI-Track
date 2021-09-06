// Use your Sales_data class to rewrite the exercises in §1.5.1 (p. 22), § 1.5.2 (p. 24), and § 1.6 (p. 25).
// For now, you should define your Sales_data class in the same file as your main function.
#include "ex42.h"
#include <iostream>

int main() {
    Sales_data total; // variable to hold data for the next transaction
    // read the first transaction and ensure that there are data to process
    if (std::cin >> total.isbn >> total.price >> total.units_sold >> total.revenue) {
        Sales_data trans; // variable to hold the running sum
        // read and process the remaining transactions
        while (std::cin >> trans.isbn >> trans.price >> trans.units_sold >> trans.revenue) {
            // if we're still processing the same book
            if (total.isbn == trans.isbn) {
                total.units_sold += trans.units_sold; // update the running total
                total.revenue += trans.revenue;
            } else {
                // print results for the previous book
                std::cout << total.isbn << " "
                            << total.price << " "
                            << total.units_sold << " "
                            << total.revenue << std::endl;
                total = trans;  // total now refers to the next book
            }
        }
        std::cout << total.isbn << " "
                    << total.price << " "
                    << total.units_sold << " "
                    << total.revenue << std::endl; // print the last transaction
    } else {
        // no input! warn the user
        std::cerr << "No data?!" << std::endl;
        return -1;  // indicate failure
    }
    return 0;
}