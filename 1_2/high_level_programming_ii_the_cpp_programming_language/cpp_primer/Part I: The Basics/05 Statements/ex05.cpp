// Using an if–else statement, write your own version of the program to generate the letter grade from a numeric grade.
#include <iostream>
#include <vector>
#include <string>


int main() {
    std::vector<std::string> scores = {"F", "D", "C", "B", "A", "A++"};
    std::string lettergrade;
    int grade;

    while (std::cin >> grade)
        if (grade < 60)
            lettergrade = scores[0];
        else
            lettergrade = scores[(grade-50)/10];
            lettergrade += (grade % 10 > 7) ? "+" : (grade % 10 < 3) ? "-" : "";
        
        std::cout << "Grade: " << lettergrade << std::endl;

        

    return 0;
}