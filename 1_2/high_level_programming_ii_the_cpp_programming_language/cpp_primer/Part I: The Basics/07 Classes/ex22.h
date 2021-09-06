// Update your Person class to hide its implementation.
#ifndef EX19_H
#define EX19_H

#include <string>
#include <iostream>

class Person {
// FRIENDS:
    friend std::istream &read(std::istream &, Person &);
    friend std::ostream &print(std::ostream &, const Person &);

private:
    std::string name;
    std::string address;
public:
    Person() = default;
    Person(const std::string &n): name(n) {}
    Person(const std::string &n, const std::string &ad): name(n), address(ad) {}

    std::string getName() const { return this->name; }
    std::string getAddress() const { return this->address; }\
};

std::istream &read(std::istream &is, Person &p) {
    is >> p.name >> p.address;
    return is;
}

std::ostream &print(std::ostream &os, const Person &p) {
    os << "NAME: " << p.name << "\nADDRESS: " << p.address << std::endl;
    return os;
}

#endif  //EX19_H