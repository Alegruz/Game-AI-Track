// Rewrite your grading program to use the conditional operator (§ 4.7, p. 151) in place of the if–else statement.

#include <iostream>
#include <vector>
#include <string>


int main() {
    std::vector<std::string> scores = {"F", "D", "C", "B", "A", "A++"};
    std::string lettergrade;
    int grade;

    while (std::cin >> grade)
        lettergrade = (grade < 60) ? scores[0] : (lettergrade = scores[(grade-50)/10] + ((grade % 10 > 7) ? "+" : (grade % 10 < 3) ? "-" : ""));
        
        std::cout << "Grade: " << lettergrade << std::endl;

        

    return 0;
}