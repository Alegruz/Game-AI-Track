from __future__ import annotations

import pygame

from engine.core.Math import Vector2f
from engine.events.Events import Events, InputNameScreenEvent, TitleScreenEvent
from engine.graphics.Orientation import Orientation
from engine.graphics.Renderable import Renderable
from engine.graphics.Renderer import Depth, Renderer
from engine.player.Player import Player


class Engine:
    def __init__(self):
        # pre init
        # pygame.mixer.pre_init(44100, 16, 2, 4096)

        # init
        pygame.init()

        # init graphics
        self.width: float = 256.0
        self.height: float = 224.0
        self.scale_rate: float = 3.0
        # self.flags: int = pygame.DOUBLEBUF
        self.flags: int = 0

        self.__renderer: Renderer = Renderer(size=(self.width, self.height), scale_rate=self.scale_rate,
                                             flags=self.flags)
        self.__renderables: dict[str, Renderable] = dict()

        self.logo: pygame.Surface = pygame.image.load("resources/icons/logo.png").convert_alpha()
        pygame.display.set_icon(self.logo)
        pygame.display.set_caption("The Legend of Younghee")

        # init updates
        self.clock: pygame.time.Clock = pygame.time.Clock()
        self.delta_time: float = self.clock.tick(60)
        self.allowed_events: set[int] = {pygame.QUIT,
                                         pygame.KEYDOWN,
                                         pygame.KEYUP,
                                         pygame.USEREVENT}
        self.allowed_custom_event_types: set[int] = {Events.TITLE_SCREEN_EVENT,
                                                     Events.INPUT_NAME_EVENT}
        pygame.event.set_allowed(list(self.allowed_events))

        # init sounds
        self.__background_musics: dict[str, pygame.mixer.Sound] = dict()
        self.__sound_effects: dict[str, pygame.mixer.Sound] = dict()

        # init resources
        # title screen resources
        self.__title_screen_keys: list[str] = []
        self.title_screen_resource: pygame.Surface = None
        self.title_screen_triforce_frames: list[pygame.Surface] = list()
        self.title_screen_shine_frames: list[pygame.Surface] = list()
        self.title_screen_shine_coordinates: list[Vector2f] = [Vector2f(x=55.0, y=91.0),
                                                               Vector2f(x=194.0, y=127.0),
                                                               Vector2f(x=155.0, y=88.0),
                                                               Vector2f(x=114.0, y=127.0)]
        # input name screen resources
        self.__input_name_screen_keys: list[str] = []
        self.input_name_screen_resource: pygame.Surface = None

        # init gameplay
        self.__players: list[Player] = [None, None, None]
        self.__current_player_index: int = 0

    def __del__(self):
        del self.__renderer
        self.destroy()

    def destroy(self):
        print("quiting pygame...")
        pygame.quit()

    def destroy_title_screen(self):
        for key in self.__title_screen_keys:
            del self.__renderables[key]
            if self.__renderer.remove_renderable(key=key):
                print(f"removed {key} successfully")
            else:
                print(f"unable to remove {key}")
        del self.__title_screen_keys
        self.allowed_custom_event_types.remove(Events.TITLE_SCREEN_EVENT)

        self.__background_musics["title"].stop()

        del self.__background_musics["title"]

    def initialize_title_screen(self):
        self.title_screen_resource: pygame.Surface = pygame.image.load(
            "resources/miscellaneous/title_screen.png").convert_alpha()

        # developer screen
        slice_rect: pygame.Rect = pygame.Rect(559.0, 519.0, 51.0, 16.0)
        self.__renderables["title_screen_developer"] = Renderable(
            surface=self.title_screen_resource.subsurface(slice_rect),
            coordinate=Vector2f(x=(self.width / 2) - 25.5,
                                y=(self.height / 2) - 8.0),
            depth=Depth.UI_DEPTH,
            name="title_screen_developer"
        )
        self.__title_screen_keys.append(self.__renderables["title_screen_developer"].name)

        # copyright image
        slice_rect = pygame.Rect(659.0, 536.0, 73.0, 10.0)
        copyright_surface: pygame.Surface = self.title_screen_resource.subsurface(slice_rect)
        self.__renderables["title_screen_copyright"] = Renderable(surface=copyright_surface,
                                                                  coordinate=Vector2f(
                                                                      x=(self.width / 2) - (
                                                                              copyright_surface.get_width() / 2),
                                                                      y=184.0
                                                                  ),
                                                                  depth=Depth.HUD_DEPTH,
                                                                  name="title_screen_copyright")
        self.__title_screen_keys.append(self.__renderables["title_screen_copyright"].name)

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
            self.title_screen_triforce_frames.append(self.title_screen_resource.subsurface(rect))

        self.__renderables["title_screen_power_triforce"] = Renderable(surface=self.title_screen_triforce_frames[0],
                                                                       coordinate=Vector2f(
                                                                           x=(self.width / 2.0) - (
                                                                               self.title_screen_triforce_frames[
                                                                                   0].get_width() / 2.0),
                                                                           y=-self.title_screen_triforce_frames[
                                                                               0].get_height()
                                                                       ),
                                                                       depth=Depth.NORMAL0_DEPTH,
                                                                       name="title_screen_power_triforce",
                                                                       surfaces=self.title_screen_triforce_frames)
        self.__renderables["title_screen_power_triforce"].flip_x = True
        self.__renderables["title_screen_wisdom_triforce"] = Renderable(surface=self.title_screen_triforce_frames[0],
                                                                        coordinate=Vector2f(x=self.width / 6,
                                                                                            y=self.height),
                                                                        depth=Depth.NORMAL0_DEPTH,
                                                                        name="title_screen_wisdom_triforce",
                                                                        surfaces=self.title_screen_triforce_frames)
        self.__renderables["title_screen_wisdom_triforce"].flip_x = True
        self.__renderables["title_screen_courage_triforce"] = Renderable(surface=self.title_screen_triforce_frames[0],
                                                                         coordinate=Vector2f(
                                                                             x=self.width * (5.0 / 6.0),
                                                                             y=self.height
                                                                         ),
                                                                         depth=Depth.NORMAL0_DEPTH,
                                                                         name="title_screen_courage_triforce",
                                                                         surfaces=self.title_screen_triforce_frames)
        self.__title_screen_keys.append(self.__renderables["title_screen_power_triforce"].name)
        self.__title_screen_keys.append(self.__renderables["title_screen_wisdom_triforce"].name)
        self.__title_screen_keys.append(self.__renderables["title_screen_courage_triforce"].name)

        # triforce
        slice_rect = pygame.Rect(532.0, 421.0, 82.0, 81.0)
        self.__renderables["title_screen_triforce"] = Renderable(
            surface=self.title_screen_resource.subsurface(slice_rect),
            coordinate=Vector2f(x=87, y=60),
            depth=Depth.MAP_DEPTH,
            name="title_screen_triforce"
        )
        self.__title_screen_keys.append(self.__renderables["title_screen_triforce"].name)

        slice_rect = pygame.Rect(16.0, 400.0, 256.0, 143.0)
        self.__renderables["title_screen_background"] = Renderable(
            surface=self.title_screen_resource.subsurface(slice_rect),
            coordinate=Vector2f(x=0, y=31),
            depth=Depth.BACKGROUND_DEPTH,
            name="title_screen_background"
        )
        self.__title_screen_keys.append(self.__renderables["title_screen_background"].name)

        slice_rect = pygame.Rect(304.0, 443.0, 147.0, 44.0)

        self.__renderables["title_screen_over_sword_title"]: Renderable = Renderable(
            surface=self.title_screen_resource.subsurface(slice_rect),
            coordinate=Vector2f(x=52, y=89),
            depth=Depth.VFX_DEPTH,
            name="title_screen_over_sword_title"
        )
        self.__title_screen_keys.append(self.__renderables["title_screen_over_sword_title"].name)

        slice_rect = pygame.Rect(305.0, 418.0, 147.0, 25.0)
        self.__renderables["title_screen_behind_sword_title_upper"]: Renderable = Renderable(
            surface=self.title_screen_resource.subsurface(slice_rect),
            coordinate=Vector2f(x=53, y=64),
            depth=Depth.NORMAL0_DEPTH,
            name="title_screen_behind_sword_title_upper"
        )
        self.__title_screen_keys.append(self.__renderables["title_screen_behind_sword_title_upper"].name)

        slice_rect = pygame.Rect(302.0, 487.0, 174.0, 17.0)
        self.__renderables["title_screen_behind_sword_title_lower"] = Renderable(
            surface=self.title_screen_resource.subsurface(slice_rect),
            coordinate=Vector2f(x=50, y=133),
            depth=Depth.NORMAL0_DEPTH,
            name="title_screen_behind_sword_title_lower"
        )
        self.__title_screen_keys.append(self.__renderables["title_screen_behind_sword_title_lower"].name)

        slice_rect = pygame.Rect(501.0, 399.0, 31.0, 128.0)
        self.__renderables["title_screen_sword"] = Renderable(surface=self.title_screen_resource.subsurface(slice_rect),
                                                              coordinate=Vector2f(x=56, y=-128.0),
                                                              depth=Depth.NORMAL1_DEPTH,
                                                              name="title_screen_sword")
        self.__title_screen_keys.append(self.__renderables["title_screen_sword"].name)

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
            self.title_screen_shine_frames.append(self.title_screen_resource.subsurface(rect))

        self.__renderables["title_screen_shiny_effect"] = Renderable(surface=self.title_screen_shine_frames[0],
                                                                     coordinate=Vector2f(x=0.0, y=0.0),
                                                                     depth=Depth.HUD_DEPTH,
                                                                     name="title_screen_shiny_effect",
                                                                     surfaces=self.title_screen_shine_frames,
                                                                     coordinates=self.title_screen_shine_coordinates)
        self.__title_screen_keys.append(self.__renderables["title_screen_shiny_effect"].name)

        self.__background_musics["title"] = pygame.mixer.Sound(file="resources/musics/title.mp3")
        self.__sound_effects["intro"] = pygame.mixer.Sound(file="resources/sounds/intro.ogg")
        self.__sound_effects["ok"] = pygame.mixer.Sound(file="resources/sounds/ok.ogg")
        self.__sound_effects["sword1"] = pygame.mixer.Sound(file="resources/sounds/sword1.ogg")

    def initialize_input_name_screen(self):
        self.input_name_screen_resource: pygame.Surface = pygame.image.load(
            "resources/miscellaneous/input_name_screen.png").convert_alpha()
        self.input_name_screen_resource.set_colorkey((56, 56, 94))

        # player select
        ui_coordinate: Vector2f = Vector2f(179.0, 253.0)
        slice_rect: pygame.Rect = pygame.Rect(179.0, 253.0, 256.0, 224.0)
        coordinate: Vector2f = Vector2f(179.0, 253.0)
        self.__renderables["input_name_screen_ui"] = Renderable(
            surface=self.input_name_screen_resource.subsurface(slice_rect),
            coordinate=coordinate - ui_coordinate,
            depth=Depth.HUD_DEPTH,
            name="input_name_screen_ui"
        )
        self.__input_name_screen_keys.append(self.__renderables["input_name_screen_ui"].name)

        # player select
        coordinate.set_coordinate(x=211.0, y=276.0)
        player_select_rect_size: Vector2f = coordinate - Vector2f(x=339.0, y=293.0)
        slice_rect = pygame.Rect(46.0, 278.0, 121.0, 13.0)
        self.__renderables["input_name_screen_player_select"] = Renderable(
            surface=self.input_name_screen_resource.subsurface(slice_rect),
            coordinate=Vector2f.get_oriented_vector(top_left=coordinate - ui_coordinate,
                                                    size=player_select_rect_size,
                                                    orientation=Orientation.TOP_LEFT),
            depth=Depth.HUD_DEPTH,
            name="input_name_screen_player_select"
        )
        self.__input_name_screen_keys.append(self.__renderables["input_name_screen_player_select"].name)

        # numbers
        coordinate.set_coordinate(x=201.0, y=324.0)
        slice_rect = pygame.Rect(46.0, 324.0, 121.0, 16.0)
        self.__renderables["input_name_screen_player_one"] = Renderable(
            surface=self.input_name_screen_resource.subsurface(slice_rect),
            coordinate=Vector2f.get_oriented_vector(top_left=coordinate - ui_coordinate,
                                                    size=player_select_rect_size,
                                                    orientation=Orientation.TOP_LEFT),
            depth=Depth.HUD_DEPTH,
            name="input_name_screen_player_one"
        )
        self.__input_name_screen_keys.append(self.__renderables["input_name_screen_player_one"].name)

    def initialize_maps(self):
        # self.light_world_map: pygame.Surface = pygame.image.load("resources/maps/light_world.png")
        # self.screen.blit(source=self.light_world_map, dest=(0, 0))
        pass

    def on_input_name_screen_event(self, event_type: int):
        print(f"input_name_screen_event: {event_type}")
        if event_type == InputNameScreenEvent.START:
            self.initialize_input_name_screen()

            self.__renderer.add_renderable(renderable=self.__renderables["input_name_screen_ui"])
            self.__renderer.add_renderable(renderable=self.__renderables["input_name_screen_player_select"])
            self.__renderer.add_renderable(renderable=self.__renderables["input_name_screen_player_one"])

    def on_title_screen_event(self, event_type: int):
        if event_type == TitleScreenEvent.END:
            self.destroy_title_screen()
            self.__renderer.start_fade_in(duration=1000)
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.INPUT_NAME_EVENT,
                                                           event_type=InputNameScreenEvent.START),
                                  millis=1000)
        elif event_type == TitleScreenEvent.FADE_OUT:
            self.__renderer.remove_renderable(key="title_screen_shiny_effect"),
            self.__renderer.start_fade_out(duration=1000)
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.END),
                                  millis=1000)
        elif event_type == TitleScreenEvent.SHOW_SHINY_EFFECT:
            # show shiny effects
            self.__renderables["title_screen_shiny_effect"].start_coordinate_change(duration=500, should_loop=True)
            self.__renderables["title_screen_shiny_effect"].start_animation(from_frame_index=0,
                                                                            to_frame_index=len(
                                                                                self.title_screen_shine_frames) - 1,
                                                                            duration=500,
                                                                            should_loop=True)
            self.__renderer.add_renderable(renderable=self.__renderables["title_screen_shiny_effect"])
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.FADE_OUT),
                                  millis=8000)
        elif event_type == TitleScreenEvent.FADE_IN_BACKGROUND:
            # show background
            self.__renderer.stop_flashing()
            self.__sound_effects["ok"].stop()
            self.__renderables["title_screen_background"].start_fade_in(duration=1000)
            self.__renderer.add_renderable(renderable=self.__renderables["title_screen_background"])
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.SHOW_SHINY_EFFECT),
                                  millis=1000)
        elif event_type == TitleScreenEvent.SHOW_FLASHING_EFFECT:
            self.__renderer.start_flashing(duration=17)
            self.__sound_effects["sword1"].stop()
            self.__sound_effects["ok"].set_volume(0.5)
            self.__sound_effects["ok"].play()
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.FADE_IN_BACKGROUND),
                                  millis=1003)
        elif event_type == TitleScreenEvent.SHOW_SWORD:
            # show sword
            self.__renderer.add_renderable(renderable=self.__renderables["title_screen_sword"])
            self.__renderer.get_renderable(key="title_screen_sword").start_move(
                from_coordinate=Vector2f(56.0, -float(self.__renderables["title_screen_sword"].surface.get_height())),
                to_coordinate=Vector2f(56.0, 38.0),
                duration=250
            )
            self.__sound_effects["sword1"].set_volume(0.4)
            self.__sound_effects["sword1"].play()
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.SHOW_FLASHING_EFFECT),
                                  millis=250)
        elif event_type == TitleScreenEvent.FADE_IN_TITLE:
            # fade in title
            self.__renderables["title_screen_over_sword_title"].start_fade_in(duration=1000)
            self.__renderables["title_screen_behind_sword_title_upper"].start_fade_in(duration=1000)
            self.__renderables["title_screen_behind_sword_title_lower"].start_fade_in(duration=1000)
            self.__renderer.add_renderable(renderable=self.__renderables["title_screen_over_sword_title"])
            self.__renderer.add_renderable(renderable=self.__renderables["title_screen_behind_sword_title_upper"])
            self.__renderer.add_renderable(renderable=self.__renderables["title_screen_behind_sword_title_lower"])
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.SHOW_SWORD),
                                  millis=1000)
        elif event_type == TitleScreenEvent.SHOW_COMPLETE_TRIFORCE:
            # show completed triforce
            self.__renderer.remove_renderable(key="title_screen_power_triforce")
            self.__renderer.remove_renderable(key="title_screen_wisdom_triforce")
            self.__renderer.remove_renderable(key="title_screen_courage_triforce")
            self.__renderer.add_renderable(renderable=self.__renderables["title_screen_triforce"])
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.FADE_IN_TITLE),
                                  millis=1500)
        elif event_type == TitleScreenEvent.PLAY_MUSIC:
            # play title music
            self.__background_musics["title"].set_volume(0.4)
            self.__background_musics["title"].play()
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.SHOW_COMPLETE_TRIFORCE),
                                  millis=5000 - 160)
        elif event_type == TitleScreenEvent.ANIMATE_TRIFORCE:
            # animate triforce
            self.__renderables["title_screen_power_triforce"].start_move(
                from_coordinate=self.__renderables["title_screen_power_triforce"].coordinate,
                to_coordinate=Vector2f(x=107.0, y=60.0),
                duration=4000
            )
            self.__renderables["title_screen_wisdom_triforce"].start_move(
                from_coordinate=self.__renderables["title_screen_wisdom_triforce"].coordinate,
                to_coordinate=Vector2f(x=87.0, y=100.0),
                duration=4000
            )
            self.__renderables["title_screen_courage_triforce"].start_move(
                from_coordinate=self.__renderables["title_screen_courage_triforce"].coordinate,
                to_coordinate=Vector2f(x=128.0, y=100.0),
                duration=4000
            )
            self.__renderables["title_screen_power_triforce"].start_animation(from_frame_index=0,
                                                                              to_frame_index=len(
                                                                                  self.title_screen_triforce_frames),
                                                                              duration=5000)
            self.__renderables["title_screen_wisdom_triforce"].start_animation(from_frame_index=0,
                                                                               to_frame_index=len(
                                                                                   self.title_screen_triforce_frames),
                                                                               duration=5000)
            self.__renderables["title_screen_courage_triforce"].start_animation(from_frame_index=0,
                                                                                to_frame_index=len(
                                                                                    self.title_screen_triforce_frames),
                                                                                duration=5000)
            self.__renderer.add_renderable(renderable=self.__renderables["title_screen_power_triforce"])
            self.__renderer.add_renderable(renderable=self.__renderables["title_screen_wisdom_triforce"])
            self.__renderer.add_renderable(renderable=self.__renderables["title_screen_courage_triforce"])
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.PLAY_MUSIC),
                                  millis=160)
        elif event_type == TitleScreenEvent.SHOW_COPYRIGHT:
            # show copyright
            self.__renderer.remove_renderable(key="title_screen_developer")
            self.__renderer.add_renderable(renderable=self.__renderables["title_screen_copyright"])
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.ANIMATE_TRIFORCE),
                                  millis=500)
        elif event_type == TitleScreenEvent.FADE_OUT_DEVELOPER:
            # fade out developer
            self.__renderer.get_renderable(key="title_screen_developer").start_fade_out(duration=1000)
            self.__sound_effects["intro"].stop()
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.SHOW_COPYRIGHT),
                                  millis=2000)
        elif event_type == TitleScreenEvent.SHOW_DEVELOPER:
            self.__renderer.add_renderable(renderable=self.__renderables["title_screen_developer"])
            self.__sound_effects["intro"].play()

            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.TITLE_SCREEN_EVENT,
                                                           event_type=TitleScreenEvent.FADE_OUT_DEVELOPER),
                                  millis=1000)
        else:
            assert False

    def run(self):
        # fps: Renderable = Renderable(
        #     surface=pygame.font.SysFont("Monospace", 8).render(f"{int(self.clock.get_fps())}",
        #                                                        False,
        #                                                        (255, 255, 255)), coordinate=(0.0, 0.0),
        #     depth=Depth.DEBUG_DEPTH,
        #     name="fps_text"
        # )
        # self.__renderer.add_renderable(renderable=fps)
        self.initialize_title_screen()
        pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                       class_type=Events.TITLE_SCREEN_EVENT,
                                                       event_type=TitleScreenEvent.SHOW_DEVELOPER),
                              millis=1000)

        while 1:
            if pygame.event.peek():
                event: pygame.event.Event = pygame.event.poll()
                # if event.type not in self.allowed_events:
                #     continue

                # print(f"event: {event}")

                if event.type == pygame.QUIT:
                    self.destroy()
                    return
                elif event.type == pygame.USEREVENT:
                    print(f"event: {event}")
                    if "class_type" in event.__dict__:
                        if event.class_type not in self.allowed_custom_event_types:
                            continue
                        if event.class_type == Events.TITLE_SCREEN_EVENT:
                            self.on_title_screen_event(event_type=event.event_type)
                        elif event.class_type == Events.INPUT_NAME_EVENT:
                            self.on_input_name_screen_event(event_type=event.event_type)

            self.__renderer.update(delta_time=self.clock.tick(60))
            # fps: Renderable = Renderable(
            #     surface=pygame.font.SysFont("Monospace", 8).render(f"{int(self.clock.get_fps())}",
            #                                                        False,
            #                                                        (255, 255, 255)), coordinate=(0.0, 0.0),
            #     depth=Depth.DEBUG_DEPTH,
            #     name="fps_text"
            # )
            # self.__renderer.set_renderable(key="fps_text", renderable=fps)
            self.__renderer.render()
