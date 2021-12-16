from __future__ import annotations
from typing import Union

import pygame.mixer

from engine.components.Component import RenderableComponent
from engine.core.GlobalConstants import GlobalConstants
from engine.core.Math import Vector2f
from engine.graphics.Orientation import Orientation
from engine.graphics.Renderable import Renderable
from engine.object.CollidableObject import CollidableObject
from engine.resources.RenderableStorage import RenderableStorage


class DestructibleObject(CollidableObject):
    __slots__ = ["__can_be_cut", "__destruction_sound", "__data", "__offset", "__depth", "__name",
                 "__unique_name"]

    def __init__(self, coordinate: Vector2f, width: float, height: float, can_be_cut: bool,
                 sprite_data_file: str, depth: int, name: str, destruction_sound: pygame.mixer.Sound = None):
        super().__init__(coordinate, width, height)
        self.__name: str = name
        self.__can_be_cut: bool = can_be_cut
        self.__destruction_sound: pygame.mixer.Sound = destruction_sound
        self.__data: dict[str, dict[str, dict[str, Union[list[dict[str, int]], str, int]]]] = Renderable.parse_data(
            file_path=f"resources/sprites/{sprite_data_file}.dat")
        self.__offset: dict[str, Vector2f] = dict()
        self.__depth: int = depth

    @property
    def can_be_cut(self) -> bool:
        return self.__can_be_cut

    @property
    def destruction_sound(self) -> Union[pygame.mixer.Sound, None]:
        return self.__destruction_sound

    @property
    def name(self) -> str:
        return self.__name

    def copy(self, other: DestructibleObject):
        super(DestructibleObject, self).copy(other=other)
        self.__destruction_sound = other.destruction_sound
        self.__data = other.__data
        self.__offset = other.__offset
        self.__depth = other.__depth

    def destroy(self):
        for data_key in self.__data:
            for data_name in self.__data[data_key]:
                for attribute_key in self.__data[data_key][data_name]:
                    RenderableStorage.remove_surface(key=self.__data[data_key][data_name][attribute_key])

        super(DestructibleObject, self).destroy()

    def initialize(self):
        super().initialize()

        surfaces: [str, list[list[str, Vector2f]]] = dict()
        coordinates: [str, list[list[Vector2f]]] = dict()
        for data_key in self.__data:
            # print(f"key: {data_key}")
            for data_name in self.__data[data_key]:
                # print(f"data_name: {data_name}")
                self.__offset[data_name] = Vector2f(x=0.0, y=0.0)
                if data_name not in surfaces and data_name not in coordinates:
                    surfaces[data_name] = []
                    coordinates[data_name] = []
                for attribute_key in self.__data[data_key][data_name]:
                    if attribute_key == "src_image":
                        if not RenderableStorage.contains_surface(key=self.__data[data_key][data_name][attribute_key]):
                            RenderableStorage.add_surface(key=self.__data[data_key][data_name][attribute_key],
                                                          surface=pygame.image.load(
                                                              f"resources/sprites/{self.__data[data_key][data_name][attribute_key]}").convert_alpha())
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
                                    key=self.__data[data_key][data_name]["src_image"]
                                ).subsurface(rect))

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
                    RenderableStorage.add_renderable(renderable=Renderable(surface=surfaces[surfaces_key][0][0],
                                                                           coordinate=Vector2f(x=0.0, y=0.0),
                                                                           depth=self.__depth,
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
                    RenderableStorage.add_renderable(renderable=Renderable(surface=surfaces[surfaces_key][1][0],
                                                                           coordinate=Vector2f(x=0.0, y=0.0),
                                                                           depth=self.__depth,
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
                    RenderableStorage.add_renderable(renderable=Renderable(surface=surfaces[surfaces_key][2][0],
                                                                           coordinate=Vector2f(x=0.0, y=0.0),
                                                                           depth=self.__depth,
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
                    RenderableStorage.add_renderable(renderable=Renderable(surface=surfaces[surfaces_key][3][0],
                                                                           coordinate=Vector2f(x=0.0, y=0.0),
                                                                           depth=self.__depth,
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
                    RenderableStorage.add_renderable(renderable=Renderable(surface=surfaces[surfaces_key][0][0],
                                                                           coordinate=Vector2f(x=0.0, y=0.0),
                                                                           depth=self.__depth,
                                                                           name=f"{self.__name}_{surfaces_key}_east"))
                    RenderableStorage.add_renderable(renderable=Renderable(surface=surfaces[surfaces_key][1][0],
                                                                           coordinate=Vector2f(x=0.0, y=0.0),
                                                                           depth=self.__depth,
                                                                           name=f"{self.__name}_{surfaces_key}_north"))
                    RenderableStorage.add_renderable(renderable=Renderable(surface=surfaces[surfaces_key][2][0],
                                                                           coordinate=Vector2f(x=0.0, y=0.0),
                                                                           depth=self.__depth,
                                                                           name=f"{self.__name}_{surfaces_key}_west"))
                    RenderableStorage.add_renderable(renderable=Renderable(surface=surfaces[surfaces_key][3][0],
                                                                           coordinate=Vector2f(x=0.0, y=0.0),
                                                                           depth=self.__depth,
                                                                           name=f"{self.__name}_{surfaces_key}_south"))
            else:
                if len(surfaces[surfaces_key][0]) > 1:
                    RenderableStorage.add_renderable(renderable=Renderable(surface=surfaces[surfaces_key][0][0],
                                                                           coordinate=Vector2f(x=0.0, y=0.0),
                                                                           depth=self.__depth,
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
                    RenderableStorage.add_renderable(renderable=Renderable(surface=surfaces[surfaces_key][0][0],
                                                                           coordinate=Vector2f(x=0.0, y=0.0),
                                                                           depth=self.__depth,
                                                                           name=f"{self.__name}_{surfaces_key}"))

    def on_collision_with(self, other: CollidableObject):
        if other._is_attack:
            self.on_destroy()

    def on_destroy(self):
        RenderableStorage.pull_from_renderer(key=self._current_renderable_name)
        if self.__destruction_sound is not None:
            self.__destruction_sound.play()

    def update(self, delta_time: float):
        super(DestructibleObject, self).update(delta_time=delta_time)

        self.update_animation()

        RenderableStorage.get_renderable_or_none(key=self._current_renderable_name).coordinate = self._coordinates

    def update_animation(self):
        if self._current_renderable_name is None or \
                RenderableStorage.get_renderable_or_none(key=self._current_renderable_name) is not \
                RenderableStorage.get_renderable_or_none(key=f"{self.__name}_on_ground"):
            self._current_renderable_name = f"{self.__name}_on_ground"
            RenderableStorage.push_to_renderer(key=self._current_renderable_name)
            # print(f"renderable: {self.get_renderable_component(self.__name).renderable.name}")
            self.__offset[f"on_ground"].x = -self.__data["animation"]["on_ground"]["directions"][0]["origin_x"]
            self.__offset[f"on_ground"].y = -self.__data["animation"]["on_ground"]["directions"][0]["origin_y"]
            self._coordinates += self.__offset["on_ground"]
