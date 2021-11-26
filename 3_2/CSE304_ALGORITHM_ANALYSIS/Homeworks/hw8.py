from __future__ import annotations

import queue


class Item:
    __slots__ = ["profit", "weight"]

    def __init__(self, profit: int, weight: int) -> None:
        assert isinstance(profit, int) and isinstance(weight, int)

        self.profit: int = profit
        self.weight: int = weight

    def __str__(self) -> str:
        return f"{{ profit={self.profit}, weight={self.weight}, ratio={self.get_profit_by_weight()} }}"

    def get_profit_by_weight(self) -> float:
        return float(self.profit) / float(self.weight)


class Knapsack:
    __slots__ = ["items", "maximum_weight", "current_weight", "profit"]

    def __init__(self, maximum_weight: int):
        self.items: list[Item] = []
        self.maximum_weight: int = maximum_weight
        self.current_weight: int = 0
        self.profit: int = 0

    def __str__(self) -> str:
        format_string: str = f"knapsack(weight={self.current_weight}/{self.maximum_weight}, profit={self.profit}): [\n"

        for item in self.items:
            format_string += f"\t {str(item)}, \n"
        format_string += "]"

        return format_string

    def add_item(self, item_to_add: Item, ignore_boundary: bool = False) -> bool:
        if ignore_boundary or self.current_weight <= self.maximum_weight - item_to_add.weight:
            left_index: int = 0
            right_index: int = len(self.items) - 1
            mid_index: int = 0
            should_add_at_right_side: bool = False
            while left_index <= right_index:
                mid_index = left_index + int((right_index - left_index) / 2)
                if self.items[mid_index].get_profit_by_weight() == item_to_add.get_profit_by_weight():
                    should_add_at_right_side = True
                    break
                elif self.items[mid_index].get_profit_by_weight() > item_to_add.get_profit_by_weight():
                    left_index = mid_index + 1
                    should_add_at_right_side = True
                else:
                    right_index = mid_index - 1
                    should_add_at_right_side = False

            self.items.insert(mid_index + (1 if should_add_at_right_side else 0), item_to_add)
            self.current_weight += item_to_add.weight
            self.profit += item_to_add.profit
            return True

        return False

    def clear(self) -> None:
        self.items.clear()
        self.current_weight = 0
        self.profit = 0

    def copy(self, other: Knapsack):
        self.items = other.items.copy()
        self.maximum_weight = other.maximum_weight
        self.current_weight = other.current_weight
        self.profit = other.profit

    def get_item(self, i: int) -> Item:
        return self.items[i]

    def is_empty(self) -> bool:
        return self.current_weight == 0

    def is_full(self) -> bool:
        return self.current_weight >= self.maximum_weight

    def remove_item(self, item_to_remove: Item) -> bool:
        for item in self.items:
            if item is item_to_remove:
                self.items.remove(item)
                self.current_weight -= item.weight
                self.profit -= item.profit
                return True

        return False

    def get_knapsack_dfs(self, maximum_weight: int) -> tuple[Knapsack, int]:
        knapsack: Knapsack = Knapsack(maximum_weight=maximum_weight)
        best_set: Knapsack = Knapsack(maximum_weight=maximum_weight)
        node_count: int = 0
        node_count = self.__get_knapsack_internal(index=-1, knapsack=knapsack, best_set=best_set, node_count=node_count)

        return best_set, node_count

    def get_knapsack_best_fs(self, maximum_weight: int) -> tuple[Knapsack, int]:
        pq: queue.PriorityQueue = queue.PriorityQueue()
        best_set: Knapsack = Knapsack(maximum_weight=maximum_weight)
        node: KnapsackNode = KnapsackNode(level=0,
                                          knapsack=best_set,
                                          bound=self.__get_bound(index=-1, knapsack=best_set),
                                          original_knapsack=self)
        pq.put((-node.bound, node))
        node_count: int = 0
        next_knapsack: Knapsack = Knapsack(maximum_weight=node.knapsack.maximum_weight)

        while not pq.empty():
            bound, node = pq.get()
            node_count += 1

            # print(f"level={node.level}, bound={-bound}, max_profit={best_set.profit}============================")
            # print(f"{node.knapsack}, node_count: {node_count}")

            if node.knapsack.current_weight <= node.knapsack.maximum_weight and node.bound > best_set.profit:
                next_knapsack.copy(other=node.knapsack)
                if next_knapsack.add_item(item_to_add=self.items[node.level]):
                    knapsack0: Knapsack = Knapsack(maximum_weight=maximum_weight)
                    knapsack0.copy(other=next_knapsack)
                    if knapsack0.profit > best_set.profit:
                        best_set.copy(other=knapsack0)
                    next_node0: KnapsackNode = KnapsackNode(level=node.level + 1,
                                                            knapsack=knapsack0,
                                                            bound=self.__get_bound(index=node.level,
                                                                                   knapsack=knapsack0),
                                                            original_knapsack=self)
                    if next_node0.bound > best_set.profit:
                        pq.put((-self.__compute_bound(index=node.level, knapsack=knapsack0), next_node0))
                    next_knapsack.remove_item(item_to_remove=self.items[node.level])
                knapsack1: Knapsack = Knapsack(maximum_weight=maximum_weight)
                knapsack1.copy(other=next_knapsack)
                next_node1: KnapsackNode = KnapsackNode(level=node.level + 1,
                                                        knapsack=knapsack1,
                                                        bound=self.__get_bound(index=node.level,
                                                                               knapsack=knapsack1),
                                                        original_knapsack=self)
                if next_node1.bound > best_set.profit:
                    pq.put((-self.__compute_bound(index=node.level, knapsack=knapsack1), next_node1))

        return best_set, node_count

    def __compute_bound(self, index: int, knapsack: Knapsack) -> int:
        if knapsack.current_weight >= knapsack.maximum_weight:
            return 0

        return self.__get_bound(index=index, knapsack=knapsack)

    def __get_knapsack_internal(self, index: int, knapsack: Knapsack, best_set: Knapsack, node_count: int) -> int:
        node_count += 1

        if knapsack.current_weight <= knapsack.maximum_weight and knapsack.profit > best_set.profit:
            best_set.copy(other=knapsack)

        if self.__is_promising(index=index, knapsack=knapsack, best_set=best_set):
            knapsack.add_item(item_to_add=self.items[index + 1], ignore_boundary=True)
            node_count = self.__get_knapsack_internal(index=index + 1,
                                                      knapsack=knapsack,
                                                      best_set=best_set,
                                                      node_count=node_count)
            knapsack.remove_item(item_to_remove=self.items[index + 1])
            node_count = self.__get_knapsack_internal(index=index + 1,
                                                      knapsack=knapsack,
                                                      best_set=best_set,
                                                      node_count=node_count)

        return node_count

    def __is_promising(self, index: int, knapsack: Knapsack, best_set: Knapsack) -> bool:
        if knapsack.current_weight >= knapsack.maximum_weight:
            return False

        return self.__get_bound(index=index, knapsack=knapsack) > best_set.profit

    def __get_bound(self, index: int, knapsack: Knapsack) -> int:
        j_index: int = index + 1
        bound = knapsack.profit
        total_weight: int = knapsack.current_weight
        while j_index < len(self.items) and total_weight <= knapsack.maximum_weight - self.items[j_index].weight:
            total_weight += self.items[j_index].weight
            bound += self.items[j_index].profit
            j_index += 1
        k_index: int = j_index

        if k_index < len(self.items):
            bound += (knapsack.maximum_weight - total_weight) * self.items[k_index].get_profit_by_weight()

        return bound


class KnapsackNode:
    __slots__ = ["level", "knapsack", "bound", "original_knapsack"]

    def __init__(self, level: int, knapsack: Knapsack, bound: int, original_knapsack: Knapsack):
        self.level: int = level
        self.knapsack: Knapsack = knapsack
        self.bound: int = bound
        self.original_knapsack: Knapsack = original_knapsack

    def __lt__(self, other: KnapsackNode):
        return self.bound < other.bound


def main():
    knapsack: Knapsack = Knapsack(maximum_weight=10000)
    # knapsack.add_item(item_to_add=Item(profit=40, weight=2))
    # knapsack.add_item(item_to_add=Item(profit=30, weight=5))
    # knapsack.add_item(item_to_add=Item(profit=50, weight=10))
    # knapsack.add_item(item_to_add=Item(profit=10, weight=5))
    knapsack.add_item(item_to_add=Item(profit=20, weight=2))
    knapsack.add_item(item_to_add=Item(profit=40, weight=5))
    knapsack.add_item(item_to_add=Item(profit=24, weight=4))
    knapsack.add_item(item_to_add=Item(profit=40, weight=8))
    # knapsack.add_item(item_to_add=Item(profit=40, weight=2))
    # knapsack.add_item(item_to_add=Item(profit=30, weight=5))
    # knapsack.add_item(item_to_add=Item(profit=50, weight=10))
    # knapsack.add_item(item_to_add=Item(profit=10, weight=5))
    print(f"{knapsack}")

    best_set, node_count = knapsack.get_knapsack_dfs(maximum_weight=9)
    print(f"best={best_set}")
    print(f"total nodes: {node_count}")

    best_set, node_count = knapsack.get_knapsack_best_fs(maximum_weight=9)
    print(f"best={best_set}")
    print(f"total nodes: {node_count}")
    # knapsack_problem(i=0, knapsack=knapsack, item_flags=item_flags, best_set=best_set)


if __name__ == "__main__":
    main()
