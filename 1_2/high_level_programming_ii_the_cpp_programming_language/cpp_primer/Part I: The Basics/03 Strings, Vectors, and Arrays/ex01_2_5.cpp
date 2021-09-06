// Rewrite the exercises from § 1.4.1 (p. 13) and § 2.6.2 (p. 76)
// with appropriate using declarations.

#include <iostream>
#include <vector>
#include "../02 Variables and Basic Types/ex42.h"
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

int main()
{
    std::vector<Sales_data> book_log;
    Sales_data book;
    bool duplicate;

    while (cin >> book.isbn >> book.price >> book.units_sold >> book.revenue) {
        duplicate = false;
        cout << "INPUT: " << book.isbn << " "
                                << book.price << " "
                                << book.units_sold << " "
                                << book.revenue << endl;
        for (int i = 0; i < book_log.size(); ++i)
            if (book_log[i].isbn == book.isbn) {
                duplicate = true;
                book_log[i].units_sold += book.units_sold;
                book_log[i].revenue += book.revenue;
                break;
            }
        
        if (!duplicate)
            book_log.push_back(book);
    }

    for (auto elem: book_log) {
        cout << "OUTPUT: " << elem.isbn << " "
                                << elem.price << " "
                                << elem.units_sold << " "
                                << elem.revenue << endl;
    }

    return 0;
}
