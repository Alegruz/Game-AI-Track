// Rewrite the exercises from § 1.4.1 (p. 13) and § 2.6.2 (p. 76)
// with appropriate using declarations.

#include <iostream>
#include "../02 Variables and Basic Types/ex42.h"
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::clog;

int main()
{
    cout << "Welcome to book sales transaction manager." << endl;
    Sales_data prev_book, book;
    int transaction_count = 0;

    // read ISBN, number of copies sold, and sales price
    if (!(cin >> prev_book.isbn >> prev_book.price >> prev_book.units_sold >> prev_book.revenue)) {
        cerr << "Error in initial input: NO INPUT" << endl;
        return -1;
    }
    cout << "INPUT: " << prev_book.isbn << " "
                            << prev_book.price << " "
                            << prev_book.units_sold << " "
                            << prev_book.revenue << endl;
    transaction_count = 1;

    while (cin >> book.isbn >> book.price >> book.units_sold >> book.revenue) {     
        cout << "INPUT: " << book.isbn << " "
                                << book.price << " "
                                << book.units_sold << " "
                                << book.revenue << endl;
        
        if (prev_book.isbn == book.isbn) {
            prev_book.units_sold += book.units_sold;
            prev_book.revenue += book.revenue;
            ++transaction_count;
        } else {
            cout << "OUTPUT: " << prev_book.isbn << " "
                                    << prev_book.price << " "
                                    << prev_book.units_sold << " "
                                    << prev_book.revenue
                                    << " number of transaction: " << transaction_count << endl;
            prev_book = book;
            transaction_count = 1;
        }
    }
    cout << "OUTPUT: " << prev_book.isbn << " "
                            << prev_book.price << " "
                            << prev_book.units_sold << " "
                            << prev_book.revenue
                            << " number of transaction: " << transaction_count << endl;

    clog << "$ Program Terminated" << endl;
    return 0;
}
