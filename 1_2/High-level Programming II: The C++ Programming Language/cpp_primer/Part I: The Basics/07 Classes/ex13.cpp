// Rewrite the program from page 255 to use the istream constructor.
#include "ex12.h"

int main()
{
    Sales_data total(std::cin); // variable to hold data for the next transaction
    // read the first transaction and ensure that there are data to process
    if (std::cin) {
        Sales_data trans(std::cin); // variable to hold the running sum
        // read and process the remaining transactions
        while (std::cin) {
            // if we're still processing the same book
            
            if (total.isbn() == trans.isbn())
                total.combine(trans);   // update the running total
            else {
                // print results for the previous book
                write(std::cout, total);
                total = trans;  // total now refers to the next book
            }
        }
        write(std::cout, total); // print the last transaction
    } else {
        // no input! warn the user
        std::cerr << "No data?!" << std::endl;
        return -1;  // indicate failure
    }
    return 0;
}