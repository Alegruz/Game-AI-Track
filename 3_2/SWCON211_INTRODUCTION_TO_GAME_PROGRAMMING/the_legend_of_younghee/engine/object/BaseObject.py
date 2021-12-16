from __future__ import annotations

from enum import Enum

from engine.core.Math import Vector2f, Box
from engine.resources.RenderableStorage import RenderableStorage


class eFacingDirection(Enum):
    EAST = 0
    NORTH = 1
    WEST = 2
    SOUTH = 3


class BaseObject:
    __slots__ = ["_coordinates", "_renderable_names", "_current_renderable_name"]

    def __init__(self, coordinate: Vector2f):
        self._coordinates: Vector2f = Vector2f(x=coordinate.x, y=coordinate.y)
        self._renderable_names: set[str] = set()
        self._current_renderable_name: str = None

    def __del__(self):
        self.destroy()
        # print(f"BaseObject::Destructor: {self}, {id(self)}")

    @property
    def coordinate(self) -> Vector2f:
        return self._coordinates

    @coordinate.setter
    def coordinate(self, coordinate: Vector2f) -> None:
        self._coordinates.copy(other=coordinate)

    def copy(self, other: BaseObject):
        pass

    def initialize(self):
        pass

    def destroy(self):
        for renderable_name in self._renderable_names:
            RenderableStorage.pull_from_renderer(key=renderable_name)
            print(renderable_name)
            RenderableStorage.remove_renderable(key=renderable_name)
            RenderableStorage.remove_surface(key=renderable_name)


    def on_print_coord(self):
        print(f"{id(self)}: {self._coordinates}")

    def update(self, delta_time: float):
        pass
