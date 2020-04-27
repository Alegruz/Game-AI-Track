/*
If memory locations are allocated as shown in the second column of the following table, what is printed by the statements in the first column?
Fill in the last column in the following table for Exercises 19–24.
The exercise number is in the first-column comments.
Statements							Memory Allocated			What Is Printed?
int value;							value is at location 200	
value = 500;
char* charPtr;						charPtris at location 202
char string[10] = "Good luck";		string[0]is at location 300
charPtr = string;
cout << &value; // Exercise 19		&means "the address of"		"200"				address of value
cout << value; // Exercise 20									"500"				stored value of variable value
cout << &charPtr; // Exercise 21	&means "the address of"		"202"				address of charPtr
cout << charPtr; // Exercise 22									"Good Luck"			value of charPtr as a string
cout << *charPtr; // Exercise 23								"G"					value of char charPtr is pointing, the first char of the string
cout << &string[2]; // Exercise 24								"od Luck"			value of third char of the string as a string, which translates into a string that starts from the third char of string
*/