#include "IOhandler.h"

void GetLineInput(std::istream& in, std::string& stringIn)
{
	std::string trash;
	in >> trash;
	while (!in.eof())
	{
		getline(in, stringIn);

		if (in.fail())
		{
			in.clear();
			in >> trash;
			trash.clear();
		}
		else if (stringIn == "\n")
		{
			continue;
		}
		else if (stringIn.length() > 0)
		{
			if (trash != "\n")
			{
				trash += stringIn;
				stringIn = trash;
			}
			return;
		}
	}
}

void GetWordInput(std::istream& in, std::string& stringIn)
{
	std::string trash;
	while (!in.eof())
	{
		in >> stringIn;

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