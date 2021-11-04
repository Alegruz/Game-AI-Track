import math
import matplotlib.pyplot as plt
import numpy as np
from random import randint
from typing import List, Tuple

from numpy.core.shape_base import hstack, vstack

def main():
	size_list: list[int] = [8, 16, 24, 32, 40]

	compare_count_list: list[int] = []
	for size in size_list:
		print(f"SIZE: {size}")
		compare_count: int = 0
		for count in range(0, 20):
			data: list[int] = []
			for i in range(0, size):
				data.append(randint(0, size))
			print(f"dataset-{count}: {data}")
			compare_count += quick_sort_recusive(data=data, low=0, high=len(data) - 1)
		compare_count_list.append(compare_count / 20)
		print(f"Average compare count: {compare_count / 20}")
	
	x: np.ndarray = np.arange(start=1, stop=42, step=2)
	y: np.ndarray = np.ndarray(shape=x.shape)
	for i, value in enumerate(x):
		y[i] = (value * math.log2(value)) * 0.7

	plt.plot(size_list, compare_count_list, "bo", label="data")
	plt.plot(x, y, "g-", label="y = (x log_2(x)) * 0.7)")
	plt.xlabel(xlabel="size")
	plt.ylabel(ylabel="compare count")
	plt.title(label="quick sort compare count comparison")
	plt.xticks(ticks=size_list)
	plt.grid(b=True)
	plt.legend()
	plt.show()

	size: int = 4
	#A = [[1 for cols in range(n)]for rows in range(n)]
	#B = [[2 for cols in range(n)]for rows in range(n)]
	A = [ [1,2,0,2], [3,1,0,0], [0,1,1,2],[2,0,2,0]]
	B = [ [0,3,0,2], [1,1,4,0], [1,1,0,2],[0,5,2,0]]
	C = np.dot(a=A, b=B)
	print(C)
	D = strassen(size=size, lhs=A, rhs=B)
	print(D)

def partition(data: List[int], low: int, high: int) -> Tuple[int, int]:
	# print(f"partition(data={data}, low={low}, high={high})")
	left_index: int = low - 1
	right_index: int = high + 1
	compare_count: int = 0

	while True:
		left_index += 1
		while data[left_index] < data[low]:
			# print(f"\tdata[{left_index}]={data[left_index]} < data[{low}]={data[low]} ?")
			left_index += 1
			compare_count += 1
		
		right_index -= 1
		while data[right_index] > data[low]:
			# print(f"\tdata[{right_index}]={data[right_index]} > data[{low}]={data[low]} ?")
			right_index -= 1
			compare_count += 1
		
		if left_index >= right_index:
			# print(f"\tcompare_count: {compare_count}")
			return right_index, compare_count
		
		data[left_index], data[right_index] = data[right_index], data[left_index]

def quick_sort_recusive(data: List[int], low: int, high: int) -> int:
	# print(f"qs(data={data}, low={low}, high={high})")
	if low >= high:
		# print(f"\tcompare_count: 0")
		return 0
	
	pivot, compare_count = partition(data=data, low=low, high=high)
	compare_count += quick_sort_recusive(data=data, low=low, high=pivot)
	compare_count += quick_sort_recusive(data=data, low=pivot + 1, high=high)
	# print(f"\tcompare_count: {compare_count}")
	return compare_count

def strassen(size: int, lhs: np.ndarray, rhs: np.ndarray) -> np.ndarray:
	threshold: int = 2
	if size <= threshold:
		result = np.dot(a=lhs, b=rhs)
	else:
		lhs_11: np.array = np.array([[lhs[rows][cols] for cols in range(0, size // 2)] for rows in range(0, size // 2)])
		lhs_12: np.array = np.array([[lhs[rows][cols] for cols in range(size // 2, size)] for rows in range(0, size // 2)])
		lhs_21: np.array = np.array([[lhs[rows][cols] for cols in range(0, size // 2)] for rows in range(size // 2, size)])
		lhs_22: np.array = np.array([[lhs[rows][cols] for cols in range(size // 2, size)] for rows in range(size // 2, size)])

		rhs_11: np.array = np.array([[rhs[rows][cols] for cols in range(0, size // 2)] for rows in range(0, size // 2)])
		rhs_12: np.array = np.array([[rhs[rows][cols] for cols in range(size // 2, size)] for rows in range(0, size // 2)])
		rhs_21: np.array = np.array([[rhs[rows][cols] for cols in range(0, size // 2)] for rows in range(size // 2, size)])
		rhs_22: np.array = np.array([[rhs[rows][cols] for cols in range(size // 2, size)] for rows in range(size // 2, size)])

		m_1: np.ndarray = strassen(size=size // 2, lhs=(lhs_11 + lhs_22), rhs=(rhs_11 + rhs_22))
		m_2: np.ndarray = strassen(size=size // 2, lhs=(lhs_21 + lhs_22), rhs=rhs_11)
		m_3: np.ndarray = strassen(size=size // 2, lhs=lhs_11, rhs=(rhs_12 - rhs_22))
		m_4: np.ndarray = strassen(size=size // 2, lhs=lhs_22, rhs=(rhs_21 - rhs_11))
		m_5: np.ndarray = strassen(size=size // 2, lhs=(lhs_11 + lhs_12), rhs=rhs_22)
		m_6: np.ndarray = strassen(size=size // 2, lhs=(lhs_21 - lhs_11), rhs=(rhs_11 + rhs_12))
		m_7: np.ndarray = strassen(size=size // 2, lhs=(lhs_12 - lhs_22), rhs=(rhs_21 + rhs_22))

		result = np.vstack(tup=(hstack(tup=(m_1 + m_4 - m_5 + m_7, m_3 + m_5)), hstack(tup=(m_2 + m_4, m_1 - m_2 + m_3 - m_6))))

	return result

if __name__ == "__main__":
	main()