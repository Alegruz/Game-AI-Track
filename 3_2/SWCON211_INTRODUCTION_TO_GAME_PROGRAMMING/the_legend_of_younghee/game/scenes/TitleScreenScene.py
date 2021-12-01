import pygame

from engine.core.Math import Vector2f
from engine.events.Events import Events, TitleScreenEvent, InputNameScreenEvent
from engine.graphics.Renderable import Renderable
from engine.graphics.Renderer import Renderer, Depth
from engine.resources.Scene import Scene


class TitleScreenScene(Scene):
    __slots__ = ["__title_screen_keys", "__title_screen_resource", "__title_screen_triforce_frames",
                 "__title_screen_shine_frames", "__title_screen_shine_coordinates"]

    def __init__(self, renderer: Renderer = None):
        super().__init__(name="title_screen", event_class_type=Events.TITLE_SCREEN_EVENT, renderer=renderer)

        self.__title_screen_keys: list[str] = []
        self.__title_screen_resource: pygame.Surface = None
        self.__title_screen_triforce_frames: list[pygame.Surface] = list()
        self.__title_screen_shine_frames: list[pygame.Surface] = list()
        self.__title_screen_shine_coordinates: list[Vector2f] = [Vector2f(x=55.0, y=91.0),
                                                                 Vector2f(x=194.0, y=127.0),
                                                                 Vector2f(x=155.0, y=88.0),
                                                                 Vector2f(x=114.0, y=127.0)]

    def initialize(self):
        super().initialize()

        for i in range(0, TitleScreenEvent.END + 1):
            self._events_flag.append(False)

        self.__title_screen_resource: pygame.Surface = pygame.image.load(
            "resources/miscellaneous/title_screen.png").convert_alpha()

        # developer screen
        slice_rect: pygame.Rect = pygame.Rect(559.0, 519.0, 51.0, 16.0)
        self._renderables["title_screen_developer"] = Renderable(
            surface=self.__title_screen_resource.subsurface(slice_rect),
            coordinate=Vector2f(x=(self._renderer.unscaled_size.x / 2) - 25.5,
                                y=(self._renderer.unscaled_size.y / 2) - 8.0),
            depth=Depth.UI_DEPTH,
            name="title_screen_developer"
        )
        self.__title_screen_keys.append(self._renderables["title_screen_developer"].name)

        # copyright image
        slice_rect = pygame.Rect(659.0, 536.0, 73.0, 10.0)
        copyright_surface: pygame.Surface = self.__title_screen_resource.subsurface(slice_rect)
        self._renderables["title_screen_copyright"] = Renderable(surface=copyright_surface,
                                                                 coordinate=Vector2f(
                                                                     x=(self._renderer.unscaled_size.x / 2) - (
                                                                             copyright_surface.get_width() / 2),
                                                                     y=184.0
                                                                 ),
                                                                 depth=Depth.HUD_DEPTH,
                                                                 name="title_screen_copyright")
        self.__title_screen_keys.append(self._renderables["title_screen_copyright"].name)

        # triforce animation
        slice_rects: list[pygame.Rect] = [pygame.Rect(20.0, 48.0, 7.0, 14.0),
                                          pygame.Rect(38.0, 48.0, 5.0, 14.0),
                                          pygame.Rect(56.0, 48.0, 4.0, 15.0),
                                          pygame.Rect(72.0, 50.0, 3.0, 14.0),
                                          pygame.Rect(86.0, 48.0, 5.0, 15.0),
                                          pygame.Rect(102.0, 48.0, 7.0, 15.0),
                                          pygame.Rect(117.0, 48.0, 9.0, 15.0),
                                          pygame.Rect(132.0, 49.0, 9.0, 15.0),
                                          pygame.Rect(148.0, 49.0, 11.0, 15.0),
                                          pygame.Rect(165.0, 50.0, 11.0, 14.0),
                                          pygame.Rect(185.0, 49.0, 13.0, 14.0),
                                          pygame.Rect(208.0, 49.0, 13.0, 14.0),
                                          pygame.Rect(230.0, 49.0, 13.0, 12.0),
                                          pygame.Rect(251.0, 51.0, 15.0, 9.0),
                                          pygame.Rect(272.0, 53.0, 15.0, 10.0),
                                          pygame.Rect(294.0, 53.0, 15.0, 9.0),
                                          pygame.Rect(315.0, 53.0, 15.0, 7.0),
                                          pygame.Rect(337.0, 54.0, 15.0, 7.0),
                                          pygame.Rect(358.0, 53.0, 15.0, 8.0),
                                          pygame.Rect(401.0, 52.0, 15.0, 10.0),
                                          pygame.Rect(423.0, 50.0, 13.0, 12.0),
                                          pygame.Rect(443.0, 49.0, 13.0, 13.0),
                                          pygame.Rect(463.0, 50.0, 13.0, 13.0),
                                          pygame.Rect(482.0, 48.0, 11.0, 14.0),
                                          pygame.Rect(500.0, 48.0, 9.0, 15.0),
                                          pygame.Rect(515.0, 48.0, 8.0, 15.0),
                                          pygame.Rect(534.0, 48.0, 7.0, 16.0),
                                          pygame.Rect(550.0, 46.0, 5.0, 17.0),
                                          pygame.Rect(565.0, 45.0, 5.0, 18.0),
                                          pygame.Rect(581.0, 44.0, 7.0, 19.0),
                                          pygame.Rect(595.0, 44.0, 10.0, 20.0),
                                          pygame.Rect(612.0, 44.0, 12.0, 20.0),
                                          pygame.Rect(630.0, 43.0, 13.0, 21.0),
                                          pygame.Rect(651.0, 43.0, 15.0, 21.0),
                                          pygame.Rect(674.0, 43.0, 17.0, 21.0),
                                          pygame.Rect(696.0, 43.0, 18.0, 21.0),
                                          pygame.Rect(720.0, 43.0, 19.0, 21.0),
                                          pygame.Rect(744.0, 42.0, 19.0, 20.0),
                                          pygame.Rect(767.0, 43.0, 21.0, 21.0),
                                          pygame.Rect(792.0, 43.0, 21.0, 21.0),
                                          pygame.Rect(819.0, 42.0, 21.0, 21.0),
                                          pygame.Rect(845.0, 42.0, 21.0, 21.0),
                                          pygame.Rect(871.0, 43.0, 21.0, 21.0),
                                          pygame.Rect(895.0, 42.0, 22.0, 21.0),
                                          pygame.Rect(924.0, 41.0, 21.0, 23.0),
                                          pygame.Rect(951.0, 41.0, 21.0, 23.0),
                                          pygame.Rect(17.0, 102.0, 21.0, 24.0),
                                          pygame.Rect(43.0, 102.0, 20.0, 25.0),
                                          pygame.Rect(69.0, 101.0, 18.0, 26.0),
                                          pygame.Rect(92.0, 101.0, 16.0, 25.0),
                                          pygame.Rect(114.0, 100.0, 14.0, 26.0),
                                          pygame.Rect(134.0, 100.0, 12.0, 26.0),
                                          pygame.Rect(150.0, 101.0, 9.0, 25.0),
                                          pygame.Rect(166.0, 100.0, 7.0, 26.0),
                                          pygame.Rect(180.0, 102.0, 11.0, 24.0),
                                          pygame.Rect(196.0, 101.0, 14.0, 24.0),
                                          pygame.Rect(214.0, 102.0, 17.0, 25.0),
                                          pygame.Rect(237.0, 100.0, 21.0, 27.0),
                                          pygame.Rect(262.0, 100.0, 23.0, 27.0),
                                          pygame.Rect(288.0, 100.0, 27.0, 26.0),
                                          pygame.Rect(321.0, 99.0, 29.0, 26.0),
                                          pygame.Rect(352.0, 99.0, 31.0, 24.0),
                                          pygame.Rect(388.0, 102.0, 33.0, 20.0),
                                          pygame.Rect(424.0, 105.0, 35.0, 19.0),
                                          pygame.Rect(466.0, 110.0, 35.0, 16.0),
                                          pygame.Rect(508.0, 108.0, 37.0, 19.0),
                                          pygame.Rect(551.0, 105.0, 37.0, 21.0),
                                          pygame.Rect(593.0, 101.0, 39.0, 26.0),
                                          pygame.Rect(636.0, 97.0, 39.0, 30.0),
                                          pygame.Rect(680.0, 93.0, 41.0, 34.0),
                                          pygame.Rect(727.0, 88.0, 40.0, 38.0),
                                          pygame.Rect(774.0, 85.0, 39.0, 42.0),
                                          pygame.Rect(818.0, 83.0, 40.0, 42.0),
                                          pygame.Rect(864.0, 85.0, 38.0, 42.0),
                                          pygame.Rect(910.0, 82.0, 34.0, 45.0),
                                          pygame.Rect(951.0, 82.0, 31.0, 45.0),
                                          pygame.Rect(987.0, 82.0, 27.0, 45.0),
                                          pygame.Rect(19.0, 146.0, 22.0, 45.0),
                                          pygame.Rect(53.0, 146.0, 18.0, 45.0),
                                          pygame.Rect(84.0, 148.0, 12.0, 44.0),
                                          pygame.Rect(112.0, 147.0, 14.0, 44.0),
                                          pygame.Rect(143.0, 150.0, 18.0, 42.0),
                                          pygame.Rect(173.0, 150.0, 23.0, 41.0),
                                          pygame.Rect(207.0, 149.0, 26.0, 41.0),
                                          pygame.Rect(243.0, 149.0, 30.0, 43.0),
                                          pygame.Rect(280.0, 147.0, 33.0, 44.0),
                                          pygame.Rect(319.0, 149.0, 36.0, 43.0),
                                          pygame.Rect(359.0, 147.0, 38.0, 45.0),
                                          pygame.Rect(402.0, 147.0, 39.0, 44.0),
                                          pygame.Rect(445.0, 148.0, 40.0, 44.0),
                                          pygame.Rect(490.0, 149.0, 40.0, 42.0),
                                          pygame.Rect(532.0, 151.0, 39.0, 41.0),
                                          pygame.Rect(574.0, 152.0, 39.0, 38.0),
                                          pygame.Rect(616.0, 152.0, 39.0, 39.0),
                                          pygame.Rect(660.0, 150.0, 39.0, 40.0),
                                          pygame.Rect(702.0, 149.0, 39.0, 41.0),
                                          pygame.Rect(744.0, 150.0, 38.0, 40.0),
                                          pygame.Rect(786.0, 150.0, 36.0, 40.0),
                                          pygame.Rect(826.0, 150.0, 34.0, 40.0),
                                          pygame.Rect(864.0, 153.0, 32.0, 37.0),
                                          pygame.Rect(902.0, 154.0, 29.0, 36.0),
                                          pygame.Rect(936.0, 154.0, 26.0, 37.0),
                                          pygame.Rect(969.0, 153.0, 22.0, 38.0),
                                          pygame.Rect(999.0, 153.0, 18.0, 39.0),

                                          pygame.Rect(18.0, 216.0, 14.0, 39.0),
                                          pygame.Rect(40.0, 217.0, 11.0, 37.0),
                                          pygame.Rect(58.0, 217.0, 15.0, 38.0),
                                          pygame.Rect(82.0, 216.0, 19.0, 39.0),
                                          pygame.Rect(106.0, 216.0, 23.0, 38.0),
                                          pygame.Rect(134.0, 217.0, 26.0, 37.0),
                                          pygame.Rect(166.0, 219.0, 29.0, 35.0),
                                          pygame.Rect(202.0, 219.0, 32.0, 36.0),
                                          pygame.Rect(236.0, 216.0, 34.0, 39.0),
                                          pygame.Rect(275.0, 216.0, 36.0, 39.0),
                                          pygame.Rect(315.0, 216.0, 38.0, 39.0),
                                          pygame.Rect(358.0, 214.0, 39.0, 40.0),
                                          pygame.Rect(405.0, 215.0, 39.0, 39.0),
                                          pygame.Rect(448.0, 215.0, 39.0, 39.0),
                                          pygame.Rect(493.0, 216.0, 39.0, 38.0),
                                          pygame.Rect(537.0, 213.0, 39.0, 41.0),
                                          pygame.Rect(583.0, 212.0, 41.0, 42.0),
                                          pygame.Rect(636.0, 209.0, 40.0, 44.0),
                                          pygame.Rect(688.0, 211.0, 39.0, 44.0),
                                          pygame.Rect(738.0, 209.0, 38.0, 45.0),
                                          pygame.Rect(791.0, 212.0, 36.0, 43.0),
                                          pygame.Rect(841.0, 210.0, 33.0, 44.0),
                                          pygame.Rect(892.0, 214.0, 30.0, 42.0),
                                          pygame.Rect(943.0, 217.0, 26.0, 41.0),
                                          pygame.Rect(980.0, 215.0, 23.0, 42.0),
                                          pygame.Rect(1028.0, 215.0, 18.0, 42.0),
                                          pygame.Rect(28.0, 275.0, 14.0, 44.0),
                                          pygame.Rect(62.0, 274.0, 12.0, 44.0),
                                          pygame.Rect(95.0, 273.0, 18.0, 45.0),
                                          pygame.Rect(140.0, 275.0, 22.0, 45.0),
                                          pygame.Rect(181.0, 274.0, 27.0, 45.0),
                                          pygame.Rect(221.0, 273.0, 30.0, 45.0),
                                          pygame.Rect(258.0, 273.0, 34.0, 44.0),
                                          pygame.Rect(299.0, 277.0, 38.0, 42.0),
                                          pygame.Rect(345.0, 278.0, 40.0, 42.0),
                                          pygame.Rect(393.0, 281.0, 42.0, 39.0),
                                          pygame.Rect(439.0, 283.0, 44.0, 36.0),
                                          pygame.Rect(487.0, 281.0, 45.0, 33.0),
                                          pygame.Rect(537.0, 283.0, 45.0, 29.0),
                                          pygame.Rect(587.0, 286.0, 43.0, 24.0),
                                          pygame.Rect(637.0, 287.0, 44.0, 22.0),
                                          pygame.Rect(685.0, 287.0, 45.0, 19.0),
                                          pygame.Rect(738.0, 283.0, 45.0, 24.0),
                                          pygame.Rect(785.0, 284.0, 43.0, 25.0),
                                          pygame.Rect(840.0, 282.0, 43.0, 30.0),
                                          pygame.Rect(898.0, 280.0, 41.0, 35.0),
                                          pygame.Rect(944.0, 281.0, 37.0, 36.0),
                                          pygame.Rect(995.0, 279.0, 37.0, 39.0),
                                          pygame.Rect(18.0, 345.0, 32.0, 39.0),
                                          pygame.Rect(74.0, 345.0, 26.0, 38.0),
                                          pygame.Rect(126.0, 346.0, 22.0, 36.0),
                                          pygame.Rect(163.0, 345.0, 16.0, 38.0),
                                          pygame.Rect(196.0, 343.0, 12.0, 39.0),
                                          pygame.Rect(224.0, 341.0, 14.0, 41.0),
                                          pygame.Rect(252.0, 341.0, 20.0, 42.0),
                                          pygame.Rect(284.0, 338.0, 24.0, 44.0),
                                          pygame.Rect(326.0, 339.0, 29.0, 43.0),
                                          pygame.Rect(367.0, 337.0, 32.0, 44.0),
                                          pygame.Rect(407.0, 338.0, 36.0, 45.0),
                                          pygame.Rect(455.0, 339.0, 38.0, 44.0),
                                          pygame.Rect(502.0, 339.0, 40.0, 44.0),
                                          pygame.Rect(553.0, 340.0, 40.0, 43.0),
                                          pygame.Rect(601.0, 339.0, 42.0, 42.0),
                                          pygame.Rect(649.0, 340.0, 41.0, 41.0),
                                          pygame.Rect(695.0, 341.0, 41.0, 41.0),
                                          pygame.Rect(741.0, 340.0, 41.0, 41.0),
                                          ]

        for rect in slice_rects:
            self.__title_screen_triforce_frames.append(self.__title_screen_resource.subsurface(rect))

        self._renderables["title_screen_power_triforce"] = Renderable(surface=self.__title_screen_triforce_frames[0],
                                                                      coordinate=Vector2f(
                                                                          x=(self._renderer.unscaled_size.x / 2.0) - (
                                                                                  self.__title_screen_triforce_frames[
                                                                                      0].get_width() / 2.0),
                                                                          y=-self.__title_screen_triforce_frames[
                                                                              0].get_height()
                                                                      ),
                                                                      depth=Depth.NORMAL0_DEPTH,
                                                                      name="title_screen_power_triforce",
                                                                      surfaces=self.__title_screen_triforce_frames)
        self._renderables["title_screen_power_triforce"].flip_x = True
        self._renderables["title_screen_wisdom_triforce"] = Renderable(
            surface=self.__title_screen_triforce_frames[0],
            coordinate=Vector2f(x=self._renderer.unscaled_size.x / 6,
                                y=self._renderer.unscaled_size.y),
            depth=Depth.NORMAL0_DEPTH,
            name="title_screen_wisdom_triforce",
            surfaces=self.__title_screen_triforce_frames)
        self._renderables["title_screen_wisdom_triforce"].flip_x = True
        self._renderables["title_screen_courage_triforce"] = Renderable(
            surface=self.__title_screen_triforce_frames[0],
            coordinate=Vector2f(
                x=self._renderer.unscaled_size.x * (5.0 / 6.0),
                y=self._renderer.unscaled_size.y
            ),
            depth=Depth.NORMAL0_DEPTH,
            name="title_screen_courage_triforce",
            surfaces=self.__title_screen_triforce_frames)
        self.__title_screen_keys.append(self._renderables["title_screen_power_triforce"].name)
        self.__title_screen_keys.append(self._renderables["title_screen_wisdom_triforce"].name)
        self.__title_screen_keys.append(self._renderables["title_screen_courage_triforce"].name)

        # triforce
        slice_rect = pygame.Rect(532.0, 421.0, 82.0, 81.0)
        self._renderables["title_screen_triforce"] = Renderable(
            surface=self.__title_screen_resource.subsurface(slice_rect),
            coordinate=Vector2f(x=87, y=60),
            depth=Depth.MAP_DEPTH,
            name="title_screen_triforce"
        )
        self.__title_screen_keys.append(self._renderables["title_screen_triforce"].name)

        slice_rect = pygame.Rect(16.0, 400.0, 256.0, 143.0)
        self._renderables["title_screen_background"] = Renderable(
            surface=self.__title_screen_resource.subsurface(slice_rect),
            coordinate=Vector2f(x=0, y=31),
            depth=Depth.BACKGROUND_DEPTH,
            name="title_screen_background"
        )
        self.__title_screen_keys.append(self._renderables["title_screen_background"].name)

        slice_rect = pygame.Rect(304.0, 443.0, 147.0, 44.0)

        self._renderables["title_screen_over_sword_title"]: Renderable = Renderable(
            surface=self.__title_screen_resource.subsurface(slice_rect),
            coordinate=Vector2f(x=52, y=89),
            depth=Depth.VFX_DEPTH,
            name="title_screen_over_sword_title"
        )
        self.__title_screen_keys.append(self._renderables["title_screen_over_sword_title"].name)

        slice_rect = pygame.Rect(305.0, 418.0, 147.0, 25.0)
        self._renderables["title_screen_behind_sword_title_upper"]: Renderable = Renderable(
            surface=self.__title_screen_resource.subsurface(slice_rect),
            coordinate=Vector2f(x=53, y=64),
            depth=Depth.NORMAL0_DEPTH,
            name="title_screen_behind_sword_title_upper"
        )
        self.__title_screen_keys.append(self._renderables["title_screen_behind_sword_title_upper"].name)

        slice_rect = pygame.Rect(302.0, 487.0, 174.0, 17.0)
        self._renderables["title_screen_behind_sword_title_lower"] = Renderable(
            surface=self.__title_screen_resource.subsurface(slice_rect),
            coordinate=Vector2f(x=50, y=133),
            depth=Depth.NORMAL0_DEPTH,
            name="title_screen_behind_sword_title_lower"
        )
        self.__title_screen_keys.append(self._renderables["title_screen_behind_sword_title_lower"].name)

        slice_rect = pygame.Rect(501.0, 399.0, 31.0, 128.0)
        self._renderables["title_screen_sword"] = Renderable(
            surface=self.__title_screen_resource.subsurface(slice_rect),
            coordinate=Vector2f(x=56, y=-128.0),
            depth=Depth.NORMAL1_DEPTH,
            name="title_screen_sword")
        self.__title_screen_keys.append(self._renderables["title_screen_sword"].name)

        # pygame.Rect(373.0, 522.0, 3.0, 3.0),
        # pygame.Rect(372.0, 538.0, 3.0, 3.0),
        # pygame.Rect(355.0, 521.0, 5.0, 5.0),
        # pygame.Rect(355.0, 537.0, 5.0, 5.0),
        slice_rects: list[pygame.Rect] = [pygame.Rect(338.0, 520.0, 7.0, 7.0),
                                          # pygame.Rect(338.0, 536.0, 7.0, 7.0),
                                          pygame.Rect(322.0, 536.0, 7.0, 7.0),
                                          pygame.Rect(318.0, 516.0, 15.0, 15.0),
                                          pygame.Rect(322.0, 536.0, 7.0, 7.0),
                                          pygame.Rect(338.0, 520.0, 7.0, 7.0),
                                          ]

        for rect in slice_rects:
            self.__title_screen_shine_frames.append(self.__title_screen_resource.subsurface(rect))

        self._renderables["title_screen_shiny_effect"] = Renderable(surface=self.__title_screen_shine_frames[0],
                                                                    coordinate=Vector2f(x=0.0, y=0.0),
                                                                    depth=Depth.HUD_DEPTH,
                                                                    name="title_screen_shiny_effect",
                                                                    surfaces=self.__title_screen_shine_frames,
                                                                    coordinates=self.__title_screen_shine_coordinates)
        self.__title_screen_keys.append(self._renderables["title_screen_shiny_effect"].name)

        self._background_musics["title"] = pygame.mixer.Sound(file="resources/musics/title.mp3")
        self._sound_effects["intro"] = pygame.mixer.Sound(file="resources/sounds/intro.ogg")
        self._sound_effects["ok"] = pygame.mixer.Sound(file="resources/sounds/ok.ogg")
        self._sound_effects["sword1"] = pygame.mixer.Sound(file="resources/sounds/sword1.ogg")

    def destroy(self):
        for key in self.__title_screen_keys:
            del self._renderables[key]
            if self._renderer.remove_renderable(key=key):
                print(f"removed {key} successfully")
            else:
                print(f"unable to remove {key}")
        del self.__title_screen_keys

        for music in self._background_musics.values():
            music.stop()
            del music

        super().destroy()

    def start(self, millis: int = 0):
        super().start(millis=millis)

        if millis == 0:
            pygame.event.post(pygame.event.Event(pygame.USEREVENT,
                                                 class_type=Events.TITLE_SCREEN_EVENT,
                                                 event_type=TitleScreenEvent.SHOW_DEVELOPER))
        else:
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.SHOW_DEVELOPER),
                                  millis=millis)
            self._is_start_timer_enabled = True


    def on_event(self, event: pygame.event.Event):
        super().on_event(event=event)

        if event.event_type == TitleScreenEvent.END:
            assert "input_name_screen" in self._next_scenes
            self._next_possible_scene.add("input_name_screen")
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.END),
                                  millis=0)
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TRANSITION_EVENT,
                                                           to_scene_name="input_name_screen"),
                                  millis=1000)
        elif event.event_type == TitleScreenEvent.FADE_OUT:
            self._renderer.remove_renderable(key="title_screen_shiny_effect"),
            self._renderer.start_fade_out(duration=1000)
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.FADE_OUT),
                                  millis=0)
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.END),
                                  millis=1000)
        elif event.event_type == TitleScreenEvent.SHOW_SHINY_EFFECT:
            # show shiny effects
            self._renderables["title_screen_shiny_effect"].start_coordinate_change(duration=500, should_loop=True)
            self._renderables["title_screen_shiny_effect"].start_animation(from_frame_index=0,
                                                                           to_frame_index=len(
                                                                               self.__title_screen_shine_frames) - 1,
                                                                           duration=500,
                                                                           should_loop=True)
            self._renderer.add_renderable(renderable=self._renderables["title_screen_shiny_effect"])
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.SHOW_SHINY_EFFECT),
                                  millis=0)
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.FADE_OUT),
                                  millis=8000)
        elif event.event_type == TitleScreenEvent.FADE_IN_BACKGROUND:
            # show background
            self._renderer.stop_flashing()
            self._sound_effects["ok"].stop()
            self._renderables["title_screen_background"].start_fade_in(duration=1000)
            self._renderer.add_renderable(renderable=self._renderables["title_screen_background"])
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.FADE_IN_BACKGROUND),
                                  millis=0)
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.SHOW_SHINY_EFFECT),
                                  millis=1000)
        elif event.event_type == TitleScreenEvent.SHOW_FLASHING_EFFECT:
            self._renderer.start_flashing(duration=17)
            self._sound_effects["sword1"].stop()
            self._sound_effects["ok"].set_volume(0.5)
            self._sound_effects["ok"].play()
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.SHOW_FLASHING_EFFECT),
                                  millis=0)
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.FADE_IN_BACKGROUND),
                                  millis=1003)
        elif event.event_type == TitleScreenEvent.SHOW_SWORD:
            # show sword
            self._renderer.add_renderable(renderable=self._renderables["title_screen_sword"])
            self._renderer.get_renderable(key="title_screen_sword").start_move(
                from_coordinate=Vector2f(56.0,
                                         -float(self._renderables["title_screen_sword"].surface.get_height())),
                to_coordinate=Vector2f(56.0, 38.0),
                duration=250
            )
            self._sound_effects["sword1"].set_volume(0.4)
            self._sound_effects["sword1"].play()
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.SHOW_SWORD),
                                  millis=0)
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.SHOW_FLASHING_EFFECT),
                                  millis=250)
        elif event.event_type == TitleScreenEvent.FADE_IN_TITLE:
            # fade in title
            self._renderables["title_screen_over_sword_title"].start_fade_in(duration=1000)
            self._renderables["title_screen_behind_sword_title_upper"].start_fade_in(duration=1000)
            self._renderables["title_screen_behind_sword_title_lower"].start_fade_in(duration=1000)
            self._renderer.add_renderable(renderable=self._renderables["title_screen_over_sword_title"])
            self._renderer.add_renderable(renderable=self._renderables["title_screen_behind_sword_title_upper"])
            self._renderer.add_renderable(renderable=self._renderables["title_screen_behind_sword_title_lower"])
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.FADE_IN_TITLE),
                                  millis=0)
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.SHOW_SWORD),
                                  millis=1000)
        elif event.event_type == TitleScreenEvent.SHOW_COMPLETE_TRIFORCE:
            # show completed triforce
            self._renderer.remove_renderable(key="title_screen_power_triforce")
            self._renderer.remove_renderable(key="title_screen_wisdom_triforce")
            self._renderer.remove_renderable(key="title_screen_courage_triforce")
            self._renderer.add_renderable(renderable=self._renderables["title_screen_triforce"])
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.SHOW_COMPLETE_TRIFORCE),
                                  millis=0)
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.FADE_IN_TITLE),
                                  millis=1500)
        elif event.event_type == TitleScreenEvent.PLAY_MUSIC:
            # play title music
            self._background_musics["title"].set_volume(0.4)
            self._background_musics["title"].play()
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.PLAY_MUSIC),
                                  millis=0)
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.SHOW_COMPLETE_TRIFORCE),
                                  millis=5000 - 160)
        elif event.event_type == TitleScreenEvent.ANIMATE_TRIFORCE:
            # animate triforce
            self._renderables["title_screen_power_triforce"].start_move(
                from_coordinate=self._renderables["title_screen_power_triforce"].coordinate,
                to_coordinate=Vector2f(x=107.0, y=60.0),
                duration=4000
            )
            self._renderables["title_screen_wisdom_triforce"].start_move(
                from_coordinate=self._renderables["title_screen_wisdom_triforce"].coordinate,
                to_coordinate=Vector2f(x=87.0, y=100.0),
                duration=4000
            )
            self._renderables["title_screen_courage_triforce"].start_move(
                from_coordinate=self._renderables["title_screen_courage_triforce"].coordinate,
                to_coordinate=Vector2f(x=128.0, y=100.0),
                duration=4000
            )
            self._renderables["title_screen_power_triforce"].start_animation(from_frame_index=0,
                                                                             to_frame_index=len(
                                                                                 self.__title_screen_triforce_frames),
                                                                             duration=5000)
            self._renderables["title_screen_wisdom_triforce"].start_animation(from_frame_index=0,
                                                                              to_frame_index=len(
                                                                                  self.__title_screen_triforce_frames),
                                                                              duration=5000)
            self._renderables["title_screen_courage_triforce"].start_animation(from_frame_index=0,
                                                                               to_frame_index=len(
                                                                                   self.__title_screen_triforce_frames),
                                                                               duration=5000)
            self._renderer.add_renderable(renderable=self._renderables["title_screen_power_triforce"])
            self._renderer.add_renderable(renderable=self._renderables["title_screen_wisdom_triforce"])
            self._renderer.add_renderable(renderable=self._renderables["title_screen_courage_triforce"])
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.ANIMATE_TRIFORCE),
                                  millis=0)
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.PLAY_MUSIC),
                                  millis=160)
        elif event.event_type == TitleScreenEvent.SHOW_COPYRIGHT:
            # show copyright
            self._renderer.remove_renderable(key="title_screen_developer")
            self._renderer.add_renderable(renderable=self._renderables["title_screen_copyright"])
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.SHOW_COPYRIGHT),
                                  millis=0)
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.ANIMATE_TRIFORCE),
                                  millis=500)
        elif event.event_type == TitleScreenEvent.FADE_OUT_DEVELOPER:
            # fade out developer
            self._renderer.get_renderable(key="title_screen_developer").start_fade_out(duration=1000)
            self._sound_effects["intro"].stop()
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.FADE_OUT_DEVELOPER),
                                  millis=0)
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.SHOW_COPYRIGHT),
                                  millis=2000)
        elif event.event_type == TitleScreenEvent.SHOW_DEVELOPER:
            self._renderer.add_renderable(renderable=self._renderables["title_screen_developer"])
            self._sound_effects["intro"].play()

            if self._is_start_timer_enabled:
                pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                               class_type=Events.TITLE_SCREEN_EVENT,
                                                               event_type=TitleScreenEvent.SHOW_DEVELOPER),
                                      millis=0)
                self._is_start_timer_enabled = False
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.FADE_OUT_DEVELOPER),
                                  millis=1000)
        else:
            assert False
