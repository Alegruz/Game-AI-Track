#include "BinarySearch.h"

#include <cassert>
#include <iomanip>
#include <iostream>

const unsigned int TEST_CASE_MESSAGE_WIDTH = 50;

int main()
{
	int* nullList = nullptr;
	int identicalList[5] = {1, 1, 1, 1, 1};
	int leftEndIdenticalList[5] = {1, 3, 3, 3, 3};
	int rightEndIdenticalList[5] = {1, 1, 1, 1, 3};
	int mixedList[7] = {1, 2, 2, 3, 4, 4, 5};
	int leftDuplicated[5] = {1, 1, 2, 3, 4};
	int rightDuplicated[6] = {1, 2, 3, 4, 5, 5};

	std::cerr << std::setw(TEST_CASE_MESSAGE_WIDTH) << std::left << "TEST CASE 00: NULLPTR LIST:";
	{
		assert(BinarySearch(nullList, 0, 100) == -1);
	}
	std::cerr << "SUCCESS" << std::endl;

	std::cerr << std::setw(TEST_CASE_MESSAGE_WIDTH) << std::left << "TEST CASE 01: ELEMENT IN THE MIDDLE: ";
	{
		assert(BinarySearch(mixedList, 7, 3) == 3);
		assert(BinarySearch(leftDuplicated, 5, 2) == 2);
		assert(BinarySearch(rightDuplicated, 6, 4) == 3);
	}
	std::cerr << "SUCCESS" << std::endl;

	std::cerr << std::setw(TEST_CASE_MESSAGE_WIDTH) << std::left << "TEST CASE 02: LEFTMOST ELEMENT: ";
	{
		assert(BinarySearch(leftEndIdenticalList, 5, 1) == 0);
		assert(BinarySearch(mixedList, 7, 1) == 0);
		assert(BinarySearch(rightDuplicated, 6, 1) == 0);
	}
	std::cerr << "SUCCESS" << std::endl;

	std::cerr << std::setw(TEST_CASE_MESSAGE_WIDTH) << std::left << "TEST CASE 03: RIGHTMOST ELEMENT: ";
	{
		assert(BinarySearch(rightEndIdenticalList, 5, 3) == 4);
		assert(BinarySearch(mixedList, 7, 5) == 6);
		assert(BinarySearch(leftDuplicated, 5, 4) == 4);
	}
	std::cerr << "SUCCESS" << std::endl;

	std::cerr << std::setw(TEST_CASE_MESSAGE_WIDTH) << std::left << "TEST CASE 04: DUPLICANT ELEMENT IN THE MIDDLE: ";
	{
		assert(BinarySearch(identicalList, 5, 1) == 2);
		assert(BinarySearch(leftEndIdenticalList, 5, 3) == 2);
		assert(BinarySearch(rightEndIdenticalList, 5, 1) == 2);
		assert(BinarySearch(mixedList, 7, 2) == 1);
		assert(BinarySearch(mixedList, 7, 4) == 5);
	}
	std::cerr << "SUCCESS" << std::endl;

	std::cerr << std::setw(TEST_CASE_MESSAGE_WIDTH) << std::left << "TEST CASE 05: LEFTMOST DUPLICANT ELEMENT: ";
	{
		assert(BinarySearch(leftDuplicated, 5, 1) == 0);
	}
	std::cerr << "SUCCESS" << std::endl;

	std::cerr << std::setw(TEST_CASE_MESSAGE_WIDTH) << std::left << "TEST CASE 06: RIGHTMOST DUPLICANT ELEMENT: ";
	{
		assert(BinarySearch(rightDuplicated, 6, 5) == 4);
	}
	std::cerr << "SUCCESS" << std::endl;

	std::cerr << std::setw(TEST_CASE_MESSAGE_WIDTH) << std::left << "TEST CASE 07: FIND NON-EXISTING LESSER ELEMENT: ";
	{
		assert(BinarySearch(identicalList, 5, -1) == -1);
		assert(BinarySearch(leftEndIdenticalList, 5, 0) == -1);
		assert(BinarySearch(rightEndIdenticalList, 5, -2) == -1);
		assert(BinarySearch(mixedList, 7, -4) == -1);
		assert(BinarySearch(leftDuplicated, 5, -1) == -1);
		assert(BinarySearch(rightDuplicated, 6, -5) == -1);
	}
	std::cerr << "SUCCESS" << std::endl;

	std::cerr << std::setw(TEST_CASE_MESSAGE_WIDTH) << std::left << "TEST CASE 08: FIND NON-EXISTING LARGER ELEMENT: ";
	{
		assert(BinarySearch(identicalList, 5, 10) == -1);
		assert(BinarySearch(leftEndIdenticalList, 5, 20) == -1);
		assert(BinarySearch(rightEndIdenticalList, 5, 22) == -1);
		assert(BinarySearch(mixedList, 7, -4) == -1);
		assert(BinarySearch(leftDuplicated, 5, 14) == -1);
		assert(BinarySearch(rightDuplicated, 6, 55) == -1);
	}
	std::cerr << "SUCCESS" << std::endl;


	return 0;
}