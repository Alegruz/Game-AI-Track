from typing import Union

import pygame

from engine.core.Math import Vector2f
from engine.graphics.Renderable import Renderable
from engine.graphics.Renderer import Renderer


class RenderableStorage:
    __renderables: dict[str, Renderable] = dict()
    __surfaces: dict[str, pygame.Surface] = dict()
    __renderer: Renderer = None

    @staticmethod
    def add_renderable(renderable: Renderable) -> bool:
        assert isinstance(renderable, Renderable)
        if renderable.name in RenderableStorage.__renderables:
            return False

        # print(f"added renderable {renderable.name}")
        RenderableStorage.__renderables[renderable.name] = renderable

        return True

    @staticmethod
    def add_surface(key: str, surface: pygame.Surface) -> bool:
        assert isinstance(surface, pygame.Surface)
        if key in RenderableStorage.__renderables:
            return False

        RenderableStorage.__surfaces[key] = surface

        return True

    @staticmethod
    def add_or_set_renderable(renderable: Renderable) -> None:
        assert isinstance(renderable, Renderable)
        RenderableStorage.__renderables[renderable.name] = renderable

    @staticmethod
    def add_or_set_surface(key: str, surface: Renderable) -> None:
        assert isinstance(surface, pygame.Surface)
        RenderableStorage.__surfaces[key] = surface

    @staticmethod
    def contains_renderable(key: str) -> bool:
        return key in RenderableStorage.__renderables

    @staticmethod
    def contains_surface(key: str) -> bool:
        return key in RenderableStorage.__surfaces

    @staticmethod
    def get_renderable_or_none(key: str) -> Union[Renderable, None]:
        try:
            return RenderableStorage.__renderables[key]
        except KeyError:
            return None

    @staticmethod
    def get_surface_or_none(key: str) -> Union[pygame.Surface, None]:
        try:
            return RenderableStorage.__surfaces[key]
        except KeyError:
            return None

    @staticmethod
    def is_rendering(key: str) -> bool:
        assert RenderableStorage.__renderer is not None

        if key not in RenderableStorage.__renderables:
            return False

        return RenderableStorage.__renderer.has_renderable(key=key)

    @staticmethod
    def pull_from_renderer(key: str) -> bool:
        assert RenderableStorage.__renderer is not None

        if key not in RenderableStorage.__renderables:
            return False

        return RenderableStorage.__renderer.remove_renderable(key=key)

    @staticmethod
    def push_to_renderer(key: str) -> bool:
        assert RenderableStorage.__renderer is not None

        if key not in RenderableStorage.__renderables:
            print(f"unable to push to renderer. {key} not in data")
            return False

        return RenderableStorage.__renderer.add_renderable(renderable=RenderableStorage.__renderables[key])

    @staticmethod
    def push_to_renderer_at(key: str, coordinate: Vector2f) -> bool:
        assert RenderableStorage.__renderer is not None

        if key not in RenderableStorage.__renderables:
            return False

        RenderableStorage.__renderables[key].coordinate.copy(other=coordinate)
        return RenderableStorage.__renderer.add_renderable(renderable=RenderableStorage.__renderables[key])

    @staticmethod
    def remove_renderable(key: str) -> bool:
        if key not in RenderableStorage.__renderables:
            return False

        if RenderableStorage.is_rendering(key=key):
            RenderableStorage.pull_from_renderer(key=key)

        del RenderableStorage.__renderables[key]

        return True

    @staticmethod
    def remove_surface(key: str) -> bool:
        if key not in RenderableStorage.__surfaces:
            return False

        del RenderableStorage.__surfaces[key]

        return True

    @staticmethod
    def set_renderable(renderable: Renderable) -> bool:
        assert isinstance(renderable, Renderable)
        if renderable.name not in RenderableStorage.__renderables:
            return False

        RenderableStorage.__renderables[renderable.name] = renderable

    @staticmethod
    def set_surface(key: str, surface: Renderable) -> bool:
        assert isinstance(surface, Renderable)
        if key not in RenderableStorage.__renderables:
            return False

        RenderableStorage.__surfaces[key] = surface

    @staticmethod
    def set_renderer(renderer: Renderer):
        assert isinstance(renderer, Renderer)

        RenderableStorage.__renderer = renderer
