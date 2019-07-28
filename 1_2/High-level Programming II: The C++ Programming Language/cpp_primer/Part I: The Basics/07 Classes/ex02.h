// Add the combine and isbn members to the Sales_data class
// you wrote for the exercises in § 2.6.2 (p. 76).
#if !defined(EX02_H)
#define EX02_H

#include <string>

struct Sales_data {
    std::string isbn;
    double price;
    unsigned int units_sold = 0;
    double revenue = 0.0;
    Sales_data &combine(const Sales_data &sd);
    std::string getIsbn() const { return this->isbn; }
};

Sales_data &Sales_data::combine(const Sales_data &sd) {
    if (this->isbn != sd.isbn)
        return;

    this->units_sold += sd.units_sold;
    this->revenue += sd.revenue;
    return *this;
}

#endif // EX02_H
