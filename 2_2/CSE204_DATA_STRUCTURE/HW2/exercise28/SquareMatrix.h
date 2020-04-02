#pragma once
#include <iostream>

namespace Lab01
{
	class SquareMatrix final
	{
		friend std::ostream& operator<<(std::ostream& os, const SquareMatrix& rhs);
	public:
		SquareMatrix();
		SquareMatrix(size_t size);
		SquareMatrix(size_t size, int initialValue);
		SquareMatrix(const SquareMatrix& other);
		~SquareMatrix();

		int* operator[](size_t index) const;

		void MakeEmpty();
		// Set all elements to zero
		// precondition : mSquareMatrix has been initialized
		// postcondition: all elements of mSquareMatrix has been set to zero
		void StoreValue(size_t row, size_t column, int value);
		// Store value into rowth, columnth position in mSquareMatrix
		// preconditions: mSquareMatrix has been initialized
		//				  row and column are smaller than mSize
		// postcondition: Set mSquareMatrix[row][column] to value
		void Add(const SquareMatrix& other);
		// Adds the value of elements in other to mSquareMatrix
		// preconditions : mSquareMatrix has been initialized
		//				   other.mSquareMatrix has been initialized
		// postconditions: adds two matrices.
		//			       if size differs, set the addition limit to the smallest mSize between mSquareMatrix and other.mSquareMatrix, then add.
		void Subtract(const SquareMatrix& other);
		// Subtracts the value of elements in other to mSquareMatrix
		// preconditions : mSquareMatrix has been initialized
		//				   other.mSquareMatrix has been initialized
		// postconditions: subtracts two matrices.
		//			       if size differs, set the subtraction limit to the smallest mSize between mSquareMatrix and other.mSquareMatrix, then subtract.
		void Copy(const SquareMatrix& other);
		// Copy other matrix into mSquareMatrix
		// preconditions : mSquareMatrix has been initialized
		//				   other.mSquareMatrix has been initialized
		// postconditions: copy the elements of other.mSquareMatrix into mSquareMatrix
		//				   if size differs, set the size of mSquareMatrix to other.mSquareMatrix's size, then copy
	private:
		size_t mSize;
		int** mSquareMatrix;
	};
}