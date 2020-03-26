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
	StudentRecord  student;			// students의 크기는 36바이트
	student.gpa = 3.87;
	StudentRecord students[100];	// 36바이트를 갖는 개체의 개수가 100인 배열, 즉 36 * 100 == 3600 바이트

	std::cout << sizeof(students) << std::endl;	// 3600

	return 0;
}
