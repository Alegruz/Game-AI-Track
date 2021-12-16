from queue import PriorityQueue

from engine.core.Math import Vector2i
from engine.core.NavigationBox import NavigationBox, Neighbor
from engine.core.Stack import Stack


class Navigation:
    @staticmethod
    def find_path(start: NavigationBox, end: NavigationBox) -> list[Vector2i]:
        cache: set[NavigationBox] = set()

        path: Stack = Stack()

        Navigation.__find_path_resursive(start=start,
                                         cache=cache,
                                         path=path,
                                         end=end)

        return path.data

    @staticmethod
    def __find_path_resursive(start: NavigationBox,
                              cache: set[NavigationBox],
                              path: Stack,
                              end: NavigationBox) -> bool:
        if start in cache:
            return False

        cache.add(start)
        path.push(element=start)

        if start is end:
            return True
        else:
            possible_neighbors: list[Neighbor] = []
            end_index: int = -1

            for i, neighbor in enumerate(start.neighbors):
                if neighbor.box is end:
                    end_index = i
                    break

            if end_index != -1:
                Navigation.__find_path_resursive(start=start.neighbors[end_index].box,
                                                 cache=cache,
                                                 path=path,
                                                 end=end)
            else:
                if len(possible_neighbors) > 0:
                    has_optimal_path: bool = False

                    for neighbor in start.neighbors:
                        if Navigation.__find_path_resursive(start=neighbor.box, cache=cache, path=path, end=end):
                            has_optimal_path = True
                            break

                    if not has_optimal_path:
                        path.pop()
                        return False

        return True




