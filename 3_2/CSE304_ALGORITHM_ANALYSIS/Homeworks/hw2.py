from typing import List, Tuple

def merge_sort(high: int, data: List[int]) -> Tuple[List[int], int]:
	# print(f"merge_sort(high={high}, data={data})")
	additional_memory: int = 0
	if high > 1:
		mid: int = int(high / 2)
		lhs: List[int] = []
		for i in range(0, mid):
			lhs.append(data[i])
			additional_memory += 1

		rhs: List[int] = []
		for i in range(mid, high):
			rhs.append(data[i])
			additional_memory += 1

		# print(f"\tlhs: {lhs}\n"
		# 	  f"\trhs: {rhs}")
		# print("lhs ", end='')
		_, lhs_additional_memory = merge_sort(high=mid, data=lhs)
		additional_memory += lhs_additional_memory
		# print("rhs ", end='')
		merge_sort(high=high - mid, data=rhs)
		merge(mid=mid, high=high, lhs=lhs, rhs=rhs, data=data)
	
	# print(f"\tadditional_memory: {additional_memory}")
	return data, additional_memory

def merge_sort2(low: int, high: int, data: List[int]) -> Tuple[List[int], int]:
	# print(f"merge_sort(low={low}, high={high}, data={data})")
	additional_memory: int = 0
	if low < high:
		mid: int = int((low + high) / 2)
		# print("lhs ", end='')
		merge_sort2(low=low, high=mid, data=data)
		# print("rhs ", end='')
		merge_sort2(low=mid + 1, high=high, data=data)
		result, result_additional_memory = merge2(low=low, mid=mid, high=high, data=data)

		for i in range(low, high + 1):
			data[i] = result[i - low]

		additional_memory += result_additional_memory
	
	# print(f"\tadditional_memory: {additional_memory}")
	return data, additional_memory

def merge(mid: int, high: int, lhs: List[int], rhs: List[int], data: List[int]) -> List[int]:
	# print(f"merge(mid={mid}, high={high}, lhs={lhs}, rhs={rhs}, data={data})")
	left: int = 0
	right: int = mid
	for i in range(0, high):
		# print(f"i: {i}, left: {left}, right: {right}")
		if left < mid and (right >= high or lhs[left] <= rhs[right - mid]):
			data[i] = lhs[left]
			left += 1
			# print(f"\tdata: {data}, lhs: {lhs}")
		else:
			data[i] = rhs[right - mid]
			right += 1
			# print(f"\tdata: {data}, rhs: {rhs}")
	
	return data

def merge2(low: int, mid: int, high: int, data: List[int]) -> Tuple[List[int], int]:
	# print(f"merge2(low={low}, mid={mid}, high={high}, data={data})")
	left: int = low
	right: int = mid + 1
	result: List[int] = []
	for i in range(low, high + 1):
		# print(f"i: {i}, left: {left}, right: {right}")
		if left < mid + 1 and (right > high or data[left] <= data[right]):
			result.append(data[left])
			left += 1
		else:
			result.append(data[right])
			right += 1
		# print(f"\tresult: {result}")

	return result, len(result)

def main():
	test_list0: List[int] = [3, 5, 2, 9, 10, 14, 4, 8]
	_, additional_memory = merge_sort(high=len(test_list0), data=test_list0)
	print(test_list0, additional_memory)

	test_list1: List[int] = [11, 5, 2, 16, 12, 1, 8, 15, 6, 14, 9, 3, 10, 7, 13, 4]
	_, additional_memory = merge_sort(high=len(test_list1), data=test_list1)
	print(test_list1, additional_memory)

	test_list2: List[int] = [27, 10, 12, 20, 25, 13, 15, 22]
	_, additional_memory = merge_sort(high=len(test_list2), data=test_list2)
	print(test_list2, additional_memory)

	test_list3: List[int] = [3, 5, 2, 9, 10, 14, 4, 8]
	_, additional_memory = merge_sort2(low=0, high=len(test_list3) - 1, data=test_list3)
	print(test_list3, additional_memory)

	test_list4: List[int] = [11, 5, 2, 16, 12, 1, 8, 15, 6, 14, 9, 3, 10, 7, 13, 4]
	_, additional_memory = merge_sort2(low=0, high=len(test_list4) - 1, data=test_list4)
	print(test_list4, additional_memory)

	test_list5: List[int] = [27, 10, 12, 20, 25, 13, 15, 22]
	_, additional_memory = merge_sort2(low=0, high=len(test_list5) - 1, data=test_list5)
	print(test_list5, additional_memory)

if __name__ == "__main__":
	main()