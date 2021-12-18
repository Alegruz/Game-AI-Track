def is_promising(is_connected: list[list[bool]], vertex_colors: list[int], index: int):
    is_switch: bool = True
    j_index: int = 0

    while j_index < index and is_switch:
        if is_connected[index][j_index] and vertex_colors[index] == vertex_colors[j_index]:
            is_switch = False
        j_index += 1
    
    return is_switch

def m_coloring(is_connected: list[list[bool]], vertex_colors: list[int], index: int, num_colors: int):
    if is_promising(is_connected=is_connected, vertex_colors=vertex_colors, index=index):
        if index == len(is_connected) - 1:
            print("[", end="")
            for x in range(0, len(is_connected) - 1):
                print(vertex_colors[x], end=", ")
            print(f"{vertex_colors[-1]}]")
        else:
            for color in range(0, num_colors):
                vertex_colors[index + 1] = color
                m_coloring(is_connected=is_connected,
                           vertex_colors=vertex_colors,
                           index=index + 1,
                           num_colors=num_colors)

def main():
    is_connected: list[list[bool]] = [[False, True, True, True],
                                      [True, False, True, False],
                                      [True, True, False, True],
                                      [True, False, True, False]]
    vertex_colors: list[int] = [0] * len(is_connected)
    num_colors: int = 3
    m_coloring(is_connected=is_connected, vertex_colors=vertex_colors, index=-1, num_colors=num_colors)

if __name__ == "__main__":
    main()