# print integer matrix

def print_matrixi(matrix: list[list[int]]):
    num_rows: int = len(matrix)
    num_columns = len(matrix[0])
    for y in range(0, num_rows):
        for x in range(0, num_columns):
            print(f"{matrix[y][x]:4d}", end=" ")
        print()

#print float matrix
def print_matrixf(matrix: list[list[float]]):
    size: int = len(matrix[0])
    for y in range(0, size):
        for x in range(0, size):
            print(f"{matrix[y][x]:5.2f}",end=" ")
        print()
