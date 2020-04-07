#pragma once

#include <iostream>
#include <string>

void GetLineInput(std::istream& in, std::string& stringIn);
void GetWordInput(std::istream& in, std::string& stringIn);

template<typename T>
void GetNumberInput(std::istream& in, T& number)
{
	std::string trash;
	while (!in.eof())
	{
		in >> number;

		if (in.fail())
		{
			in.clear();
			in >> trash;
		}
		else
		{
			return;
		}
	}
}