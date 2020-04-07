// HouseType.h  contains the specifications for the data for the real
//  estate manipulation program.
#include "IOhandler.h"

#include <fstream>
#include <iostream>
#include <string>

const int MAX_ITEMS = 25;

enum eRelationType
{
	LESS,
	EQUAL,
	GREATER
};

class HouseType
{ 
public:
	HouseType() = default;
	HouseType(const HouseType& other) = delete;
	~HouseType() = default;
	
	bool operator<(const HouseType& other) const;
	bool operator<=(const HouseType& other) const;
	bool operator>(const HouseType& other) const;
	bool operator>=(const HouseType& other) const;
	bool operator==(const HouseType& other) const;
	HouseType& operator=(const HouseType& other) = default;

	void GetFromFile(std::ifstream& file); 
	void WriteToFile(std::ofstream& file); 
	void GetFromUser();
	void PrintHouseToScreen();
	void GetNameFromUser();
	void PrintNameToScreen();

private:
	std::string mLastName;
	std::string mFirstName;
	std::string mAddress;
	float mPrice;
	unsigned int mSquareFeet;
	unsigned int mBedRooms;
	unsigned int mBathrooms;
};