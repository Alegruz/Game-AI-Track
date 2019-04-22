/* Reads and prints the grade sums and the student sums of a 5x5 array */

#include <stdio.h>

int main(void) {
    double class_quiz_grades[5][5] = {{0.00}};
    double quiz_grade;
    double student_score[5] = {0.00};
    double quiz_score[5][3] = {{0.00}};
    double max[5], min[5];

    for (int student = 0; student < 5; ++student) {
        printf("Enter grade for student no %d: ", student + 1);
        for (int grade = 0; grade < 5; ++grade) {
            scanf("%lf", &quiz_grade);
            class_quiz_grades[student][grade] = quiz_grade;
        }
    }

    for (int i = 0; i < 5; ++i) {
        max[i] = class_quiz_grades[i][0];
        min[i] = class_quiz_grades[i][0];
    }

    for (int student = 0; student < 5; ++student) {
        for (int quiz = 0; quiz < 5; ++quiz) {
            student_score[student] += class_quiz_grades[student][quiz];
            quiz_score[quiz][0] += class_quiz_grades[student][quiz];
            if (class_quiz_grades[student][quiz] > max[quiz])
                max[quiz] = class_quiz_grades[student][quiz];
            else if (class_quiz_grades[student][quiz] < min[quiz])
                min[quiz] = class_quiz_grades[student][quiz];
        }
    }

    printf("\n");
    for (int student = 0; student < 5; ++student)
        printf("Student no. %d. Total Score: %.2lf, Average Score: %.2lf\n", student + 1, student_score[student], student_score[student] / 5.00);

    for (int quiz = 0; quiz < 5; ++quiz)
        printf("Quiz no. %d. Average Score: %.2lf, High Score: %.2lf, Low Score: %.2lf\n", quiz + 1, quiz_score[quiz][0] / 5.00, max[quiz], min[quiz]);

    return 0;
}
