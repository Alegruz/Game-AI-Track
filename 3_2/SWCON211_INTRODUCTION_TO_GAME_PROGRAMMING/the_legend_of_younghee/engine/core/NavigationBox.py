from __future__ import annotations

import sys

import pygame

from engine.core.Math import Box, Vector2f
from engine.graphics.Renderable import Renderable
from engine.graphics.Renderer import Depth
from engine.resources.RenderableStorage import RenderableStorage


class Neighbor:
    __slots__ = ["__box", "distance"]

    def __init__(self, box: Box, distance: float):
        self.__box: Box = box
        self.distance: float = distance

    @property
    def box(self) -> Box:
        return self.__box


class NavigationBox(Box):
    __slots__ = ["__neighbors", "__distance_from_start", "__remaining_estimated_distance_to_end", "__center", "__end"]

    def __init__(self, top_left: Vector2f, width: float, height: float, end: NavigationBox = None):
        super().__init__(top_left, width, height)

        self.__neighbors: list[Neighbor] = []
        self.__end: NavigationBox = end
        self.__center: Vector2f = Vector2f(x=top_left.x + width / 2.0,
                                           y=top_left.y + height / 2.0)

        self.__distance_from_start: float = sys.float_info.max
        self.__remaining_estimated_distance_to_end: float = sys.float_info.max

        # debug_bounding_box: pygame.Surface = pygame.Surface(size=(self.width,
        #                                                           self.height))
        # RenderableStorage.add_surface(key=f"{id(self)}_debug_bounding_box", surface=debug_bounding_box)
        # debug_bounding_box.fill(color=pygame.Color(255, 255, 255))
        # debug_bounding_box.set_alpha(128)
        # # if self is GlobalConstants.get_constant_or_non(key="player"):
        # #     print(self._coordinates)
        #
        # RenderableStorage.add_renderable(renderable=Renderable(surface=debug_bounding_box,
        #                                                        coordinate=self.top_left,
        #                                                        depth=Depth.DEBUG_DEPTH,
        #                                                        name=f"{id(self)}_debug_bounding_box"))

    def __del__(self):
        # RenderableStorage.pull_from_renderer(key=f"{id(self)}_debug_bounding_box")
        # RenderableStorage.remove_renderable(key=f"{id(self)}_debug_bounding_box")
        pass

    @property
    def center(self) -> Vector2f:
        return self.__center

    @property
    def distance_from_start(self) -> float:
        return self.__distance_from_start

    @property
    def end(self) -> NavigationBox:
        return self.__end

    @property
    def neighbors(self) -> list[Neighbor]:
        return self.__neighbors

    @property
    def total_distance(self) -> float:
        if self.__distance_from_start >= sys.float_info.max:
            return sys.float_info.max
        return self.__distance_from_start + self.__remaining_estimated_distance_to_end

    @distance_from_start.setter
    def distance_from_start(self, distance: float) -> None:
        self.__distance_from_start = distance

    @end.setter
    def end(self, end: NavigationBox) -> None:
        self.__end = end
        self.__remaining_estimated_distance_to_end = end.__center.get_distance_squared_from(other=self.__center)

    def __lt__(self, other: NavigationBox) -> bool:
        return self.total_distance < other.total_distance

    def draw_bounding_box(self) -> None:
        # GlobalConstants.get_constant_or_non(key="renderer").remove_renderable(key=f"{id(self)}")
        # RenderableStorage.push_to_renderer(key=f"{id(self)}_debug_bounding_box")
        pass

    def undraw_bounding_box(self) -> None:
        # RenderableStorage.pull_from_renderer(key=f"{id(self)}_debug_bounding_box")
        pass
