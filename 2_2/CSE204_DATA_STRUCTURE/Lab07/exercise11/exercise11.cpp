#include "TextEditor.h"

#include <iostream>

int main()
{
	TextEditor te1("test");
	TextEditor te2;

	std::cout << te1 << std::endl;

	te1.PrintCurrentLine();

	te1.GoToBottom();
	te1.PrintCurrentLine();
	te1.GoToTop();
	te1.PrintCurrentLine();

	te1.Insert("Second node?");

	std::cout << te1 << std::endl;

	te1.GoToBottom();

	te1.Insert("Last node?");

	std::cout << te1 << std::endl;

	std::cout << te2 << std::endl;

	te2.Insert("First Node!");

	std::cout << te2 << std::endl;

	te2.Insert("Last Node!");

	std::cout << te2 << std::endl;

	return 0;
}