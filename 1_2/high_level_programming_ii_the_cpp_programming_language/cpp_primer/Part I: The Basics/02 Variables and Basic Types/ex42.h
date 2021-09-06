// Write your own version of the Sales_data.h header and use it to rewrite the exercise from § 2.6.2 (p. 76).
#if !defined(EX42_H)
#define EX42_H

#include <string>

struct Sales_data {
    std::string isbn;
    double price;
    unsigned int units_sold = 0;
    double revenue = 0.0;
};

#endif // EX42_H
