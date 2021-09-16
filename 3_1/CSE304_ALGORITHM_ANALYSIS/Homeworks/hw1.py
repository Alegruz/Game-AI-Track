import time


def algorithm_recursive(n: int) -> int:
    if n == 1 or n == 2:
        return 1
    else:
        sum: int = 0
        for i in range(1, n):
            sum += algorithm_recursive(i)
        return sum


def algorithm(n: int) -> int:
    count: int = 0
    data: list[int] = [0] * (n + 1)
    data[1] = 1
    data[2] = 1

    for i in range(3, n + 1):
        for j in range(1, i):
            data[i] += data[j]
            count += 1
        # print(f"{i}: {data[i]}")

    return data[n], count


def algorithm_best(n: int) -> int:
    if n == 1:
        return 1
    return 1 << n - 2


if __name__ == "__main__":
    input_list: list[int] = [1600, 3200, 6400, 12800, 25600]
    # for i in range(24, 29):
    #     tic: float = time.time()
    #     result: int = algorithm_recursive(n=i)
    #     toc: float = time.time()
    #     print(f"RECURSIVE{i}-result: {result}, elapsed time: {toc - tic}")
    #
    # for item in input_list:
    #     tic: float = time.time()
    #     result: int = algorithm_best(n=item)
    #     toc: float = time.time()
    #     print(f"BEST[{item}]-elapsed time: {toc - tic}, result: {result}")

    for item in input_list:
        tic: float = time.time()
        result, count = algorithm(n=item)
        toc: float = time.time()
        print(f"ARRAY[{item}]-count: {count}, elapsed time: {toc - tic}")
