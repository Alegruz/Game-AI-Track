// Rewrite the exercises from § 1.4.1 (p. 13) and § 2.6.2 (p. 76)
// with appropriate using declarations.
#include "../02 Variables and Basic Types/ex42.h"
#include <iostream>

using std::cout;
using std::endl;
using std::cin;
using std::cerr;

int main() {
    cout << "Welcome to book sales transaction manager." << endl;
    Sales_data prev_book;

    // read ISBN, number of copies sold, and sales price
    if (!(cin >> prev_book.isbn >> prev_book.price >> prev_book.units_sold >> prev_book.revenue))
        cerr << "INVALID INPUT" << endl;
        return -1;

    cout << "INPUT: " << prev_book.isbn << " "
                            << prev_book.price << " "
                            << prev_book.units_sold << " "
                            << prev_book.revenue << endl;

    Sales_data book;
    cout << "Enter an isbn" << endl;
    while (cin >> book.isbn >> book.price >> book.units_sold >> book.revenue) {
        cout << "INPUT: " << book.isbn << " "
                                << book.price << " "
                                << book.units_sold << " "
                                << book.revenue << endl;

        if (prev_book.isbn == book.isbn) {
            prev_book.units_sold += book.units_sold;
            prev_book.revenue += book.revenue;
        } else {
            cout << "OUTPUT: " << prev_book.isbn << " "
                                    << prev_book.price << " "
                                    << prev_book.units_sold << " "
                                    << prev_book.revenue << endl;
            prev_book = book;
        }
    }
    cout << "OUTPUT: " << prev_book.isbn << " "
                            << prev_book.price << " "
                            << prev_book.units_sold << " "
                            << prev_book.revenue << endl;


    cout << "Program Terminated" << endl;
    return 0;
}