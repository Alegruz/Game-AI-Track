/* Simplify the if statements as much as possible */

#include <stdio.h>

int main(void) {
    int age;
    bool teenager;

    printf("Enter your age: ");
    scanf("%d", &age);

//    if (age >= 13)
//        if (age <= 19)
//            teenager = true;
//        else
//            teenager = false;
//    else if (age < 13)
//        teenager = false;

    teenager = age >= 13 && age <= 19;

    if (teenager)
        printf("You are a teenager!\n");
    else
        printf("You are not a teenager!\n");

    return 0;
}
