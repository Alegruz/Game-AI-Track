import math


class Heap:
    __slots__ = ["data"]

    def __init__(self, data: list[int]):
        self.data: list[int] = data

    def add_element(self, element: int):
        self.data.append(self.data[len(self.data) - 1])
        self.data[len(self.data) - 1] = element

        # print(f"data: {self.data}")
        current_index: int = len(self.data) - 1
        parent_index: int = math.ceil(current_index // 2)
        while self.data[current_index] > self.data[parent_index] and parent_index > 0:
            # print(f"current[{current_index}]: {self.data[current_index]}")
            # print(f"parent[{parent_index}]: {self.data[parent_index]}")
            key: int = self.data[current_index]
            self.data[current_index] = self.data[parent_index]
            self.data[parent_index] = key
            current_index = parent_index
            parent_index = math.ceil(current_index // 2)
            # print(f"data: {self.data}")

    def make_heap(self) -> None:
        for i in range(math.ceil((len(self.data) - 1) // 2), 0, -1):
            self.siftdown(index=i)

    def remove_key(self) -> list[int]:
        result_data: list[int] = []
        while len(self.data) > 1:
            result_data.append(self.root())
        return result_data

    def root(self) -> int:
        result: int = self.data[1]
        self.data[1] = self.data[len(self.data) - 1]
        self.data.pop()
        if len(self.data) > 1:
            self.siftdown(index=1)
        return result

    def siftdown(self, index: int) -> None:
        sift_key: int = self.data[index]
        parent_index: int = index
        has_found_spot: bool = False
        while 2 * parent_index <= len(self.data) - 1 and not has_found_spot:
            if 2 * parent_index < len(self.data) - 1 and self.data[2 * parent_index] < self.data[2 * parent_index + 1]:
                larger_child_index: int = 2 * parent_index + 1
            else:
                larger_child_index: int = 2 * parent_index

            if sift_key < self.data[larger_child_index]:
                self.data[parent_index] = self.data[larger_child_index]
                parent_index = larger_child_index
            else:
                has_found_spot = True

        self.data[parent_index] = sift_key

    def sort(self) -> list[int]:
        self.make_heap()
        return self.remove_key()


def main():
    data: list[int] = [0, 11, 14, 2, 7, 6, 3, 9, 5]
    heap: Heap = Heap(data=data)
    heap.make_heap()
    print(heap.data)
    heap.add_element(element=50)
    print(heap.data)
    print(heap.sort())


if __name__ == "__main__":
    main()
