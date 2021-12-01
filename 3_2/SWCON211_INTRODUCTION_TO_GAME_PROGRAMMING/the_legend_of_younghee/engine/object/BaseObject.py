import pygame

from engine.components.Component import Component, ComponentType, RenderableComponent
from engine.core.Math import Vector2f, Box


class BaseObject:
    __slots__ = ["_components", "_coordinates"]

    def __init__(self, coordinate: Vector2f):
        self._components: dict[int, dict[str, Component]] = dict()
        self._coordinates: Vector2f = Vector2f(x=coordinate.x, y=coordinate.y)

    def __del__(self):
        self.destroy()
        # print(f"BaseObject::Destructor: {self}, {id(self)}")

    @property
    def coordinate(self) -> Vector2f:
        return self._coordinates

    def initialize(self):
        pass

    def destroy(self):
        pass

    def add_renderable_component(self, renderable_component: RenderableComponent):
        if ComponentType.RENDERABLE not in self._components:
            self._components[ComponentType.RENDERABLE] = dict()

        self._components[ComponentType.RENDERABLE][renderable_component.name] = renderable_component

    def get_renderable_component(self, name: str) -> RenderableComponent:
        if ComponentType.RENDERABLE not in self._components:
            return None

        if name not in self._components[ComponentType.RENDERABLE]:
            return None

        return self._components[ComponentType.RENDERABLE][name]

    def update(self, delta_time: float):
        pass

