INF: int = 1000


def get_shortest_path(weights: list[list[int]], start_index: int = 0) -> tuple[set[tuple[int, int]], list[int]]:
    size: int = len(weights)
    result: list[set[tuple[int, int]]] = list(set())

    vnear: int = None
    f: set = set()
    touch: list[int] = size * [0]
    length: list[int] = size * [0]
    shortest_distances: list[int] = size * [0]

    for i in range(0, size):
        if i != start_index:
            touch[i] = start_index
            length[i] = weights[start_index][i]

    for times in range(0, size - 1):
        minimum: int = INF
        for i in range(0, size):
            if i != start_index and 0 <= length[i] < minimum:
                minimum = length[i]
                vnear: int = i
        if vnear is None:
            break
        edge: tuple[int, int] = (touch[vnear], vnear)
        f.add(edge)

        for i in range(1, size):
            if length[vnear] + weights[vnear][i] < length[i]:
                length[i] = length[vnear] + weights[vnear][i]
                touch[i] = vnear
        shortest_distances[vnear] = length[vnear]
        length[vnear] = -1

    return f, shortest_distances


def get_shortest_path_from_all_nodes(weights: list[list[int]]) -> list[tuple[set[tuple[int, int]], list[int]]]:
    size: int = len(weights)
    result: list[tuple[set[tuple[int, int]], list[int]]] = list()

    for start_index in range(0, size):
        f, shortest_distances = get_shortest_path(weights=weights, start_index=start_index)
        result.append((f, shortest_distances))

    return result


def is_promising(index: int, columns: list) -> bool:
    k_index: int = 0
    is_switch: bool = True

    while k_index < index and is_switch:
        if columns[index] == columns[k_index] or abs(columns[index] - columns[k_index]) == index - k_index:
            is_switch = False
        k_index += 1

    return is_switch


def queens(index: int, columns: list, depth: int) -> None:
    queens_recursive(index=index, columns=columns, depth=depth, current_depth=0)


def queens_recursive(index: int, columns: list, depth: int, current_depth: int) -> int:
    if current_depth == -1:
        return -1

    if is_promising(index=index, columns=columns):
        if index == len(columns) - 1:
            if current_depth == depth:
                print(columns)
                return -1
            current_depth += 1
        else:
            for j in range(0, len(columns)):
                columns[index + 1] = j
                current_depth = queens_recursive(index=index + 1, columns=columns, depth=depth,
                                                 current_depth=current_depth)
                if current_depth == -1:
                    return -1

    return current_depth


def main() -> None:
    weights: list[list[int]] = [[0, 7, 4, 6, 1],
                                [INF, 0, INF, INF, INF],
                                [INF, 2, 0, 5, INF],
                                [INF, 3, INF, 0, INF],
                                [INF, INF, INF, 1, 0]]

    f, distances = get_shortest_path(weights=weights)

    print(f"edges: {f}\ndistances: {distances}")

    size: int = 7
    columns: list[int] = size * [0]
    queens(index=-1, columns=columns, depth=1)


if __name__ == "__main__":
    main()
