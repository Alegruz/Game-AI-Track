import random
import time

def find_maximum_subarray_brute_force(data: list, low: int, high: int):
	max_sum: int = data[low]
	for i in range(low, high + 1):
		sum: int = 0
		for j in range(i, high + 1):
			sum += data[j]
			if sum > max_sum:
				max_sum = sum
				low = i
				high = j
	
	return (low, high, max_sum)

def find_maximum_subarray(data: list, low: int, high: int):
	if len(data) < 220:
		return find_maximum_subarray_brute_force(data=data, low=low, high=high)
	if low >= high:
		return (low, high, data[low])
	else:
		mid: int = int((low + high) / 2)
		left_low, left_high, left_sum = find_maximum_subarray(data=data, low=low, high=mid)
		right_low, right_high, right_sum = find_maximum_subarray(data=data, low=mid + 1, high=high)
		cross_low, cross_high, cross_sum = find_max_crossing_subarray(data=data, low=low, mid=mid, high=high)

		if left_sum >= right_sum and left_sum >= cross_sum:
			return (left_low, left_high, left_sum)
		elif right_sum >= left_sum and right_sum >= cross_sum:
			return (right_low, right_high, right_sum)
		else:
			return (cross_low, cross_high, cross_sum)

def find_max_crossing_subarray(data: list, low: int, mid: int, high: int):
	left_sum: int = data[low]
	max_left: int = low
	sum: int = 0
	for i in range(mid, low - 1, -1):
		sum += data[i]
		if sum > left_sum:
			left_sum = sum
			max_left = i

	right_sum: int = data[mid + 1]
	max_right: int = mid + 1
	sum = 0
	for i in range(mid + 1, high + 1):
		sum += data[i]
		if sum > right_sum:
			right_sum = sum
			max_right = i
	
	return (max_left, max_right, left_sum + right_sum)
	

if __name__ == "__main__":
	average_brute_force: int = 0
	average: int = 0
	for i in range(0, 100):
		data: list = []
		for i in range(0, 220):
			data.append(random.randint(-1000000, 1000000))

		tic: int = time.time_ns()
		low, high, max_sum = find_maximum_subarray_brute_force(data=data, low=0, high=len(data) - 1)
		toc: int = time.time_ns()
		average_brute_force += toc - tic

		# print(f"brute_force low: {low:>5}, high: {high:>5}, max_sum: {max_sum:>10}, elapsed_time: {toc - tic:>10}")

		tic = time.time_ns()
		low, high, max_sum = find_maximum_subarray(data=data, low=0, high=len(data) - 1)
		toc = time.time_ns()

		average += toc - tic
		# print(f"brute_force low: {low:>5}, high: {high:>5}, max_sum: {max_sum:>10}, elapsed_time: {toc - tic:>10}")
	
	print(f"elapsed time: {average_brute_force/100.0:<10} brute force")
	print(f"elapsed time: {average/100.0:<10}")
		