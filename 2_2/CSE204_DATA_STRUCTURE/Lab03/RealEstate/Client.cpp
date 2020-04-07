// CLIENT PROGRAM 
// This program manipulates real estate property listings. 
#include <iostream> 
#include "SortedType.h"       // Gain access to Sorted List ADT. 
#include <fstream> 
#include <string>


enum eCommandType
{
	ADD,
	DELETE,
	PRINT_ONE,
	PRINT_ALL,
	QUIT
};

// Each constant represents a task. 
bool FileToList(SortedType&, std::ifstream&);
// moves houses from file to list 
void ListToFile(SortedType&, std::ofstream&);
// moves houses from list to file 
void AddHouse(SortedType&);
// adds a house to the list 
void DeleteHouse(SortedType&);
// removes a house from the list 
void PrintHouse(SortedType&);
// prints a specific owner listing 
void PrintOwners(SortedType&);
// prints a sorted list of owners 
void GetCommand(eCommandType&);
// prompts for and gets next command 

int main() 
{
	std::ifstream masterInputFile;		// master file of houses (input)
	std::ofstream masterOutputFile;	// master file of houses (output)
	eCommandType command;
	SortedType houseList;

	if (!FileToList(houseList, masterInputFile))
	{
		return -1;
	}

	GetCommand(command); 
	// Read and process commands until user enters a quit command.

	while (command != QUIT) 
	{
		switch (command) 
		{
			case ADD      : AddHouse(houseList);
							break; 
			case DELETE   : DeleteHouse(houseList);
							break; 
			case PRINT_ONE: PrintHouse(houseList);
							break;
			case PRINT_ALL: PrintOwners(houseList);
							break; 
			default:		break;
		} 
		GetCommand(command); 
	}

	ListToFile(houseList, masterOutputFile); 
	return 0; 
}

//*************************************************************
// **************** Second Level Functions ********************

bool FileToList(SortedType& houseList, std::ifstream& masterInputFile) 
// Pre:  masterInputFile has not been opened. 
// Post: houseList contains items from masterInputFile. 
//       masterInputFile has been closed. 
{
	HouseType house;
	std::string fileName;

	// Prompt for file names, read file names, and prepare files
	std::cout << "Enter name of file of houses; press return. (Enter 0 to terminate)" << std::endl;
	std::string trash;
	while (!std::cin.eof())
	{
		std::cin  >> fileName;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin >> trash;
		}
		else
		{
			if (fileName == "0")
			{
				std::cout << "Program Terminated. Thank you for using our product" << std::endl;
				return false;
			}
			break;
		}
	}

	masterInputFile.open(fileName.c_str());

	while (!masterInputFile.eof())
	{
		house.GetFromFile(masterInputFile);  // Reads one house from masterInputFile.

		if (masterInputFile.fail())
		{
			masterInputFile.clear();
			masterInputFile >> trash;
		}
		else
		{
			houseList.InsertItem(house);
		}
	}
	masterInputFile.close();

	return true;
}

void ListToFile(SortedType& houseList, std::ofstream& masterOutputFile) 
// Pre:  masterOutputFile has not been opened. 
//       houseList has been initialized. 
// Post: houseList has been written on masterOutputFile. 
//       masterOutputFile has been closed. 
{
  HouseType house; 
  int length;
  std::string outFileName;
  std::cout << "Enter name of output file; press return." << std::endl;
  std::cin  >> outFileName;
  masterOutputFile.open(outFileName.c_str());

  houseList.ResetList(); 
  length = houseList.LengthIs(); 

  for (int count = 1; count <= length; count++) 
  {
    houseList.GetNextItem(house); 
    house.WriteToFile(masterOutputFile); 
  }

  masterOutputFile.close(); 
}

void AddHouse(SortedType& houseList) 
// Pre:  houseList has been initialized. 
// Post: A house has been added to the list if the names are 
//       not duplicated; otherwise the operation is aborted with 
//       message to user. 
{
	HouseType house;

	house.GetFromUser();
	if (!houseList.RetrieveItem(house)) 
	{
		houseList.InsertItem(house);
	}
	else
	{
		std::cout << "Duplicate name; operation aborted" << std::endl; 
	}
}

void DeleteHouse(SortedType& houseList) 
// Pre:  houseList has been initialized. 
// Post: A house, specified by user input, is no longer in the list. 
{

	HouseType house;

	house.GetNameFromUser(); 
	if (houseList.RetrieveItem(house)) 
	{
		houseList.DeleteItem(house); 
		std::cout << "Operation completed." << std::endl; 
	} 
	else
	{
    	std::cout << "Person not in list." << std::endl;
	}
}

void PrintHouse(SortedType& houseList) 
// Pre:  houseList has been initialized. 
// Post: If owner, specified by user input, is in houseList, 
//       house info is printed on the screen. 
{
	HouseType house;

	house.GetNameFromUser();
	if (houseList.RetrieveItem(house))
	{
		house.PrintHouseToScreen(); 
	}
	else
	{
		std::cout << "Owner not in list." << std::endl;
	}
}

void PrintOwners(SortedType& houseList) 
// Pre:  houseList has been initialized. 
// Post: Owners' names are printed on the screen.
{
	HouseType house;
	int length;

	houseList.ResetList(); 
	length = houseList.LengthIs(); 
	for (int count = 1; count <= length; count++) 
	{
		houseList.GetNextItem(house); 
		house.PrintNameToScreen();
	} 
	std::cout << "Operation completed." << std::endl;
}

void GetCommand(eCommandType& command) 
// Pre:  None 
// Post: User command has been prompted for and input; a valid 
//       command has been found. 
{
	// Prompt.
	std::cout << "Operations are listed below. " 
			<< "Enter the appropriate uppercase letter and " 
			<< "press return."  << std::endl; 
	std::cout << "A : Add a house to the list of houses." << std::endl; 
	std::cout << "D : Delete a specific owner's house."  << std::endl; 
	std::cout << "P : Print the information about an owner's house." 
			<< std::endl; 
	std::cout << "L : Print all the names on the screen." 
			<< std::endl; 
	std::cout << "Q : Quit processing."  << std::endl;
	
	// Input command. 
	char letter;
	std::string trash;

	while (!std::cin.eof())
	{
		std::cin >> letter;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin >> trash;
		}
		else
		{
			switch (letter) 
			{
				case 'A':	command = ADD;
							return;
				case 'D': 	command = DELETE;
							return;
				case 'P': 	command = PRINT_ONE;
							return;
				case 'L':	command = PRINT_ALL;
							return;
				case 'Q': 	command = QUIT;
							return;
				default: 	std::cout << "Letter entered is not one of the "
									<< "specified uppercase commands. " 
									<< "Reenter and press return."
									<< std::endl;
							std::cin.clear();
							std::cin >> trash;
							break;
			}
		}
	}
}


