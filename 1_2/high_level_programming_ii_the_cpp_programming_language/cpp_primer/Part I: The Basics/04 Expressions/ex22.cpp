// Extend the program that assigned high pass, pass, and fail grades
// to also assign low pass for grades between 60 and 75 inclusive.
// Write two versions:
// One version that uses only conditional operators;
// the other should use one or more if statements.
// Which version do you think is easier to understand and why?
#include <iostream>
#include <string>

int main() {
    int grade;
    std::string finalgrade1 = (grade > 90) ? "high pass" :
                            (grade > 75) ? "pass" :
                            (grade > 60) ? "low pass" : "fail";
    
    std::string finalgrade2;
    if (grade > 90)
        finalgrade2 = "high pass";
    else if (grade > 75)
        finalgrade2 = "pass";
    else if (grade > 60)
        finalgrade2 = "low pass";
    else
        finalgrade2 = "fail";

    // Easier to understand? definitely latter, the cascaded if.   

    return 0;
}