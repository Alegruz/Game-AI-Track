from __future__ import annotations
from enum import Enum
from typing import Union

import pygame

from engine.core.Math import Vector2f, Box
from engine.graphics.Renderable import Renderable
from engine.resources.RenderableStorage import RenderableStorage


class eGroundType(Enum):
    EMPTY = 0
    WALL = 1
    LOW_WALL = 2
    WALL_BOTTOM_LEFT = 3
    WALL_BOTTOM_RIGHT = 4
    WALL_TOP_LEFT = 5
    WALL_TOP_RIGHT = 6
    TRAVERSABLE = 7
    HOLE = 8
    LAVA = 9
    PRICKLES = 10
    LADDER = 11
    DEEP_WATER = 12
    SHALLOW_WATER = 13
    ICE = 14
    GRASS = 15
    WALL_TOP_LEFT_WATER = 16
    WALL_TOP_RIGHT_WATER = 17
    WALL_BOTTOM_LEFT_WATER = 18
    WALL_BOTTOM_RIGHT_WATER = 19

    @staticmethod
    def ground_type_to_str(ground_type: eGroundType) -> str:
        if ground_type == eGroundType.EMPTY:
            return "empty"
        elif ground_type == eGroundType.WALL:
            return "wall"
        elif ground_type == eGroundType.LOW_WALL:
            return "low_wall"
        elif ground_type == eGroundType.WALL_BOTTOM_LEFT:
            return "wall_bottom_left"
        elif ground_type == eGroundType.WALL_BOTTOM_RIGHT:
            return "wall_bottom_right"
        elif ground_type == eGroundType.WALL_TOP_LEFT:
            return "wall_top_left"
        elif ground_type == eGroundType.WALL_TOP_RIGHT:
            return "wall_top_right"
        elif ground_type == eGroundType.TRAVERSABLE:
            return "traversable"
        elif ground_type == eGroundType.HOLE:
            return "hole"
        elif ground_type == eGroundType.LAVA:
            return "lava"
        elif ground_type == eGroundType.PRICKLES:
            return "prickles"
        elif ground_type == eGroundType.LADDER:
            return "ladder"
        elif ground_type == eGroundType.DEEP_WATER:
            return "deep_water"
        elif ground_type == eGroundType.SHALLOW_WATER:
            return "shallow_water"
        elif ground_type == eGroundType.ICE:
            return "ice"
        elif ground_type == eGroundType.GRASS:
            return "grass"
        elif ground_type == eGroundType.WALL_TOP_LEFT_WATER:
            return "wall_top_left_water"
        elif ground_type == eGroundType.WALL_TOP_RIGHT_WATER:
            return "wall_top_right_water"
        elif ground_type == eGroundType.WALL_BOTTOM_LEFT_WATER:
            return "wall_bottom_left_water"
        elif ground_type == eGroundType.WALL_BOTTOM_RIGHT_WATER:
            return "wall_bottom_right_water"
        else:
            assert False

    @staticmethod
    def str_to_ground_type(key: str) -> eGroundType:
        if key == "empty":
            return eGroundType.EMPTY
        elif key == "wall":
            return eGroundType.WALL
        elif key == "low_wall":
            return eGroundType.LOW_WALL
        elif key == "wall_bottom_left":
            return eGroundType.WALL_BOTTOM_LEFT
        elif key == "wall_bottom_right":
            return eGroundType.WALL_BOTTOM_RIGHT
        elif key == "wall_top_left":
            return eGroundType.WALL_TOP_LEFT
        elif key == "wall_top_right":
            return eGroundType.WALL_TOP_RIGHT
        elif key == "traversable":
            return eGroundType.TRAVERSABLE
        elif key == "hole":
            return eGroundType.HOLE
        elif key == "lava":
            return eGroundType.LAVA
        elif key == "prickles":
            return eGroundType.PRICKLES
        elif key == "ladder":
            return eGroundType.LADDER
        elif key == "deep_water":
            return eGroundType.DEEP_WATER
        elif key == "shallow_water":
            return eGroundType.SHALLOW_WATER
        elif key == "ice":
            return eGroundType.ICE
        elif key == "grass":
            return eGroundType.GRASS
        elif key == "wall_top_left_water":
            return eGroundType.WALL_TOP_LEFT_WATER
        elif key == "wall_top_right_water":
            return eGroundType.WALL_TOP_RIGHT_WATER
        elif key == "wall_bottom_left_water":
            return eGroundType.WALL_BOTTOM_LEFT_WATER
        elif key == "wall_bottom_right_water":
            return eGroundType.WALL_BOTTOM_RIGHT_WATER
        else:
            print(f"wrong key: {key}")
            assert False

    @staticmethod
    def is_walkable(ground_type: eGroundType):
        return ground_type == eGroundType.TRAVERSABLE or \
               ground_type == eGroundType.EMPTY or \
               ground_type == eGroundType.LADDER


class eRepeatMode(Enum):
    NONE = 0
    HORIZONTAL = 1
    VERTICAL = 2

    @staticmethod
    def str_to_repeat_mode(key: str) -> eRepeatMode:
        if key == "none":
            return eRepeatMode.NONE
        elif key == "horizontal":
            return eRepeatMode.HORIZONTAL
        elif key == "vertical":
            return eRepeatMode.VERTICAL
        else:
            print(f"wrong key: {key}")
            assert False


class Tile:
    __slots__ = ["__id", "__ground", "__default_layer", "__renderable", "__repeat_mode"]

    def __init__(self, tile_id: str, ground: Union[str, eGroundType], default_layer: int,
                 repeat_mode: Union[str, eRepeatMode] = eRepeatMode.NONE):
        assert isinstance(tile_id, str) and (isinstance(ground, str) or isinstance(ground, eGroundType))
        assert isinstance(default_layer, int) and (isinstance(repeat_mode, str) or isinstance(repeat_mode, eRepeatMode))

        self.__id: str = tile_id
        if isinstance(ground, str):
            self.__ground: eGroundType = eGroundType.str_to_ground_type(key=ground)
        else:
            self.__ground: eGroundType = ground
        self.__default_layer: int = default_layer
        self.__renderable: Renderable = None
        if isinstance(repeat_mode, str):
            self.__repeat_mode: eRepeatMode = eRepeatMode.str_to_repeat_mode(key=repeat_mode)
        else:
            self.__repeat_mode: eRepeatMode = repeat_mode

    @staticmethod
    def create_tile_from_data(id: str, data: dict[str, Union[str, int, list[int]]], resource: pygame.Surface) -> Tile:
        tile: Tile = Tile(tile_id=id,
                          ground=data["ground"],
                          default_layer=data["default_layer"],
                          repeat_mode=data["repeat_mode"] if "repeat_mode" in data else eRepeatMode.NONE)
        assert isinstance(data["x"], int)

        try:
            rect: pygame.Rect = pygame.Rect(data["x"], data["y"], data["width"], data["height"])
            tile.__renderable = Renderable(surface=resource.subsurface(rect),
                                           coordinate=Vector2f(x=0.0, y=0.0),
                                           depth=tile.__default_layer,
                                           name=tile.__id)
        except ValueError:
            print(f'rect: {data["x"]}, {data["y"]}, width: {data["width"]}, height: {data["height"]}')
            print(f"tile id: {tile.__id}")
            # assert False

        return tile

    @staticmethod
    def create_tiles_from_data(id: str, data: dict[str, Union[str, int, list[int]]], resource: pygame.Surface) -> list[
        Tile]:
        tiles: list[Tile] = []
        assert isinstance(data["x"], list)

        for i in range(0, len(data["x"])):
            tile: Tile = Tile(tile_id=f"{id}_{i}",
                              ground=data["ground"],
                              default_layer=data["default_layer"],
                              repeat_mode=data["repeat_mode"] if "repeat_mode" in data else eRepeatMode.NONE)
            rect: pygame.Rect = pygame.Rect(data["x"][i], data["y"][i], data["width"], data["height"])
            tile.__renderable = Renderable(surface=resource.subsurface(rect),
                                           coordinate=Vector2f(x=0.0, y=0.0),
                                           depth=tile.__default_layer,
                                           name=tile.__id)
            RenderableStorage.add_renderable(renderable=tile.__renderable)
            tiles.append(tile)

        return tiles

    @property
    def id(self) -> str:
        return self.__id

    @property
    def ground(self) -> eGroundType:
        return self.__ground

    @property
    def renderable(self) -> Renderable:
        return self.__renderable

    def __del__(self):
        if self.__renderable is not None:
            RenderableStorage.remove_renderable(key=self.__renderable.name)
