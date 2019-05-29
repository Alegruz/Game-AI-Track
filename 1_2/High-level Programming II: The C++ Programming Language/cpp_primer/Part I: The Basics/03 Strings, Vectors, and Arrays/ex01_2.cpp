// Rewrite the exercises from § 1.4.1 (p. 13) and § 2.6.2 (p. 76)
// with appropriate using declarations.

#include <iostream>
#include <string>
#include "Sales_data.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

int main()
{
    Sales_data data1, data2;

    double price = 0;   // price per book, used to calculate total revenue
    // read the first transactions: ISBN, number of books sold, price per book
    cin >> data1.bookNo >> data1.units_sold >> price;
    // calculate total revenue from price and units_sold
    data1.revenue = data1.units_sold * price;
    // read the second transaction
    cin >> data2.bookNo >> data2.units_sold >> price;
    data2.revenue = data2.units_sold * price;
    
    if (data1.bookNo == data2.bookNo) {
        unsigned totalCnt = data1.units_sold + data2.units_sold;
        double totalRevenue = data1.revenue + data2.revenue;
        // print: ISBN, total sold, total revenue, average price per book
        cout << data1.bookNo << " " << totalCnt
                << " " << totalRevenue << " ";
        if (totalCnt != 0)
            cout << totalRevenue/totalCnt << std::endl;
        else
            cout << "(no sales)" << endl;
        return 0; // indicate success
    } else {  // transactions weren't for the same ISBN
        cerr << "Data must refer to the same ISBN"
                << endl;
        return -1; // indicate failure
    }
}
