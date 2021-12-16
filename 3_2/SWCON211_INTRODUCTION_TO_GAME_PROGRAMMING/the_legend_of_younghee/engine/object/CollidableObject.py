from __future__ import annotations

import pygame

from engine.core.GlobalConstants import GlobalConstants
from engine.core.Math import Vector2f, Box
from engine.core.NavigationBox import NavigationBox
from engine.graphics.Renderable import Renderable
from engine.graphics.Renderer import Depth
from engine.object.BaseObject import BaseObject
from engine.resources.RenderableStorage import RenderableStorage


class CollidableObject(BaseObject):
    __slots__ = ["_collision_box", "_is_attack", "_is_collision_enabled"]

    def __init__(self,
                 coordinate: Vector2f,
                 width: float,
                 height: float,
                 is_attack: bool = False,
                 is_collision_enabled: bool = False):
        super().__init__(coordinate)

        self._collision_box: Box = Box(top_left=coordinate, width=width, height=height)
        self._is_attack: bool = is_attack
        self._is_collision_enabled: bool = True

        debug_bounding_box: pygame.Surface = pygame.Surface(size=(self._collision_box.width,
                                                                  self._collision_box.height))
        RenderableStorage.add_surface(key=f"{id(self)}_debug_bounding_box", surface=debug_bounding_box)
        debug_bounding_box.fill(color=pygame.Color(255, 0, 255))
        debug_bounding_box.set_alpha(64)
        # if self is GlobalConstants.get_constant_or_non(key="player"):
        #     print(self._coordinates)

        top_left_coordinate: Vector2f = Vector2f(x=self._coordinates.x,
                                                 y=self._coordinates.y)
        self._collision_box.top_left.copy(other=top_left_coordinate)

        RenderableStorage.add_renderable(renderable=Renderable(surface=debug_bounding_box,
                                                               coordinate=top_left_coordinate,
                                                               depth=Depth.DEBUG_DEPTH,
                                                               name=f"{id(self)}_debug_bounding_box"))
        self._renderable_names.add(f"{id(self)}_debug_bounding_box")

    @property
    def collision_box(self) -> Box:
        return self._collision_box

    def copy(self, other: CollidableObject):
        super(CollidableObject, self).copy(other=other)

    def has_collided_with(self, other: CollidableObject):
        assert issubclass(other.__class__, CollidableObject)
        return self._collision_box.has_collided_with(box=other._collision_box)

    def on_collision_with(self, other: CollidableObject):
        assert issubclass(other.__class__, CollidableObject)

    def draw_bounding_box(self) -> None:
        top_left_coordinate: Vector2f = Vector2f(x=self._coordinates.x,
                                                 y=self._coordinates.y)
        self._collision_box.top_left.copy(other=top_left_coordinate)
        # GlobalConstants.get_constant_or_non(key="renderer").remove_renderable(key=f"{id(self)}")
        # RenderableStorage.push_to_renderer_at(key=f"{id(self)}_debug_bounding_box", coordinate=top_left_coordinate)

    def undraw_bounding_box(self) -> None:
        RenderableStorage.pull_from_renderer(key=f"{id(self)}_debug_bounding_box")
