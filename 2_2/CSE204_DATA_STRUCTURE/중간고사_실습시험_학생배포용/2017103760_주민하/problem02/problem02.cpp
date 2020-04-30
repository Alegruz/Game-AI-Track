#include "Queue.h"
#include "Stack.h"

#include <cctype>
#include <iostream>

bool isPalindrome(char* myStr);

int main()
{
	char myStr[100];
	
	std::cout << "Enter a string: ";
	std::cin >> myStr;

	if (isPalindrome(myStr) == true)
	{
		std::cout << "It's a palindrome." << std::endl;
	}
	else
	{
		std::cout << "It's NOT a palindrome." << std::endl;
	}

	return 0;
}

bool isPalindrome(char *myStr)
{
	Stack<char> s;
	Queue<char> q;
	char* character = myStr;
	char sItem;
	char qItem;

	while ( *character != '\0' )
	{
		if ( *character == '\n' )
		{
			continue;
		}

		s.Push(*character);
		q.Enqueue(*character);
		++character;
	}
	
	while ( !q.IsEmpty() && !s.IsEmpty() )
	{
		s.Pop(sItem);
		q.Dequeue(qItem);

		if ( toupper(sItem) != toupper(qItem) )
		{
			return false;
		}
	}

	return true;
}