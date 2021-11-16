def get_sum_of_subsets(index: int,
                       weight: int,
                       total: int,
                       sum: int,
                       subset: int,
                       weights: list[int],
                       subset_hashset: set[int]) -> None:
    if is_promising_subset(index=index, weight=weight, total=total, sum=sum, weights=weights):
        if weight == sum:
            assert (subset not in subset_hashset)
            subset_hashset.add(subset)
            print("subset: ", end="")
            for i in range(0, len(weights)):
                if (subset >> i) & 1:
                    print("1", end="")
                else:
                    print("0", end="")

                if i % 4 == 3:
                    print(" ", end="")
            print()
        else:
            subset |= (1 << (index + 1))
            get_sum_of_subsets(index=index + 1,
                               weight=weight + weights[index + 1],
                               total=total - weights[index + 1],
                               sum=sum,
                               subset=subset,
                               weights=weights,
                               subset_hashset=subset_hashset)
            subset &= ~(1 << (index + 1))
            get_sum_of_subsets(index=index + 1,
                               weight=weight,
                               total=total - weights[index + 1],
                               sum=sum,
                               subset=subset,
                               weights=weights,
                               subset_hashset=subset_hashset)


def is_promising_m_coloring(index: int, color_vertices: list[int], is_edge: list[list[bool]]) -> bool:
    switch: bool = True
    j_index: int = 0

    while j_index < index and switch:
        if is_edge[index][j_index] and color_vertices[index] == color_vertices[j_index]:
            switch = False
        j_index += 1

    return switch


def is_promising_subset(index: int, weight: int, total: int, sum: int, weights: list[int]) -> bool:
    return (weight + total >= sum) and (weight == sum or weight + weights[index + 1] <= sum)


def m_coloring(m: int, index: int, color_vertices: list[int], is_edge: list[list[bool]]) -> None:
    if is_promising_m_coloring(index=index, color_vertices=color_vertices, is_edge=is_edge):
        if index == len(color_vertices) - 1:
            print(f"data: {color_vertices}")
        else:
            for color in range(1, m + 1):
                color_vertices[index + 1] = color
                m_coloring(m=m, index=index + 1, color_vertices=color_vertices, is_edge=is_edge)


def main():
    is_edge: list[list[bool]] = [[False, True, True, False, True],
                                 [True, False, True, False, False],
                                 [True, True, False, True, True],
                                 [False, False, True, False, True],
                                 [True, False, True, True, False]]
    color_vertices: list[int] = len(is_edge) * [0]
    m: int = 3
    m_coloring(m=m, index=-1, color_vertices=color_vertices, is_edge=is_edge)

    weights: list[int] = [i for i in range(1, 7)]
    sum: int = 11
    print(f"items={weights}, sum: {sum}")
    include: list[int] = len(weights) * [0]
    subset: int = 0
    total: int = 0
    for weight in weights:
        total += weight
    subset_hashset: set[int] = set()
    get_sum_of_subsets(index=-1,
                       weight=0,
                       total=total,
                       sum=sum,
                       subset=subset,
                       weights=weights,
                       subset_hashset=subset_hashset)
    # print(f"subset_hashset size: {len(subset_hashset)}")

if __name__ == "__main__":
    main()
