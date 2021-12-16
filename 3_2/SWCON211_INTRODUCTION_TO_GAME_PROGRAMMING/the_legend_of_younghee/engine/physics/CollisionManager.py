import math

from engine.core.GlobalConstants import GlobalConstants
from engine.core.Math import Vector2i, Vector2f
from engine.core.NavigationBox import NavigationBox
from engine.object.CollidableObject import CollidableObject
from engine.object.DestructibleObject import DestructibleObject
from engine.object.Enemy import Enemy
from engine.player.Player import Player


class CollisionManager:
    __slots__ = ["__collidables_map", "__grid_object_hashes", "__grid_object_indices", "__collidables", "__grid_size",
                 "__cell_size", "__cell_starts", "__cell_ends", "__num_cells", "__sorted_collidables",
                 "__collidables_to_key", "__navigation_boxes_map", "__navigation_boxes_to_key", "__navigation_boxes",
                 "__sorted_navigation_boxes", "__grid_navigation_box_hashes", "__grid_navigation_box_indices",
                 "__navigation_cell_starts", "__navigation_cell_ends"]

    def __init__(self, grid_size: Vector2i, cell_size: Vector2f):
        self.__grid_size: Vector2i = grid_size
        self.__cell_size: Vector2f = cell_size
        self.__num_cells: int = self.__grid_size.x * self.__grid_size.y

        self.__collidables_map: dict[str, CollidableObject] = dict()
        self.__collidables_to_key: dict[CollidableObject, str] = dict()

        self.__navigation_boxes_map: dict[str, NavigationBox] = dict()
        self.__navigation_boxes_to_key: dict[NavigationBox, str] = dict()

        self.__grid_object_hashes: list[int] = []
        self.__grid_object_indices: list[int] = []

        self.__grid_navigation_box_hashes: list[int] = []
        self.__grid_navigation_box_indices: list[int] = []

        self.__collidables: list[CollidableObject] = []
        self.__sorted_collidables: list[CollidableObject] = []

        self.__navigation_boxes: list[NavigationBox] = []
        self.__sorted_navigation_boxes: list[NavigationBox] = []

        self.__cell_starts: list[int] = [-1 for i in range(0, self.__num_cells)]
        self.__cell_ends: list[int] = [-1 for i in range(0, self.__num_cells)]

        self.__navigation_cell_starts: list[int] = [-1 for i in range(0, self.__num_cells)]
        self.__navigation_cell_ends: list[int] = [-1 for i in range(0, self.__num_cells)]

    def add_collidable(self, key: str, collidable_object: CollidableObject) -> bool:
        assert isinstance(key, str) and issubclass(collidable_object.__class__, CollidableObject)

        if key in self.__collidables_map:
            return False

        self.__collidables_map[key] = collidable_object
        self.__collidables_to_key[collidable_object] = key
        self.__collidables.append(collidable_object)
        self.__sorted_collidables.append(self.__collidables[-1])
        self.__grid_object_hashes.append(-1)
        self.__grid_object_indices.append(-1)

        self.__calculate_hashes()
        self.__sort_objects()
        self.__reorder_data_and_find_cell_starts()

    def add_navigation_box(self, key: str, navigation_box: NavigationBox) -> bool:
        assert isinstance(key, str) and isinstance(navigation_box, NavigationBox)

        if key in self.__navigation_boxes_map:
            return False

        self.__navigation_boxes_map[key] = navigation_box
        self.__navigation_boxes_to_key[navigation_box] = key
        self.__navigation_boxes.append(navigation_box)
        self.__sorted_navigation_boxes.append(self.__navigation_boxes[-1])
        self.__grid_navigation_box_hashes.append(-1)
        self.__grid_navigation_box_indices.append(-1)

        self.__calculate_navigation_hashes()
        self.__sort_navigation_objects()
        self.__reorder_navigation_data_and_find_cell_starts()

    def contains_collidable_by_key(self, key: str):
        return key in self.__collidables_map

    def contains_navigation_box_by_key(self, key: str):
        return key in self.__navigation_boxes_map

    def remove_collidable(self, key: str) -> bool:
        if key not in self.__collidables_map:
            return False

        self.__collidables_map[key].undraw_bounding_box()
        self.__collidables.remove(self.__collidables_map[key])
        self.__sorted_collidables.remove(self.__collidables_map[key])
        del self.__collidables_to_key[self.__collidables_map[key]]
        del self.__collidables_map[key]

        self.__calculate_hashes()
        self.__sort_objects()
        self.__reorder_data_and_find_cell_starts()

        return True

    def remove_navigation_box(self, key: str) -> bool:
        if key not in self.__navigation_boxes_map:
            return False

        self.__navigation_boxes_map[key].undraw_bounding_box()
        self.__navigation_boxes.remove(self.__navigation_boxes_map[key])
        self.__sorted_navigation_boxes.remove(self.__navigation_boxes_map[key])
        del self.__navigation_boxes_to_key[self.__navigation_boxes_map[key]]
        del self.__navigation_boxes_map[key]

        self.__calculate_navigation_hashes()
        self.__sort_navigation_objects()
        self.__reorder_navigation_data_and_find_cell_starts()

        return True

    def update(self, player: Player, delta_time: float):
        for j in range(0, len(self.__sorted_collidables)):
            self.__sorted_collidables[j].undraw_bounding_box()

        if player is None:
            return

        player.draw_bounding_box()
        position: Vector2f = player.coordinate
        grid_position: Vector2i = self.__calculate_grid_position(position=position)
        is_player_and_ganon_in_same_grid_position: bool = False
        has_player_collided_with_ganon: bool = False
        has_sword_collided_with_ganon: bool = False

        ganon: Enemy = GlobalConstants.get_constant_or_none(key="ganon")
        if ganon is not None:
            ganon_position: Vector2i = self.__calculate_grid_position(position=ganon.coordinate)
            ganon.draw_bounding_box()
            is_player_and_ganon_in_same_grid_position: bool = grid_position == ganon_position

        for y in range(-1, 2):
            for x in range(-1, 2):
                neighbor_position: Vector2i = grid_position + Vector2i(x=x, y=y)
                grid_hash: int = self.__calculate_grid_hash(grid_position=neighbor_position)
                start_idx: int = self.__cell_starts[grid_hash]
                # print(f"start_idx: {start_idx}")
                if start_idx != -1:
                    end_idx: int = self.__cell_ends[grid_hash]
                    # print(f"start: {start_idx}, end: {end_idx}")
                    for j in range(start_idx, end_idx):
                        self.__sorted_collidables[j].draw_bounding_box()
                        sword_hit: CollidableObject = GlobalConstants.get_constant_or_none(key="sword_hit")
                        if player is not self.__sorted_collidables[j]:
                            if ganon is not None and self.__sorted_collidables[j] is ganon:
                                if player.has_collided_with(other=ganon):
                                    print(f"player collided with ganon")
                                    player.on_collision_with_ganon(ganon=ganon)
                                    ganon.on_collision_with(other=player)
                                    has_player_collided_with_ganon = True
                            else:
                                if player.has_collided_with(other=self.__sorted_collidables[j]):
                                    print(f"player collided with {self.__collidables_to_key[self.__sorted_collidables[j]]}")
                                    player.on_collision_with(other=self.__sorted_collidables[j])
                                    self.__sorted_collidables[j].on_collision_with(other=player)

                        if sword_hit is not None and sword_hit is not self.__sorted_collidables[j]:
                            # print(f"sword: {sword_hit.collision_box} ~ other:{self.__collidables_to_key[self.__sorted_collidables[j]]} {self.__sorted_collidables[j].collision_box}, {sword_hit.has_collided_with(other=self.__sorted_collidables[j])}")
                            if sword_hit.has_collided_with(other=self.__sorted_collidables[j]):
                                # print(f"sword collided with {self.__collidables_to_key[self.__sorted_collidables[j]]}")
                                sword_hit.on_collision_with(other=self.__sorted_collidables[j])
                                if ganon is not None and self.__sorted_collidables[j] is ganon:
                                    ganon.on_collision_with_sword(sword=sword_hit)
                                    has_sword_collided_with_ganon = True
                                else:
                                    self.__sorted_collidables[j].on_collision_with(other=sword_hit)
                                if isinstance(self.__sorted_collidables[j], DestructibleObject):
                                    self.remove_collidable(key=self.__collidables_to_key[self.__sorted_collidables[j]])

                        if is_player_and_ganon_in_same_grid_position:
                            if ganon is not self.__sorted_collidables[j]:
                                if ganon.has_collided_with(other=self.__sorted_collidables[j]):
                                    # print(
                                    #     f"ganon collided with {self.__collidables_to_key[self.__sorted_collidables[j]]}")
                                    ganon.on_collision_with(other=self.__sorted_collidables[j])
                                    self.__sorted_collidables[j].on_collision_with(other=player)

        if ganon is not None:
            if not is_player_and_ganon_in_same_grid_position:
                for y in range(-1, 2):
                    for x in range(-1, 2):
                        neighbor_position: Vector2i = ganon_position + Vector2i(x=x, y=y)
                        grid_hash: int = self.__calculate_grid_hash(grid_position=neighbor_position)
                        start_idx: int = self.__cell_starts[grid_hash]
                        # print(f"start_idx: {start_idx}")
                        if start_idx != -1:
                            end_idx: int = self.__cell_ends[grid_hash]
                            # print(f"start: {start_idx}, end: {end_idx}")
                            for j in range(start_idx, end_idx):
                                self.__sorted_collidables[j].draw_bounding_box()
                                if ganon is not self.__sorted_collidables[j]:
                                    if self.__sorted_collidables[j] is player and has_player_collided_with_ganon:
                                        continue

                                    if self.__sorted_collidables[j] is sword_hit and has_sword_collided_with_ganon:
                                        continue

                                    if ganon.has_collided_with(other=self.__sorted_collidables[j]):
                                        if self.__sorted_collidables[j] is player:
                                            print("ganon collided with player")
                                            ganon.on_collision_with(other=player)
                                            player.on_collision_with_ganon(ganon=ganon)
                                        else:
                                            # print(f"ganon collided with {self.__collidables_to_key[self.__sorted_collidables[j]]}")
                                            ganon.on_collision_with(other=self.__sorted_collidables[j])
                                            self.__sorted_collidables[j].on_collision_with(other=player)
            for y in range(-1, 2):
                for x in range(-1, 2):
                    neighbor_position: Vector2i = ganon_position + Vector2i(x=x, y=y)
                    grid_hash: int = self.__calculate_grid_hash(grid_position=neighbor_position)
                    start_idx: int = self.__navigation_cell_starts[grid_hash]
                    # print(f"start_idx: {start_idx}")
                    if start_idx != -1:
                        end_idx: int = self.__navigation_cell_ends[grid_hash]
                        # print(f"start: {start_idx}, end: {end_idx}")
                        for j in range(start_idx, end_idx):
                            self.__sorted_navigation_boxes[j].draw_bounding_box()

                            if ganon.is_on_navigation_box(other=self.__sorted_navigation_boxes[j]):
                                # print(f"ganon is on nav box {self.__navigation_boxes_to_key[self.__sorted_navigation_boxes[j]]}")
                                ganon.on_navigation_box(other=self.__sorted_navigation_boxes[j])

        # for key in self.__collidables_map:
        #     for other_key in self.__collidables_map:
        #         if key is not other_key:
        #             if self.__collidables_map[key].has_collided_with(other=self.__collidables_map[other_key]):
        #                 self.__collidables_map[key].on_collision_with(other=self.__collidables_map[other_key])
        #                 self.__collidables_map[other_key].on_collision_with(other=self.__collidables_map[key])
        #                 if key == "player":
        #                     print(f"{key} collided with {other_key}")
                        # print(f"\t{self.__collidables[key]._collision_box} ~ {self.__collidables[other_key]._collision_box}")

    def __calculate_grid_hash(self, grid_position: Vector2i) -> int:
        grid_position.x = grid_position.x & (self.__grid_size.x - 1)
        grid_position.y = grid_position.y & (self.__grid_size.y - 1)

        return (grid_position.y * self.__grid_size.x) + grid_position.x

    def __calculate_grid_position(self, position: Vector2f) -> Vector2i:
        grid_position: Vector2i = Vector2i(x=0, y=0)
        # print(f"calc grid pos: pos={position} - cellsize={self.__cell_size}")
        grid_position.x = math.floor(position.x // self.__cell_size.x)
        grid_position.y = math.floor(position.y // self.__cell_size.y)
        return grid_position

    def __calculate_hashes(self):
        for object_idx in range(0, len(self.__collidables)):
            position: Vector2f = self.__collidables[object_idx].coordinate
            grid_position: Vector2i = self.__calculate_grid_position(position=position)
            hash: int = self.__calculate_grid_hash(grid_position=grid_position)

            self.__grid_object_hashes[object_idx] = hash
            self.__grid_object_indices[object_idx] = object_idx

            # print(f"[{object_idx}]: hash={hash}, index={object_idx}")

    def __calculate_navigation_hashes(self):
        for object_idx in range(0, len(self.__navigation_boxes)):
            position: Vector2f = self.__navigation_boxes[object_idx].center
            grid_position: Vector2i = self.__calculate_grid_position(position=position)
            hash: int = self.__calculate_grid_hash(grid_position=grid_position)

            self.__grid_navigation_box_hashes[object_idx] = hash
            self.__grid_navigation_box_indices[object_idx] = object_idx

            # print(f"[{object_idx}]: hash={hash}, index={object_idx}")

    def __reorder_data_and_find_cell_starts(self):
        for i in range(0, self.__num_cells):
            self.__cell_starts[i] = -1

        shared_hash: list[int] = [-1 for i in range(0, len(self.__collidables) + 1)]
        for i in range(0, len(self.__collidables)):
            hash: int = self.__grid_object_hashes[i]
            shared_hash[i + 1] = hash

            # if i == 0:
            #     shared_hash[0] = self.__grid_object_hashes[i - 1]

        for i in range(0, len(self.__collidables)):
            hash: int = self.__grid_object_hashes[i]
            if i == 0 or hash != shared_hash[i]:
                self.__cell_starts[hash] = i

                if i > 0:
                    self.__cell_ends[shared_hash[i]] = i

            if i == len(self.__collidables) - 1:
                self.__cell_ends[hash] = i + 1

            sorted_index: int = self.__grid_object_indices[i]
            object: CollidableObject = self.__collidables[sorted_index]

            self.__sorted_collidables[i] = object
            # print(f"[{i}]: sorted collidable={self.__sorted_collidables[i].coordinate}")

    def __reorder_navigation_data_and_find_cell_starts(self):
        for i in range(0, self.__num_cells):
            self.__navigation_cell_starts[i] = -1

        shared_hash: list[int] = [-1 for i in range(0, len(self.__navigation_boxes) + 1)]
        for i in range(0, len(self.__navigation_boxes)):
            hash: int = self.__grid_navigation_box_hashes[i]
            shared_hash[i + 1] = hash

            # if i == 0:
            #     shared_hash[0] = self.__grid_object_hashes[i - 1]

        for i in range(0, len(self.__navigation_boxes)):
            hash: int = self.__grid_navigation_box_hashes[i]
            if i == 0 or hash != shared_hash[i]:
                self.__navigation_cell_starts[hash] = i

                if i > 0:
                    self.__navigation_cell_ends[shared_hash[i]] = i

            if i == len(self.__navigation_boxes) - 1:
                self.__navigation_cell_ends[hash] = i + 1

            sorted_index: int = self.__grid_navigation_box_indices[i]
            navigation_box: NavigationBox = self.__navigation_boxes[sorted_index]

            self.__sorted_navigation_boxes[i] = navigation_box

    def __sort_objects(self):
        CollisionManager.__quick_sort_by_hash_recursive(hashes=self.__grid_object_hashes,
                                                        indices=self.__grid_object_indices,
                                                        left_idx=0,
                                                        right_idx=len(self.__collidables) - 1)

    def __sort_navigation_objects(self):
        CollisionManager.__quick_sort_by_hash_recursive(hashes=self.__grid_navigation_box_hashes,
                                                        indices=self.__grid_navigation_box_indices,
                                                        left_idx=0,
                                                        right_idx=len(self.__navigation_boxes) - 1)
        # for i in range(0, len(self.__collidables)):
        #     print(f"[{i}]: sorted hash={self.__grid_object_hashes[i]}, index={self.__grid_object_indices[i]}")

    @staticmethod
    def __partition_by_hash(hashes: list[int], indices: list[int], left_idx: int, right_idx: int) -> int:
        i: int = left_idx - 1
        j: int = right_idx + 1

        while 1:
            while 1:
                i += 1
                if not (hashes[i] < hashes[left_idx]):
                    break

            while 1:
                j -= 1
                if not (hashes[j] > hashes[left_idx]):
                    break

            if i >= j:
                return j

            temp_hash: int = hashes[i]
            hashes[i] = hashes[j]
            hashes[j] = temp_hash

            temp_index: int = indices[i]
            indices[i] = indices[j]
            indices[j] = temp_index

    @staticmethod
    def __quick_sort_by_hash_recursive(hashes: list[int], indices: list[int], left_idx: int, right_idx: int) -> None:
        if left_idx >= right_idx:
            return

        pivot_idx: int = CollisionManager.__partition_by_hash(hashes=hashes,
                                                              indices=indices,
                                                              left_idx=left_idx,
                                                              right_idx=right_idx)

        CollisionManager.__quick_sort_by_hash_recursive(hashes=hashes,
                                                        indices=indices,
                                                        left_idx=left_idx,
                                                        right_idx=pivot_idx)
        CollisionManager.__quick_sort_by_hash_recursive(hashes=hashes,
                                                        indices=indices,
                                                        left_idx=pivot_idx + 1,
                                                        right_idx=right_idx)
