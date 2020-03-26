#include "SquareMatrix.h"

namespace Lab01
{
	SquareMatrix::SquareMatrix(size_t row, size_t column)
		: mRow(row), mColumn(column), mSquareMatrix(new int*[mRow])
	{
		for (size_t rowIndex = 0; rowIndex < mRow; ++rowIndex)
		{
			mSquareMatrix[rowIndex] = new int[mColumn];
		}
	}

	SquareMatrix::SquareMatrix(size_t row, size_t column, int initialValue)
		: mRow(row), mColumn(column), mSquareMatrix(new int*[mRow])
	{
		for (size_t rowIndex = 0; rowIndex < mRow; ++rowIndex)
		{
			mSquareMatrix[rowIndex] = new int[mColumn];
			for (size_t columnIndex = 0; columnIndex < mColumn; ++columnIndex)
			{
				mSquareMatrix[rowIndex][columnIndex] = initialValue;
			}
		}
	}

	SquareMatrix::SquareMatrix(const SquareMatrix& other)
		: mRow(other.mRow), mColumn(other.mColumn), mSquareMatrix(new int*[mRow])
	{
		for (size_t rowIndex = 0; rowIndex < mRow; ++rowIndex)
		{
			mSquareMatrix[rowIndex] = new int[mColumn];
			for (size_t columnIndex = 0; columnIndex < mColumn; ++columnIndex)
			{
				mSquareMatrix[rowIndex][columnIndex] = other.mSquareMatrix[rowIndex][columnIndex];
			}
		}
	}

	SquareMatrix::~SquareMatrix()
	{
		for (size_t rowIndex = 0; rowIndex < mRow; ++rowIndex)
		{
			mSquareMatrix[rowIndex] = nullptr;
			delete[] mSquareMatrix[rowIndex];
		}
		delete[] mSquareMatrix;
	}

	int* SquareMatrix::operator[](size_t index) const
	{
		return mSquareMatrix[index];
	}

	void SquareMatrix::Add(const SquareMatrix& other)
	{
		for (size_t rowIndex = 0; rowIndex < mRow; ++rowIndex)
		{
			for (size_t columnIndex = 0; columnIndex < mColumn; ++columnIndex)
			{
				mSquareMatrix[rowIndex][columnIndex] += other.mSquareMatrix[rowIndex][columnIndex];
			}
		}
	}

	void SquareMatrix::Subtract(const SquareMatrix& other)
	{
		for (size_t rowIndex = 0; rowIndex < mRow; ++rowIndex)
		{
			for (size_t columnIndex = 0; columnIndex < mColumn; ++columnIndex)
			{
				mSquareMatrix[rowIndex][columnIndex] -= other.mSquareMatrix[rowIndex][columnIndex];
			}
		}
	}

	void SquareMatrix::Copy(const SquareMatrix& other)
	{
		if (mColumn != other.mColumn || mRow != other.mRow)
		{
			for (size_t rowIndex = 0; rowIndex < mRow; ++rowIndex)
			{
				mSquareMatrix[rowIndex] = nullptr;
			}

			mSquareMatrix = nullptr;

			mRow = other.mRow;
			mColumn = other.mColumn;

			mSquareMatrix = new int*[mRow];

			for (size_t rowIndex = 0; rowIndex < mRow; ++rowIndex)
			{
				mSquareMatrix[rowIndex] = new int[mColumn];
			}
		}

		for (size_t rowIndex = 0; rowIndex < mRow; ++rowIndex)
		{
			for (size_t columnIndex = 0; columnIndex < mColumn; ++columnIndex)
			{
				mSquareMatrix[rowIndex][columnIndex] = other.mSquareMatrix[rowIndex][columnIndex];
			}
		}
	}

	void SquareMatrix::MakeEmpty(size_t n)
	{
		if (n >= mRow || n >= mColumn)
		{
			n = (mRow > mColumn) ? mRow - 1 : mColumn - 1;
		}

		for (size_t rowIndex = 0; rowIndex <= n; ++rowIndex)
		{
			for (size_t columnIndex = 0; columnIndex <= n; ++columnIndex)
			{
				mSquareMatrix[rowIndex][columnIndex] = 0;
			}
		}
	}

	void SquareMatrix::StoreValue(size_t row, size_t column, int value)
	{
		mSquareMatrix[row][column] = value;
	}
}
