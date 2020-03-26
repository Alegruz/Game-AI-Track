#pragma once
#include <iostream>

namespace Lab01
{
	class SquareMatrix final
	{
	public:
		SquareMatrix(size_t row, size_t column);
		SquareMatrix(size_t row, size_t column, int initialValue);
		SquareMatrix(const SquareMatrix& other);
		~SquareMatrix();

		int* operator[](size_t index) const;

		void MakeEmpty(size_t row);	// 모든 n행과 열들을 0으로 설정한다
		void StoreValue(size_t row, size_t column, int value);	// value를 i번째행, j번째 열의 위치에 저장한다
		void Add(const SquareMatrix& other);	// 두 행렬을 더한다
		void Subtract(const SquareMatrix& other);	// 한 행렬을 다른 행렬로부터 뺀다
		void Copy(const SquareMatrix& other);	// 한 행렬을 다른 행렬로 복사한다
	private:
		size_t mRow;
		size_t mColumn;
		int** mSquareMatrix;
	};
}
