import sys
from typing import List

def main():
	d: List[int] = [5, 2, 3, 4, 6, 7, 8]
	n: int = len(d) - 1

	indices: List[List[int]] = [[0] * n for i in range(0, n)]
	result: List[List[int]] = min_mul(matrix_size=n, diagonal_elements=d, indices=indices)

	print_matrix(matrix=result)
	print()
	print_matrix(matrix=indices)
	order(row=0, col=n - 1, indices=indices)
	print()

def min_mul(matrix_size: int, diagonal_elements: List[int], indices: List[List[int]]) -> List[List[int]]:
	result: List[List[int]] = [[0] * matrix_size for i in range(0, matrix_size)]

	for diagonal in range(0, matrix_size - 1):
		for row in range(0, matrix_size - 1 - diagonal):
			col: int = row + diagonal + 1
			minimum: int = None
			minimum_index: int = None
			for i in range(row, col):
				new_minimum: int = result[row][i] + result[i + 1][col] + diagonal_elements[row] * diagonal_elements[i + 1] * diagonal_elements[col + 1]

				if minimum is None or minimum > new_minimum:
					minimum = new_minimum
					minimum_index = i
			result[row][col] = minimum
			indices[row][col] = minimum_index
	
	return result

def print_matrix(matrix: List[List[int]]) -> None:
	for i in range(0, len(matrix)):
		for j in range(0, len(matrix[i])):
			print(f"{matrix[i][j]:4d}", end=" ")
		print()

def order(row: int, col: int, indices: List[List[int]]) -> None:
	if row == col:
		print(f"A{row + 1}", end="")
	else:
		index: int = indices[row][col]
		print("(", end="")
		order(row=row, col=index, indices=indices)
		order(row=index + 1, col=col, indices=indices)
		print(")", end="")

if __name__ == "__main__":
	main()