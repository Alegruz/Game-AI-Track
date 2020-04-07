#include "HouseType.h"

// HouseType.cpp is the implementation file for data for the real 
//  estate manipulation program.

bool HouseType::operator<(const HouseType& other) const
{
	return (mLastName < other.mLastName);
}

bool HouseType::operator<=(const HouseType& other) const
{
	return (mLastName <= other.mLastName);
}

bool HouseType::operator>(const HouseType& other) const
{
	return (mLastName > other.mLastName);
}

bool HouseType::operator>=(const HouseType& other) const
{
	return (mLastName >= other.mLastName);
}

bool HouseType::operator==(const HouseType& other) const
{
	return (mLastName == other.mLastName);
}
 
void HouseType::GetFromFile(std::ifstream& file) 
{
	GetWordInput(file, mLastName);
	GetWordInput(file, mFirstName);
	GetLineInput(file, mAddress);
	GetNumberInput(file, mPrice);
	GetNumberInput(file, mSquareFeet);
	GetNumberInput(file, mBedRooms);
	GetNumberInput(file, mBathrooms);
}

void HouseType::WriteToFile(std::ofstream& file)
{
	file << mLastName << std::endl;
	file << mFirstName << std::endl;
	file << mAddress << std::endl;
	file << mPrice << std::endl;
	file << mSquareFeet << std::endl;
	file << mBedRooms << std::endl;
	file << mBathrooms << std::endl;
}

void HouseType::GetFromUser() 
{
	std::cout << "Enter last name; press return." << std::endl;
	GetWordInput(std::cin, mLastName);
	std::cout << "Enter first name; press return." << std::endl;
	GetWordInput(std::cin, mFirstName);
	std::cout << "Enter address; press return." << std::endl;
	GetLineInput(std::cin, mAddress);
	std::cout << "Enter price, square feet, number of bedrooms, number of bathrooms;"
		<< " press return." << std::endl;
	GetNumberInput(std::cin, mPrice);
	GetNumberInput(std::cin, mSquareFeet);
	GetNumberInput(std::cin, mBedRooms);
	GetNumberInput(std::cin, mBathrooms);
}

void HouseType::PrintHouseToScreen()
{
	std::cout << mFirstName << " " << mLastName << " " << mAddress << std::endl;
	std::cout << "Price: " << mPrice << std::endl;
	std::cout << "Square Feet: " << mSquareFeet << std::endl;
	std::cout << "Bedrooms: " << mBedRooms << std::endl;
	std::cout << "Bathrooms: " << mBathrooms << std::endl;
}

void HouseType::GetNameFromUser() 
{
	std::cout << "Enter last name;  press return." << std::endl;
	GetWordInput(std::cin, mLastName);
	std::cout << "Enter first name;  press return." << std::endl;
	GetWordInput(std::cin, mFirstName);
}

void HouseType::PrintNameToScreen()
{
	std::cout << mFirstName << " " << mLastName << std::endl;
}