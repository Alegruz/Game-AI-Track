class Node:
    def __init__(self, data=list[list]) -> None:
        self.left_child: Node = None
        self.right_child: Node = None
        self.data: list[list] = data

def get_dna_sequence_alignment():
    a: list[str] = ['A', 'A', 'C', 'A', 'G', 'T', 'T', 'A', 'C', 'C']
    b: list[str] = ['T', 'A', 'A', 'G', 'G', 'T', 'C', 'A']

    m: int = len(a)
    n: int = len(b)
    table: list[list[int]] = [[0 for j in range(0, n + 1)] for i in range(0, m + 1)]
    min_indices: list[list[tuple[int, int]]] = [[(0, 0) for j in range(0, n + 1)] for i in range(0, m + 1)]

    for j in range(n - 1, -1, -1):
        table[m][j] = table[m][j + 1] + 2
    
    for i in range(m - 1, -1, -1):
        table[i][n] = table[i + 1][n] + 2
    
    # generate table
    min_index = (m, n)
    for diagonal in range(m + n - 1, 0, -1):
        for i in range(max(diagonal - n, 0), min(diagonal, m)):
            j: int = min(diagonal - i, n) - 1
            penalty: int = int(a[i] != b[j])

            value: int = min(table[i + 1][j + 1] + penalty, table[i + 1][j] + 2, table[i][j + 1] + 2)
            if value == table[i + 1][j + 1] + penalty:
                min_indices[i][j] = (i + 1, j + 1)
            elif value == table[i + 1][j] + 2:
                min_indices[i][j] = (i + 1, j)
            else:
                min_indices[i][j] = (i, j + 1)
            table[i][j] = value

    print_integer_matrix(matrix=table)
    x: int = 0
    y: int = 0

    while x < m and y < n:
        tx: int = x
        ty: int = y
        print(min_indices[x][y])
        x, y = min_indices[x][y]
        if x == tx + 1 and y == ty + 1:
            print(f"{a[tx]}   {b[ty]}")
        elif x == tx and ty == ty + 1:
            print(f" -    {b[ty]}")
        else:
            print(f"{a[tx]}    - ")


def get_optimal_bst():
    key: list[str] = [" ", "A", "B", "C", "D", "E"]
    p: list[float] = [0., 3/15, 1/15, 2/15, 5/15, 4/15]
    n: int = len(p) - 1

    a_matrix: list[list[int]] = [[0 for j in range(0, n + 2)] for i in range(0, n + 2)]
    indices: list[list[int]] = [[0 for j in range(0, n + 2)] for i in range(0, n + 2)]

    for i in range(1, n + 1):
        a_matrix[i][i - 1] = 0
        a_matrix[i][i] = p[i]
        indices[i][i] = i
        indices[i][i - 1] = 0
    a_matrix[n + 1][n] = 0
    indices[n + 1][n] = 0

    for diagonal in range(1, n):
        for i in range(1, n - diagonal + 1):
            j: int = i + diagonal
            p_sum: int = 0
            for sum_index in range(i, j + 1):
                p_sum += p[sum_index]
            min_value: float = a_matrix[i][i - 1] + a_matrix[i + 1][j] + p_sum
            min_index: int = i
            for index in range(i + 1, j + 1):
                value: float = a_matrix[i][index - 1] + a_matrix[index + 1][j] + p_sum
                if min_value > value:
                    min_value = value
                    min_index = index
            a_matrix[i][j] = min_value
            indices[i][j] = min_index
        
    print(f"min_average={a_matrix[1][n]}")

    print_float_matrix(matrix=a_matrix)
    print()
    print_integer_matrix(matrix=indices)

    root: Node = tree(key=key, r=indices, i=1, j=n)
    print_in_order(root=root)
    print()
    print_pre_order(root=root)

def main() -> None:
    get_optimal_bst()
    get_dna_sequence_alignment()

def print_in_order(root: Node) -> None:
    if root is None:
        return
    
    print_in_order(root=root.left_child)
    print(root.data)
    print_in_order(root=root.right_child)

def print_post_order(root: Node) -> None:
    if root is None:
        return

    print_post_order(root=root.left_child)
    print_post_order(root=root.right_child)
    print(root.data)

def print_pre_order(root: Node) -> None:
    if root is None:
        return
    
    print(root.data)
    print_in_order(root=root.left_child)
    print_in_order(root=root.right_child)

def print_integer_matrix(matrix: list[list[int]]) -> None:
    height: int = len(matrix)
    width: int = len(matrix[0])

    for row in range(0, height):
        for col in range(0, width):
            print(f"{matrix[row][col]: 4d}", end=" ")
        print()

def print_float_matrix(matrix: list[list[float]]) -> None:
    size: int = len(matrix[0])

    for row in range(0, size):
        for col in range(0, size):
            print(f"{matrix[row][col]: 5.2f}", end=" ")
        print()

def tree(key: list, r: list[list], i: int, j: int) -> Node:
    k = r[i][j]

    if k == 0:
        return None
    else:
        p: Node = Node(data=key[k])
        p.left_child = tree(key=key, r=r, i=i, j=k-1)
        p.right_child = tree(key=key, r=r, i=k+1, j=j)
        return p

if __name__ == "__main__":
    main()