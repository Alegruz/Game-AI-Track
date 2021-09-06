// Rewrite the exercises from § 1.4.1 (p. 13) and § 2.6.2 (p. 76)
// with appropriate using declarations.
#include "../02 Variables and Basic Types/ex42.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main() {
    Sales_data book1, book2;

    cin >> book1.isbn >> book1.price >> book1.units_sold >> book1.revenue >> book2.isbn >> book2.price >> book2.units_sold >> book2.revenue;
    cout << book1.isbn << book1.price << book1.units_sold << book1.revenue << endl;
    cout << book2.isbn << book2.price << book2.units_sold << book2.revenue << endl;
    book1.units_sold += book2.units_sold;
    book2.revenue += book2.revenue;
    cout << "SUM: " << book1.isbn << book1.price << book1.units_sold << book1.revenue << endl;

    return 0;
}