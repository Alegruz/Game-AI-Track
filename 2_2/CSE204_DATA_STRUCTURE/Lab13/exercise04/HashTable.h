#pragma once

#include <cstring>
#include <iostream>

const int MAX_ITEMS = 255;

template <typename ItemType>
class HashTable
{
public:
	HashTable();
	int Hash(char* key) const;
	void InsertItem(ItemType* item);
	void RetrieveItem(ItemType*& outItem, bool &outFound);
private:
	ItemType* info[MAX_ITEMS];
	int length;
	int emptyItem;
};

template <typename ItemType>
HashTable<ItemType>::HashTable()
	: length(0), emptyItem(-1)
{
	for (unsigned int i = 0; i < MAX_ITEMS; ++i)
	{
		info[i] = nullptr;
	}
}

int getIntFromString(char* key);

// This file contains the individual functions from the text.
// Note that there are two InsertItems
template <typename ItemType>
int HashTable<ItemType>::Hash(char* key) const
// Post: Returns an integer between 0 and MAX_ITEMS -1.
{
	return (getIntFromString(key) % MAX_ITEMS);
}

int getIntFromString(char* key)
{
	int sum = 0;
	int len = strlen(key);
	if (len % 2 == 1)
	{
		++len;
	}
	
	for (int j = 0; j < len; j += 2)
	{
		// std::cout << sum << " + " << 100 << " * " << static_cast<unsigned int>(key[j]) << " + " << static_cast<unsigned int>(key[j + 1]) << " % " << 19937 << std::endl;
		sum = (sum + 100 * static_cast<unsigned char>(key[j]) + static_cast<unsigned char>(key[j + 1])) % 19937;
		// std::cout << "GetIntFromString: sum is now " << sum << std::endl;
	}

	return sum;
}

template<typename ItemType>
void HashTable<ItemType>::RetrieveItem(ItemType*& outItem, bool &outFound)
// Post: Returns the element in the array at position 
//       item.Hash().
{
	int location;
	int startLocation;
	bool bMoreToSearch = true;

	startLocation = Hash(outItem->Key());
	location = startLocation;
	do
	{
		if (info[location] == nullptr || (strcmp(info[location]->Key(), outItem->Key()) == 0))
		{
			bMoreToSearch = false;
		}
		else
		{
			location = (location + 1) % MAX_ITEMS;
		}
	} while (location != startLocation && bMoreToSearch);

	outFound = (strcmp(info[location]->Key(), outItem->Key()) == 0);
	if (outFound)
	{
		outItem = info[location];
	}
}

template<typename ItemType>
void HashTable<ItemType>::InsertItem(ItemType* item)
// Post: item is stored in the array at position item.Hash().
{
	int location;
	location = Hash(item->Key());
	while (info[location] != nullptr)
	{
		location = (location + 1) % MAX_ITEMS;
	}
	info[location] = item;
	++length;
}