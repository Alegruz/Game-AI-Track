# 4-Queens
# 4 개의 Queen을 서로 상대방을 위협하지 않도록 4 x 4 체스판에 위치시키는 문제.

# 상태 공간 트리, 즉 queen 1, 2, 3, 4을 순서대로 비치하는 순으로 트리를 만들면 (처음엔 1이 움직이고, 그 다음엔 2, 그 다음엔 3, 그 다음엔 4 식으로) 이거 언제 다 읽음?
# 그래서 되추적 기술 사용

# 마디의 유망성:
#   전혀 해답이 나올 가능성이 없는 마디는 유망하지 않다: non-promising
#   그렇지 않으면 유망하다: promising

# 되추적:
#   어떤 마디의 유망성을 점검한 후, 유망하지 않다고 판단이 되면 그 마디의 부모 마디(parent)로 돌아가서("backtrack") 다음 후손 마디에 대한 검색을 계속하게 되는 절차
#   부모 마디로 돌아 가는 것 -> 가치치기(pruning)
#   이 과정에서 방문한 마디만으로 구성된 부분 트리 -> 가지친 상태 공간 트리(pruned state space tree)

# 되추적 알고리듬
# 되추적 알고리듬은 상태 공간 트리에서 DFS
#   유망하지 않은 마디들은 pruning
#   유망한 마디만 child 탐색
# 절차:
#   1. 상태 공간 트리의 DFS
#   2. 각 마디가 유망한지 점검
#   3. 마디가 유망하지 않으면 해당 마디의 부모 마디로 돌아가서 탐색 계속

# def check_node(node: Node):
#     if node.is_promising():
#         if there is a solution at node:
#             write the solution
#         else:
#             for child_node in node.children:
#                 check_node(node=child_node)

def is_promising(columns: list[int], index: int) -> bool:
    switch: bool = True
    k_index: int = 0

    while k_index < index and switch:
        # is on the same column or is on the same diagonal
        if columns[index] == columns[k_index] or \
            abs(columns[index] - columns[k_index] == index - k_index):
            switch = False
        k_index += 1
    
    return switch

def queens(columns: list[int], index: int) -> None:
    if is_promising(columns=columns, index=index):
        if index == len(columns) - 1:
            print("[", end="")
            for x in range(0, len(columns) - 1):
                print(columns[x], end=", ")
            print(f"{columns[len(columns) - 1]}]")

        else:
            for neighbor_index in range(0, len(columns)):
                columns[index + 1] = neighbor_index
                queens(columns=columns, index=index + 1)

def main():
    num_columns: int = 5
    columns: list[int] = num_columns * [0]
    queens(columns=columns, index=-1)

if __name__ == "__main__":
    main()