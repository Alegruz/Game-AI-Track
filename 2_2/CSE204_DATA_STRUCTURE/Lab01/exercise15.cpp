#include <iostream>
#include <stddef.h>

typedef char String[9];

struct StudentRecord
{
	String firstName;
	String lastName;
	int id;
	float gpa;
	// char gender;
	int currentHours;
	int totalHours;
};

int main()
{
	StudentRecord  student;
	student.gpa = 3.87;
	StudentRecord students[100];

	int offset = offsetof(StudentRecord, gpa);			// 24

	std::cout << "GPA: " << &student + offset << " to " << &student.gpa			<< std::endl;

	// struct의 memory layout은 추상적으로 공부를 할 때에는 struct의 구조 순서대로 메모리가 할당된다고 생각할 수 있으나, 실제로는 컴파일러마다 컴파일러가 원하는 대로 재배치한다.
	// Offset은 대신 순서대로 계산해낼 수는 있으나 실제로 메모리에 대입하면 작동하지 않는다.

	// 물론 추상적으로, 개념적으로 접근하면, &student가 100일 때, &student + offset은 100 + 24, 즉 124 이다.

	return 0;
}
