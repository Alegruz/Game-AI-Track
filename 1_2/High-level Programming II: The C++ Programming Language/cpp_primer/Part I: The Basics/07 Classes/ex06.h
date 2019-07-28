// Define your own versions of the add, read, and print functions.
#if !defined(EX06_H)
#define EX06_H

#include <string>
#include <iostream>

struct Sales_data {
    std::string bookNo;
    double price;
    unsigned int units_sold = 0;
    double revenue = 0.0;
    Sales_data &combine(const Sales_data &sd);
    std::string isbn() const { return this->bookNo; }
};

Sales_data &Sales_data::combine(const Sales_data &sd) {
    this->units_sold += sd.units_sold;
    this->revenue += sd.revenue;
    return *this;
}

Sales_data add(const Sales_data &sd1, const Sales_data &sd2) {
    Sales_data nsd = sd1;
    nsd.combine(sd2);
    return nsd;
}

std::istream &read(std::istream &is, Sales_data &sd) {
    double price = 0.;
    is >> sd.bookNo >> sd.units_sold >> price;
    sd.revenue = price * sd.units_sold;
    return is;
}

std::ostream &write(std::ostream &os, Sales_data &sd) {
    os << sd.isbn() << ' ' << sd.units_sold << ' '
        << sd.revenue << std::endl;
    return os;
}

#endif // EX06_H
