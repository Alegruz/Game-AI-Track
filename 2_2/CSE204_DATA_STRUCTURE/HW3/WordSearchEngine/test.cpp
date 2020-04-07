#include "SortedStringMap.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

template<size_t N>
void SearchDictionary(const SortedStringMap<N>& dict);
std::string GetInput(const char* question);

int main()
{
	std::ifstream fileIn;
	SortedStringMap<30> dict;
	
	SearchDictionary<30>(dict);

	fileIn.open("Words.dat");
	dict.ReadFile(fileIn);

	SearchDictionary<30>(dict);

	fileIn.close();
	return 0;
}

template<size_t N>
void SearchDictionary(const SortedStringMap<N>& dict)
{
	if (dict.IsEmpty())
	{
		std::cout << "The Dictionary is EMPTY!! Search ended" << std::endl;
		return;
	}

	std::ofstream fileOut;
	fileOut.open("Pattern.out");
	if (!fileOut.is_open())
	{
		std::cout << "Output File creation failed. Terminating program..." << std::endl;
		return;
	}

	std::cout << "Welcome to Aperture Science Dictionary Search Engine!" << std::endl;
	char command;
	while (!std::cin.eof())
	{
		std::cout << "Please choose a command below:\n"
				"S: Find the meaning of the word that starts with the input\n"
				"E: Find the meaning of the word that ends with the input\n"
				"C: Find the meaning of the word that contains the input\n"
				"T: Terminate program" << std::endl;
	
		std::vector<std::string> keyResult;
		keyResult.reserve(dict.GetSize());
		std::string input;
		std::string trash;
		std::cin >> command;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin >> trash;
		}
		else
		{
			fileOut << command << std::endl;
			switch(command)
			{
			case 'S':	input = GetInput("Please enter the starting characters: ");
						fileOut << input << std::endl;
						if (dict.GetKeyStartsWithInput(input, keyResult) == true)
						{
							if (keyResult.size() > 1)
							{
								for (size_t result = 0; result < keyResult.size(); ++result)
								{
									fileOut << keyResult[result] << " ";
								}
								fileOut << "\n";
							}
							else
							{
								fileOut << keyResult[0] << " " << dict[keyResult[0]] << "\n";
							}
						}
						else
						{
							std::cout << "No word starts with " << input << std::endl;
							fileOut << "No word starts with " << input << std::endl;
						}
						break;
			case 'E':	input = GetInput("Please enter the ending characters: ");
						fileOut << input << std::endl;
						if (dict.GetKeyEndsWithInput(input, keyResult) == true)
						{
							if (keyResult.size() > 1)
							{
								for (size_t result = 0; result < keyResult.size(); ++result)
								{
									fileOut << keyResult[result] << " ";
								}
								fileOut << "\n";
							}
							else
							{
								fileOut << keyResult[0] << " " << dict[keyResult[0]] << "\n";
							}
						}
						else
						{
							std::cout << "No word ends with " << input << std::endl;
							fileOut << "No word ends with " << input << std::endl;
						}						
						break;
			case 'C':	input = GetInput("Please enter the containing characters: ");
						fileOut << input << std::endl;
						if (dict.GetKeyWithInput(input, keyResult) == true)
						{
							if (keyResult.size() > 1)
							{
								for (size_t result = 0; result < keyResult.size(); ++result)
								{
									fileOut << keyResult[result] << " ";
								}
								fileOut << "\n";
							}
							else
							{
								fileOut << keyResult[0] << " " << dict[keyResult[0]] << "\n";
							}
						}
						else
						{
							std::cout << "No word contains " << input << std::endl;
							fileOut << "No word contains " << input << std::endl;
						}				
						break;
			case 'T':	std::cout << "Program Termination.\nSearch ended" << std::endl;
						fileOut << "Program Termination.\nSearch ended" << std::endl;
						return;
			default:	std::cout << "INVALID INPUT; try again." << std::endl;
						fileOut << "INVALID INPUT; try again." << std::endl;
						std::cin.clear();
						std::cin >> trash;
						break;
			}
		}
	}

	fileOut.close();
}

std::string GetInput(const char* question)
{
	std::string input;
	std::string trash;
	while (!std::cin.eof())
	{
		std::cout << question;
		std::cin >> input;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin >> trash;
			std::cout << "INVALID INPUT!\n" << question;
		}
		else
		{
			return input;
		}
		
	}

	return input;
}