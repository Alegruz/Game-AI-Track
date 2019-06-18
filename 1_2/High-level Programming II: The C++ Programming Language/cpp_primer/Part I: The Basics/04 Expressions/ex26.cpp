// In our grading example in this section, what would happen if we used unsigned int as the type for quiz1?

int main() {
    unsigned int quiz1 = 0;
    // int has at least 16 bits. thus, if the system says int has 16 bits, students above number 16 would be expelled from school.

    // student no 27 has passed
    quiz1 |= 1u << 27;

    // student no 28 has failed
    quiz1 &= ~(1u << 28);

    // has student no 27 passed?
    bool status = quiz1 & (1u << 27);

    return 0;
}