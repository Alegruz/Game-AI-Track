from __future__ import annotations
import pygame

from engine.graphics.Renderable import Renderable
from engine.graphics.Renderer import Renderer


class Scene:
    __slots__ = ["_name", "_event_class_type", "_renderer", "_renderables", "_background_musics", "_sound_effects",
                 "_next_scenes", "_next_possible_scene", "_is_initialized", "_events_flag", "_is_start_timer_enabled"]

    def __init__(self, name: str, event_class_type: int, renderer: Renderer = None):
        assert isinstance(name, str)
        self._name: str = name
        self._event_class_type: int = event_class_type

        self._is_initialized: bool = False

        self._next_scenes: dict[str, Scene] = dict()
        self._next_possible_scene: set[str] = set()

        self._events_flag: list[bool] = []

        self._is_start_timer_enabled: bool = False

        # graphics
        self._renderer: Renderer = renderer
        self._renderables: dict[str, Renderable] = dict()

        # audio
        # init sounds
        self._background_musics: dict[str, pygame.mixer.Sound] = dict()
        self._sound_effects: dict[str, pygame.mixer.Sound] = dict()

    def __del__(self):
        print(f"deleting {self}")

    def __str__(self) -> str:
        return f"Scene={{ name={self._name} }}"

    @property
    def name(self) -> str:
        return self._name

    @property
    def class_type(self) -> int:
        return self._event_class_type

    @property
    def is_initialized(self) -> bool:
        return self._is_initialized

    def initialize(self):
        self._is_initialized = True
        print(f"initialize {self._name}")

    def destroy(self):
        self._is_initialized = False
        print(f"destroy {self._name}")

        del self._next_scenes
        del self._next_possible_scene

        # graphics
        del self._renderables

        # audio
        del self._background_musics
        del self._sound_effects

    def start(self, millis: int = 0):
        assert self._is_initialized

    def add_next_scene(self, scene: Scene) -> bool:
        assert issubclass(scene.__class__, Scene)

        if scene._name in self._next_scenes:
            return False

        self._next_scenes[scene._name] = scene
        return True

    def can_transit_to(self, scene_name: str) -> bool:
        return scene_name in self._next_possible_scene

    def set_renderer(self, renderer: Renderer) -> None:
        assert isinstance(renderer, Renderer)

        self._renderer = renderer

    def on_event(self, event: pygame.event.Event):
        # print(f"on_event: {event}")
        pass

    def update(self, delta_time: float):
        pass