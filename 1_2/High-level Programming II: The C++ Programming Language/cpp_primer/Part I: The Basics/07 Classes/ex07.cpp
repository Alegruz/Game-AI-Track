// Rewrite the transaction-processing program you wrote for the
// exercises in § 7.1.2 (p. 260) to use these new functions.
#include <iostream>
#include "ex06.h"

int main()
{
    Sales_data total; // variable to hold data for the next transaction
    // read the first transaction and ensure that there are data to process
    if (read(std::cin, total)) {
        Sales_data trans; // variable to hold the running sum
        // read and process the remaining transactions
        while (read(std::cin, trans)) {
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