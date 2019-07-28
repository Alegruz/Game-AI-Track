// Indicate which members of your Person class you
// would declare as public and which you would
// declare as private. Explain your choice.
#ifndef EX19_H
#define EX19_H

#include <string>
#include <iostream>

class Person {
private:
    std::string name;
    std::string address;
public:
    Person() = default;
    Person(const std::string &n): name(n) {}
    Person(const std::string &n, const std::string &ad): name(n), address(ad) {}

    std::string getName() const { return this->name; }
    std::string getAddress() const { return this->address; }

    std::istream &read(std::istream &is) {
        is >> this->name >> this->address;
        return is;
    }

    std::ostream &print(std::ostream &os) {
        os << "NAME: " << this->name << "\nADDRESS: " << this->address << std::endl;
        return os;
    }

};

#endif  //EX19_H