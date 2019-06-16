// Rewrite the exercises from § 1.4.1 (p. 13) and § 2.6.2 (p. 76)
// with appropriate using declarations.
#include "../02 Variables and Basic Types/ex42.h"
#include <iostream>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

int main() {
    Sales_data total, book;
    if (!(cin >> total.isbn >> total.price >> total.units_sold >> total.revenue)) {
        cerr << "INVALID INPUT" << endl;
        return -1;
    }
    while (cin >> book.isbn >> book.price >> book.units_sold >> book.revenue) {
        total.units_sold += book.units_sold;
        total.revenue += book.revenue;
    }
    
    cout << total.isbn << total.price << total.units_sold << total.revenue << endl;

    return 0;
}
