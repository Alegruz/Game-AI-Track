// Add appropriate constructors to your Person class.
#ifndef EX15_H
#define EX15_H

#include <string>
#include <iostream>

struct Person {
    std::string name;
    std::string address;

    Person() = default;
    Person(const std::string &n): name(n) {}
    Person(const std::string &n, const std::string &ad): name(n), address(ad) {}

    std::string getName() const { return this->name; }
    std::string getAddress() const { return this->address; }
};

std::istream &read(std::istream &is, Person &p) {
    is >> p.name >> p.address;
    return is;
}

std::ostream &print(std::ostream &os, const Person &p) {
    os << "NAME: " << p.name << "\nADDRESS: " << p.address << std::endl;
    return os;
}

#endif  //EX15_H