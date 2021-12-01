from enum import Enum
from typing import Union

import pygame.surface

from engine.components.Component import RenderableComponent
from engine.core.Math import Vector2f
from engine.graphics.Orientation import Orientation
from engine.graphics.Renderable import Renderable
from engine.graphics.Renderer import Depth, Renderer
from engine.object.BaseObject import BaseObject
from engine.object.CollidableObject import CollidableObject


class eFacingDirection(Enum):
    EAST = 0
    NORTH = 1
    WEST = 2
    SOUTH = 3


class Player(CollidableObject):
    __slots__ = ["__name", "__resources", "__speed", "__direction", "__input", "__movement_input_stack", "__renderer",
                 "__data", "__last_movement_input", "__offset", "__has_shield", "__is_attacking_with_sword",
                 "__is_loading_sword",
                 "__sound_effects", "__is_lifting", "__facing_direction", "__has_collided"]

    def __init__(self, name: str, coordinate: Vector2f, renderer: Renderer):
        super().__init__(coordinate=coordinate, width=24, height=24)
        self.__name: str = name
        self.__renderer: Renderer = renderer

        self.__resources: dict[str, pygame.Surface] = dict()
        self.__speed: float = 2.4
        self.__direction: Vector2f = Vector2f(x=0.0, y=0.0)
        self.__facing_direction: eFacingDirection = eFacingDirection.SOUTH
        self.__input: dict[int, bool] = dict()

        self.__input[pygame.K_UP] = False
        self.__input[pygame.K_DOWN] = False
        self.__input[pygame.K_LEFT] = False
        self.__input[pygame.K_RIGHT] = False

        self.__movement_input_stack: list[int] = []
        self.__last_movement_input: int = pygame.K_DOWN

        self.__offset: dict[str, Vector2f] = dict()

        self.__data: dict[str, dict[str, dict[str, dict[str, Union[list[dict[str, int]], str, int]]]]] = dict()

        self.__sound_effects: dict[str, pygame.mixer.Sound] = dict()

        # state
        self.__has_shield: bool = False
        self.__is_attacking_with_sword: bool = False
        self.__is_loading_sword: bool = False
        self.__is_lifting: bool = False

        self.__has_collided: bool = False

    def initialize(self):
        super().initialize()

        pre_load_data: list[str] = ["shield", "sword_stars", "sword", "trail", "tunic"]
        self.__data["shield"] = Renderable.parse_data(
            file_path="resources/sprites/hero/shield2.dat")
        self.__data["sword_stars"] = Renderable.parse_data(
            file_path="resources/sprites/hero/sword_stars2.dat")
        self.__data["sword"] = Renderable.parse_data(
            file_path="resources/sprites/hero/sword2.dat")
        self.__data["trail"] = Renderable.parse_data(
            file_path="resources/sprites/hero/trail.dat")
        self.__data["tunic"] = Renderable.parse_data(
            file_path="resources/sprites/hero/tunic2.dat")

        depths: dict[str, int] = {"shield": Depth.NORMAL1_DEPTH,
                                  "sword_stars": Depth.VFX_DEPTH,
                                  "sword": Depth.NORMAL1_DEPTH,
                                  "trail": Depth.MAP_DEPTH,
                                  "tunic": Depth.NORMAL0_DEPTH}
        should_loops: dict[str, bool] = {"shield": False,
                                         "sword_stars": False,
                                         "sword": False,
                                         "trail": False,
                                         "tunic": True}
        surfaces: dict[str, [str, list[list[pygame.Surface, Vector2f]]]] = dict()
        coordinates: dict[str, [str, list[list[Vector2f]]]] = dict()
        renderable_components: dict[str, RenderableComponent] = dict()
        for data in pre_load_data:
            surfaces[data] = dict()
            coordinates[data] = dict()
            renderable_components[data] = RenderableComponent(name=data, renderer=self.__renderer)
            self.__offset[data] = Vector2f(x=0.0, y=0.0)
            for data_key in self.__data[data]:
                for data_name in self.__data[data][data_key]:
                    if data_name not in surfaces[data] and data_name not in coordinates[data]:
                        surfaces[data][data_name] = []
                        coordinates[data][data_name] = []
                    for attribute_key in self.__data[data][data_key][data_name]:
                        if attribute_key == "src_image":
                            if self.__data[data][data_key][data_name][attribute_key] not in self.__resources:
                                self.__resources[
                                    self.__data[data][data_key][data_name][attribute_key]] = pygame.image.load(
                                    f'resources/sprites/{self.__data[data][data_key][data_name][attribute_key]}').convert_alpha()
                        elif attribute_key == "directions":
                            for direction in range(0, len(self.__data[data][data_key][data_name][attribute_key])):
                                count: int = 1
                                if "num_frames" in self.__data[data][data_key][data_name][attribute_key][direction]:
                                    count = self.__data[data][data_key][data_name][attribute_key][direction][
                                        "num_frames"]

                                surfaces[data][data_name].append([])
                                coordinates[data][data_name].append([])
                                if "num_columns" in self.__data[data][data_key][data_name][attribute_key][direction]:
                                    num_columns: int = self.__data[data][data_key][data_name][attribute_key][direction][
                                        "num_columns"]
                                else:
                                    num_columns: int = -1
                                for frame_index in range(0, count):
                                    rect: pygame.Rect = pygame.Rect(
                                        float(self.__data[data][data_key][data_name][attribute_key][direction]["x"] + (
                                            frame_index % num_columns if num_columns != -1 else frame_index) *
                                              self.__data[data][data_key][data_name][attribute_key][direction][
                                                  "frame_width"]),
                                        float(self.__data[data][data_key][data_name][attribute_key][direction][
                                                  "y"] + (
                                                  frame_index // num_columns if num_columns != -1 else 0) *
                                              self.__data[data][data_key][data_name][attribute_key][direction][
                                                  "frame_height"]),
                                        float(self.__data[data][data_key][data_name][attribute_key][direction][
                                                  "frame_width"]),
                                        float(self.__data[data][data_key][data_name][attribute_key][direction][
                                                  "frame_height"])
                                    )

                                    surfaces[data][data_name][direction].append(
                                        self.__resources[
                                            self.__data[data][data_key][data_name]["src_image"]].subsurface(rect))

                                    if "origin_x" in self.__data[data][data_key][data_name][attribute_key][direction]:
                                        coordinates[data][data_name][direction].append(
                                            Vector2f(x=float(
                                                self.__data[data][data_key][data_name][attribute_key][direction][
                                                    "origin_x"] -
                                                self.__data[data][data_key][data_name][attribute_key][direction][
                                                    "frame_width"] / 2
                                            ),
                                                y=float(
                                                    self.__data[data][data_key][data_name][attribute_key][direction][
                                                        "origin_y"] -
                                                    self.__data[data][data_key][data_name][attribute_key][direction][
                                                        "frame_height"] / 2))
                                        )
                                    else:
                                        coordinates[data][data_name][direction].append(Vector2f(x=0.0, y=0.0))

            for surfaces_key in surfaces[data]:
                if len(surfaces[data][surfaces_key]) == 4:
                    if len(surfaces[data][surfaces_key][0]) > 1:
                        renderable_components[data].add_renderable(
                            renderable=Renderable(surface=surfaces[data][surfaces_key][0][0],
                                                  coordinate=Vector2f(x=0.0, y=0.0),
                                                  depth=depths[data],
                                                  name=f"{data}_{surfaces_key}_east",
                                                  surfaces=surfaces[data][surfaces_key][0],
                                                  coordinates=coordinates[data][surfaces_key][0],
                                                  orientation=Orientation.CENTER))
                        renderable_components[data].get_renderable_by_name(
                            name=f"{data}_{surfaces_key}_east").set_animation_data(
                            from_frame_index=0,
                            to_frame_index=len(surfaces[data][surfaces_key][0]) - 1,
                            duration=self.__data[data]["animation"][surfaces_key]["frame_delay"] * 3,
                            should_loop=False if data == "tunic" and surfaces_key == "sword" else should_loops[data]
                        )
                        renderable_components[data].add_renderable(
                            renderable=Renderable(surface=surfaces[data][surfaces_key][1][0],
                                                  coordinate=Vector2f(x=0.0, y=0.0),
                                                  depth=depths[data],
                                                  name=f"{data}_{surfaces_key}_north",
                                                  surfaces=surfaces[data][surfaces_key][1],
                                                  coordinates=coordinates[data][surfaces_key][1]))
                        renderable_components[data].get_renderable_by_name(
                            name=f"{data}_{surfaces_key}_north").set_animation_data(
                            from_frame_index=0,
                            to_frame_index=len(surfaces[data][surfaces_key][1]) - 1,
                            duration=self.__data[data]["animation"][surfaces_key]["frame_delay"] * 3,
                            should_loop=False if data == "tunic" and surfaces_key == "sword" else should_loops[data]
                        )
                        renderable_components[data].add_renderable(
                            renderable=Renderable(surface=surfaces[data][surfaces_key][2][0],
                                                  coordinate=Vector2f(x=0.0, y=0.0),
                                                  depth=depths[data],
                                                  name=f"{data}_{surfaces_key}_west",
                                                  surfaces=surfaces[data][surfaces_key][2],
                                                  coordinates=coordinates[data][surfaces_key][2]))
                        renderable_components[data].get_renderable_by_name(
                            name=f"{data}_{surfaces_key}_west").set_animation_data(
                            from_frame_index=0,
                            to_frame_index=len(surfaces[data][surfaces_key][2]) - 1,
                            duration=self.__data[data]["animation"][surfaces_key]["frame_delay"] * 3,
                            should_loop=False if data == "tunic" and surfaces_key == "sword" else should_loops[data]
                        )
                        renderable_components[data].add_renderable(
                            renderable=Renderable(surface=surfaces[data][surfaces_key][3][0],
                                                  coordinate=Vector2f(x=0.0, y=0.0),
                                                  depth=depths[data],
                                                  name=f"{data}_{surfaces_key}_south",
                                                  surfaces=surfaces[data][surfaces_key][3],
                                                  coordinates=coordinates[data][surfaces_key][3]))
                        renderable_components[data].get_renderable_by_name(
                            name=f"{data}_{surfaces_key}_south").set_animation_data(
                            from_frame_index=0,
                            to_frame_index=len(surfaces[data][surfaces_key][3]) - 1,
                            duration=self.__data[data]["animation"][surfaces_key]["frame_delay"] * 3,
                            should_loop=False if data == "tunic" and surfaces_key == "sword" else should_loops[data]
                        )
                    else:
                        renderable_components[data].add_renderable(
                            renderable=Renderable(surface=surfaces[data][surfaces_key][0][0],
                                                  coordinate=Vector2f(x=0.0, y=0.0),
                                                  depth=depths[data],
                                                  name=f"{data}_{surfaces_key}_east"))
                        renderable_components[data].add_renderable(
                            renderable=Renderable(surface=surfaces[data][surfaces_key][1][0],
                                                  coordinate=Vector2f(x=0.0, y=0.0),
                                                  depth=depths[data],
                                                  name=f"{data}_{surfaces_key}_north"))
                        renderable_components[data].add_renderable(
                            renderable=Renderable(surface=surfaces[data][surfaces_key][2][0],
                                                  coordinate=Vector2f(x=0.0, y=0.0),
                                                  depth=depths[data],
                                                  name=f"{data}_{surfaces_key}_west"))
                        renderable_components[data].add_renderable(
                            renderable=Renderable(surface=surfaces[data][surfaces_key][3][0],
                                                  coordinate=Vector2f(x=0.0, y=0.0),
                                                  depth=depths[data],
                                                  name=f"{data}_{surfaces_key}_south"))
                else:
                    if len(surfaces[data][surfaces_key][0]) > 1:
                        renderable_components[data].add_renderable(
                            renderable=Renderable(surface=surfaces[data][surfaces_key][0][0],
                                                  coordinate=Vector2f(x=0.0, y=0.0),
                                                  depth=depths[data],
                                                  name=f"{data}_{surfaces_key}",
                                                  surfaces=surfaces[data][surfaces_key][0],
                                                  coordinates=coordinates[data][surfaces_key][0]))
                        renderable_components[data].get_renderable_by_name(
                            name=f"{data}_{surfaces_key}").set_animation_data(
                            from_frame_index=0,
                            to_frame_index=len(surfaces[data][surfaces_key][0]) - 1,
                            duration=self.__data[data]["animation"][surfaces_key]["frame_delay"] * 3,
                            should_loop=False if data == "tunic" and surfaces_key == "sword" else should_loops[data]
                        )
                    else:
                        renderable_components[data].add_renderable(
                            renderable=Renderable(surface=surfaces[data][surfaces_key][0][0],
                                                  coordinate=Vector2f(x=0.0, y=0.0),
                                                  depth=depths[data],
                                                  name=f"{data}_{surfaces_key}"))

            # assert renderable_component.set_renderable("stopped_south")
            self.add_renderable_component(renderable_component=renderable_components[data])

        self.__sound_effects["sword1"] = pygame.mixer.Sound(file="resources/sounds/sword1.ogg")

    def destroy(self):
        super().destroy()

    @property
    def facing_direction(self) -> eFacingDirection:
        return self.__facing_direction

    @property
    def direction(self) -> Vector2f:
        return self.__direction

    @property
    def name(self) -> str:
        return self.__name

    @property
    def speed(self) -> float:
        return self.__speed

    @property
    def width(self) -> float:
        return self.get_renderable_component("tunic").renderable.surface.get_width()

    @property
    def height(self) -> float:
        return self.get_renderable_component("tunic").renderable.surface.get_height()

    @name.setter
    def name(self, name: str) -> None:
        self.__name = name

    def lift_pressed_action(self):
        if not self.__is_lifting:
            self.__is_lifting = True

            if self.__has_shield:
                self.get_renderable_component("shield").hide_renderable()

    def on_collision_with(self, other: CollidableObject):
        self.__has_collided = True

        if len(self.__movement_input_stack) > 0:
            self._coordinates.x -= self.__direction.x * self.__speed
            self._coordinates.y -= self.__direction.y * self.__speed

    def on_lifting_animation_done(self):
        self.__is_lifting = False
        self.get_renderable_component("tunic").renderable.reset_animation()

        if self.__has_shield:
            self.get_renderable_component("shield").show_renderable()

    def shield_pressed_action(self):
        self.__has_shield = not self.__has_shield

        if not self.__has_shield:
            self.get_renderable_component("shield").hide_renderable()
        else:
            self.get_renderable_component("shield").show_renderable()

        if self.__is_attacking_with_sword:
            self.sword_pressed_action()

    def sword_pressed_action(self):
        if not self.__is_attacking_with_sword:
            self.__sound_effects["sword1"].play()
            self.__is_attacking_with_sword = True

            if self.get_renderable_component("sword").renderable is not None:
                self.get_renderable_component("sword").show_renderable()

            if self.__has_shield:
                self.get_renderable_component("shield").hide_renderable()

    def on_sword_animation_done(self):
        self.__sound_effects["sword1"].stop()
        self.__is_attacking_with_sword = False
        self.get_renderable_component("sword").renderable.reset_animation()
        self.get_renderable_component("tunic").renderable.reset_animation()
        self.get_renderable_component("sword").hide_renderable()

        if self.__has_shield:
            self.get_renderable_component("shield").show_renderable()

    def movement_input_pressed(self, key: int):
        assert key in self.__input

        self.__input[key] = True

        if key == pygame.K_UP or key == pygame.K_DOWN or key == pygame.K_LEFT or key == pygame.K_RIGHT:
            self.__movement_input_stack.append(key)

    def movement_input_released(self, key: int):
        assert key in self.__input

        self.__input[key] = False
        if key == pygame.K_UP or key == pygame.K_DOWN or key == pygame.K_LEFT or key == pygame.K_RIGHT:
            if len(self.__movement_input_stack) > 1:
                self.__movement_input_stack.remove(key)

    def update(self, delta_time: float):
        super().update(delta_time=delta_time)

        self.update_movement()
        self.update_animation()

        # print(self.get_renderable_component().renderable.coordinate)

        if not (self.__direction.x == 0.0 and self.__direction.y == 0.0):
            self._coordinates.x += self.__direction.x * self.__speed
            self._coordinates.y += self.__direction.y * self.__speed

        if self.get_renderable_component("sword").renderable is not None:
            self.get_renderable_component("sword").renderable.coordinate = self._coordinates + self.__offset["sword"]
        if self.get_renderable_component("shield").renderable is not None:
            self.get_renderable_component("shield").renderable.coordinate = self._coordinates + self.__offset["shield"]
        if self.get_renderable_component("tunic").renderable is not None:
            if self.__is_attacking_with_sword and self.get_renderable_component("tunic").renderable.is_animation_done:
                self.on_sword_animation_done()

            self.get_renderable_component("tunic").renderable.coordinate = self._coordinates + self.__offset["tunic"]
        self.__renderer.player_offset = self._coordinates

        debug_coordinate_surface: pygame.Surface = pygame.Surface(size=(2, 2))
        debug_coordinate_surface.fill(color=pygame.Color(255, 0, 0))

        debug_bounding_box: pygame.Surface = pygame.Surface(size=(self._collision_box.width, self._collision_box.height))
        debug_bounding_box.fill(color=pygame.Color(255, 0, 0))
        debug_bounding_box.set_alpha(32)

        top_left_coordinate: Vector2f = Vector2f(x=self._coordinates.x - self._collision_box.width / 2.0,
                                                 y=self._coordinates.y - 20.0)
        self._collision_box.top_left.copy(other=top_left_coordinate)
        self.__renderer.remove_renderable(key="debug_coordinate")
        self.__renderer.remove_renderable(key="debug_bounding_box")
        self.__renderer.add_renderable(renderable=Renderable(surface=debug_coordinate_surface,
                                                             coordinate=self._coordinates,
                                                             depth=Depth.DEBUG_DEPTH,
                                                             name="debug_coordinate"))
        self.__renderer.add_renderable(renderable=Renderable(surface=debug_bounding_box,
                                                             coordinate=top_left_coordinate,
                                                             depth=Depth.DEBUG_DEPTH,
                                                             name="debug_bounding_box"))

    def update_animation(self):
        is_idle: bool = self.__direction.x == 0.0 and self.__direction.y == 0.0
        if self.__last_movement_input == pygame.K_UP:
            self.__facing_direction = eFacingDirection.NORTH
            if is_idle:
                if self.__is_attacking_with_sword:
                    if self.get_renderable_component("tunic").renderable is not self.get_renderable_component(
                            "tunic").get_renderable_by_name(
                        name="tunic_sword_north"):
                        self.get_renderable_component("tunic").set_renderable(name="tunic_sword_north")
                        self.get_renderable_component("tunic").renderable.start_animation()
                        self.__offset["tunic"].x = -self.__data["tunic"]["animation"]["sword"]["directions"][1][
                            "origin_x"]
                        self.__offset["tunic"].y = -self.__data["tunic"]["animation"]["sword"]["directions"][1][
                            "origin_y"]

                    if self.get_renderable_component("sword").renderable is not self.get_renderable_component(
                            "sword").get_renderable_by_name(
                        name="sword_sword_north"):
                        self.get_renderable_component("sword").set_renderable(name="sword_sword_north")
                        self.get_renderable_component("sword").renderable.start_animation()
                        self.__offset["sword"].x = -self.__data["sword"]["animation"]["sword"]["directions"][1][
                            "origin_x"]
                        self.__offset["sword"].y = -self.__data["sword"]["animation"]["sword"]["directions"][1][
                            "origin_y"]
                elif self.__has_shield:
                    if self.get_renderable_component("tunic").renderable is not self.get_renderable_component(
                            "tunic").get_renderable_by_name(
                        name="tunic_stopped_with_shield_north"):
                        self.get_renderable_component("tunic").set_renderable(name="tunic_stopped_with_shield_north")
                        self.__offset["tunic"].x = - \
                            self.__data["tunic"]["animation"]["stopped_with_shield"]["directions"][1][
                                "origin_x"]
                        self.__offset["tunic"].y = - \
                            self.__data["tunic"]["animation"]["stopped_with_shield"]["directions"][1][
                                "origin_y"]

                    if self.get_renderable_component("shield").renderable is not self.get_renderable_component(
                            "shield").get_renderable_by_name(
                        name="shield_stopped_north"):
                        self.get_renderable_component("shield").set_renderable(name="shield_stopped_north")
                        self.__offset["shield"].x = -self.__data["shield"]["animation"]["stopped"]["directions"][1][
                            "origin_x"]
                        self.__offset["shield"].y = -self.__data["shield"]["animation"]["stopped"]["directions"][1][
                            "origin_y"]
                else:
                    if self.get_renderable_component("tunic").renderable is not self.get_renderable_component(
                            "tunic").get_renderable_by_name(
                        name="tunic_stopped_north"):
                        self.get_renderable_component("tunic").set_renderable(name="tunic_stopped_north")
                        self.__offset["tunic"].x = -self.__data["tunic"]["animation"]["stopped"]["directions"][1][
                            "origin_x"]
                        self.__offset["tunic"].y = -self.__data["tunic"]["animation"]["stopped"]["directions"][1][
                            "origin_y"]
            else:
                if self.__has_shield:
                    if self.get_renderable_component("tunic").renderable is not self.get_renderable_component(
                            "tunic").get_renderable_by_name(
                        name="tunic_walking_with_shield_north"):
                        self.get_renderable_component("tunic").set_renderable(name="tunic_walking_with_shield_north")
                        self.get_renderable_component("tunic").renderable.start_animation()
                        self.__offset["tunic"].x = - \
                            self.__data["tunic"]["animation"]["walking_with_shield"]["directions"][1][
                                "origin_x"]
                        self.__offset["tunic"].y = - \
                            self.__data["tunic"]["animation"]["walking_with_shield"]["directions"][1][
                                "origin_y"]

                    if self.get_renderable_component("shield").renderable is not self.get_renderable_component(
                            "shield").get_renderable_by_name(
                        name="shield_walking_north"):
                        self.get_renderable_component("shield").set_renderable(name="shield_walking_north")
                        self.__offset["shield"].x = -self.__data["shield"]["animation"]["walking"]["directions"][1][
                            "origin_x"]
                        self.__offset["shield"].y = -self.__data["shield"]["animation"]["walking"]["directions"][1][
                            "origin_y"]
                else:
                    if self.get_renderable_component("tunic").renderable is not self.get_renderable_component(
                            "tunic").get_renderable_by_name(
                        name="tunic_walking_north"):
                        self.get_renderable_component("tunic").set_renderable(name="tunic_walking_north")
                        self.get_renderable_component("tunic").renderable.start_animation()
                        self.__offset["tunic"].x = -self.__data["tunic"]["animation"]["walking"]["directions"][1][
                            "origin_x"]
                        self.__offset["tunic"].y = -self.__data["tunic"]["animation"]["walking"]["directions"][1][
                            "origin_y"]
        elif self.__last_movement_input == pygame.K_DOWN:
            self.__facing_direction = eFacingDirection.SOUTH
            if is_idle:
                if self.__is_attacking_with_sword:
                    if self.get_renderable_component("tunic").renderable is not self.get_renderable_component(
                            "tunic").get_renderable_by_name(
                        name="tunic_sword_south"):
                        self.get_renderable_component("tunic").set_renderable(name="tunic_sword_south")
                        self.get_renderable_component("tunic").renderable.start_animation()
                        self.__offset["tunic"].x = -self.__data["tunic"]["animation"]["sword"]["directions"][3][
                            "origin_x"]
                        self.__offset["tunic"].y = -self.__data["tunic"]["animation"]["sword"]["directions"][3][
                            "origin_y"]

                    if self.get_renderable_component("sword").renderable is not self.get_renderable_component(
                            "sword").get_renderable_by_name(
                        name="sword_sword_south"):
                        self.get_renderable_component("sword").set_renderable(name="sword_sword_south")
                        self.get_renderable_component("sword").renderable.start_animation()
                        self.__offset["sword"].x = -self.__data["sword"]["animation"]["sword"]["directions"][3][
                            "origin_x"]
                        self.__offset["sword"].y = -self.__data["sword"]["animation"]["sword"]["directions"][3][
                            "origin_y"]
                elif self.__has_shield:
                    if self.get_renderable_component("tunic").renderable is not self.get_renderable_component(
                            "tunic").get_renderable_by_name(
                        name="tunic_stopped_with_shield_south"):
                        self.get_renderable_component("tunic").set_renderable(name="tunic_stopped_with_shield_south")
                        self.__offset["tunic"].x = - \
                            self.__data["tunic"]["animation"]["stopped_with_shield"]["directions"][3][
                                "origin_x"]
                        self.__offset["tunic"].y = - \
                            self.__data["tunic"]["animation"]["stopped_with_shield"]["directions"][3][
                                "origin_y"]

                    if self.get_renderable_component("shield").renderable is not self.get_renderable_component(
                            "shield").get_renderable_by_name(
                        name="shield_stopped_south"):
                        self.get_renderable_component("shield").set_renderable(name="shield_stopped_south")
                        self.__offset["shield"].x = -self.__data["shield"]["animation"]["stopped"]["directions"][3][
                            "origin_x"]
                        self.__offset["shield"].y = -self.__data["shield"]["animation"]["stopped"]["directions"][3][
                            "origin_y"]
                else:
                    if self.get_renderable_component(name="tunic").renderable is not self.get_renderable_component(
                            "tunic").get_renderable_by_name(
                        name="tunic_stopped_south"):
                        self.get_renderable_component("tunic").set_renderable(name="tunic_stopped_south")
                        self.__offset["tunic"].x = -self.__data["tunic"]["animation"]["stopped"]["directions"][3][
                            "origin_x"]
                        self.__offset["tunic"].y = -self.__data["tunic"]["animation"]["stopped"]["directions"][3][
                            "origin_y"]
            else:
                if self.__has_shield:
                    if self.get_renderable_component("tunic").renderable is not self.get_renderable_component(
                            "tunic").get_renderable_by_name(
                        name="tunic_walking_with_shield_south"):
                        self.get_renderable_component("tunic").set_renderable(name="tunic_walking_with_shield_south")
                        self.get_renderable_component("tunic").renderable.start_animation()
                        self.__offset["tunic"].x = - \
                            self.__data["tunic"]["animation"]["walking_with_shield"]["directions"][3][
                                "origin_x"]
                        self.__offset["tunic"].y = - \
                            self.__data["tunic"]["animation"]["walking_with_shield"]["directions"][3][
                                "origin_y"]

                    if self.get_renderable_component("shield").renderable is not self.get_renderable_component(
                            "shield").get_renderable_by_name(
                        name="shield_walking_south"):
                        self.get_renderable_component("shield").set_renderable(name="shield_walking_south")
                        self.__offset["shield"].x = -self.__data["shield"]["animation"]["walking"]["directions"][1][
                            "origin_x"]
                        self.__offset["shield"].y = -self.__data["shield"]["animation"]["walking"]["directions"][1][
                            "origin_y"]
                else:
                    if self.get_renderable_component("tunic").renderable is not self.get_renderable_component(
                            "tunic").get_renderable_by_name(
                        name="tunic_walking_south"):
                        self.get_renderable_component("tunic").set_renderable(name="tunic_walking_south")
                        self.get_renderable_component("tunic").renderable.start_animation()
                        self.__offset["tunic"].x = -self.__data["tunic"]["animation"]["walking"]["directions"][3][
                            "origin_x"]
                        self.__offset["tunic"].y = -self.__data["tunic"]["animation"]["walking"]["directions"][3][
                            "origin_y"]
        elif self.__last_movement_input == pygame.K_LEFT:
            self.__facing_direction = eFacingDirection.WEST
            if is_idle:
                if self.__is_attacking_with_sword:
                    if self.get_renderable_component("tunic").renderable is not self.get_renderable_component(
                            "tunic").get_renderable_by_name(
                        name="tunic_sword_west"):
                        self.get_renderable_component("tunic").set_renderable(name="tunic_sword_west")
                        self.get_renderable_component("tunic").renderable.start_animation()
                        self.__offset["tunic"].x = -self.__data["tunic"]["animation"]["sword"]["directions"][2][
                            "origin_x"]
                        self.__offset["tunic"].y = -self.__data["tunic"]["animation"]["sword"]["directions"][2][
                            "origin_y"]

                    if self.get_renderable_component("sword").renderable is not self.get_renderable_component(
                            "sword").get_renderable_by_name(
                        name="sword_sword_west"):
                        self.get_renderable_component("sword").set_renderable(name="sword_sword_west")
                        self.get_renderable_component("sword").renderable.start_animation()
                        self.__offset["sword"].x = -self.__data["sword"]["animation"]["sword"]["directions"][2][
                            "origin_x"]
                        self.__offset["sword"].y = -self.__data["sword"]["animation"]["sword"]["directions"][2][
                            "origin_y"]
                elif self.__has_shield:
                    if self.get_renderable_component("tunic").renderable is not self.get_renderable_component(
                            "tunic").get_renderable_by_name(
                        name="tunic_stopped_with_shield_west"):
                        self.get_renderable_component("tunic").set_renderable(name="tunic_stopped_with_shield_west")
                        self.__offset["tunic"].x = - \
                            self.__data["tunic"]["animation"]["stopped_with_shield"]["directions"][2][
                                "origin_x"]
                        self.__offset["tunic"].y = - \
                            self.__data["tunic"]["animation"]["stopped_with_shield"]["directions"][2][
                                "origin_y"]

                    if self.get_renderable_component("shield").renderable is not self.get_renderable_component(
                            "shield").get_renderable_by_name(
                        name="shield_stopped_west"):
                        self.get_renderable_component("shield").set_renderable(name="shield_stopped_west")
                        self.__offset["shield"].x = -self.__data["shield"]["animation"]["stopped"]["directions"][2][
                            "origin_x"]
                        self.__offset["shield"].y = -self.__data["shield"]["animation"]["stopped"]["directions"][2][
                            "origin_y"]
                else:
                    if self.get_renderable_component("tunic").renderable is not self.get_renderable_component(
                            "tunic").get_renderable_by_name(
                        name="tunic_stopped_west"):
                        self.get_renderable_component("tunic").set_renderable(name="tunic_stopped_west")
                        self.__offset["tunic"].x = -self.__data["tunic"]["animation"]["stopped"]["directions"][2][
                            "origin_x"]
                        self.__offset["tunic"].y = -self.__data["tunic"]["animation"]["stopped"]["directions"][2][
                            "origin_y"]
            else:
                if self.__has_shield:
                    if self.get_renderable_component("tunic").renderable is not self.get_renderable_component(
                            "tunic").get_renderable_by_name(
                        name="tunic_walking_with_shield_west"):
                        self.get_renderable_component("tunic").set_renderable(name="tunic_walking_with_shield_west")
                        self.get_renderable_component("tunic").renderable.start_animation()
                        self.__offset["tunic"].x = - \
                            self.__data["tunic"]["animation"]["walking_with_shield"]["directions"][2][
                                "origin_x"]
                        self.__offset["tunic"].y = - \
                            self.__data["tunic"]["animation"]["walking_with_shield"]["directions"][2][
                                "origin_y"]

                    if self.get_renderable_component("shield").renderable is not self.get_renderable_component(
                            "shield").get_renderable_by_name(
                        name="shield_walking_west"):
                        self.get_renderable_component("shield").set_renderable(name="shield_walking_west")
                        self.__offset["shield"].x = -self.__data["shield"]["animation"]["walking"]["directions"][2][
                            "origin_x"]
                        self.__offset["shield"].y = -self.__data["shield"]["animation"]["walking"]["directions"][2][
                            "origin_y"]
                else:
                    if self.get_renderable_component("tunic").renderable is not self.get_renderable_component(
                            "tunic").get_renderable_by_name(
                        name="tunic_walking_west"):
                        self.get_renderable_component("tunic").set_renderable(name="tunic_walking_west")
                        self.get_renderable_component("tunic").renderable.start_animation()
                        self.__offset["tunic"].x = -self.__data["tunic"]["animation"]["walking"]["directions"][2][
                            "origin_x"]
                        self.__offset["tunic"].y = -self.__data["tunic"]["animation"]["walking"]["directions"][2][
                            "origin_y"]
        elif self.__last_movement_input == pygame.K_RIGHT:
            self.__facing_direction = eFacingDirection.EAST
            if is_idle:
                if self.__is_attacking_with_sword:
                    if self.get_renderable_component("tunic").renderable is not self.get_renderable_component(
                            "tunic").get_renderable_by_name(
                        name="tunic_sword_east"):
                        self.get_renderable_component("tunic").set_renderable(name="tunic_sword_east")
                        self.get_renderable_component("tunic").renderable.start_animation()
                        self.__offset["tunic"].x = -self.__data["tunic"]["animation"]["sword"]["directions"][0][
                            "origin_x"]
                        self.__offset["tunic"].y = -self.__data["tunic"]["animation"]["sword"]["directions"][0][
                            "origin_y"]

                    if self.get_renderable_component("sword").renderable is not self.get_renderable_component(
                            "sword").get_renderable_by_name(
                        name="sword_sword_east"):
                        self.get_renderable_component("sword").set_renderable(name="sword_sword_east")
                        self.get_renderable_component("sword").renderable.start_animation()
                        self.__offset["sword"].x = -self.__data["sword"]["animation"]["sword"]["directions"][0][
                            "origin_x"]
                        self.__offset["sword"].y = -self.__data["sword"]["animation"]["sword"]["directions"][0][
                            "origin_y"]
                elif self.__has_shield:
                    if self.get_renderable_component("tunic").renderable is not self.get_renderable_component(
                            "tunic").get_renderable_by_name(
                        name="tunic_stopped_with_shield_east"):
                        self.get_renderable_component("tunic").set_renderable(name="tunic_stopped_with_shield_east")
                        self.__offset["tunic"].x = - \
                            self.__data["tunic"]["animation"]["stopped_with_shield"]["directions"][0][
                                "origin_x"]
                        self.__offset["tunic"].y = - \
                            self.__data["tunic"]["animation"]["stopped_with_shield"]["directions"][0][
                                "origin_y"]

                    if self.get_renderable_component("shield").renderable is not self.get_renderable_component(
                            "shield").get_renderable_by_name(
                        name="shield_stopped_east"):
                        self.get_renderable_component("shield").set_renderable(name="shield_stopped_east")
                        self.__offset["shield"].x = -self.__data["shield"]["animation"]["stopped"]["directions"][0][
                            "origin_x"]
                        self.__offset["shield"].y = -self.__data["shield"]["animation"]["stopped"]["directions"][0][
                            "origin_y"]
                else:
                    if self.get_renderable_component("tunic").renderable is not self.get_renderable_component(
                            "tunic").get_renderable_by_name(
                        name="tunic_stopped_east"):
                        self.get_renderable_component("tunic").set_renderable(name="tunic_stopped_east")
                        self.__offset["tunic"].x = -self.__data["tunic"]["animation"]["stopped"]["directions"][0][
                            "origin_x"]
                        self.__offset["tunic"].y = -self.__data["tunic"]["animation"]["stopped"]["directions"][0][
                            "origin_y"]
            else:
                if self.__has_shield:
                    if self.get_renderable_component("tunic").renderable is not self.get_renderable_component(
                            "tunic").get_renderable_by_name(
                        name="tunic_walking_with_shield_east"):
                        self.get_renderable_component("tunic").set_renderable(name="tunic_walking_with_shield_east")
                        self.get_renderable_component("tunic").renderable.start_animation()
                        self.__offset["tunic"].x = - \
                            self.__data["tunic"]["animation"]["walking_with_shield"]["directions"][0][
                                "origin_x"]
                        self.__offset["tunic"].y = - \
                            self.__data["tunic"]["animation"]["walking_with_shield"]["directions"][0][
                                "origin_y"]

                    if self.get_renderable_component("shield").renderable is not self.get_renderable_component(
                            "shield").get_renderable_by_name(
                        name="shield_walking_east"):
                        self.get_renderable_component("shield").set_renderable(name="shield_walking_east")
                        self.__offset["shield"].x = -self.__data["shield"]["animation"]["walking"]["directions"][0][
                            "origin_x"]
                        self.__offset["shield"].y = -self.__data["shield"]["animation"]["walking"]["directions"][0][
                            "origin_y"]
                else:
                    if self.get_renderable_component("tunic").renderable is not self.get_renderable_component(
                            "tunic").get_renderable_by_name(
                        name="tunic_walking_east"):
                        self.get_renderable_component("tunic").set_renderable(name="tunic_walking_east")
                        self.get_renderable_component("tunic").renderable.start_animation()
                        self.__offset["tunic"].x = -self.__data["tunic"]["animation"]["walking"]["directions"][0][
                            "origin_x"]
                        self.__offset["tunic"].y = -self.__data["tunic"]["animation"]["walking"]["directions"][0][
                            "origin_y"]

    def update_movement(self):
        if self.__is_attacking_with_sword:
            self.__direction.x = 0.0
            self.__direction.y = 0.0
        else:
            while len(self.__movement_input_stack) > 0:
                self.__last_movement_input = self.__movement_input_stack[-1]
                if not self.__input[self.__movement_input_stack[-1]]:
                    self.__direction.x = 0.0
                    self.__direction.y = 0.0
                    self.__movement_input_stack.pop()
                else:
                    if self.__movement_input_stack[-1] == pygame.K_UP:
                        self.__direction.x = 0.0
                        self.__direction.y = -1.0
                    elif self.__movement_input_stack[-1] == pygame.K_DOWN:
                        self.__direction.x = 0.0
                        self.__direction.y = 1.0
                    elif self.__movement_input_stack[-1] == pygame.K_LEFT:
                        self.__direction.x = -1.0
                        self.__direction.y = 0.0
                    elif self.__movement_input_stack[-1] == pygame.K_RIGHT:
                        self.__direction.x = 1.0
                        self.__direction.y = 0.0
                    break
