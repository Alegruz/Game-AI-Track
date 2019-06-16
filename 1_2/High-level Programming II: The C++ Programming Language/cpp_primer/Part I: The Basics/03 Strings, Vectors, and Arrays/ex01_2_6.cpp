// Rewrite the exercises from § 1.4.1 (p. 13) and § 2.6.2 (p. 76)
// with appropriate using declarations.

#include <iostream>
#include "../02 Variables and Basic Types/ex42.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

int main()
{
    Sales_data total; // variable to hold data for the next transaction
    // read the first transaction and ensure that there are data to process
    if (cin >> total.isbn >> total.price >> total.units_sold >> total.revenue) {
        Sales_data trans; // variable to hold the running sum
        // read and process the remaining transactions
        while (cin >> trans.isbn >> trans.price >> trans.units_sold >> trans.revenue) {
            // if we're still processing the same book
            if (total.isbn == trans.isbn) {
                total.units_sold += trans.units_sold; // update the running total
                total.revenue += trans.revenue;
            } else {
                // print results for the previous book
                cout << total.isbn << " "
                            << total.price << " "
                            << total.units_sold << " "
                            << total.revenue << endl;
                total = trans;  // total now refers to the next book
            }
        }
        cout << total.isbn << " "
                    << total.price << " "
                    << total.units_sold << " "
                    << total.revenue << endl; // print the last transaction
    } else {
        // no input! warn the user
        cerr << "No data?!" << endl;
        return -1;  // indicate failure
    }
    return 0;
}
