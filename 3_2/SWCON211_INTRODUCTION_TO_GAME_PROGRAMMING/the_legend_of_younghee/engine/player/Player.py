import random
from typing import Union

import pygame.surface

from engine.core.GlobalConstants import GlobalConstants
from engine.core.Math import Vector2f
from engine.graphics.Orientation import Orientation
from engine.graphics.Renderable import Renderable
from engine.graphics.Renderer import Depth, Renderer
from engine.object.BaseObject import eFacingDirection
from engine.object.CollidableObject import CollidableObject
from engine.object.Enemy import Enemy
from engine.resources.RenderableStorage import RenderableStorage


class Player(CollidableObject):
    __slots__ = ["__name", "__speed", "__direction", "__input", "__movement_input_stack", "__renderer",
                 "__data", "__last_movement_input", "__offset", "__has_shield", "__is_attacking_with_sword",
                 "__is_loading_sword", "__sound_effects", "__is_lifting", "__facing_direction", "__has_collided",
                 "__previous_coordinate", "__sword_hit", "__facing_vector", "__current_shield_name",
                 "__current_sword_name", "__health", "__damage", "__is_damaged", "__is_hurting", "__hurt_timer",
                 "__hurt_timer_init_value", "__is_dying_playing", "__walk_on_grass_timer_threshold",
                 "__walk_on_grass_timer"]

    def __init__(self, name: str, coordinate: Vector2f):
        super().__init__(coordinate=coordinate, width=12, height=12)
        self.__name: str = name

        self.__speed: float = 2.4
        self.__direction: Vector2f = Vector2f(x=0.0, y=0.0)
        self.__facing_vector: Vector2f = Vector2f(x=0.0, y=1.0)
        self.__facing_direction: eFacingDirection = eFacingDirection.SOUTH
        self.__input: dict[int, bool] = dict()

        self.__input[pygame.K_UP] = False
        self.__input[pygame.K_DOWN] = False
        self.__input[pygame.K_LEFT] = False
        self.__input[pygame.K_RIGHT] = False

        self.__movement_input_stack: list[int] = []
        self.__last_movement_input: int = pygame.K_DOWN

        self.__offset: dict[str, Vector2f] = dict()

        self.__walk_on_grass_timer: int = 0
        self.__walk_on_grass_timer_threshold: int = 150

        # resources
        self.__data: dict[str, dict[str, dict[str, dict[str, Union[list[dict[str, int]], str, int]]]]] = dict()
        self.__sound_effects: dict[str, pygame.mixer.Sound] = dict()
        self.__current_shield_name: str = None
        self.__current_sword_name: str = None

        # state
        self.__has_shield: bool = False
        self.__is_attacking_with_sword: bool = False
        self.__is_loading_sword: bool = False
        self.__is_lifting: bool = False
        self.__is_damaged: bool = False
        self.__is_hurting: bool = False
        self.__hurt_timer: int = 0
        self.__hurt_timer_init_value: int = 333
        self.__health: float = 100.0
        self.__damage: float = 25.0
        self.__is_dying_playing: bool = False

        # collision
        self.__has_collided: bool = False
        self.__previous_coordinate: Vector2f = Vector2f(x=self._coordinates.x, y=self._coordinates.y)
        self.__sword_hit: CollidableObject = None

    def initialize(self):
        super().initialize()

        pre_load_data: list[str] = ["shield", "sword_stars", "sword", "trail", "tunic"]
        self.__data["shield"] = Renderable.parse_data(
            file_path="resources/sprites/hero/shield1.dat")
        self.__data["sword_stars"] = Renderable.parse_data(
            file_path="resources/sprites/hero/sword_stars1.dat")
        self.__data["sword"] = Renderable.parse_data(
            file_path="resources/sprites/hero/sword1.dat")
        self.__data["trail"] = Renderable.parse_data(
            file_path="resources/sprites/hero/trail.dat")
        self.__data["tunic"] = Renderable.parse_data(
            file_path="resources/sprites/hero/tunic1.dat")

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
        for data in pre_load_data:
            print(f"data: {data}")
            surfaces[data] = dict()
            coordinates[data] = dict()
            self.__offset[data] = Vector2f(x=0.0, y=0.0)
            for data_key in self.__data[data]:
                # print(f"\tdata_key: {data_key}")
                for data_name in self.__data[data][data_key]:
                    # print(f"\t\tdata_name: {data_name}")
                    if data_name not in surfaces[data] and data_name not in coordinates[data]:
                        surfaces[data][data_name] = []
                        coordinates[data][data_name] = []
                    for attribute_key in self.__data[data][data_key][data_name]:
                        if attribute_key == "src_image":
                            if not RenderableStorage.contains_surface(key=self.__data[data][data_key][data_name][attribute_key]):
                                RenderableStorage.add_surface(key=self.__data[data][data_key][data_name][attribute_key],
                                                              surface=pygame.image.load(
                                                                  f'resources/sprites/{self.__data[data][data_key][data_name][attribute_key]}'
                                                              ).convert_alpha())
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
                                        RenderableStorage.get_surface_or_none(
                                            key=self.__data[data][data_key][data_name]["src_image"]
                                        ).subsurface(rect)
                                    )

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

            # print(f"data: {data}")
            for surfaces_key in surfaces[data]:
                print(f"\tkey: {surfaces_key}, {len(surfaces[data][surfaces_key])}")
                if len(surfaces[data][surfaces_key]) == 4:
                    if len(surfaces[data][surfaces_key][0]) > 1:
                        RenderableStorage.add_renderable(
                            renderable=Renderable(surface=surfaces[data][surfaces_key][0][0],
                                                  coordinate=Vector2f(x=0.0, y=0.0),
                                                  depth=depths[data],
                                                  name=f"{data}_{surfaces_key}_east",
                                                  surfaces=surfaces[data][surfaces_key][0],
                                                  coordinates=coordinates[data][surfaces_key][0],
                                                  orientation=Orientation.CENTER))
                        RenderableStorage.get_renderable_or_none(
                            key=f"{data}_{surfaces_key}_east").set_animation_data(
                            from_frame_index=0,
                            to_frame_index=len(surfaces[data][surfaces_key][0]) - 1,
                            duration=self.__data[data]["animation"][surfaces_key]["frame_delay"] * 3,
                            should_loop=False if data == "tunic" and surfaces_key == "sword" else should_loops[data]
                        )
                        RenderableStorage.add_renderable(
                            renderable=Renderable(surface=surfaces[data][surfaces_key][1][0],
                                                  coordinate=Vector2f(x=0.0, y=0.0),
                                                  depth=depths[data],
                                                  name=f"{data}_{surfaces_key}_north",
                                                  surfaces=surfaces[data][surfaces_key][1],
                                                  coordinates=coordinates[data][surfaces_key][1]))
                        RenderableStorage.get_renderable_or_none(
                            key=f"{data}_{surfaces_key}_north").set_animation_data(
                            from_frame_index=0,
                            to_frame_index=len(surfaces[data][surfaces_key][1]) - 1,
                            duration=self.__data[data]["animation"][surfaces_key]["frame_delay"] * 3,
                            should_loop=False if data == "tunic" and surfaces_key == "sword" else should_loops[data]
                        )
                        RenderableStorage.add_renderable(
                            renderable=Renderable(surface=surfaces[data][surfaces_key][2][0],
                                                  coordinate=Vector2f(x=0.0, y=0.0),
                                                  depth=depths[data],
                                                  name=f"{data}_{surfaces_key}_west",
                                                  surfaces=surfaces[data][surfaces_key][2],
                                                  coordinates=coordinates[data][surfaces_key][2]))
                        RenderableStorage.get_renderable_or_none(
                            key=f"{data}_{surfaces_key}_west").set_animation_data(
                            from_frame_index=0,
                            to_frame_index=len(surfaces[data][surfaces_key][2]) - 1,
                            duration=self.__data[data]["animation"][surfaces_key]["frame_delay"] * 3,
                            should_loop=False if data == "tunic" and surfaces_key == "sword" else should_loops[data]
                        )
                        RenderableStorage.add_renderable(
                            renderable=Renderable(surface=surfaces[data][surfaces_key][3][0],
                                                  coordinate=Vector2f(x=0.0, y=0.0),
                                                  depth=depths[data],
                                                  name=f"{data}_{surfaces_key}_south",
                                                  surfaces=surfaces[data][surfaces_key][3],
                                                  coordinates=coordinates[data][surfaces_key][3]))
                        RenderableStorage.get_renderable_or_none(
                            key=f"{data}_{surfaces_key}_south").set_animation_data(
                            from_frame_index=0,
                            to_frame_index=len(surfaces[data][surfaces_key][3]) - 1,
                            duration=self.__data[data]["animation"][surfaces_key]["frame_delay"] * 3,
                            should_loop=False if data == "tunic" and surfaces_key == "sword" else should_loops[data]
                        )
                    else:
                        RenderableStorage.add_renderable(
                            renderable=Renderable(surface=surfaces[data][surfaces_key][0][0],
                                                  coordinate=Vector2f(x=0.0, y=0.0),
                                                  depth=depths[data],
                                                  name=f"{data}_{surfaces_key}_east"))
                        RenderableStorage.add_renderable(
                            renderable=Renderable(surface=surfaces[data][surfaces_key][1][0],
                                                  coordinate=Vector2f(x=0.0, y=0.0),
                                                  depth=depths[data],
                                                  name=f"{data}_{surfaces_key}_north"))
                        RenderableStorage.add_renderable(
                            renderable=Renderable(surface=surfaces[data][surfaces_key][2][0],
                                                  coordinate=Vector2f(x=0.0, y=0.0),
                                                  depth=depths[data],
                                                  name=f"{data}_{surfaces_key}_west"))
                        RenderableStorage.add_renderable(
                            renderable=Renderable(surface=surfaces[data][surfaces_key][3][0],
                                                  coordinate=Vector2f(x=0.0, y=0.0),
                                                  depth=depths[data],
                                                  name=f"{data}_{surfaces_key}_south"))
                else:
                    if len(surfaces[data][surfaces_key][0]) > 1:
                        RenderableStorage.add_renderable(
                            renderable=Renderable(surface=surfaces[data][surfaces_key][0][0],
                                                  coordinate=Vector2f(x=0.0, y=0.0),
                                                  depth=depths[data],
                                                  name=f"{data}_{surfaces_key}",
                                                  surfaces=surfaces[data][surfaces_key][0],
                                                  coordinates=coordinates[data][surfaces_key][0]))
                        RenderableStorage.get_renderable_or_none(
                            key=f"{data}_{surfaces_key}").set_animation_data(
                            from_frame_index=0,
                            to_frame_index=len(surfaces[data][surfaces_key][0]) - 1,
                            duration=self.__data[data]["animation"][surfaces_key]["frame_delay"] * 3,
                            should_loop=False if data == "tunic" and surfaces_key == "sword" else should_loops[data]
                        )
                    else:
                        RenderableStorage.add_renderable(
                            renderable=Renderable(surface=surfaces[data][surfaces_key][0][0],
                                                  coordinate=Vector2f(x=0.0, y=0.0),
                                                  depth=depths[data],
                                                  name=f"{data}_{surfaces_key}"))

        self.__sound_effects["sword1"] = pygame.mixer.Sound(file="resources/sounds/sword1.ogg")
        self.__sound_effects["sword2"] = pygame.mixer.Sound(file="resources/sounds/sword2.ogg")
        self.__sound_effects["sword3"] = pygame.mixer.Sound(file="resources/sounds/sword3.ogg")
        self.__sound_effects["sword4"] = pygame.mixer.Sound(file="resources/sounds/sword4.ogg")
        self.__sound_effects["hero_hurt"] = pygame.mixer.Sound(file="resources/sounds/hero_hurt.ogg")
        self.__sound_effects["hero_dying"] = pygame.mixer.Sound(file="resources/sounds/hero_dying.ogg")
        self.__sound_effects["shield"] = pygame.mixer.Sound(file="resources/sounds/shield.ogg")
        self.__sound_effects["ok"] = pygame.mixer.Sound(file="resources/sounds/ok.ogg")
        self.__sound_effects["walk_on_grass"] = pygame.mixer.Sound(file="resources/sounds/walk_on_grass.ogg")
        GlobalConstants.add_constant(key="player", value=self)

    def destroy(self):
        super().destroy()
        GlobalConstants.remove_constant(key="player")

    @property
    def facing_direction(self) -> eFacingDirection:
        return self.__facing_direction

    @property
    def direction(self) -> Vector2f:
        return self.__direction

    @property
    def health(self) -> float:
        return self.__health

    @property
    def name(self) -> str:
        return self.__name

    @property
    def speed(self) -> float:
        return self.__speed

    @property
    def width(self) -> float:
        return RenderableStorage.get_renderable_or_none(key=self._current_renderable_name).surface.get_width()

    @property
    def height(self) -> float:
        return RenderableStorage.get_renderable_or_none(key=self._current_renderable_name).surface.get_height()

    @property
    def is_attacking(self) -> bool:
        return self.__is_attacking_with_sword

    @property
    def sword_hit(self) -> Union[CollidableObject, None]:
        return self.__sword_hit

    @name.setter
    def name(self, name: str) -> None:
        self.__name = name

    def flash_pressed_action(self):
        self._coordinates += self.__direction * self.__speed * 20.0
        self.__sound_effects["ok"].play()

    def lift_pressed_action(self):
        if not self.__is_lifting:
            self.__is_lifting = True

            if self.__has_shield:
                RenderableStorage.pull_from_renderer(key=self.__current_shield_name)

    def on_collision_with(self, other: CollidableObject):
        self.__has_collided = True
        # print(f"coordinate: {self._coordinates}")
        if self._coordinates != self.__previous_coordinate:
            self._coordinates.copy(other=self.__previous_coordinate)
        # if len(self.__movement_input_stack) > 0:
        #     self._coordinates.x -= self.__direction.x * self.__speed
        #     self._coordinates.y -= self.__direction.y * self.__speed

    def on_collision_with_ganon(self, ganon: Enemy):
        self.__has_collided = True
        # print(f"coordinate: {self._coordinates}")
        if self._coordinates != self.__previous_coordinate:
            self._coordinates.copy(other=self.__previous_coordinate)
        # if len(self.__movement_input_stack) > 0:
        #     self._coordinates.x -= self.__direction.x * self.__speed
        #     self._coordinates.y -= self.__direction.y * self.__speed
        if not self.__has_shield:
            if not self.__is_hurting:
                self.__is_hurting = True
                self.__is_damaged = True
                self.__health -= self.__damage
                self.__hurt_timer = self.__hurt_timer_init_value

                if self.__health <= 0:
                    self.__sound_effects["hero_dying"].play()
                else:
                    self.__sound_effects["hero_hurt"].play()

                if ganon.facing_direction == eFacingDirection.SOUTH:
                    # self.movement_input_pressed(key=pygame.K_UP)
                    self.__last_movement_input = pygame.K_UP
                    self.__direction.x = 0.0
                    self.__direction.y = -1.0
                    self.__facing_vector.x = 0.0
                    self.__facing_vector.y = -1.0
                elif ganon.facing_direction == eFacingDirection.WEST:
                    # self.movement_input_pressed(key=pygame.K_RIGHT)
                    self.__last_movement_input = pygame.K_RIGHT
                    self.__direction.x = 1.0
                    self.__direction.y = 0.0
                    self.__facing_vector.x = 1.0
                    self.__facing_vector.y = 0.0
                elif ganon.facing_direction == eFacingDirection.EAST:
                    # self.movement_input_pressed(key=pygame.K_LEFT)
                    self.__last_movement_input = pygame.K_LEFT
                    self.__direction.x = -1.0
                    self.__direction.y = 0.0
                    self.__facing_vector.x = -1.0
                    self.__facing_vector.y = 0.0
                elif ganon.facing_direction == eFacingDirection.NORTH:
                    # self.movement_input_pressed(key=pygame.K_DOWN)
                    self.__last_movement_input = pygame.K_DOWN
                    self.__direction.x = 0.0
                    self.__direction.y = 1.0
                    self.__facing_vector.x = 0.0
                    self.__facing_vector.y = 1.0

    def on_lifting_animation_done(self):
        self.__is_lifting = False
        RenderableStorage.get_renderable_or_none(key=self._current_renderable_name).reset_animation()

        if self.__has_shield:
            # self.get_renderable_component("shield").show_renderable()
            RenderableStorage.push_to_renderer(key=self.__current_shield_name)

    def shield_pressed_action(self):
        self.__has_shield = not self.__has_shield

        if not self.__has_shield:
            # self.get_renderable_component("shield").hide_renderable()
            RenderableStorage.pull_from_renderer(key=self.__current_shield_name)
        else:
            # self.get_renderable_component("shield").show_renderable()
            RenderableStorage.push_to_renderer(key=self.__current_shield_name)
            self.__sound_effects["shield"].play()

        if self.__is_attacking_with_sword:
            self.sword_pressed_action()

    def sword_pressed_action(self, is_strong_attack: bool = False):
        if not self.__is_attacking_with_sword and not self.__is_hurting:
            if is_strong_attack:
                pass
            else:
                self.__sound_effects[f"sword{random.randint(1, 4)}"].play()
                self.__is_attacking_with_sword = True

                sword_hit_coordinate: Vector2f = self._coordinates + Vector2f.elementwise_multiply(
                    lhs=self.__facing_vector,
                    rhs=Vector2f(x=self._collision_box.width,
                                 y=self._collision_box.height)
                )
                sword_hit_coordinate.x -= float(self.__facing_vector.x < 0) * 6.0
                sword_hit_coordinate.y -= float(self.__facing_vector.y < 0) * 6.0
                self.__sword_hit = CollidableObject(
                    coordinate=sword_hit_coordinate,
                    width=12.0 + 4.0 * int(self.__facing_vector.x != 0),
                    height=12.0,
                    is_attack=True
                )
                GlobalConstants.add_constant(key="sword_hit", value=self.__sword_hit)
                GlobalConstants.get_constant_or_none(key="collision_manager").add_collidable(key="sword_hit",
                                                                                             collidable_object=self.__sword_hit)

                if self.__current_sword_name is not None:
                    RenderableStorage.push_to_renderer(key=self.__current_sword_name)
                    # self.get_renderable_component("sword").show_renderable()

                if self.__has_shield:
                    RenderableStorage.pull_from_renderer(key=self.__current_shield_name)
                    # self.get_renderable_component("shield").hide_renderable()

    def on_sword_animation_done(self):
        self.__sound_effects["sword1"].stop()
        self.__is_attacking_with_sword = False

        RenderableStorage.get_renderable_or_none(key=self.__current_sword_name).reset_animation()
        RenderableStorage.get_renderable_or_none(key=self._current_renderable_name).reset_animation()
        RenderableStorage.pull_from_renderer(key=self.__current_sword_name)

        if GlobalConstants.contains_constant(key="sword_hit"):
            GlobalConstants.remove_constant(key="sword_hit")
            GlobalConstants.get_constant_or_none(key="collision_manager").remove_collidable(key="sword_hit")

        if self.__has_shield:
            RenderableStorage.push_to_renderer(key=self.__current_shield_name)

    def teleport_to_ganon_pressed_action(self):
        self._coordinates.copy(other=GlobalConstants.get_constant_or_none(key="ganon").coordinate)

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

        if not self.__is_dying_playing:
            if self.__is_hurting:
                self.__hurt_timer -= int(delta_time)
                if self.__hurt_timer <= 0:
                    self.__is_hurting = False
            else:
                self.update_movement()
            self.update_animation()

            if self.__is_hurting:
                self.__previous_coordinate.copy(other=self._coordinates)
                self._coordinates.x += -self.__facing_vector.x * 7.0 * (self.__hurt_timer / self.__hurt_timer_init_value)
                self._coordinates.y += -self.__facing_vector.y * 7.0 * (self.__hurt_timer / self.__hurt_timer_init_value)
                print(f"coord: {self.coordinate}. {self.__hurt_timer}, {self.__facing_vector}")
            elif not (self.__direction.x == 0.0 and self.__direction.y == 0.0):
                self.__previous_coordinate.copy(other=self._coordinates)
                self._coordinates.x += self.__direction.x * self.__speed
                self._coordinates.y += self.__direction.y * self.__speed
                if self.__walk_on_grass_timer <= 0:
                    self.__sound_effects["walk_on_grass"].play()
                    self.__walk_on_grass_timer = self.__walk_on_grass_timer_threshold
                else:
                    self.__walk_on_grass_timer -= int(delta_time)

            if RenderableStorage.is_rendering(key=self.__current_sword_name):
                RenderableStorage.get_renderable_or_none(
                    key=self.__current_sword_name
                ).coordinate = self._coordinates + self.__offset["sword"] + Vector2f(x=6.0, y=9.0)
            if RenderableStorage.is_rendering(key=self.__current_shield_name):
                RenderableStorage.get_renderable_or_none(
                    key=self.__current_shield_name
                ).coordinate = self._coordinates + self.__offset["shield"] + Vector2f(x=6.0, y=9.0)
            # print(f"is {self._current_renderable_name} rendering? {RenderableStorage.is_rendering(key=self._current_renderable_name)}")
        if RenderableStorage.is_rendering(key=self._current_renderable_name):
            # print(f"is done: {RenderableStorage.get_renderable_or_none(key=self._current_renderable_name).is_animation_done}")
            if self.__is_attacking_with_sword and \
                    RenderableStorage.get_renderable_or_none(key=self._current_renderable_name).is_animation_done:
                self.on_sword_animation_done()

            RenderableStorage.get_renderable_or_none(
                key=self._current_renderable_name
            ).coordinate = self._coordinates + self.__offset["tunic"] + Vector2f(x=6.0, y=9.0)
        GlobalConstants.get_constant_or_none(key="renderer").player_offset = self._coordinates

        if not RenderableStorage.contains_surface(key="debug_coordinate_surface"):
            debug_coordinate_surface: pygame.Surface = pygame.Surface(size=(2, 2))
            debug_coordinate_surface.fill(color=pygame.Color(255, 0, 0))
            RenderableStorage.add_surface(key="debug_coordinate_surface", surface=debug_coordinate_surface)
            if not RenderableStorage.contains_renderable(key="debug_coordinate_surface"):
                RenderableStorage.add_renderable(renderable=Renderable(surface=debug_coordinate_surface,
                                                                       coordinate=self._coordinates,
                                                                       depth=Depth.DEBUG_DEPTH,
                                                                       name="debug_coordinate"))
            RenderableStorage.get_renderable_or_none(key="debug_coordinate").coordinate = self._coordinates

    def update_animation(self):
        is_idle: bool = self.__direction.x == 0.0 and self.__direction.y == 0.0
        if self.__health <= 0.0 and not self.__is_dying_playing:
            if self._current_renderable_name != "tunic_dying":
                print(f"dying")
                if self._current_renderable_name is not None:
                    RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                self._current_renderable_name = "tunic_dying"
                RenderableStorage.push_to_renderer(key=self._current_renderable_name)
                RenderableStorage.get_renderable_or_none(key=self._current_renderable_name).start_animation()
                self.__is_dying_playing = True
                # print(f"pushed {self._current_renderable_name}")

                self.__offset["tunic"].x = -self.__data["tunic"]["animation"]["dying"]["directions"][0][
                    "origin_x"]
                self.__offset["tunic"].y = -self.__data["tunic"]["animation"]["dying"]["directions"][0][
                    "origin_y"]
        else:
            if self.__last_movement_input == pygame.K_UP:
                self.__facing_direction = eFacingDirection.NORTH
                if self.__is_hurting:
                    if self._current_renderable_name != "tunic_hurt_north":
                        if self._current_renderable_name is not None:
                            RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                        self._current_renderable_name = "tunic_hurt_north"
                        RenderableStorage.push_to_renderer(key=self._current_renderable_name)
                        # RenderableStorage.get_renderable_or_none(key=self._current_renderable_name).start_animation()
                        # print(f"pushed {self._current_renderable_name}")

                        self.__offset["tunic"].x = -self.__data["tunic"]["animation"]["hurt"]["directions"][1][
                            "origin_x"]
                        self.__offset["tunic"].y = -self.__data["tunic"]["animation"]["hurt"]["directions"][1][
                            "origin_y"]
                elif is_idle:
                    if self.__is_attacking_with_sword:
                        if self._current_renderable_name != "tunic_sword_north":
                            if self._current_renderable_name is not None:
                                RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                            self._current_renderable_name = "tunic_sword_north"
                            RenderableStorage.push_to_renderer(key=self._current_renderable_name)
                            # print(f"pushed {self._current_renderable_name}")

                            RenderableStorage.get_renderable_or_none(key=self._current_renderable_name).start_animation()
                            self.__offset["tunic"].x = -self.__data["tunic"]["animation"]["sword"]["directions"][1][
                                "origin_x"]
                            self.__offset["tunic"].y = -self.__data["tunic"]["animation"]["sword"]["directions"][1][
                                "origin_y"]

                        if self.__current_sword_name != "sword_sword_north":
                            if self.__current_sword_name is not None:
                                RenderableStorage.pull_from_renderer(key=self.__current_sword_name)
                            self.__current_sword_name = "sword_sword_north"
                            RenderableStorage.push_to_renderer(key="sword_sword_north")
                            RenderableStorage.get_renderable_or_none(key="sword_sword_north").start_animation()
                            self.__offset["sword"].x = -self.__data["sword"]["animation"]["sword"]["directions"][1][
                                "origin_x"]
                            self.__offset["sword"].y = -self.__data["sword"]["animation"]["sword"]["directions"][1][
                                "origin_y"]
                    elif self.__has_shield:
                        if self._current_renderable_name != "tunic_stopped_with_shield_north":
                            if self._current_renderable_name is not None:
                                RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                            self._current_renderable_name = "tunic_stopped_with_shield_north"
                            RenderableStorage.push_to_renderer(key=self._current_renderable_name)
                            # print(f"pushed {self._current_renderable_name}")

                            self.__offset["tunic"].x = - \
                                self.__data["tunic"]["animation"]["stopped_with_shield"]["directions"][1][
                                    "origin_x"]
                            self.__offset["tunic"].y = - \
                                self.__data["tunic"]["animation"]["stopped_with_shield"]["directions"][1][
                                    "origin_y"]

                        if self.__current_shield_name != "shield_stopped_north":
                            if self.__current_shield_name is not None:
                                RenderableStorage.pull_from_renderer(key=self.__current_shield_name)
                            self.__current_shield_name = "shield_stopped_north"
                            RenderableStorage.push_to_renderer(key=self.__current_shield_name)

                            self.__offset["shield"].x = -self.__data["shield"]["animation"]["stopped"]["directions"][1][
                                "origin_x"]
                            self.__offset["shield"].y = -self.__data["shield"]["animation"]["stopped"]["directions"][1][
                                "origin_y"]
                    else:
                        if self._current_renderable_name != "tunic_stopped_north":
                            if self._current_renderable_name is not None:
                                RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                            self._current_renderable_name = "tunic_stopped_north"
                            RenderableStorage.push_to_renderer(key=self._current_renderable_name)
                            # print(f"pushed {self._current_renderable_name}")

                            self.__offset["tunic"].x = -self.__data["tunic"]["animation"]["stopped"]["directions"][1][
                                "origin_x"]
                            self.__offset["tunic"].y = -self.__data["tunic"]["animation"]["stopped"]["directions"][1][
                                "origin_y"]
                else:
                    if self.__has_shield:
                        if self._current_renderable_name != "tunic_walking_with_shield_north":
                            if self._current_renderable_name is not None:
                                RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                            self._current_renderable_name = "tunic_walking_with_shield_north"
                            RenderableStorage.push_to_renderer(key=self._current_renderable_name)
                            # print(f"pushed {self._current_renderable_name}")

                            RenderableStorage.get_renderable_or_none(key=self._current_renderable_name).start_animation()

                            self.__offset["tunic"].x = - \
                                self.__data["tunic"]["animation"]["walking_with_shield"]["directions"][1][
                                    "origin_x"]
                            self.__offset["tunic"].y = - \
                                self.__data["tunic"]["animation"]["walking_with_shield"]["directions"][1][
                                    "origin_y"]

                        if self.__current_shield_name != "shield_walking_north":
                            if self.__current_shield_name is not None:
                                RenderableStorage.pull_from_renderer(key=self.__current_shield_name)
                            self.__current_shield_name = "shield_walking_north"
                            RenderableStorage.push_to_renderer(key=self.__current_shield_name)

                            self.__offset["shield"].x = -self.__data["shield"]["animation"]["walking"]["directions"][1][
                                "origin_x"]
                            self.__offset["shield"].y = -self.__data["shield"]["animation"]["walking"]["directions"][1][
                                "origin_y"]
                    else:
                        if self._current_renderable_name != "tunic_walking_north":
                            if self._current_renderable_name is not None:
                                RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                            self._current_renderable_name = "tunic_walking_north"
                            RenderableStorage.push_to_renderer(key=self._current_renderable_name)
                            # print(f"pushed {self._current_renderable_name}")

                            RenderableStorage.get_renderable_or_none(key=self._current_renderable_name).start_animation()

                            self.__offset["tunic"].x = -self.__data["tunic"]["animation"]["walking"]["directions"][1][
                                "origin_x"]
                            self.__offset["tunic"].y = -self.__data["tunic"]["animation"]["walking"]["directions"][1][
                                "origin_y"]
            elif self.__last_movement_input == pygame.K_DOWN:
                self.__facing_direction = eFacingDirection.SOUTH
                if self.__is_hurting:
                    if self._current_renderable_name != "tunic_hurt_south":
                        if self._current_renderable_name is not None:
                            RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                        self._current_renderable_name = "tunic_hurt_south"
                        RenderableStorage.push_to_renderer(key=self._current_renderable_name)
                        # RenderableStorage.get_renderable_or_none(key=self._current_renderable_name).start_animation()
                        # print(f"pushed {self._current_renderable_name}")

                        self.__offset["tunic"].x = -self.__data["tunic"]["animation"]["hurt"]["directions"][3][
                            "origin_x"]
                        self.__offset["tunic"].y = -self.__data["tunic"]["animation"]["hurt"]["directions"][3][
                            "origin_y"]
                elif is_idle:
                    if self.__is_attacking_with_sword:
                        if self._current_renderable_name != "tunic_sword_south":
                            if self._current_renderable_name is not None:
                                RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                            self._current_renderable_name = "tunic_sword_south"
                            RenderableStorage.push_to_renderer(key=self._current_renderable_name)
                            # print(f"pushed {self._current_renderable_name}")

                            RenderableStorage.get_renderable_or_none(key=self._current_renderable_name).start_animation()

                            self.__offset["tunic"].x = -self.__data["tunic"]["animation"]["sword"]["directions"][3][
                                "origin_x"]
                            self.__offset["tunic"].y = -self.__data["tunic"]["animation"]["sword"]["directions"][3][
                                "origin_y"]

                        if self.__current_sword_name != "sword_sword_south":
                            if self.__current_sword_name is not None:
                                RenderableStorage.pull_from_renderer(key=self.__current_sword_name)
                            self.__current_sword_name = "sword_sword_south"
                            RenderableStorage.push_to_renderer(key=self.__current_sword_name)
                            RenderableStorage.get_renderable_or_none(key=self.__current_sword_name).start_animation()

                            self.__offset["sword"].x = -self.__data["sword"]["animation"]["sword"]["directions"][3][
                                "origin_x"]
                            self.__offset["sword"].y = -self.__data["sword"]["animation"]["sword"]["directions"][3][
                                "origin_y"]
                    elif self.__has_shield:
                        if self._current_renderable_name != "tunic_stopped_with_shield_south":
                            if self._current_renderable_name is not None:
                                RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                            self._current_renderable_name = "tunic_stopped_with_shield_south"
                            RenderableStorage.push_to_renderer(key=self._current_renderable_name)
                            # print(f"pushed {self._current_renderable_name}")

                            self.__offset["tunic"].x = - \
                                self.__data["tunic"]["animation"]["stopped_with_shield"]["directions"][3][
                                    "origin_x"]
                            self.__offset["tunic"].y = - \
                                self.__data["tunic"]["animation"]["stopped_with_shield"]["directions"][3][
                                    "origin_y"]

                        if self.__current_shield_name != "shield_stopped_south":
                            if self.__current_shield_name is not None:
                                RenderableStorage.pull_from_renderer(key=self.__current_shield_name)
                            self.__current_shield_name = "shield_stopped_south"
                            RenderableStorage.push_to_renderer(key=self.__current_shield_name)

                            self.__offset["shield"].x = -self.__data["shield"]["animation"]["stopped"]["directions"][3][
                                "origin_x"]
                            self.__offset["shield"].y = -self.__data["shield"]["animation"]["stopped"]["directions"][3][
                                "origin_y"]
                    else:
                        if self._current_renderable_name != "tunic_stopped_south":
                            if self._current_renderable_name is not None:
                                RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                            self._current_renderable_name = "tunic_stopped_south"
                            RenderableStorage.push_to_renderer(key=self._current_renderable_name)
                            # print(f"pushed {self._current_renderable_name}")

                            self.__offset["tunic"].x = -self.__data["tunic"]["animation"]["stopped"]["directions"][3][
                                "origin_x"]
                            self.__offset["tunic"].y = -self.__data["tunic"]["animation"]["stopped"]["directions"][3][
                                "origin_y"]
                else:
                    if self.__has_shield:
                        if self._current_renderable_name != "tunic_walking_with_shield_south":
                            if self._current_renderable_name is not None:
                                RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                            self._current_renderable_name = "tunic_walking_with_shield_south"
                            RenderableStorage.push_to_renderer(key=self._current_renderable_name)
                            # print(f"pushed {self._current_renderable_name}")

                            RenderableStorage.get_renderable_or_none(key=self._current_renderable_name).start_animation()

                            self.__offset["tunic"].x = - \
                                self.__data["tunic"]["animation"]["walking_with_shield"]["directions"][3][
                                    "origin_x"]
                            self.__offset["tunic"].y = - \
                                self.__data["tunic"]["animation"]["walking_with_shield"]["directions"][3][
                                    "origin_y"]

                        if self.__current_shield_name != "shield_walking_south":
                            if self.__current_shield_name is not None:
                                RenderableStorage.pull_from_renderer(key=self.__current_shield_name)
                            self.__current_shield_name = "shield_walking_south"
                            RenderableStorage.push_to_renderer(key=self.__current_shield_name)

                            self.__offset["shield"].x = -self.__data["shield"]["animation"]["walking"]["directions"][1][
                                "origin_x"]
                            self.__offset["shield"].y = -self.__data["shield"]["animation"]["walking"]["directions"][1][
                                "origin_y"]
                    else:
                        if self._current_renderable_name != "tunic_walking_south":
                            if self._current_renderable_name is not None:
                                RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                            self._current_renderable_name = "tunic_walking_south"
                            RenderableStorage.push_to_renderer(key=self._current_renderable_name)
                            # print(f"pushed {self._current_renderable_name}")

                            RenderableStorage.get_renderable_or_none(key=self._current_renderable_name).start_animation()

                            self.__offset["tunic"].x = -self.__data["tunic"]["animation"]["walking"]["directions"][3][
                                "origin_x"]
                            self.__offset["tunic"].y = -self.__data["tunic"]["animation"]["walking"]["directions"][3][
                                "origin_y"]
            elif self.__last_movement_input == pygame.K_LEFT:
                self.__facing_direction = eFacingDirection.WEST
                if self.__is_hurting:
                    if self._current_renderable_name != "tunic_hurt_west":
                        if self._current_renderable_name is not None:
                            RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                        self._current_renderable_name = "tunic_hurt_west"
                        RenderableStorage.push_to_renderer(key=self._current_renderable_name)
                        # RenderableStorage.get_renderable_or_none(key=self._current_renderable_name).start_animation()
                        # print(f"pushed {self._current_renderable_name}")

                        self.__offset["tunic"].x = -self.__data["tunic"]["animation"]["hurt"]["directions"][2][
                            "origin_x"]
                        self.__offset["tunic"].y = -self.__data["tunic"]["animation"]["hurt"]["directions"][2][
                            "origin_y"]
                elif is_idle:
                    if self.__is_attacking_with_sword:
                        if self._current_renderable_name != "tunic_sword_west":
                            if self._current_renderable_name is not None:
                                RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                            self._current_renderable_name = "tunic_sword_west"
                            RenderableStorage.push_to_renderer(key=self._current_renderable_name)
                            # print(f"pushed {self._current_renderable_name}")

                            RenderableStorage.get_renderable_or_none(key=self._current_renderable_name).start_animation()

                            self.__offset["tunic"].x = -self.__data["tunic"]["animation"]["sword"]["directions"][2][
                                "origin_x"]
                            self.__offset["tunic"].y = -self.__data["tunic"]["animation"]["sword"]["directions"][2][
                                "origin_y"]

                        if self.__current_sword_name != "sword_sword_west":
                            if self.__current_sword_name is not None:
                                RenderableStorage.pull_from_renderer(key=self.__current_sword_name)
                            self.__current_sword_name = "sword_sword_west"
                            RenderableStorage.push_to_renderer(key=self.__current_sword_name)
                            RenderableStorage.get_renderable_or_none(key=self.__current_sword_name).start_animation()

                            self.__offset["sword"].x = -self.__data["sword"]["animation"]["sword"]["directions"][2][
                                "origin_x"]
                            self.__offset["sword"].y = -self.__data["sword"]["animation"]["sword"]["directions"][2][
                                "origin_y"]
                    elif self.__has_shield:
                        if self._current_renderable_name != "tunic_stopped_with_shield_west":
                            if self._current_renderable_name is not None:
                                RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                            self._current_renderable_name = "tunic_stopped_with_shield_west"
                            RenderableStorage.push_to_renderer(key=self._current_renderable_name)
                            # print(f"pushed {self._current_renderable_name}")

                            self.__offset["tunic"].x = - \
                                self.__data["tunic"]["animation"]["stopped_with_shield"]["directions"][2][
                                    "origin_x"]
                            self.__offset["tunic"].y = - \
                                self.__data["tunic"]["animation"]["stopped_with_shield"]["directions"][2][
                                    "origin_y"]

                        if self.__current_shield_name != "shield_stopped_west":
                            if self.__current_shield_name is not None:
                                RenderableStorage.pull_from_renderer(key=self.__current_shield_name)
                            self.__current_shield_name = "shield_stopped_west"
                            RenderableStorage.push_to_renderer(key=self.__current_shield_name)

                            self.__offset["shield"].x = -self.__data["shield"]["animation"]["stopped"]["directions"][2][
                                "origin_x"]
                            self.__offset["shield"].y = -self.__data["shield"]["animation"]["stopped"]["directions"][2][
                                "origin_y"]
                    else:
                        if self._current_renderable_name != "tunic_stopped_west":
                            if self._current_renderable_name is not None:
                                RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                            self._current_renderable_name = "tunic_stopped_west"
                            RenderableStorage.push_to_renderer(key=self._current_renderable_name)
                            # print(f"pushed {self._current_renderable_name}")

                            self.__offset["tunic"].x = -self.__data["tunic"]["animation"]["stopped"]["directions"][2][
                                "origin_x"]
                            self.__offset["tunic"].y = -self.__data["tunic"]["animation"]["stopped"]["directions"][2][
                                "origin_y"]
                else:
                    if self.__has_shield:
                        if self._current_renderable_name != "tunic_walking_with_shield_west":
                            if self._current_renderable_name is not None:
                                RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                            self._current_renderable_name = "tunic_walking_with_shield_west"
                            RenderableStorage.push_to_renderer(key=self._current_renderable_name)
                            # print(f"pushed {self._current_renderable_name}")

                            RenderableStorage.get_renderable_or_none(key=self._current_renderable_name).start_animation()

                            self.__offset["tunic"].x = - \
                                self.__data["tunic"]["animation"]["walking_with_shield"]["directions"][2][
                                    "origin_x"]
                            self.__offset["tunic"].y = - \
                                self.__data["tunic"]["animation"]["walking_with_shield"]["directions"][2][
                                    "origin_y"]

                        if self.__current_shield_name != "shield_walking_west":
                            if self.__current_shield_name is not None:
                                RenderableStorage.pull_from_renderer(key=self.__current_shield_name)
                            self.__current_shield_name = "shield_walking_west"
                            RenderableStorage.push_to_renderer(key=self.__current_shield_name)

                            self.__offset["shield"].x = -self.__data["shield"]["animation"]["walking"]["directions"][2][
                                "origin_x"]
                            self.__offset["shield"].y = -self.__data["shield"]["animation"]["walking"]["directions"][2][
                                "origin_y"]
                    else:
                        if self._current_renderable_name != "tunic_walking_west":
                            if self._current_renderable_name is not None:
                                RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                            self._current_renderable_name = "tunic_walking_west"
                            RenderableStorage.push_to_renderer(key=self._current_renderable_name)
                            # print(f"pushed {self._current_renderable_name}")

                            RenderableStorage.get_renderable_or_none(key=self._current_renderable_name).start_animation()

                            self.__offset["tunic"].x = -self.__data["tunic"]["animation"]["walking"]["directions"][2][
                                "origin_x"]
                            self.__offset["tunic"].y = -self.__data["tunic"]["animation"]["walking"]["directions"][2][
                                "origin_y"]
            elif self.__last_movement_input == pygame.K_RIGHT:
                    self.__facing_direction = eFacingDirection.EAST
                    if self.__is_hurting:
                        if self._current_renderable_name != "tunic_hurt_east":
                            if self._current_renderable_name is not None:
                                RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                            self._current_renderable_name = "tunic_hurt_east"
                            RenderableStorage.push_to_renderer(key=self._current_renderable_name)
                            # RenderableStorage.get_renderable_or_none(
                            #     key=self._current_renderable_name).start_animation()
                            # print(f"pushed {self._current_renderable_name}")

                            self.__offset["tunic"].x = -self.__data["tunic"]["animation"]["hurt"]["directions"][0][
                                "origin_x"]
                            self.__offset["tunic"].y = -self.__data["tunic"]["animation"]["hurt"]["directions"][0][
                                "origin_y"]
                    elif is_idle:
                        if self.__is_attacking_with_sword:
                            if self._current_renderable_name != "tunic_sword_east":
                                if self._current_renderable_name is not None:
                                    RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                                self._current_renderable_name = "tunic_sword_east"
                                RenderableStorage.push_to_renderer(key=self._current_renderable_name)
                                # print(f"pushed {self._current_renderable_name}")

                                RenderableStorage.get_renderable_or_none(key=self._current_renderable_name).start_animation()

                                self.__offset["tunic"].x = -self.__data["tunic"]["animation"]["sword"]["directions"][0][
                                    "origin_x"]
                                self.__offset["tunic"].y = -self.__data["tunic"]["animation"]["sword"]["directions"][0][
                                    "origin_y"]

                            if self.__current_sword_name != "sword_sword_east":
                                if self.__current_sword_name is not None:
                                    RenderableStorage.pull_from_renderer(key=self.__current_sword_name)
                                self.__current_sword_name = "sword_sword_east"
                                RenderableStorage.push_to_renderer(key=self.__current_sword_name)
                                RenderableStorage.get_renderable_or_none(key=self.__current_sword_name).start_animation()

                                self.__offset["sword"].x = -self.__data["sword"]["animation"]["sword"]["directions"][0][
                                    "origin_x"]
                                self.__offset["sword"].y = -self.__data["sword"]["animation"]["sword"]["directions"][0][
                                    "origin_y"]
                        elif self.__has_shield:
                            if self._current_renderable_name != "tunic_stopped_with_shield_east":
                                if self._current_renderable_name is not None:
                                    RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                                self._current_renderable_name = "tunic_stopped_with_shield_east"
                                RenderableStorage.push_to_renderer(key=self._current_renderable_name)
                                # print(f"pushed {self._current_renderable_name}")

                                self.__offset["tunic"].x = - \
                                    self.__data["tunic"]["animation"]["stopped_with_shield"]["directions"][0][
                                        "origin_x"]
                                self.__offset["tunic"].y = - \
                                    self.__data["tunic"]["animation"]["stopped_with_shield"]["directions"][0][
                                        "origin_y"]

                            if self.__current_shield_name != "shield_stopped_east":
                                if self.__current_shield_name is not None:
                                    RenderableStorage.pull_from_renderer(key=self.__current_shield_name)
                                self.__current_shield_name = "shield_stopped_east"
                                RenderableStorage.push_to_renderer(key=self.__current_shield_name)

                                self.__offset["shield"].x = -self.__data["shield"]["animation"]["stopped"]["directions"][0][
                                    "origin_x"]
                                self.__offset["shield"].y = -self.__data["shield"]["animation"]["stopped"]["directions"][0][
                                    "origin_y"]
                        else:
                            if self._current_renderable_name != "tunic_stopped_east":
                                if self._current_renderable_name is not None:
                                    RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                                self._current_renderable_name = "tunic_stopped_east"
                                RenderableStorage.push_to_renderer(key=self._current_renderable_name)
                                # print(f"pushed {self._current_renderable_name}")

                                self.__offset["tunic"].x = -self.__data["tunic"]["animation"]["stopped"]["directions"][0][
                                    "origin_x"]
                                self.__offset["tunic"].y = -self.__data["tunic"]["animation"]["stopped"]["directions"][0][
                                    "origin_y"]
                    else:
                        if self.__has_shield:
                            if self._current_renderable_name != "tunic_walking_with_shield_east":
                                if self._current_renderable_name is not None:
                                    RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                                self._current_renderable_name = "tunic_walking_with_shield_east"
                                RenderableStorage.push_to_renderer(key=self._current_renderable_name)
                                # print(f"pushed {self._current_renderable_name}")

                                RenderableStorage.get_renderable_or_none(key=self._current_renderable_name).start_animation()

                                self.__offset["tunic"].x = - \
                                    self.__data["tunic"]["animation"]["walking_with_shield"]["directions"][0][
                                        "origin_x"]
                                self.__offset["tunic"].y = - \
                                    self.__data["tunic"]["animation"]["walking_with_shield"]["directions"][0][
                                        "origin_y"]

                            if self.__current_shield_name != "shield_walking_east":
                                if self.__current_shield_name is not None:
                                    RenderableStorage.pull_from_renderer(key=self.__current_shield_name)
                                self.__current_shield_name = "shield_walking_east"
                                RenderableStorage.push_to_renderer(key=self.__current_shield_name)
                                RenderableStorage.get_renderable_or_none(key=self.__current_shield_name).start_animation()

                                self.__offset["shield"].x = -self.__data["shield"]["animation"]["walking"]["directions"][0][
                                    "origin_x"]
                                self.__offset["shield"].y = -self.__data["shield"]["animation"]["walking"]["directions"][0][
                                    "origin_y"]
                        else:
                            if self._current_renderable_name != "tunic_walking_east":
                                if self._current_renderable_name is not None:
                                    RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
                                self._current_renderable_name = "tunic_walking_east"
                                RenderableStorage.push_to_renderer(key=self._current_renderable_name)
                                # print(f"pushed {self._current_renderable_name}")

                                RenderableStorage.get_renderable_or_none(key=self._current_renderable_name).start_animation()

                                self.__offset["tunic"].x = -self.__data["tunic"]["animation"]["walking"]["directions"][0][
                                    "origin_x"]
                                self.__offset["tunic"].y = -self.__data["tunic"]["animation"]["walking"]["directions"][0][
                                    "origin_y"]

    def update_movement(self):
        if self.__is_attacking_with_sword or self.__is_hurting:
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
                        self.__facing_vector.x = 0.0
                        self.__facing_vector.y = -1.0
                    elif self.__movement_input_stack[-1] == pygame.K_DOWN:
                        self.__direction.x = 0.0
                        self.__direction.y = 1.0
                        self.__facing_vector.x = 0.0
                        self.__facing_vector.y = 1.0
                    elif self.__movement_input_stack[-1] == pygame.K_LEFT:
                        self.__direction.x = -1.0
                        self.__direction.y = 0.0
                        self.__facing_vector.x = -1.0
                        self.__facing_vector.y = 0.0
                    elif self.__movement_input_stack[-1] == pygame.K_RIGHT:
                        self.__direction.x = 1.0
                        self.__direction.y = 0.0
                        self.__facing_vector.x = 1.0
                        self.__facing_vector.y = 0.0
                    break
