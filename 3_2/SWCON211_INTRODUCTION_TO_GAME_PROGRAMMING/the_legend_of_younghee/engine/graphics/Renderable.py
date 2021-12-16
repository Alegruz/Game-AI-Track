from typing import IO, Union

import pygame

from engine.core.Math import Math, Vector2f
from engine.graphics.Orientation import Orientation


class Renderable:
    __slots__ = ["__surface",
                 "__coordinate",
                 "__depth",
                 "__name",
                 "__frames",
                 "__coordinates",
                 "__should_fade_out",
                 "__should_fade_in",
                 "__fade_duration",
                 "__fade_counter",
                 "__should_move",
                 "__from_coordinate",
                 "__to_coordinate",
                 "__move_duration",
                 "__move_counter",
                 "__should_animate",
                 "__should_loop_animation",
                 "__frame_index",
                 "__from_frame_index",
                 "__to_frame_index",
                 "__animation_duration",
                 "__animation_counter",
                 "__should_change_coordinates",
                 "__should_loop_coordinates_change",
                 "__coordinates_index",
                 "__coordinates_change_counter",
                 "__coordinates_change_duration",
                 "__flip_x",
                 "__flip_y",
                 "__is_animation_done"]

    def __init__(self, surface: pygame.Surface, coordinate: Vector2f, depth: int, name: str = "",
                 surfaces: list[pygame.Surface] = None, coordinates: list[Vector2f] = None,
                 orientation: int = Orientation.TOP_LEFT):
        assert isinstance(surface, pygame.Surface)
        assert isinstance(coordinate, Vector2f)
        assert isinstance(depth, int)
        assert isinstance(name, str)
        assert (isinstance(surfaces, list) and len(surfaces) > 1 and isinstance(surfaces[0],
                                                                                pygame.Surface)) or surfaces is None
        assert (isinstance(coordinates, list) and len(coordinates) > 1 and isinstance(coordinates[0],
                                                                                      Vector2f)) or coordinates is None
        assert isinstance(orientation, int) and (Orientation.TOP_LEFT <= orientation <= Orientation.BOTTOM_RIGHT)

        self.__surface: pygame.Surface = surface
        self.__coordinate: Vector2f = coordinate
        self.__depth: int = depth
        self.__name: str = name
        self.__frames: list[pygame.Surface] = surfaces
        self.__coordinates: list[Vector2f] = coordinates

        self.__should_fade_out: bool = False
        self.__should_fade_in: bool = False
        self.__fade_duration: int = 0
        self.__fade_counter: int = 0

        self.__should_move: bool = False
        self.__from_coordinate: Vector2f = Vector2f(x=self.__coordinate.x, y=self.__coordinate.y)
        self.__to_coordinate: Vector2f = Vector2f(x=self.__coordinate.x, y=self.__coordinate.y)
        self.__move_duration: int = 0
        self.__move_counter: int = 0

        self.__should_animate: bool = False
        self.__should_loop_animation: bool = False
        self.__is_animation_done: bool = False
        self.__frame_index: int = 0
        self.__from_frame_index: int = 0
        self.__to_frame_index: int = 0
        self.__animation_duration: int = 0
        self.__animation_counter: int = 0

        self.__should_change_coordinates: bool = False
        self.__should_loop_coordinates_change: bool = False
        self.__coordinates_index: int = 0
        self.__coordinates_change_counter: int = 0
        self.__coordinates_change_duration: int = 0

        self.__flip_x: bool = False
        self.__flip_y: bool = False

    def __del__(self):
        pass
        # print(f"Renderable::Destructor: {self.__name} {id(self.__coordinate)}")

    #     if self.__surface is not None:
    #         del self.__surface

    @staticmethod
    def parse_data(file_path: str) -> dict[str, dict[str, dict[str, Union[list[dict[str, int]], str, int]]]]:
        animation_data: IO = open(file=file_path, mode="r")

        data: dict[str, dict[str, dict[str, Union[list[dict[str, int]], str, int]]]] = dict()

        is_animation_data: bool = False
        is_direction_data: bool = False
        data_key: str = ""
        data_name: str = ""
        direction_index: int = -1
        for line in animation_data:
            if "animation" in line:
                is_animation_data = True
                data_key = "animation"
                if data_key not in data:
                    data["animation"] = dict()
            else:
                if is_animation_data:
                    splitted_line: list[str] = line.split()
                    if not is_direction_data:
                        if splitted_line[0] == "name":
                            data_name = splitted_line[-1][1:-2]
                            data[data_key][data_name] = dict()
                        elif splitted_line[0] == "directions":
                            is_direction_data = True
                            direction_index = 0
                            data[data_key][data_name][splitted_line[0]] = []
                        elif splitted_line[-1][0] == "\"":
                            data[data_key][data_name][splitted_line[0]] = splitted_line[-1][1:-2]
                        else:
                            data[data_key][data_name][splitted_line[0]] = int(splitted_line[-1][:-1])
                    else:
                        if len(splitted_line) == 1:
                            is_animation_data = False
                            is_direction_data = False
                            continue
                        is_next_data_key: bool = True
                        key: str = ""
                        is_next_data_value: bool = False
                        data[data_key][data_name]["directions"].append(dict())
                        for parsed_data in splitted_line:
                            if parsed_data == "{" or parsed_data == "}," or parsed_data == "=":
                                continue
                            if is_next_data_key:
                                key = parsed_data
                                is_next_data_key = False
                                is_next_data_value = True
                            elif is_next_data_value:
                                if parsed_data[-1] == ",":
                                    data[data_key][data_name]["directions"][direction_index][key] = int(
                                        parsed_data[:-1])
                                else:
                                    data[data_key][data_name]["directions"][direction_index][key] = int(parsed_data)
                                is_next_data_key = True
                                is_next_data_value = False

                        direction_index += 1

        return data

    @property
    def coordinate(self) -> Vector2f:
        return self.__coordinate

    @property
    def coordinates(self) -> list[Vector2f]:
        return self.__coordinates

    @property
    def depth(self) -> int:
        return self.__depth

    @property
    def flip_x(self) -> bool:
        return self.__flip_x

    @property
    def flip_y(self) -> bool:
        return self.__flip_y

    @property
    def is_animation_done(self) -> bool:
        return self.__is_animation_done

    @property
    def name(self) -> str:
        return self.__name

    @property
    def should_loop_animation(self) -> bool:
        return self.__should_loop_animation

    @property
    def surface(self) -> pygame.Surface:
        return self.__surface

    @coordinate.setter
    def coordinate(self, in_coordinate: Vector2f) -> None:
        assert isinstance(in_coordinate, Vector2f)
        self.__coordinate.copy(other=in_coordinate)

    @depth.setter
    def depth(self, in_depth: int) -> None:
        assert isinstance(in_depth, int)
        self.__depth = in_depth

    @flip_x.setter
    def flip_x(self, value: bool) -> None:
        assert isinstance(value, bool)
        self.__flip_x = value

    @flip_y.setter
    def flip_y(self, value: bool) -> None:
        assert isinstance(value, bool)
        self.__flip_y = value

    def hide(self):
        self.__surface.set_alpha(0)

    def reset_animation(self):
        self.__should_animate = True
        self.__frame_index = self.__from_frame_index
        self.__is_animation_done = False
        self.__animation_counter = 0

    def set_animation_data(self, from_frame_index: int, to_frame_index: int, duration: int, should_loop: bool = False):
        assert (self.__frames is not None)
        assert isinstance(from_frame_index, int)
        assert isinstance(to_frame_index, int)
        assert isinstance(duration, int) and duration > 0
        assert isinstance(should_loop, bool)

        self.__should_loop_animation = should_loop
        self.__from_frame_index = from_frame_index
        self.__to_frame_index = to_frame_index
        self.__animation_duration = duration
        self.__animation_counter = 0

    def show(self):
        self.__surface.set_alpha(255)

    def start_animation(self, from_frame_index: int = -1, to_frame_index: int = -1, duration: int = -1,
                        should_loop: bool = False):
        # print(f"play animation of {self.__name}. {self.__from_frame_index} ~ {self.__to_frame_index}")
        assert (self.__frames is not None)
        assert isinstance(from_frame_index, int)
        assert isinstance(to_frame_index, int)
        assert isinstance(duration, int)
        assert isinstance(should_loop, bool)


        self.__should_animate = True
        if duration > 0:
            self.__should_loop_animation = should_loop
            if from_frame_index < 0:
                self.__from_frame_index = 0
            else:
                self.__from_frame_index = from_frame_index

            if to_frame_index < 0:
                self.__to_frame_index = len(self.__frames) - 1
            else:
                self.__to_frame_index = to_frame_index
            self.__animation_duration = duration
            self.__animation_counter = 0

    def start_coordinate_change(self, duration: int, should_loop: bool = False):
        assert (self.__coordinates is not None)
        assert isinstance(duration, int) and duration > 0
        assert isinstance(should_loop, bool)

        self.__should_change_coordinates = True
        self.__should_loop_coordinates_change = should_loop
        self.__coordinates_change_counter = 0
        self.__coordinates_change_duration = duration

    def start_move(self, from_coordinate: Vector2f, to_coordinate: Vector2f, duration: int):
        assert isinstance(from_coordinate, Vector2f)
        assert isinstance(to_coordinate, Vector2f)
        assert isinstance(duration, int) and duration > 0

        self.__should_move = True
        self.__from_coordinate.copy(other=from_coordinate)
        self.__to_coordinate.copy(other=to_coordinate)
        self.__move_duration = duration
        self.__move_counter = 0

    def start_fade_out(self, duration: int) -> None:
        assert isinstance(duration, int) and duration > 0

        self.__should_fade_out = True
        self.__should_fade_in = False
        self.__fade_duration = duration
        self.__fade_counter = 0

    def start_fade_in(self, duration: int) -> None:
        assert isinstance(duration, int) and duration > 0

        self.__should_fade_out = False
        self.__should_fade_in = True
        self.__fade_duration = duration
        self.__fade_counter = 0

    def stop_coordinate_change(self):
        self.__should_change_coordinates = False
        self.__should_loop_coordinates_change = False
        self.__coordinates_change_counter = 0
        self.__coordinates_change_duration = 0

    def update(self, delta_time: float) -> None:
        if self.__should_fade_out:
            self.__fade_counter += delta_time
            self.__surface.set_alpha(
                int(Math.lerp_float(x=255.0,
                                    y=0.0,
                                    alpha=min(self.__fade_counter / self.__fade_duration, 1.0))))
            self.__should_fade_out = self.__fade_counter < self.__fade_duration
            assert ((not self.__should_fade_out) == (self.__surface.get_alpha() == 0),
                    f"{self.__fade_counter} < {self.__fade_duration} = {self.__should_fade_out} {self.__surface.get_alpha()}")

        if self.__should_fade_in:
            self.__fade_counter += delta_time
            self.__surface.set_alpha(
                int(Math.lerp_float(x=0.0,
                                    y=255.0,
                                    alpha=min(self.__fade_counter / self.__fade_duration, 1.0))))

            self.__should_fade_in = self.__fade_counter < self.__fade_duration
            assert ((not self.__should_fade_in) == (self.__surface.get_alpha() == 255))

        if self.__should_move:
            self.__move_counter += delta_time
            # self.__coordinate = Math.lerp_vectors(coord0=self.__from_coordinate,
            #                                       coord1=self.__to_coordinate,
            #                                       alpha=min(self.__move_counter / self.__move_duration, 1.0))
            self.__coordinate.lerp(coord0=self.__from_coordinate,
                                   coord1=self.__to_coordinate,
                                   alpha=min(self.__move_counter / self.__move_duration, 1.0))
            # if self.__name == "title_screen_sword":
            #     print(f"moving coord: {self.__coordinate}")
            assert isinstance(self.__coordinate, Vector2f)
            self.__should_move = self.__move_counter < self.__move_duration
            assert ((not self.__should_move) == (self.__coordinate == self.__to_coordinate))

        if self.__should_animate:
            self.__animation_counter += delta_time
            self.__frame_index = int(Math.lerp_float(x=self.__from_frame_index,
                                                     y=self.__to_frame_index,
                                                     alpha=min(self.__animation_counter / self.__animation_duration,
                                                               1.0)))
            if not self.__should_loop_animation:
                self.__should_animate = self.__animation_counter < self.__animation_duration and \
                                        self.__frame_index <= self.__to_frame_index
                assert ((not self.__should_animate) == (self.__frame_index == self.__to_frame_index))
            else:
                if self.__animation_counter > self.__animation_duration or self.__frame_index > self.__to_frame_index:
                    self.__animation_counter -= self.__animation_duration
                    self.__frame_index = max(self.__from_frame_index, self.__frame_index - self.__to_frame_index)

            if self.__should_animate:
                self.__surface = pygame.transform.flip(surface=self.__frames[self.__frame_index],
                                                       flip_x=self.__flip_x,
                                                       flip_y=self.__flip_y)
            else:
                self.__is_animation_done = True

        if self.__should_change_coordinates:
            self.__coordinates_change_counter += delta_time
            self.__coordinates_index = int(
                self.__coordinates_change_counter / self.__coordinates_change_duration)
            if self.__coordinates_index < len(self.__coordinates):
                self.__coordinate.x = self.__coordinates[self.__coordinates_index].x - self.__surface.get_width() / 2.0
                self.__coordinate.y = self.__coordinates[self.__coordinates_index].y - self.__surface.get_height() / 2.0
            else:
                self.__surface.set_alpha(0)
                if self.__coordinates_index >= 3 * len(self.__coordinates) or \
                        self.__coordinates_change_counter >= len(
                    self.__coordinates) * self.__coordinates_change_duration:
                    self.__coordinates_change_counter -= len(self.__coordinates) * self.__coordinates_change_duration
                    self.__surface.set_alpha(255)

            if not self.__should_loop_coordinates_change:
                self.__should_change_coordinates = self.__coordinates_change_counter < self.__coordinates_change_duration
                assert ((not self.__should_loop_coordinates_change) == (
                            self.__coordinates_index == len(self.__coordinates)))
            # else:
            #     if self.__coordinates_change_counter >= len(self.__coordinates) * self.__coordinates_change_duration:
            #         self.__coordinates_change_counter -= len(self.__coordinates) * self.__coordinates_change_duration
