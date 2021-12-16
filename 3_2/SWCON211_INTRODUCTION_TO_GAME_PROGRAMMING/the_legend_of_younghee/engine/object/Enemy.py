import random
from enum import Enum
from typing import Union

import pygame

from engine.core.GlobalConstants import GlobalConstants
from engine.core.Math import Vector2f
from engine.core.NavigationBox import NavigationBox
from engine.graphics.Orientation import Orientation
from engine.graphics.Renderable import Renderable
from engine.graphics.Renderer import Depth
from engine.object.BaseObject import eFacingDirection
from engine.object.CollidableObject import CollidableObject
from engine.resources.RenderableStorage import RenderableStorage


class eEnemyState(Enum):
    IDLE = 0
    MOVING = 1
    FOLLOWING_PLAYER = 2
    ATTACKING = 3


class Enemy(CollidableObject):
    __slots__ = ["__name", "__data", "__offset", "__direction_vector", "__facing_direction", "__speed",
                 "__current_state", "__idle_timer", "__follow_player_distance", "__player_to_follow", "__follow_timer",
                 "__follow_timer_threshold", "__move_direction", "__speed", "__move_timer", "__previous_coordinate",
                 "__health", "__damage", "__is_damaged", "__is_hurting", "__hurt_timer", "__hurt_timer_init_value",
                 "__current_navigation_box", "__sound_effects"]

    def __init__(self, coordinate: Vector2f, width: float, height: float, name: str, sprite_data_file: str):
        super().__init__(coordinate, width, height)
        self.__name: str = name
        self.__data: dict[str, dict[str, dict[str, Union[list[dict[str, int]], str, int]]]] = Renderable.parse_data(
            file_path=f"resources/sprites/{sprite_data_file}.dat")
        self.__offset: dict[str, Vector2f] = dict()
        self.__direction_vector: Vector2f = Vector2f(x=0.0,
                                                     y=0.0)
        self.__facing_direction: eFacingDirection = eFacingDirection.SOUTH
        self.__speed: float = 1.8

        self.__current_state: eEnemyState = eEnemyState.IDLE
        self.__idle_timer: int = -1
        self.__move_timer: int = -1
        self.__follow_player_distance: float = 100.0
        self.__speed: float = 2.0

        self.__player_to_follow: Player = None
        self.__follow_timer: int = -1
        self.__follow_timer_threshold: int = 1000

        self.__previous_coordinate: Vector2f = Vector2f(x=self._coordinates.x, y=self._coordinates.y)

        self.__is_damaged: bool = False
        self.__is_hurting: bool = False
        self.__hurt_timer: int = 0
        self.__hurt_timer_init_value: int = 333
        self.__health: float = 100.0
        self.__damage: float = 25.0

        self.__current_navigation_box: NavigationBox = None

        self.__sound_effects: dict[str, pygame.mixer.Sound] = dict()

    @property
    def current_state(self) -> eEnemyState:
        return self.__current_state

    @property
    def facing_direction(self) -> eFacingDirection:
        return self.__facing_direction

    @property
    def health(self) -> float:
        return self.__health

    @property
    def name(self) -> str:
        return self.__name

    @health.setter
    def health(self, health: float) -> None:
        self.__health = health

    def initialize(self):
        super(Enemy, self).initialize()

        surfaces: [str, list[list[pygame.Surface, Vector2f]]] = dict()
        coordinates: [str, list[list[Vector2f]]] = dict()
        for data_key in self.__data:
            print(f"key: {data_key}")
            for data_name in self.__data[data_key]:
                print(f"data_name: {data_name}")
                self.__offset[data_name] = Vector2f(x=0.0, y=0.0)
                if data_name not in surfaces and data_name not in coordinates:
                    surfaces[data_name] = []
                    coordinates[data_name] = []
                for attribute_key in self.__data[data_key][data_name]:
                    if attribute_key == "src_image":
                        if not RenderableStorage.contains_surface(key=self.__data[data_key][data_name][attribute_key]):
                            RenderableStorage.add_surface(
                                key=self.__data[data_key][data_name][attribute_key],
                                surface=pygame.image.load(f'resources/sprites/{self.__data[data_key][data_name][attribute_key]}').convert_alpha()
                            )
                    elif attribute_key == "directions":
                        for direction in range(0, len(self.__data[data_key][data_name][attribute_key])):
                            count: int = 1
                            if "num_frames" in self.__data[data_key][data_name][attribute_key][direction]:
                                count = self.__data[data_key][data_name][attribute_key][direction][
                                    "num_frames"]

                            surfaces[data_name].append([])
                            coordinates[data_name].append([])
                            if "num_columns" in self.__data[data_key][data_name][attribute_key][direction]:
                                num_columns: int = self.__data[data_key][data_name][attribute_key][direction][
                                    "num_columns"]
                            else:
                                num_columns: int = -1
                            for frame_index in range(0, count):
                                rect: pygame.Rect = pygame.Rect(
                                    float(self.__data[data_key][data_name][attribute_key][direction]["x"] + (
                                        frame_index % num_columns if num_columns != -1 else frame_index) *
                                          self.__data[data_key][data_name][attribute_key][direction][
                                              "frame_width"]),
                                    float(self.__data[data_key][data_name][attribute_key][direction][
                                              "y"] + (
                                              frame_index // num_columns if num_columns != -1 else 0) *
                                          self.__data[data_key][data_name][attribute_key][direction][
                                              "frame_height"]),
                                    float(self.__data[data_key][data_name][attribute_key][direction][
                                              "frame_width"]),
                                    float(self.__data[data_key][data_name][attribute_key][direction][
                                              "frame_height"])
                                )

                                surfaces[data_name][direction].append(RenderableStorage.get_surface_or_none(
                                    key=self.__data[data_key][data_name]["src_image"]).subsurface(rect))

                                if "origin_x" in self.__data[data_key][data_name][attribute_key][direction]:
                                    coordinates[data_name][direction].append(
                                        Vector2f(x=float(
                                            self.__data[data_key][data_name][attribute_key][direction][
                                                "origin_x"] -
                                            self.__data[data_key][data_name][attribute_key][direction][
                                                "frame_width"] / 2
                                        ),
                                            y=float(
                                                self.__data[data_key][data_name][attribute_key][direction][
                                                    "origin_y"] -
                                                self.__data[data_key][data_name][attribute_key][direction][
                                                    "frame_height"] / 2))
                                    )
                                else:
                                    coordinates[data_name][direction].append(Vector2f(x=0.0, y=0.0))

        for surfaces_key in surfaces:
            if len(surfaces[surfaces_key]) == 4:
                if len(surfaces[surfaces_key][0]) > 1:
                    self._renderable_names.add(f"{self.__name}_{surfaces_key}_east")
                    RenderableStorage.add_renderable(renderable=Renderable(surface=surfaces[surfaces_key][0][0],
                                                                           coordinate=Vector2f(x=0.0, y=0.0),
                                                                           depth=Depth.NORMAL0_DEPTH,
                                                                           name=f"{self.__name}_{surfaces_key}_east",
                                                                           surfaces=surfaces[surfaces_key][0],
                                                                           coordinates=coordinates[surfaces_key][0],
                                                                           orientation=Orientation.CENTER))
                    RenderableStorage.get_renderable_or_none(
                        key=f"{self.__name}_{surfaces_key}_east").set_animation_data(
                        from_frame_index=0,
                        to_frame_index=len(surfaces[surfaces_key][0]) - 1,
                        duration=self.__data["animation"][surfaces_key]["frame_delay"] * 3,
                        should_loop=False
                    )
                    self._renderable_names.add(f"{self.__name}_{surfaces_key}_north")
                    RenderableStorage.add_renderable(renderable=Renderable(surface=surfaces[surfaces_key][1][0],
                                                                           coordinate=Vector2f(x=0.0, y=0.0),
                                                                           depth=Depth.NORMAL0_DEPTH,
                                                                           name=f"{self.__name}_{surfaces_key}_north",
                                                                           surfaces=surfaces[surfaces_key][1],
                                                                           coordinates=coordinates[surfaces_key][1]))
                    RenderableStorage.get_renderable_or_none(
                        key=f"{self.__name}_{surfaces_key}_north").set_animation_data(
                        from_frame_index=0,
                        to_frame_index=len(surfaces[surfaces_key][1]) - 1,
                        duration=self.__data["animation"][surfaces_key]["frame_delay"] * 3,
                        should_loop=False
                    )
                    self._renderable_names.add(f"{self.__name}_{surfaces_key}_west")
                    RenderableStorage.add_renderable(renderable=Renderable(surface=surfaces[surfaces_key][2][0],
                                                                           coordinate=Vector2f(x=0.0, y=0.0),
                                                                           depth=Depth.NORMAL0_DEPTH,
                                                                           name=f"{self.__name}_{surfaces_key}_west",
                                                                           surfaces=surfaces[surfaces_key][2],
                                                                           coordinates=coordinates[surfaces_key][2]))
                    RenderableStorage.get_renderable_or_none(
                        key=f"{self.__name}_{surfaces_key}_west").set_animation_data(
                        from_frame_index=0,
                        to_frame_index=len(surfaces[surfaces_key][2]) - 1,
                        duration=self.__data["animation"][surfaces_key]["frame_delay"] * 3,
                        should_loop=False
                    )
                    self._renderable_names.add(f"{self.__name}_{surfaces_key}_south")
                    RenderableStorage.add_renderable(renderable=Renderable(surface=surfaces[surfaces_key][3][0],
                                                                           coordinate=Vector2f(x=0.0, y=0.0),
                                                                           depth=Depth.NORMAL0_DEPTH,
                                                                           name=f"{self.__name}_{surfaces_key}_south",
                                                                           surfaces=surfaces[surfaces_key][3],
                                                                           coordinates=coordinates[surfaces_key][3]))
                    RenderableStorage.get_renderable_or_none(
                        key=f"{self.__name}_{surfaces_key}_south").set_animation_data(
                        from_frame_index=0,
                        to_frame_index=len(surfaces[surfaces_key][3]) - 1,
                        duration=self.__data["animation"][surfaces_key]["frame_delay"] * 3,
                        should_loop=False
                    )
                else:
                    self._renderable_names.add(f"{self.__name}_{surfaces_key}_east")
                    RenderableStorage.add_renderable(
                        renderable=Renderable(surface=surfaces[surfaces_key][0][0],
                                              coordinate=Vector2f(x=0.0, y=0.0),
                                              depth=Depth.NORMAL0_DEPTH,
                                              name=f"{self.__name}_{surfaces_key}_east"))
                    self._renderable_names.add(f"{self.__name}_{surfaces_key}_north")
                    RenderableStorage.add_renderable(renderable=Renderable(surface=surfaces[surfaces_key][1][0],
                                                                           coordinate=Vector2f(x=0.0, y=0.0),
                                                                           depth=Depth.NORMAL0_DEPTH,
                                                                           name=f"{self.__name}_{surfaces_key}_north"))
                    self._renderable_names.add(f"{self.__name}_{surfaces_key}_west")
                    RenderableStorage.add_renderable(renderable=Renderable(surface=surfaces[surfaces_key][2][0],
                                                                           coordinate=Vector2f(x=0.0, y=0.0),
                                                                           depth=Depth.NORMAL0_DEPTH,
                                                                           name=f"{self.__name}_{surfaces_key}_west"))
                    self._renderable_names.add(f"{self.__name}_{surfaces_key}_south")
                    RenderableStorage.add_renderable(renderable=Renderable(surface=surfaces[surfaces_key][3][0],
                                                                           coordinate=Vector2f(x=0.0, y=0.0),
                                                                           depth=Depth.NORMAL0_DEPTH,
                                                                           name=f"{self.__name}_{surfaces_key}_south"))
            else:
                if len(surfaces[surfaces_key][0]) > 1:
                    self._renderable_names.add(f"{self.__name}_{surfaces_key}")
                    RenderableStorage.add_renderable(renderable=Renderable(surface=surfaces[surfaces_key][0][0],
                                                                           coordinate=Vector2f(x=0.0, y=0.0),
                                                                           depth=Depth.NORMAL0_DEPTH,
                                                                           name=f"{self.__name}_{surfaces_key}",
                                                                           surfaces=surfaces[surfaces_key][0],
                                                                           coordinates=coordinates[surfaces_key][0]))
                    RenderableStorage.get_renderable_or_none(
                        key=f"{self.__name}_{surfaces_key}").set_animation_data(
                        from_frame_index=0,
                        to_frame_index=len(surfaces[surfaces_key][0]) - 1,
                        duration=self.__data["animation"][surfaces_key]["frame_delay"] * 3,
                        should_loop=False
                    )
                else:
                    self._renderable_names.add(f"{self.__name}_{surfaces_key}")
                    RenderableStorage.add_renderable(
                        renderable=Renderable(surface=surfaces[surfaces_key][0][0],
                                              coordinate=Vector2f(x=0.0, y=0.0),
                                              depth=Depth.NORMAL0_DEPTH,
                                              name=f"{self.__name}_{surfaces_key}"))

        self.__sound_effects["boss_hurt"] = pygame.mixer.Sound("resources/sounds/boss_hurt.ogg")
        self.__sound_effects["boss_hurt"].set_volume(0.5)
        self.__sound_effects["boss_killed"] = pygame.mixer.Sound("resources/sounds/boss_killed.ogg")
        self.__sound_effects["boss_killed"].set_volume(0.5)

    def destroy(self):
        super(Enemy, self).destroy()

    def is_on_navigation_box(self, other: NavigationBox):
        assert isinstance(other, NavigationBox)

        return self._collision_box.has_collided_with(box=other)

    def on_collision_with(self, other: CollidableObject):
        if self._coordinates != self.__previous_coordinate:
            self._coordinates.copy(other=self.__previous_coordinate)
        if self.__current_state.MOVING or self.__current_state.FOLLOWING_PLAYER:
            random_direction: eFacingDirection = self.__facing_direction
            while random_direction == self.__facing_direction:
                random_direction: eFacingDirection = eFacingDirection(random.randint(0, 3))
            self.set_direction(direction=random_direction)

    def on_navigation_box(self, other: NavigationBox):
        self.__current_navigation_box = other

    def on_collision_with_sword(self, sword: CollidableObject):
        # print(f"coordinate: {self._coordinates}")
        if self._coordinates != self.__previous_coordinate:
            self._coordinates.copy(other=self.__previous_coordinate)
        # if len(self.__movement_input_stack) > 0:
        #     self._coordinates.x -= self.__direction.x * self.__speed
        #     self._coordinates.y -= self.__direction.y * self.__speed
        if not self.__is_hurting:
            self.__is_hurting = True
            self.__is_damaged = True
            self.__health -= self.__damage
            self.__hurt_timer = self.__hurt_timer_init_value

            if self.__health <= 0.0:
                self.__sound_effects["boss_killed"].play()
                # self.destroy()
            else:
                self.__sound_effects["boss_hurt"].play()

    def reverse_direction(self) -> None:
        if self.__facing_direction == eFacingDirection.SOUTH:
            self.set_direction(direction=eFacingDirection.NORTH)
        elif self.__facing_direction == eFacingDirection.WEST:
            self.set_direction(direction=eFacingDirection.EAST)
        elif self.__facing_direction == eFacingDirection.NORTH:
            self.set_direction(direction=eFacingDirection.SOUTH)
        elif self.__facing_direction == eFacingDirection.EAST:
            self.set_direction(direction=eFacingDirection.WEST)

    def set_direction(self, direction: eFacingDirection) -> None:
        # print(f"direct set to {direction}")
        if direction == eFacingDirection.SOUTH:
            self.__facing_direction = direction
            self.__direction_vector.x = 0.0
            self.__direction_vector.y = 1.0
        elif direction == eFacingDirection.EAST:
            self.__facing_direction = direction
            self.__direction_vector.x = 1.0
            self.__direction_vector.y = 0.0
        elif direction == eFacingDirection.NORTH:
            self.__facing_direction = direction
            self.__direction_vector.x = 0.0
            self.__direction_vector.y = -1.0
        elif direction == eFacingDirection.WEST:
            self.__facing_direction = direction
            self.__direction_vector.x = -1.0
            self.__direction_vector.y = 0.0

    def update(self, delta_time: float):
        super(Enemy, self).update(delta_time=delta_time)
        # print(f"current state: {self.__current_state}")
        if self.__health <= 0.0:
            return

        if self.__player_to_follow is None:
            self.__player_to_follow = GlobalConstants.get_constant_or_none(key="player")

        if self.__is_hurting:
            self.__hurt_timer -= int(delta_time)
            if self.__hurt_timer <= 0:
                self.__is_hurting = False

        if self.__current_state == eEnemyState.FOLLOWING_PLAYER:
            self.__follow_timer += int(delta_time)
            if self.__follow_timer >= self.__follow_timer_threshold:
                self.__follow_timer = -1
                self.__current_state = eEnemyState.IDLE
                # print(f"state is IDLE")
        elif self.__current_state != eEnemyState.ATTACKING:
            if self.__current_state == eEnemyState.IDLE and self.__idle_timer <= 0:
                self.__current_state = eEnemyState.MOVING
                # print(f"state is MOVING")

                self.__move_timer = random.randint(1000, 5000)
                self.set_direction(direction=eFacingDirection(random.randint(0, 3)))
            elif self.__current_state == eEnemyState.MOVING and self.__move_timer <= 0:
                self.__current_state = eEnemyState(random.randint(0, 1))

                if self.__current_state == eEnemyState.IDLE:
                    # print(f"state is IDLE")
                    self.__idle_timer = random.randint(1000, 3000)
                else:
                    # print(f"state is MOVING")
                    self.__move_timer = random.randint(1000, 3000)
                    self.set_direction(direction=eFacingDirection(random.randint(0, 3)))

        if self.__player_to_follow.coordinate.get_distance_from(
                other=self._coordinates) <= self.__follow_player_distance:
            self.__current_state = eEnemyState.FOLLOWING_PLAYER
            # print(f"state is FOLLOWING")
            self.__follow_timer = 0

        if self.__current_state == eEnemyState.IDLE:
            self.__idle_timer -= int(delta_time)
        elif self.__current_state == eEnemyState.MOVING:
            self.__move_timer -= int(delta_time)
        elif self.__current_state == eEnemyState.FOLLOWING_PLAYER:
            follow_direction: Vector2f = self.__player_to_follow.coordinate - self._coordinates

            if follow_direction.x > follow_direction.y:
                if -follow_direction.x > follow_direction.y:
                    self.set_direction(direction=eFacingDirection.NORTH)
                else:
                    self.set_direction(direction=eFacingDirection.EAST)
            else:
                if -follow_direction.x > follow_direction.y:
                    self.set_direction(direction=eFacingDirection.WEST)
                else:
                    self.set_direction(direction=eFacingDirection.SOUTH)

        if self.__is_hurting:
            self.__previous_coordinate.copy(other=self._coordinates)
            self._coordinates.x += -self.__direction_vector.x * 7.0 * (
                    self.__hurt_timer / self.__hurt_timer_init_value)
            self._coordinates.y += -self.__direction_vector.y * 7.0 * (
                    self.__hurt_timer / self.__hurt_timer_init_value)
        elif self.__direction_vector.x != 0.0 or self.__direction_vector.y != 0.0:
            self.__previous_coordinate.copy(other=self._coordinates)
            self._coordinates += self.__direction_vector * self.__speed
            # print(f"coord={self._coordinates}, prev={self.__previous_coordinate}")
            # print(f"coord={self._coordinates}, direction={self.__direction_vector}, speed={self.__speed}")

        if self._coordinates.x < 0.0:
            self._coordinates.x = 0.0
            self.reverse_direction()
            # print(f"leftmost")

        if self._coordinates.x >= GlobalConstants.get_constant_or_none(key="map_width"):
            self._coordinates.x = GlobalConstants.get_constant_or_none(key="map_width")
            self.reverse_direction()
            # print(f"rightmost")

        if self._coordinates.y < 0.0:
            self._coordinates.y = 0.0
            self.reverse_direction()
            # print(f"topmost")

        if self._coordinates.y >= GlobalConstants.get_constant_or_none(key="map_height"):
            self._coordinates.y = GlobalConstants.get_constant_or_none(key="map_height")
            self.reverse_direction()
            # print(f"bottommost")

        self.update_animation()

        # if self.di
        if self.__is_hurting:
            RenderableStorage.get_renderable_or_none(
                key=self._current_renderable_name
            ).coordinate = self._coordinates + self.__offset["hurt"] + Vector2f(x=self.collision_box.width / 2.0,
                                                                                y=self.collision_box.height)
        else:
            RenderableStorage.get_renderable_or_none(
                key=self._current_renderable_name
            ).coordinate = self._coordinates + self.__offset["walking"] + Vector2f(x=self.collision_box.width / 2.0,
                                                                                y=self.collision_box.height)
        # GlobalConstants.get_constant_or_none(key="renderer").player_offset = self._coordinates

    def update_animation(self):
        if self.__facing_direction == eFacingDirection.SOUTH:
            if self.__is_hurting:
                RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                self._current_renderable_name = f"{self.__name}_hurt_south"
                assert RenderableStorage.push_to_renderer(key=self._current_renderable_name)
                RenderableStorage.get_renderable_or_none(key=self._current_renderable_name).start_animation()

                self.__offset["hurt"].x = - \
                    self.__data["animation"]["hurt"]["directions"][self.__facing_direction.value]["origin_x"]
                self.__offset["hurt"].y = - \
                    self.__data["animation"]["hurt"]["directions"][self.__facing_direction.value]["origin_y"]
                # self._coordinates += self.__offset["walking"]
            elif self._current_renderable_name is None or  \
                RenderableStorage.get_renderable_or_none(key=self._current_renderable_name) is not \
                RenderableStorage.get_renderable_or_none(key=f"{self.__name}_walking_south"):
                if self._current_renderable_name is not None:
                    RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                self._current_renderable_name = f"{self.__name}_walking_south"
                assert RenderableStorage.push_to_renderer(key=self._current_renderable_name)

                self.__offset[f"walking"].x = - \
                self.__data["animation"]["walking"]["directions"][self.__facing_direction.value]["origin_x"]
                self.__offset[f"walking"].y = - \
                self.__data["animation"]["walking"]["directions"][self.__facing_direction.value]["origin_y"]
                # self._coordinates += self.__offset["walking"]

                if self.__current_state == eEnemyState.MOVING or self.__current_state == eEnemyState.FOLLOWING_PLAYER:
                    RenderableStorage.get_renderable_or_none(
                        key=self._current_renderable_name
                    ).start_animation(should_loop=True)
        elif self.__facing_direction == eFacingDirection.NORTH:
            if self.__is_hurting:
                RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                self._current_renderable_name = f"{self.__name}_hurt_north"
                assert RenderableStorage.push_to_renderer(key=self._current_renderable_name)
                RenderableStorage.get_renderable_or_none(key=self._current_renderable_name).start_animation()

                self.__offset["hurt"].x = - \
                    self.__data["animation"]["hurt"]["directions"][self.__facing_direction.value]["origin_x"]
                self.__offset["hurt"].y = - \
                    self.__data["animation"]["hurt"]["directions"][self.__facing_direction.value]["origin_y"]
            elif RenderableStorage.get_renderable_or_none(key=self._current_renderable_name) is not \
                RenderableStorage.get_renderable_or_none(key=f"{self.__name}_walking_north"):
                RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                self._current_renderable_name = f"{self.__name}_walking_north"
                assert RenderableStorage.push_to_renderer(key=self._current_renderable_name)

                self.__offset[f"walking"].x = - \
                self.__data["animation"]["walking"]["directions"][self.__facing_direction.value][
                    "origin_x"]
                self.__offset[f"walking"].y = - \
                self.__data["animation"]["walking"]["directions"][self.__facing_direction.value][
                    "origin_y"]
                # self._coordinates += self.__offset["walking"]

                if self.__current_state == eEnemyState.MOVING or self.__current_state == eEnemyState.FOLLOWING_PLAYER:
                    RenderableStorage.get_renderable_or_none(
                        key=self._current_renderable_name
                    ).start_animation(should_loop=True)
        elif self.__facing_direction == eFacingDirection.EAST:
            if self.__is_hurting:
                RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                self._current_renderable_name = f"{self.__name}_hurt_east"
                assert RenderableStorage.push_to_renderer(key=self._current_renderable_name)
                RenderableStorage.get_renderable_or_none(key=self._current_renderable_name).start_animation()

                self.__offset["hurt"].x = - \
                    self.__data["animation"]["hurt"]["directions"][self.__facing_direction.value]["origin_x"]
                self.__offset["hurt"].y = - \
                    self.__data["animation"]["hurt"]["directions"][self.__facing_direction.value]["origin_y"]
            elif RenderableStorage.get_renderable_or_none(key=self._current_renderable_name) is not \
                RenderableStorage.get_renderable_or_none(key=f"{self.__name}_walking_east"):
                RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                self._current_renderable_name = f"{self.__name}_walking_east"
                assert RenderableStorage.push_to_renderer(key=self._current_renderable_name)

                self.__offset[f"walking"].x = - \
                self.__data["animation"]["walking"]["directions"][self.__facing_direction.value][
                    "origin_x"]
                self.__offset[f"walking"].y = - \
                self.__data["animation"]["walking"]["directions"][self.__facing_direction.value][
                    "origin_y"]
                # self._coordinates += self.__offset["walking"]

                if self.__current_state == eEnemyState.MOVING or self.__current_state == eEnemyState.FOLLOWING_PLAYER:
                    RenderableStorage.get_renderable_or_none(
                        key=self._current_renderable_name
                    ).start_animation(should_loop=True)
        elif self.__facing_direction == eFacingDirection.WEST:
            if self.__is_hurting:
                RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                self._current_renderable_name = f"{self.__name}_hurt_west"
                assert RenderableStorage.push_to_renderer(key=self._current_renderable_name)
                RenderableStorage.get_renderable_or_none(key=self._current_renderable_name).start_animation()

                self.__offset["hurt"].x = - \
                    self.__data["animation"]["hurt"]["directions"][self.__facing_direction.value]["origin_x"]
                self.__offset["hurt"].y = - \
                    self.__data["animation"]["hurt"]["directions"][self.__facing_direction.value]["origin_y"]
            elif RenderableStorage.get_renderable_or_none(key=self._current_renderable_name) is not \
                RenderableStorage.get_renderable_or_none(key=f"{self.__name}_walking_west"):
                RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                self._current_renderable_name = f"{self.__name}_walking_west"
                assert RenderableStorage.push_to_renderer(key=self._current_renderable_name)

                self.__offset[f"walking"].x = - \
                self.__data["animation"]["walking"]["directions"][self.__facing_direction.value][
                    "origin_x"]
                self.__offset[f"walking"].y = - \
                self.__data["animation"]["walking"]["directions"][self.__facing_direction.value][
                    "origin_y"]
                # self._coordinates += self.__offset["walking"]

                if self.__current_state == eEnemyState.MOVING or self.__current_state == eEnemyState.FOLLOWING_PLAYER:
                    RenderableStorage.get_renderable_or_none(
                        key=self._current_renderable_name
                    ).start_animation()
