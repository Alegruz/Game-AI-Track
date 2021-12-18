# Sum of Subsets Problem
# n 개의 item을 이용하여 item들의 무게의 합이 W가 되는 부분집합 구하기

# 무게가 증가하는 순으로 데이터를 정렬
#   -> 유망하지 않은지를 쉽게 판단할 수 있음
#   w_(i+1)는 i 수준에서 남아있는 가장 가벼운 아이템의 무게
#   w_(i+1)를 넣을 수 없으면  i+1 이후는 고려 X

# weight: 수준 i의 마디까지 포함된 무게의 합
# total: 남아 있는 아이템의 무게의 총합
# weight + w_(i+1) > W (if weight ≠ W) or
#   weight + total < W 이면 유망하지 않다

def is_promising(index: int, weights: list[int], weight: int, total: int, target_weight: int):
    return weight + total >= target_weight and \
        (weight == target_weight or weight + weights[index + 1] <= target_weight)

def sum_of_subsets(index: int, weights: list[int], is_included: list[bool], weight: int, total: int, target_weight: int):
    if is_promising(index=index, 
                    weights=weights, 
                    weight=weight, 
                    total=total, 
                    target_weight=target_weight):
        if weight == target_weight:
            print("[", end="")
            for x in range(0, len(weights) - 1):
                print(1 if is_included[x] else 0, end=", ")
            print(f"{1 if is_included[-1] else 0}]")
        else:
            is_included[index + 1] = True
            sum_of_subsets(index=index + 1,
                           weights=weights,
                           is_included=is_included,
                           weight=weight + weights[index + 1],
                           total=total - weights[index + 1],
                           target_weight=target_weight)
            is_included[index + 1] = False
            sum_of_subsets(index=index + 1,
                           weights=weights,
                           is_included=is_included,
                           weight=weight,
                           total=total - weights[index + 1],
                           target_weight=target_weight)

def main():
    weights: list[int] = [1, 2, 4, 6]
    target_weight: int = 6
    print(f"items: {weights} target weight={target_weight}")
    is_included: list[bool] = [False] * len(weights)
    total: int = 0
    for weight in weights:
        total += weight
    
    sum_of_subsets(index=-1, 
                   weights=weights, 
                   is_included=is_included, 
                   weight=0, 
                   total=total, 
                   target_weight=target_weight)

if __name__ == "__main__":
    main()