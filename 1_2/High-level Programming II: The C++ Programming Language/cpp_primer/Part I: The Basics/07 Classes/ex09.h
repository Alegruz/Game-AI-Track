// Add operations to read and print Person objects to the code
// you wrote for the exercises in § 7.1.2 (p. 260).

#ifndef EX09_H
#define EX09_H

#include <string>
#include <iostream>

struct Person {
    std::string name;
    std::string address;
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

#endif  //EX09_H