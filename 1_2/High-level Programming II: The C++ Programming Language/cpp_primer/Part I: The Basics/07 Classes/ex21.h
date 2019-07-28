// Update your Sales_data class to hide its implementation.
// The programs you’ve written to use Sales_data operations should still continue to work.
// Recompile those programs with your new class definition to verify that they still work.

#ifndef EX21_H
#define EX21_H

#include <string>
#include <iostream>

class Sales_data {
    // friend declarations for nonmember Sales_data operations added
    friend Sales_data add(const Sales_data &, const Sales_data &);
    friend std::istream &read(std::istream &, Sales_data &);
    friend std::ostream &print(std::ostream &, const Sales_data &);

// other members and access specifiers as before
public:
    Sales_data() = default;
    Sales_data(const std::string &s, unsigned n, double p):
               bookNo(s), units_sold(n), revenue(p*n) {}
    Sales_data(const std::string &s): bookNo(s) {}
    Sales_data(std::istream &is) { read(is, *this); }
    std::string isbn() const { return bookNo; }
    Sales_data &combine(const Sales_data &);

private:
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

// Member Function
Sales_data &Sales_data::combine(const Sales_data &sd) {
    this->units_sold += sd.units_sold;
    this->revenue += sd.revenue;
    return *this;
}

// declarations for nonmember parts of the Sales_data interface
Sales_data add(const Sales_data &sd1, const Sales_data &sd2) {
    Sales_data sd = sd1;
    sd.combine(sd2);
    return sd;
}

std::istream &read(std::istream &is, Sales_data &sd) {
    double price = 0.;
    is >> sd.bookNo >> sd.units_sold >> price;
    sd.revenue = price * sd.units_sold;
    return is;
}

std::ostream &print(std::ostream &os, const Sales_data &sd) {
    os << sd.bookNo << " " << sd.units_sold << " " << sd.revenue;
    return os;
}

#endif // EX21_H
