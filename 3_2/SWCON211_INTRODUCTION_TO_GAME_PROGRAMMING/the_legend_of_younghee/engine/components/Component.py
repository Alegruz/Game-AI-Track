from typing import Any

import pygame.surface

from engine.core.Math import Vector2f
from engine.graphics.Renderable import Renderable
from engine.graphics.Renderer import Renderer


class ComponentType:
    RENDERABLE: int = 0
    CAPSULE: int = 1
    CHARACTER_MOVEMENT: int = 2


class Component:
    __slots__ = ["_name"]

    def __init__(self, name: str):
        self._name: str = name

    def __del__(self):
        print(f"Component::Destructor: {self}, {self._name} {id(self)}")

    @property
    def name(self) -> str:
        return self._name


class RenderableComponent(Component):
    __slots__ = ["__renderer", "__renderable", "__renderables"]

    def __init__(self, name: str, renderer: Renderer):
        super().__init__(name=name)

        self.__renderer: Renderer = renderer
        self.__renderable: Renderable = None
        self.__renderables: dict[str, Renderable] = dict()

    def __del__(self):
        pass

    @property
    def renderable(self) -> Renderable:
        return self.__renderable

    def add_renderable(self, renderable: Renderable) -> bool:
        if renderable.name in self.__renderables:
            return False

        self.__renderables[renderable.name] = renderable

        return True

    def get_renderable_by_name(self, name: str) -> Renderable:
        if name not in self.__renderables:
            return None

        return self.__renderables[name]

    def set_renderable(self, name: str) -> bool:
        if name not in self.__renderables:
            # print(f"renderables: {self.__renderables}")
            return False

        if self.__renderable is not None:
            self.__renderer.remove_renderable(key=self.__renderable.name)
        self.__renderable = self.__renderables[name]
        self.__renderer.add_renderable(renderable=self.__renderable)

        return True

    def show_renderable(self) -> bool:
        if self.__renderable is None:
            return False

        self.__renderer.add_renderable(renderable=self.__renderable)

        return True

    def hide_renderable(self) -> bool:
        if self.__renderable is None:
            # print(f"renderables: {self.__renderables}")
            return False

        self.__renderer.remove_renderable(key=self.__renderable.name)

        return True
