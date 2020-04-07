#pragma once

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

template<size_t N>
class SortedStringMap
{
	template<size_t O>
	friend std::ostream& operator<<(std::ostream& os, const SortedStringMap<O>& rhs);
public:
	SortedStringMap();
	SortedStringMap(const SortedStringMap& other);
	virtual ~SortedStringMap();

	SortedStringMap& operator=(const SortedStringMap& other);
	std::string& operator[](const std::string& key) const;

	bool      		IsEmpty() const;
	bool   		   	IsFull() const;
	size_t    		GetSize() const;
	size_t			GetCapacity() const;
	bool    	  	HasItem(const std::string& key) const;
	int 			GetIndex(const std::string& key) const;
	std::string&	GetKeyByIndex(size_t index) const;
	std::string&	GetValueByIndex(size_t index) const;
	bool			GetKeyStartsWithInput(const std::string& input, std::vector<std::string>& keyResults) const;
	bool			GetKeyEndsWithInput(const std::string& input, std::vector<std::string>& keyResults) const;
	bool			GetKeyWithInput(const std::string& input, std::vector<std::string>& keyResults) const;
	bool 			InsertItem(const std::string& key, const std::string& value);
	bool 			DeleteItem(const std::string& key);
	void			ReadFile(std::ifstream& fileIn);
private:
	std::string* mKeys;
	std::string* mValues;
	size_t mSize;
};

template<size_t N>
std::ostream& operator<<(std::ostream& os, const SortedStringMap<N>& rhs)
{
	std::cerr << "Size: " << rhs.mSize << std::endl;
	if (rhs.mSize == 0)
	{
		return os;
	}

	for (size_t key = 0; key < rhs.mSize; ++key)
	{
		os << rhs.mKeys[key] << "\b: " << rhs.mValues[key] << std::endl;
	}

	os << "\b";

	return os;
}

template<size_t N>
SortedStringMap<N>::SortedStringMap()
	: mKeys(new std::string[N]), mValues(new std::string[N]), mSize(0)
{
}

template <size_t N>
SortedStringMap<N>::SortedStringMap(const SortedStringMap& other)
	: mKeys(new std::string[N]), mValues(new std::string[N])
{
	if (mKeys != other.mKeys && mValues != other.mValues)
	{
		mSize = other.mSize;

		for (size_t index = 0; index < mSize; ++index)
		{
			mKeys[index] = other.mKeys[index];
			mValues[index] = other.mValues[index];
		}
	}
}

template<size_t N>
SortedStringMap<N>::~SortedStringMap()
{
	delete[] mValues;
	delete[] mKeys;
}

template <size_t N>
SortedStringMap<N>& SortedStringMap<N>::operator=(const SortedStringMap& other)
{
	if (mKeys != other.mKeys && mValues != other.mValues)
	{
		mSize = other.mSize;

		for (size_t index = 0; index < mSize; ++index)
		{
			mKeys[index] = other.mKeys[index];
			mValues[index] = other.mValues[index];
		}
	}

	return *this;
}

template <size_t N>
std::string& SortedStringMap<N>::operator[](const std::string& key) const
{
	assert(mSize > 0);

	size_t head = 0;
	size_t tail = mSize - 1;
	size_t middle = (head + tail) / 2;

	while (head <= tail)
	{
		
		if (mKeys[middle] < key)
		{
			head = middle + 1;
		}
		else if (mKeys[middle] > key)
		{
			tail = middle - 1;
		}
		else
		{
			return mValues[middle];
		}
		middle = (head + tail) / 2;
	}

	std::string dummy;
	return dummy;
}

template<size_t N>
bool SortedStringMap<N>::IsEmpty() const
{
  return (mSize == 0);
}

template<size_t N>
bool SortedStringMap<N>::IsFull() const
{
  return (mSize == N);
}

template<size_t N>
size_t SortedStringMap<N>::GetSize() const
{
  return mSize;
}

template<size_t N>
bool SortedStringMap<N>::HasItem(const std::string& key) const
{
	if (mSize == 0)
	{
		return false;
	}

	size_t head = 0;
	size_t tail = mSize - 1;
	size_t middle = (head + tail) / 2;

	while (head <= tail)
	{
		
		if (mKeys[middle] < key)
		{
			head = middle + 1;
		}
		else if (mKeys[middle] > key)
		{
			tail = middle - 1;
		}
		else
		{
			return true;
		}
		middle = (head + tail) / 2;
	}

	return false;
}

template<size_t N>
int SortedStringMap<N>::GetIndex(const std::string& key) const
{
	if (mSize == 0)
	{
		return -1;
	}

	size_t head = 0;
	size_t tail = mSize - 1;
	size_t middle = (head + tail) / 2;

	while (head <= tail)
	{
		
		if (mKeys[middle] < key)
		{
			head = middle + 1;
		}
		else if (mKeys[middle] > key)
		{
			tail = middle - 1;
		}
		else
		{
			return middle;
		}
		middle = (head + tail) / 2;
	}

	return -1;
}

template<size_t N>
std::string& SortedStringMap<N>::GetKeyByIndex(size_t index) const
{
	return mKeys[index];
}

template<size_t N>
std::string& SortedStringMap<N>::GetValueByIndex(size_t index) const
{
	return mValues[index];
}

template<size_t N>
bool SortedStringMap<N>::GetKeyStartsWithInput(const std::string& input, std::vector<std::string>& keyResults) const
{
	keyResults.clear();
	for (size_t key = 0; key < mSize; ++key)
	{
		if (mKeys[key].find(input) == 0)
		{
			std::cout << mKeys[key] << " starts with " << input << std::endl;
			keyResults.push_back(mKeys[key]);
		}
	}

	if (keyResults.size() > 0)
	{
		return true;
	}

	return false;
}

template<size_t N>
bool SortedStringMap<N>::GetKeyEndsWithInput(const std::string& input, std::vector<std::string>& keyResults) const
{
	keyResults.clear();
	for (size_t key = 0; key < mSize; ++key)
	{
		if (mKeys[key].length() >= input.length())
		{
			if (0 == mKeys[key].compare(mKeys[key].length() - input.length(), input.length(), input))
			{
				std::cout << mKeys[key] << " ends with " << input << std::endl;
				keyResults.push_back(mKeys[key]);
			}
		}
	}

	if (keyResults.size() > 0)
	{
		return true;
	}

	return false;
}

template<size_t N>
bool SortedStringMap<N>::GetKeyWithInput(const std::string& input, std::vector<std::string>& keyResults) const
{
	keyResults.clear();
	for (size_t key = 0; key < mSize; ++key)
	{
		if (mKeys[key].find(input) != std::string::npos)
		{
			std::cout << mKeys[key] << " contains " << input << std::endl;
			keyResults.push_back(mKeys[key]);
		}
	}

	if (keyResults.size() > 0)
	{
		return true;
	}
	
	return false;
}

template<size_t N>
bool SortedStringMap<N>::InsertItem(const std::string& key, const std::string& value) 
{
	// mSize should always be lower or equal to N
	assert(mSize <= N);
	if (mSize >= N)
	{
		return false;
	}

	int head = 0;
	int tail = mSize - 1;
	int middle = (head + tail) / 2;

	while (head <= tail)
	{
		if (mKeys[middle] < key)
		{
			head = middle + 1;
		}
		else if (mKeys[middle] > key)
		{
			tail = middle - 1;
		}
		else
		{
			return false;
		}
		middle = (head + tail) / 2;
	}
	
	if (head > tail)
	{
		for (int indexToMove = mSize; indexToMove > head; --indexToMove)
		{
			mKeys[indexToMove] = mKeys[indexToMove - 1];
			mValues[indexToMove] = mValues[indexToMove - 1];
		}
		++mSize;
		mKeys[head] = key;
		// std::transform(mKeys[head].begin(), mKeys[head].end(), mKeys[head].begin(), ::tolower);
		mValues[head] = value;
	}

	return true;
}

template<size_t N>
bool SortedStringMap<N>::DeleteItem(const std::string& key) 
{
	// mSize should always be lower or equal to N
	assert(mSize <= N);
	if (mSize == 0)
	{
		return false;
	}

	size_t head = 0;
	size_t tail = mSize - 1;
	size_t middle = (head + tail) / 2;

	while (head <= tail)
	{
		
		if (mKeys[middle] < key)
		{
			head = middle + 1;
		}
		else if (mKeys[middle] > key)
		{
			tail = middle - 1;
		}
		else
		{
			--mSize;
			for (size_t index = middle; index < mSize; ++index)
			{
				mKeys[index] = mKeys[index + 1];
				mValues[index] = mValues[index + 1];
			}
			
			return true;
		}
		middle = (head + tail) / 2;
	}

	return false;
}

template<size_t N>
void SortedStringMap<N>::ReadFile(std::ifstream& fileIn)
{
	if (fileIn.is_open())
	{
		std::string key;
		std::string value;
		std::string trash;
		while (!fileIn.eof())
		{
			fileIn >> key;
			if (*key.rbegin() > 'z' || (*key.rbegin() < 'a' && *key.rbegin() > 'Z') || *key.rbegin() < 'A')
			{
				key.pop_back();
			}
			
			if (fileIn.fail())
			{
				fileIn.clear();
				fileIn >> trash;
			}

			fileIn >> std::ws;
			getline(fileIn, value);

			if (fileIn.fail())
			{
				fileIn.clear();
				fileIn >> trash;
			}

			InsertItem(key, value);
		}
	}
}