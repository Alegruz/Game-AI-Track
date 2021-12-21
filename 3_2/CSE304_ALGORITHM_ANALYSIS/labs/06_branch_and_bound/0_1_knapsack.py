# 0-1 Knapsack Problem

# problem: S = {item_1, item_2, ..., item_n}
    # w_i = weight of item_i
    # p_i = profit of item_i
    # W = maximum weight the knapsack can hold

# Normal backtracking algorithm for optimization problem:
# void checknode(node v):
#     if value(v) is better than best:
#         best = value(v)
#     if is_promising(v):
#         for each child u of v:
#             checknode(u)
# best: 지금까지 찾은 제일 좋은 해답값
# value(v): v 마디에서의 해답값

# Algorithm sketch: 아이템은 무게 당 가치가 감소하는 순서로 정렬 가정
# profit: 그 마디에 오기까지 넣었던 아이템의 값어치의 합
# weight: 그 마디에 오기까지 넣었던 아이템의 무게의 합
# bound: 마디가 수준 i에 있다고 하고, 수준 k에 있는 마디에서 총무게가 W가 넘는다고 하자, 그러면
    # totweight = weight + sig j=i+1 to k-1(w_j)
    # bound = (profit + sig j=i+1 to k-1 p_j)  +    (W - totweight)      *          (p_k / w_k)
    #        처음 k-1 개를 이용한 아이템의 값어치  k번째 아이템에 가용한 용량   k번째 아이템 단위 무게 당 값어치
    # maxprofit: 지금까지 찾은 최선의 해답이 주는 값어치
    # bound ≤ maxprofit이면 수준 i에 있는 마디는 유망하지 않음
    # p_i/w_i의 값이 큰 것부터 내림차순으로 아이템을 정렬 (일종의 탐욕적 방법이지만, 알고리듬 자체는 탐욕적인 알고리듬이 아님)
    # 초기값:
        # maxprofit: int = 0
        # profit: int = 0
        # weight: int = 0


# DFS로 각 마디 방문하여 다음 수행:
    # 그 마디의 profit과 weight 계산
    # 그 마디의 bound 계산
    # weight < W and bound > maxprofit이면 검색 계속; 그렇지 않으면 되추적

# 남은 공간이 있고 확장 시 bound 값이 현재 최대값보다 크면 true
def is_promising(index: int, 
                 profits: list[int], 
                 max_profit: int, 
                 weights: list[int],
                 weight: int, 
                 target_weight: int, best_set: list[bool]) -> bool:
    # 남은 공간 확인
    if weight >= target_weight:
        return False
    else:
        j_index: int = index + 1
        total_weight: int = weight
        bound: float = 0.0
        while j_index <= len(profits) - 1 and total_weight + weights[j_index] <= target_weight:
            total_weight += weights[j_index]
            bound += profits[j_index]
            j_index += 1
        
        k_index: int = j_index
        if k_index < len(profits):
            bound += (target_weight - total_weight) * (profits[k_index] / weights[k_index])
        
        return bound > max_profit

def knapsack(is_included: list[bool], 
             index: int, 
             profits: list[int], 
             profit: int, 
             max_profit: int, 
             weights: list[int],
             weight: int, 
             target_weight: int, best_set: list[bool]) -> tuple[int, int, int]:
    # 자신이 유효한지, 지금까지의 최대값보다 큰지

    last_index: int = 0
    best_set: list[int] = []
    if weight <= target_weight and profit > max_profit:
        max_profit = profit
        # 마지막으로 포함되는 아이템
        last_index = index
        best_set = is_included[:]
    
    # 남은 공간이 있고 확장 시 bound 값이 현재 최대값보다 크면
    if is_promising():
        # index + 1 포함
        is_included[index + 1] = True
        next_max_profit, next_last_index, next_best_set = knapsack(is_included=is_included,
                                                                   index=index + 1,
                                                                   profits=profits,
                                                                   profit=profit + profits[index + 1],
                                                                   max_profit=max_profit,
                                                                   weights=weights,
                                                                   weight=weight + weights[index + 1],
                                                                   target_weight=target_weight)

        if next_max_profit > max_profit:
            max_profit = next_max_profit
            next_last_index = last_index
            best_set = next_best_set[:]

        # index + 1 미포함
        is_included[index + 1] = False
        next_max_profit, next_last_index, next_best_set = knapsack(is_included=is_included,
                                                                   index=index + 1,
                                                                   profits=profits,
                                                                   profit=profit,
                                                                   max_profit=max_profit,
                                                                   weights=weights,
                                                                   weight=weight,
                                                                   target_weight=target_weight)
        
        if next_max_profit > max_profit:
            max_profit = next_max_profit
            next_last_index = last_index
            best_set = next_best_set[:]
    
    return max_profit, last_index, best_set

def main():
    target_weight: int = 16
    profits: list[int] = [40, 30, 50, 10]
    weights: list[int] = [2, 5, 10, 5]
    max_profit: int = 0
    is_included: list[bool] = [False, False, False, False]
    best_set: list[bool] = [False, False, False, False]
    max_profit, last_index, best_set = knapsack()

if __name__ == "__main__":
    main()
