from utility import print_matrixi

def depth_first_tree_search(has_edge: list[list[int]], first_node_index: int):
    stack: list[int] = []
    has_visited: list[bool] = len(has_edge) * [False]

    stack.append(first_node_index)

    while len(stack) > 0:
        next_node_index: int = stack[-1]
        if has_visited[next_node_index]:
            stack.pop()
            continue
        print(stack.pop())
        has_visited[next_node_index] = True

        for neighbor_index in range(0, len(has_edge[next_node_index])):
            if next_node_index == neighbor_index:
                continue
            if has_visited[neighbor_index]:
                continue
            if has_edge[next_node_index][neighbor_index] == 1:
                stack.append(neighbor_index)



def main():
    edges: dict[int, list[int]] = { 0: [1, 2, 3],
                                    1: [2, 5],
                                    2: [3, 4, 5, 6],
                                    3: [4, 6],
                                    4: [6, 7]}
    num_nodes: int = 8
    has_edge: list[list[int]] = [[0 for j in range(0, num_nodes)] for i in range(0, num_nodes)]
    for node_index in range(0, num_nodes - 1):
        for neighbor_index in range(node_index + 1, num_nodes):
            if node_index in edges:
                if neighbor_index in edges[node_index]:
                    has_edge[node_index][neighbor_index] = 1
                    has_edge[neighbor_index][node_index] = 1
    print_matrixi(matrix=has_edge)
    depth_first_tree_search(has_edge=has_edge, first_node_index=0)

if __name__ == "__main__":
    main()