from __future__ import annotations

from engine.core.Math import Vector2f, Box
from engine.object.BaseObject import BaseObject


class CollidableObject(BaseObject):
    __slots__ = ["_collision_box"]

    def __init__(self, coordinate: Vector2f, width: float, height: float):
        super().__init__(coordinate)

        self._collision_box: Box = Box(top_left=coordinate, width=width, height=height)

    def has_collided_with(self, other: CollidableObject):
        assert issubclass(other.__class__, CollidableObject)
        return self._collision_box.has_collided_with(box=other._collision_box)

    def on_collision_with(self, other: CollidableObject):
        assert issubclass(other.__class__, CollidableObject)