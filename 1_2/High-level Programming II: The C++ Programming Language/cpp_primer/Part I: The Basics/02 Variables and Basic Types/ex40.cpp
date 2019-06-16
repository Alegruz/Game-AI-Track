// Write your own version of the Sales_data class.
#include <string>

struct Sales_data {
    std::string bookNo;
    double price;
    unsigned int units_sold = 0;
    double revenue = 0.0;
};