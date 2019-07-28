// Move the definition of the Sales_data constructor
// that takes an istream into the body of the Sales_data class.
#ifndef EX12_H
#define EX12_H

#include <string>
#include <iostream>

std::istream &read(std::istream &, Sales_data &);

struct Sales_data {
    // CONSTRUCTORS
    Sales_data() = default;
    Sales_data(const std::string &bn): bookNo(bn) {}
    Sales_data(const std::string &bn, double p, unsigned int us):
                bookNo(bn), price(p), units_sold(us), revenue(p * us) {}
    Sales_data(std::istream &is) { read(is, *this); }

    // MEMBER FUNCTIONS
    Sales_data &combine(const Sales_data &sd);
    std::string isbn() const { return this->bookNo; }
    double avg_price() const { return this->revenue / this->units_sold; };

    // MEMBER VARIABLES
    std::string bookNo;
    double price;
    unsigned int units_sold = 0;
    double revenue = 0.0;
};

// FUNCTIONS
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

// MEMBER VARIABLES DEFINITION
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

#endif // EX12_H