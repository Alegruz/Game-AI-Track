import pygame

from engine.core.Math import Vector2f
from engine.events.Events import Events, TitleScreenEvent, InputNameScreenEvent
from engine.graphics.Orientation import Orientation
from engine.graphics.Renderable import Renderable
from engine.graphics.Renderer import Renderer, Depth
from engine.resources.Scene import Scene


class InputNameScreenScene(Scene):
    __slots__ = ["__input_name_screen_keys", "__input_name_screen_resource", "__player_index"]

    def __init__(self, renderer: Renderer = None):
        super().__init__(name="input_name_screen", event_class_type=Events.INPUT_NAME_EVENT, renderer=renderer)

        for i in range(0, InputNameScreenEvent.END + 1):
            self._events_flag.append(False)

        self.__input_name_screen_keys: list[str] = []
        self.__input_name_screen_resource: pygame.Surface = None
        self.__player_index: int = 0

    def initialize(self):
        print(f"InputNameScreenScene::initialize")
        super().initialize()
        self.__input_name_screen_resource: pygame.Surface = pygame.image.load(
            "resources/miscellaneous/input_name_screen.png").convert_alpha()
        self.__input_name_screen_resource.set_colorkey((56, 56, 94))

        # player select
        ui_coordinate: Vector2f = Vector2f(179.0, 253.0)
        slice_rect: pygame.Rect = pygame.Rect(179.0, 253.0, 256.0, 224.0)
        coordinate: Vector2f = Vector2f(179.0, 253.0)
        self._renderables["input_name_screen_ui"] = Renderable(
            surface=self.__input_name_screen_resource.subsurface(slice_rect),
            coordinate=coordinate - ui_coordinate,
            depth=Depth.HUD_DEPTH,
            name="input_name_screen_ui"
        )
        self.__input_name_screen_keys.append(self._renderables["input_name_screen_ui"].name)

        # player select
        coordinate.set_coordinate(x=211.0, y=276.0)
        player_select_rect_size: Vector2f = coordinate - Vector2f(x=339.0, y=293.0)
        slice_rect = pygame.Rect(46.0, 278.0, 121.0, 13.0)
        self._renderables["input_name_screen_player_select"] = Renderable(
            surface=self.__input_name_screen_resource.subsurface(slice_rect),
            coordinate=Vector2f.get_oriented_vector(top_left=coordinate - ui_coordinate,
                                                    size=player_select_rect_size,
                                                    orientation=Orientation.TOP_LEFT),
            depth=Depth.HUD_DEPTH,
            name="input_name_screen_player_select"
        )
        self.__input_name_screen_keys.append(self._renderables["input_name_screen_player_select"].name)

        # numbers
        coordinate.set_coordinate(x=201.0, y=324.0)
        slice_rect = pygame.Rect(46.0, 324.0, 121.0, 16.0)
        self._renderables["input_name_screen_player_one"] = Renderable(
            surface=self.__input_name_screen_resource.subsurface(slice_rect),
            coordinate=Vector2f.get_oriented_vector(top_left=coordinate - ui_coordinate,
                                                    size=player_select_rect_size,
                                                    orientation=Orientation.TOP_LEFT),
            depth=Depth.HUD_DEPTH,
            name="input_name_screen_player_one"
        )
        self.__input_name_screen_keys.append(self._renderables["input_name_screen_player_one"].name)

    def destroy(self):
        print(f"InputNameScreenScene::destroy")
        for key in self.__input_name_screen_keys:
            del self._renderables[key]
            if self._renderer.remove_renderable(key=key):
                print(f"removed {key} successfully")
            else:
                print(f"unable to remove {key}")
        del self.__input_name_screen_keys

        for music in self._background_musics.values():
            music.stop()
            del music

        super().destroy()

    def start(self, millis: int = 0):
        super().start(millis=millis)
        print(f"InputNameScreenScene::start")
        if millis == 0:
            pygame.event.post(pygame.event.Event(pygame.USEREVENT,
                                                 class_type=Events.INPUT_NAME_EVENT,
                                                 event_type=InputNameScreenEvent.START))
        else:
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.INPUT_NAME_EVENT,
                                                           event_type=InputNameScreenEvent.START),
                                  millis=millis)
            self._is_start_timer_enabled = True

    def on_event(self, event: pygame.event.Event):
        super().on_event(event=event)

        print(f"input_name_screen_event: {event.event_type}")
        if event.event_type == InputNameScreenEvent.START:
            self._renderer.start_fade_in(duration=1)
            self._renderer.add_renderable(renderable=self._renderables["input_name_screen_ui"])
            self._renderer.add_renderable(renderable=self._renderables["input_name_screen_player_select"])
            self._renderer.add_renderable(renderable=self._renderables["input_name_screen_player_one"])

            if self._is_start_timer_enabled:
                pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                               class_type=Events.INPUT_NAME_EVENT,
                                                               event_type=InputNameScreenEvent.END),
                                      millis=0)
                self._is_start_timer_enabled = False
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.INPUT_NAME_EVENT,
                                                           event_type=InputNameScreenEvent.END),
                                  millis=1000)
        elif event.event_type == InputNameScreenEvent.END:
            self._renderer.start_fade_out(duration=1000)
            assert "main_game" in self._next_scenes
            self._next_possible_scene.add("main_game")
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.INPUT_NAME_EVENT,
                                                           event_type=InputNameScreenEvent.END),
                                  millis=0)
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TRANSITION_EVENT,
                                                           to_scene_name="main_game",
                                                           player_index=self.__player_index),

                                  millis=1000)
        else:
            assert False
