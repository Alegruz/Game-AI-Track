# huffman0 코드 구축 방법
# 1. 빈도수를 데이터로 갖는 n 개의 노드를 생성
# 2. 빈도수의 합이 최소가 되는 노드를 merge 시켜 이진트리로 구축
# 3. 모든 노드가 하나의 이진트리가 될 때까지 단계(2)를 반복
from __future__ import annotations
from collections import defaultdict

import heapq
from typing import Any, Union

class HuffmanNode:
    def __init__(self, left: HuffmanNode, right: HuffmanNode) -> None:
        self.left: HuffmanNode = left
        self.right: HuffmanNode = right

class Queue:
    def __init__(self) -> None:
        self.__queue: list[Any] = []
    
    def put(self, value: Any) -> None:
        self.__queue.append(value)
        self.__queue.sort(key=lambda value: value[0])
    
    def get(self) -> Any:
        item: Any = self.__queue[0]
        del self.__queue[0]
        return item
    
    def get_size(self):
        return len(self.__queue)

def create_tree(frequencies: list[tuple[float, str]]) -> tuple[float, Union[HuffmanNode, str]]:
    queue: Queue = Queue()
    for pair in frequencies:    # 1. Create left leaf node for each symbol
        queue.put(value=pair)   #    and add it to the priority queue
    while queue.get_size() > 1: # 2. While there is more than one node
        left: tuple[str, Union[HuffmanNode, str]] = queue.get()  #    left. remove two highest nodes
        right: tuple[str, Union[HuffmanNode, str]] = queue.get() #
        node: HuffmanNode = HuffmanNode(left=left, right=right) #   right. create internal node with children
        queue.put((left[0] + right[0], node))   #   c. add new node to queue
    return queue.get()  # 3. tree is complete - return root node

def huffman0(frequencies: defaultdict):
    heap = [[weight, [symbol, ""]] for symbol, weight in frequencies.items()]
    print(f"heap: {heap}")

    heapq.heapify(heap)
    while len(heap) > 1:
        low: int = heapq.heappop(heap)
        high: int = heapq.heappop(heap)

        for pair in low[1:]:
            pair[1] = '0' + pair[1]
        for pair in high[1:]:
            pair[1] = '1' + pair[1]
        
        heapq.heappush(heap, [low[0] + high[0]] + low[1:] + high[1:])
    return sorted(heapq.heappop(heap)[1:], key=lambda p: (len(p[-1]), p))

def huffman1(frequencies: defaultdict) -> tuple[float, Union[HuffmanNode, str]]:
    return create_tree(frequencies=frequencies)

def main() -> None:
    frequencies: list[tuple[float, str]] = [(8.167, 'a'), (1.492, 'b'), (2.782, 'c'), (4.253, 'd'), 
                                            (12.702, 'e'),(2.228, 'f'), (2.015, 'g'), (6.094, 'h'),
                                            (6.966, 'i'), (0.153, 'j'), (0.747, 'k'), (4.025, 'l'),
                                            (2.406, 'm'), (6.749, 'n'), (7.507, 'o'), (1.929, 'p'),
                                            (0.095, 'q'), (5.987, 'r'), (6.327, 's'), (9.056, 't'),
                                            (2.758, 'u'), (1.037, 'v'), (2.365, 'w'), (0.150, 'x'),
                                            (1.974, 'y'), (0.074, 'z') ]

    node: tuple[float, Union[HuffmanNode, str]] = huffman1(frequencies=frequencies)
    print(print_tree(node=node))
    code: dict[str, str] = walk_tree(node=node)
    for i in sorted(frequencies, reverse=True):
        print(f"{i[1]} {'{:6.2f}'.format(i[0])} {code[i[1]]}")

    # data: str = "The frog at the bottom of the well drifts off into the great ocean"
    # frequencies: defaultdict[str, int] = defaultdict(int)
    # for symbol in data:
    #     frequencies[symbol] += 1
    # huffman0_encoded_data: list[list[str]] = huffman0(frequencies=frequencies)
    # print(f"{'Symbol'.ljust(10)}{'Weight'.ljust(10)}huffman0 Code")
    # for p in huffman0_encoded_data:
    #     print(f"{p[0].ljust(10)}{str(frequencies[p[0]]).ljust(10)}{p[1]}")

def print_tree(node: tuple[float, Union[HuffmanNode, str]]) -> str:
    weight, huffman_node = node
    if isinstance(huffman_node, str):
        return "%s = %.3f" % (huffman_node, weight)
    else:
        left: str = print_tree(node=huffman_node.left)
        right: str  = print_tree(node=huffman_node.right)
    return side_by_side(left=left, right=right, weight=weight)


def side_by_side(left: str, right: str, weight: float) -> str:
    left: list[str] = left.split("\n") #결과를 list에 저장
    right: list[str] = right.split("\n")
    n1: int = len(left)
    n2: int = len(right)
    if n1 < n2:
        left.extend([" "*len(left[0])]*(n2-n1))
    else:
        right.extend([" "*len(right[0])]*(n1-n2))
    r = [" "*len(left[0]) + " ^ " + " "*len(right[0])]
    r += ["/" + "-"*(len(left[0])-1) + "%7.3f" % weight + "-"*(len(right[0])-1) + "\\"]
    for l1, l2 in zip(left, right):
        r.append(l1 + " " + l2)
    return "\n".join(r)

def walk_tree(node: tuple[float, Union[HuffmanNode, str]], 
              prefix: str = "", 
              code: dict[str, str] = {}) -> dict[str, str]:
    weight, huffman_node = node
    if isinstance(huffman_node, str):
        code[huffman_node] = prefix
    else:
        walk_tree(node=huffman_node.left, prefix=prefix + "0")
        walk_tree(node=huffman_node.right, prefix=prefix + "1")
    return code


if __name__ == "__main__":
    main()