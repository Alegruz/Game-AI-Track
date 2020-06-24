#include <iostream>

#include "HashTable.h"
#include "Student.h"

int main()
{
	Student* stu[100];
	stu[0] = new Student();
	stu[0]->InitValue(2003200111, "이웅재", 3.0);
	stu[1] = new Student();
	stu[1]->InitValue(2004200121, "권오준", 3.2);
	stu[2] = new Student();
	stu[2]->InitValue(2005200132, "김진일", 2.7);

	HashTable<Student> ht;
	for (size_t studentIndex = 0; studentIndex < 3; ++studentIndex)
	{
		ht.InsertItem(stu[studentIndex]);
	}

	Student* studentToFind = new Student();
	studentToFind->InitValue(2005200132, "김진일", 0.0);
	bool bHasFoundStudent = false;
	ht.RetrieveItem(studentToFind, bHasFoundStudent);
	stu[3] = studentToFind;

	PrintByPointer(cout, stu, 4);
	return 0;
}