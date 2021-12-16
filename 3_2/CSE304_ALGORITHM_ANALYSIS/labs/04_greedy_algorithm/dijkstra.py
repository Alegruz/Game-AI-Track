# Greedy Algorithm
# Single Source Shortest Path Problem
# Dijkstra Algorithm

# 가중치가 있는 방향성 그래프에서 한 특정 정점에서 다른 모든 정점으로 가는 최단 경로 구하는 문제
# 알고리듬:
# 1. F = 공집합 (다른 노드로 가는 최단 경로를 구성하는 arc를 모은 것임)
# 2. Y = { v_1 } (v_1에서 출발하는 것으로 가정. Y 집합은 v_1으로부터 최단경로가 확정된 노드들의 잡합을 나타내주는 것임)
# 3. 최종 해답 얻지 못하면 다음 반복
#   1. 선정 절차 / 적정성 점검: V-Y에 속한 정점 중(아직 결정 안 된 노드)에서 v_1에서 Y에 속한 정점만을 거쳐서(즉, 이미 결정된 경로를 거쳐서) 최단 경로가 되는 정점 v(아직 가지 않은 노드 중 가장 거리 짧은 곳)를 선정
#   2. 그 정점 v를 Y에 추가
#   3. v에서 F로 이어지는 최단 경로 상의 이음선을 F에 추가 (F는 최단 경로가 결정된 것을 구성하는 arc들임. Y 만으로 만들어진 것과, v를 연결한 arc를 F에 추가하겠다는 의미.)
#   4. 해답 점검: Y = V, 즉 최단 경로가 모든 노드에 대해 결정되면 T = (V, F) 최단 경로를 나타내는 그래프.

# 추가적으로 touch[1..n]와 length[1..n] 배열 유지
#   * touch[i] = v_1에서 출발해서 경로가 결정된 노드만을 거쳐 경로가 결정되지 않은(V - Y) v_i 노드로 갈 때, 마지막으로 지나친 경로가 결정된 노드 v
#   * length[i] = v_1에서 출발해서 경로가 결정된 노드만을 거쳐 경로가 결정되지 않은(V = Y) v_i 노드로 갈 때, v_1에서 v_i로 가는 현재 최단 거리를 의미
INF: int = pow(2, 32)


def dijkstra(num_nodes: int, distances_from_node_to_node: list[list[int]]) -> tuple[list[tuple[int, int]], list[int]]:
    nearest_vertex_index: int = 0
    touch: list[int] = [0 for i in range(0, num_nodes)]
    length: list[int] = [0 for i in range(0, num_nodes)]
    shortest_paths: set[tuple[int, int]] = set()
    shortest_distances: list[int] = [0 for i in range(0, num_nodes)]
    for i in range(1, num_nodes):
        touch[i] = 0    # 현재 가장 최단 거리는 1에서 출발하는 것임
        length[i] = distances_from_node_to_node[0][i]   # 1번 노드에서 i번 노드로의 거리. 길이 있으면 어떤 값, 없으면 무한대
    print(f"touch: {touch}")
    print(f"length: {length}")
    
    for repeat_index in range(0, num_nodes - 1):
        min: int = INF
        for i in range(1, num_nodes):
            # find the smallest length
            if 0 <= length[i] < min:
                min = length[i]
                nearest_vertex_index = i
        print(f"min: {min}, nearest_vertex_index: {nearest_vertex_index}")
        nearest_edge: tuple[int, int] = (touch[nearest_vertex_index], nearest_vertex_index) # 이음선
        shortest_paths.add(nearest_edge)
        shortest_distances[nearest_vertex_index] = length[nearest_vertex_index]

        for i in range(1, num_nodes):
            if length[nearest_vertex_index] + distances_from_node_to_node[nearest_vertex_index][i] < length[i]:
                length[i] = length[nearest_vertex_index] + distances_from_node_to_node[nearest_vertex_index][i]
                touch[i] = nearest_vertex_index
        length[nearest_vertex_index] = -1
    
    return shortest_paths, shortest_distances

def main():
    distances_from_node_to_node: list[list[int]] = [[0,   7,   4,   6,   1], 
                                                    [INF, 0,   INF, INF, INF],
                                                    [INF, 2,   0,   5,   INF],
                                                    [INF, 3,   INF, 0,   INF],
                                                    [INF, INF, INF, 1,   0]]
    shortest_paths, shorted_distances = dijkstra(num_nodes=len(distances_from_node_to_node),
                                                 distances_from_node_to_node=distances_from_node_to_node)
    print(shortest_paths)
    print(shorted_distances)

if __name__ == "__main__":
    main()