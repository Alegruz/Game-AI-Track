// Provide operations in your Person class to return the name and address.
// Should these functions be const? Explain your choice.
#ifndef EX05_H
#define EX05_H

#include <string>

struct Person {
    std::string name;
    std::string address;
    std::string getName() const { return this->name; }
    std::string getAddress() const { return this->address; }
};

// value of `this` is not changing, thus I would prefer to use const.

#endif  //EX05_HH