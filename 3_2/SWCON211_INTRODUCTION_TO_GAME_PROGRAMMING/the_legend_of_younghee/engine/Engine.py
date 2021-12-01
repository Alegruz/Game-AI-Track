from __future__ import annotations
import threading

import pygame

from engine.core.Math import Vector2f
from engine.events.Events import Events, InputNameScreenEvent, TitleScreenEvent
from engine.graphics.Orientation import Orientation
from engine.graphics.Renderable import Renderable
from engine.graphics.Renderer import Depth, Renderer
from engine.player.Player import Player
from engine.resources.Scene import Scene


class Engine:
    LOCK = threading.Lock()
    __slots__ = ["__width", "__height", "__scale_rate", "__flags", "__renderer", "__scenes", "__logo", "__clock",
                 "__delta_time", "__allowed_events", "__allowed_custom_event_types", "__players", "__player_index",
                 "__current_player_index", "__current_scene", "__scenes_by_event", "__transitions"]

    def __init__(self, width: float, height: float):
        # pre init
        # pygame.mixer.pre_init(44100, 16, 2, 4096)

        # init
        pygame.init()

        # init graphics
        self.__width: float = width
        self.__height: float = height
        self.__scale_rate: float = 3.0
        # self.__flags: int = pygame.DOUBLEBUF
        self.__flags: int = 0

        self.__renderer: Renderer = Renderer(size=Vector2f(x=self.__width, y=self.__height),
                                             scale_rate=self.__scale_rate,
                                             flags=self.__flags)
        self.__scenes: dict[str, Scene] = dict()
        self.__scenes_by_event: dict[int, Scene] = dict()
        self.__current_scene: Scene = None
        self.__transitions: dict[str, set[str]] = dict()

        self.__logo: pygame.Surface = pygame.image.load("resources/icons/logo.png").convert_alpha()
        pygame.display.set_icon(self.__logo)
        pygame.display.set_caption("The Legend of Younghee")

        # init updates
        self.__clock: pygame.time.Clock = pygame.time.Clock()
        self.__delta_time: float = self.__clock.tick(60)
        self.__allowed_events: set[int] = {pygame.QUIT,
                                           pygame.KEYDOWN,
                                           pygame.KEYUP,
                                           pygame.USEREVENT}
        self.__allowed_custom_event_types: set[int] = set()
        self.__allowed_custom_event_types.add(Events.TRANSITION_EVENT)
        pygame.event.set_allowed(list(self.__allowed_events))

        # init gameplay
        self.__players: list[Player] = [None, None, None]
        self.__player_index: int = 0
        self.__current_player_index: int = 0

    def __del__(self):
        del self.__renderer
        self.destroy()

    @property
    def current_scene(self) -> Scene:
        return self.__current_scene

    def destroy(self):
        print("quiting pygame...")
        pygame.quit()

    def add_scene(self, scene: Scene) -> bool:
        assert issubclass(scene.__class__, Scene)

        if scene.name in self.__scenes:
            return False

        if scene.name == "main_game":
            if self.__players[self.__player_index] is None:
                self.__players[self.__player_index] = Player(name=f"player{self.__player_index}",
                                                             coordinate=Vector2f(x=self.__width / 2.0,
                                                                                 y=self.__height / 2.0),
                                                             renderer=self.__renderer)
            scene.player = self.__players[self.__player_index]
        self.__scenes[scene.name] = scene
        scene.set_renderer(renderer=self.__renderer)
        self.__scenes_by_event[scene.class_type] = scene

        self.__allowed_custom_event_types.add(scene.class_type)

        return True

    def add_transition(self, from_scene: Scene, to_scene: Scene) -> bool:
        assert issubclass(from_scene.__class__, Scene) and issubclass(to_scene.__class__, Scene)

        if from_scene.name in self.__transitions:
            if to_scene.name in self.__transitions[from_scene.name]:
                return False
        else:
            self.__transitions[from_scene.name] = set()

        self.__transitions[from_scene.name].add(to_scene.name)
        self.__scenes[from_scene.name].add_next_scene(scene=to_scene)

        return True

    def set_current_scene(self, name: str) -> bool:
        if name not in self.__scenes:
            return False

        if self.__current_scene is not None and self.__current_scene.is_initialized:
            self.__current_scene.destroy()
        self.__current_scene = self.__scenes[name]
        if self.__current_scene.name == "main_game":
            self.__current_scene.player = self.__players[self.__player_index]

        self.__current_scene.initialize()

        return True

    def start_current_scene(self, millis: int = 0) -> bool:
        if self.__current_scene is None:
            return False

        self.__current_scene.start(millis=millis)
        return True

    def transit_scene(self, to_scene_name: str):
        assert self.__current_scene is not None and to_scene_name in self.__scenes

        if self.__current_scene.name in self.__transitions and \
                to_scene_name in self.__transitions[self.__current_scene.name] and \
                self.__current_scene.can_transit_to(scene_name=to_scene_name):
            print(f"TRANSIT from {self.__current_scene.name} to {to_scene_name}")
            self.__current_scene.destroy()
            self.set_current_scene(name=to_scene_name)
            self.__current_scene.start()

    def run(self):
        assert self.__current_scene is not None

        while 1:
            if pygame.event.peek():
                event: pygame.event.Event = pygame.event.poll()

                if event.type == pygame.QUIT:
                    self.destroy()
                    return

                if event.type == pygame.USEREVENT:
                    print(f"event: {event}, {id(event)}")
                    if "class_type" in event.__dict__:
                        if event.class_type not in self.__allowed_custom_event_types:
                            continue

                        if event.class_type == Events.TRANSITION_EVENT:
                            if self.__current_scene.name == "input_name_screen":
                                self.__player_index = event.player_index
                                if self.__players[self.__player_index] is None:
                                    self.__players[self.__player_index] = Player(
                                        name=f"player_{self.__player_index + 1}",
                                        coordinate=Vector2f(x=self.__width / 2.0,
                                                            y=self.__height / 2.0),
                                        renderer=self.__renderer
                                    )
                            if event.to_scene_name == "main_game":
                                pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                                               class_type=Events.TRANSITION_EVENT,
                                                                               to_scene_name="main_game",
                                                                               player_index=self.__player_index),

                                                      millis=0)
                            else:
                                pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                                               class_type=Events.TRANSITION_EVENT,
                                                                               to_scene_name=event.to_scene_name),
                                                      millis=0)
                            self.transit_scene(to_scene_name=event.to_scene_name)
                self.__scenes_by_event[self.__current_scene.class_type].on_event(event=event)

            self.__current_scene.update(delta_time=self.__clock.tick(60))
            self.__renderer.update(delta_time=self.__clock.tick(60))
            self.__renderer.render()
