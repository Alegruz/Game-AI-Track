#include "SquareMatrix.h"

namespace Lab01
{
	std::ostream& operator<<(std::ostream& os, const SquareMatrix& rhs)
	{
		for (size_t row = 0; row < rhs.mSize; ++row)
		{
			for (size_t column = 0; column < rhs.mSize; ++column)
			{
				os << rhs[row][column] << " ";
			}
			os << "\b" << std::endl;
		}

		return os;
	}

	SquareMatrix::SquareMatrix()
		: mSize(50), mSquareMatrix(new int*[mSize])
	{
		for (size_t row = 0; row < mSize; ++row)
		{
			mSquareMatrix[row] = new int[mSize];
		}
	}

	SquareMatrix::SquareMatrix(size_t size)
		: mSize(size), mSquareMatrix(new int*[mSize])
	{
		for (size_t row = 0; row < mSize; ++row)
		{
			mSquareMatrix[row] = new int[mSize];
		}
	}

	SquareMatrix::SquareMatrix(size_t size, int initialValue)
		: mSize(size), mSquareMatrix(new int*[mSize])
	{
		for (size_t row = 0; row < mSize; ++row)
		{
			mSquareMatrix[row] = new int[mSize];
			for (size_t column = 0; column < mSize; ++column)
			{
				mSquareMatrix[row][column] = initialValue;
			}
		}
	}

	SquareMatrix::SquareMatrix(const SquareMatrix& other)
		: mSize(other.mSize), mSquareMatrix(new int*[mSize])
	{
		for (size_t row = 0; row < mSize; ++row)
		{
			mSquareMatrix[row] = new int[mSize];
			for (size_t column = 0; column < mSize; ++column)
			{
				mSquareMatrix[row][column] = other.mSquareMatrix[row][column];
			}
		}
	}

	SquareMatrix::~SquareMatrix()
	{
		for (size_t row = 0; row < mSize; ++row)
		{
			delete[] mSquareMatrix[row];
		}

		delete[] mSquareMatrix;
	}

	int* SquareMatrix::operator[](size_t rowIndex) const
	{
		if (rowIndex >= mSize)
		{
			return nullptr;
		}

		return mSquareMatrix[rowIndex];
	}

	void SquareMatrix::MakeEmpty()
	{
		for (size_t row = 0; row < mSize; ++row)
		{
			for (size_t column = 0; column < mSize; ++column)
			{
				mSquareMatrix[row][column] = 0;
			}
		}
	}

	void SquareMatrix::StoreValue(size_t row, size_t column, int value)
	{
		if (row >= mSize || column >= mSize)
		{
			return;
		}

		mSquareMatrix[row][column] = value;
	}

	void SquareMatrix::Add(const SquareMatrix& other)
	{
		size_t addIndex = (other.mSize >= mSize) ? mSize : other.mSize;

		for (size_t row = 0; row < addIndex; ++row)
		{
			for (size_t column = 0; column < addIndex; ++column)
			{
				mSquareMatrix[row][column] += other[row][column];
			}
		}
	}

	void SquareMatrix::Subtract(const SquareMatrix& other)
	{
		size_t subtractIndex = (other.mSize >= mSize) ? mSize : other.mSize;

		for (size_t row = 0; row < subtractIndex; ++row)
		{
			for (size_t column = 0; column < subtractIndex; ++column)
			{
				mSquareMatrix[row][column] -= other[row][column];
			}
		}
	}

	void SquareMatrix::Copy(const SquareMatrix& other)
	{
		if (mSize != other.mSize)
		{
			for (size_t row = 0; row < mSize; ++row)
			{
				delete[] mSquareMatrix[row];
			}

			delete[] mSquareMatrix;
		}
		mSize = other.mSize;

		mSquareMatrix = new int*[mSize];

		for (size_t row = 0; row < mSize; ++row)
		{
			mSquareMatrix[row] = new int[mSize];
			for (size_t column = 0; column < mSize; ++column)
			{
				mSquareMatrix[row][column] = other[row][column];
			}
		}
	}
}