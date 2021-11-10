import sys

import pygame
import traceback

from engine.core.Math import Math
from engine.events.Events import Events


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
        self.front_buffer: pygame.Surface = pygame.display.set_mode(
            size=(self.width * self.scale_rate, self.height * self.scale_rate),
            flags=self.flags, depth=16)
        self.back_buffer: pygame.Surface = pygame.Surface(size=(self.width, self.height))
        self.z_buffer_depth: int = 8
        self.surfaces: list[dict[str, tuple[pygame.Surface, tuple[float, float]]]] = [dict() for i in
                                                                                      range(0, self.z_buffer_depth)]

        self.logo: pygame.Surface = pygame.image.load("resources/icons/logo.png").convert_alpha()
        pygame.display.set_icon(self.logo)
        pygame.display.set_caption("The Legend of Younghee")

        # init updates
        self.clock: pygame.time.Clock = pygame.time.Clock()
        self.delta_time: float = self.clock.tick(60)
        self.allowed_events: set[int] = {pygame.QUIT,
                                         pygame.KEYDOWN,
                                         pygame.KEYUP,
                                         Events.TITLE_SCREEN_DEVELOPER_TIMER_EVENT,
                                         Events.TITLE_SCREEN_SHOW_COPYRIGHT_EVENT}
        pygame.event.set_allowed(list(self.allowed_events))

        # init sounds

        self.is_opening_screen: bool = True

        self.title_screen_resource: pygame.Surface = None
        self.title_screen_developer: pygame.Surface = None
        self.title_screen_background: pygame.Surface = None
        self.title_screen_title: pygame.Surface = None
        self.title_screen_over_sword_title: pygame.Surface = None
        self.title_screen_behind_sword_title_upper: pygame.Surface = None
        self.title_screen_behind_sword_title_lower: pygame.Surface = None
        self.title_screen_copyright: pygame.Surface = None
        self.title_screen_triforce_frames: list[pygame.Surface] = list()
        self.title_screen_triforce_frame_index: int = 0
        self.title_screen_triforce_start_time: int = None
        self.is_title_screen_triforce: bool = False
        self.title_screen_triforce: pygame.Surface = None
        self.title_screen_sword: pygame.Surface = None
        self.title_screen_shine_frames: list[pygame.Surface] = list()
        self.title_screen_shine_coordinates: list[tuple[float, float]] = [(55.0, 91.0), (194.0, 127.0), (155.0, 88.0),
                                                                          (114.0, 127.0)]
        self.title_screen_title_music: pygame.mixer.Sound = None
        self.title_screen_intro_sound_effect: pygame.mixer.Sound = None

        self.input_name_screen_resource: pygame.Surface = None
        self.input_name_screen_player_select: pygame.Surface = None

        self.light_world_map: pygame.Surface = None
        self.fps_text: pygame.Surface = None

        self.common_index: int = 0

    def __del__(self):
        self.destroy()

    def destroy(self):
        pygame.quit()

    def initialize_title_screen(self):
        self.title_screen_resource: pygame.Surface = pygame.image.load(
            "resources/miscellaneous/title_screen.png").convert_alpha()

        # developer screen
        slice_rect: pygame.Rect = pygame.Rect(559.0, 519.0, 51.0, 16.0)
        self.title_screen_developer: pygame.Surface = self.title_screen_resource.subsurface(slice_rect)

        # copyright image
        slice_rect = pygame.Rect(659.0, 536.0, 73.0, 10.0)
        self.title_screen_copyright: pygame.Surface = self.title_screen_resource.subsurface(slice_rect)

        # triforce animation
        self.triforce_floating_frames: int = 104
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

        # triforce
        slice_rect = pygame.Rect(532.0, 421.0, 82.0, 81.0)
        self.title_screen_triforce: pygame.Surface = self.title_screen_resource.subsurface(slice_rect)

        slice_rect = pygame.Rect(16.0, 400.0, 256.0, 143.0)
        self.title_screen_background: pygame.Surface = self.title_screen_resource.subsurface(slice_rect)
        # self.screen.blit(source=self.title_screen_background, dest=(0, 40))

        slice_rect = pygame.Rect(302.0, 418.0, 175.0, 86.0)
        self.title_screen_title: pygame.Surface = self.title_screen_resource.subsurface(slice_rect)
        self.title_screen_title.set_alpha(0)

        slice_rect = pygame.Rect(304.0, 443.0, 147.0, 44.0)
        self.title_screen_over_sword_title: pygame.Surface = self.title_screen_resource.subsurface(slice_rect)
        self.title_screen_over_sword_title.set_alpha(0)

        slice_rect = pygame.Rect(305.0, 418.0, 147.0, 25.0)
        self.title_screen_behind_sword_title_upper: pygame.Surface = self.title_screen_resource.subsurface(slice_rect)
        self.title_screen_behind_sword_title_upper.set_alpha(0)

        slice_rect = pygame.Rect(302.0, 487.0, 174.0, 17.0)
        self.title_screen_behind_sword_title_lower: pygame.Surface = self.title_screen_resource.subsurface(slice_rect)
        self.title_screen_behind_sword_title_lower.set_alpha(0)

        slice_rect = pygame.Rect(501.0, 399.0, 31.0, 128.0)
        self.title_screen_sword: pygame.Surface = self.title_screen_resource.subsurface(slice_rect)

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

        self.title_screen_title_music: pygame.mixer.Sound = pygame.mixer.Sound(file="resources/musics/title.mp3")
        self.title_screen_intro_sound_effect: pygame.mixer.Sound = pygame.mixer.Sound(file="resources/sounds/intro.ogg")

    def destroy_title_screen(self):
        del self.title_screen_resource
        del self.title_screen_developer
        del self.title_screen_background
        del self.title_screen_title
        del self.title_screen_over_sword_title
        del self.title_screen_behind_sword_title_upper
        del self.title_screen_behind_sword_title_lower
        del self.title_screen_copyright
        del self.title_screen_triforce_frames
        del self.title_screen_triforce_frame_index
        del self.title_screen_triforce_start_time
        del self.is_title_screen_triforce
        del self.title_screen_triforce
        del self.title_screen_sword
        del self.title_screen_shine_frames
        del self.title_screen_shine_coordinates
        del self.title_screen_title_music
        del self.title_screen_intro_sound_effect

    def initialize_input_name_screen(self):
        self.input_name_screen_resource: pygame.Surface = pygame.image.load(
            "resources/miscellaneous/input_name_screen.png").convert_alpha()
        self.input_name_screen_resource.set_colorkey(color=(56, 56, 94))

        self.input_name_screen_player_select: pygame.Surface = self.input_name_screen_resource.subsurface()


    def initialize_maps(self):
        # self.light_world_map: pygame.Surface = pygame.image.load("resources/maps/light_world.png")
        # self.screen.blit(source=self.light_world_map, dest=(0, 0))
        pass

    def on_title_screen_triforce(self):
        pass

    def on_title_screen_developer(self):
        if Events.TITLE_SCREEN_DEVELOPER_TIMER_EVENT not in self.allowed_events:
            return

        self.title_screen_intro_sound_effect.stop()
        self.title_screen_developer.set_alpha(
            max(int(self.title_screen_developer.get_alpha() - 256 / 60), 0))

        if self.title_screen_developer.get_alpha() > 0:
            pygame.event.post(pygame.event.Event(Events.TITLE_SCREEN_DEVELOPER_TIMER_EVENT))
        else:
            del self.surfaces[5]["title_screen_developer"]
            self.allowed_events.remove(Events.TITLE_SCREEN_DEVELOPER_TIMER_EVENT)
            pygame.event.set_allowed(list(self.allowed_events))
            pygame.time.set_timer(event=Events.TITLE_SCREEN_SHOW_COPYRIGHT_EVENT, millis=1000)

    def render(self):
        self.back_buffer: pygame.Surface = pygame.Surface(size=(self.width, self.height))
        # for i, buffer in enumerate(self.surfaces):
        # print(f"{i}: {buffer}")
        for buffer in self.surfaces.copy():
            for surface in buffer.copy().values():
                # print(f"\tRendering {surface[0]} on {surface[1]}")
                self.back_buffer.blit(source=surface[0], dest=surface[1])
        self.back_buffer = pygame.transform.scale(surface=self.back_buffer, size=(
            self.back_buffer.get_width() * self.scale_rate, self.back_buffer.get_height() * self.scale_rate))
        self.front_buffer.blit(source=self.back_buffer, dest=(0, 0))
        pygame.display.flip()

    def run(self):
        self.initialize_title_screen()
        pygame.time.wait(1000)
        self.show_title_screen_developer()

        sword_alpha: float = 0.0
        flashing_index: int = 0
        background_fade_in_index: int = 0
        shiny_effect_index: int = 0
        while 1:
            if pygame.event.peek():
                event: pygame.event.Event = pygame.event.poll()
                if event.type not in self.allowed_events:
                    continue

                if event.type == pygame.QUIT:
                    self.destroy()
                    return
                elif event.type > pygame.USEREVENT:
                    if event.type == Events.TITLE_SCREEN_DEVELOPER_TIMER_EVENT:
                        self.on_title_screen_developer()
                    elif event.type == Events.TITLE_SCREEN_SHOW_COPYRIGHT_EVENT:
                        self.show_title_screen_copyright()
                    elif event.type == Events.TITLE_SCREEN_TRIFORCE_START_EVENT:
                        self.show_title_screen_triforce(
                            frame_index=int(self.title_screen_triforce_frame_index / 2))
                        self.title_screen_triforce_frame_index += 1
                    elif event.type == Events.TITLE_SCREEN_SHOW_TITLE_EVENT:
                        self.show_title_screen_title()
                    elif event.type == Events.TITLE_SCREEN_SHOW_SWORD_EVENT:
                        self.show_title_screen_sword(alpha=sword_alpha)
                        sword_alpha += 6.0 / self.clock.get_fps()
                    elif event.type == Events.TITLE_SCREEN_SHOW_FLASHING_EFFECT_EVENT:
                        self.show_title_screen_flashing(flashing_index=flashing_index)
                        flashing_index += 1
                    elif event.type == Events.TITLE_SCREEN_SHOW_BACKGROUND_EVENT:
                        self.show_title_screen_background(background_index=background_fade_in_index)
                        background_fade_in_index += 1
                    elif event.type == Events.TITLE_SCREEN_SHOW_SHINY_EFFECT_EVENT:
                        self.show_title_screen_shiny_effect(frame_index=shiny_effect_index)
                        shiny_effect_index += 1
                    elif event.type == Events.TITLE_SCREEN_FADE_OUT_EVENT:
                        self.show_title_screen_fade_out()


            self.clock.tick(60)
            self.surfaces[7]["fps_text"] = (pygame.font.SysFont("Monospace", 8).render(f"{int(self.clock.get_fps())}",
                                                                                       False,
                                                                                       (255, 255, 255)), (0, 0))
            self.render()

    def show_title_screen_copyright(self):
        self.surfaces[5]["title_screen_copyright"] = (self.title_screen_copyright, (
            (self.width / 2) - (self.title_screen_copyright.get_width() / 2),
            184.0))
        self.allowed_events.remove(Events.TITLE_SCREEN_SHOW_COPYRIGHT_EVENT)
        self.allowed_events.add(Events.TITLE_SCREEN_TRIFORCE_START_EVENT)
        pygame.event.set_allowed(list(self.allowed_events))
        pygame.time.set_timer(event=Events.TITLE_SCREEN_TRIFORCE_START_EVENT, millis=500)

    def show_title_screen_background(self, background_index):
        self.surfaces[1]["title_screen_background"] = (self.title_screen_background, (0, 31))
        self.title_screen_background.set_alpha(
            int(Math.lerp_float(x=0.0, y=255.0, alpha=min(background_index / 60.0, 1.0))))

        if self.title_screen_background.get_alpha() >= 255:
            self.allowed_events.remove(Events.TITLE_SCREEN_SHOW_BACKGROUND_EVENT)
            self.allowed_events.add(Events.TITLE_SCREEN_SHOW_SHINY_EFFECT_EVENT)
            pygame.event.set_allowed(list(self.allowed_events))

            pygame.event.post(pygame.event.Event(Events.TITLE_SCREEN_SHOW_SHINY_EFFECT_EVENT))
        else:
            pygame.event.post(pygame.event.Event(Events.TITLE_SCREEN_SHOW_BACKGROUND_EVENT))

    def show_title_screen_developer(self):
        self.surfaces[5]["title_screen_developer"] = (self.title_screen_developer, (
            (self.width / 2) - (self.title_screen_developer.get_width() / 2),
            (self.height / 2) - (self.title_screen_developer.get_height() / 2)))
        self.title_screen_intro_sound_effect.play()
        pygame.time.set_timer(event=Events.TITLE_SCREEN_DEVELOPER_TIMER_EVENT, millis=1000)

    def show_title_screen_fade_out(self):
        self.surfaces[7]["title_screen_fade_out"] = (pygame.Surface(size=(self.width, self.height)), (0, 0))
        self.surfaces[7]["title_screen_fade_out"][0].fill(color=(0, 0, 0))
        self.surfaces[7]["title_screen_fade_out"][0].set_alpha(
            Math.lerp_float(x=0.0, y=255.0, alpha=self.common_index / 90))

        if self.surfaces[7]["title_screen_fade_out"][0].get_alpha() >= 255:
            self.allowed_events.remove(Events.TITLE_SCREEN_FADE_OUT_EVENT)
            pygame.event.set_allowed(list(self.allowed_events))

            del self.surfaces[7]["title_screen_fade_out"]
            del self.surfaces[5]["title_screen_copyright"]
            del self.surfaces[5]["title_screen_over_sword_title"]
            del self.surfaces[4]["title_screen_sword"]
            del self.surfaces[3]["title_screen_behind_sword_title_upper"]
            del self.surfaces[3]["title_screen_behind_sword_title_lower"]
            del self.surfaces[2]["title_screen_triforce"]
            del self.surfaces[1]["title_screen_background"]

            self.common_index = 0
            self.title_screen_title_music.stop()
        else:
            self.common_index += 1
            pygame.event.post(pygame.event.Event(Events.TITLE_SCREEN_FADE_OUT_EVENT))

    def show_title_screen_flashing(self, flashing_index: int):
        if flashing_index % 4 == 0:
            self.surfaces[7]["title_screen_flashing_mask"] = (
                pygame.Surface(size=(self.width, self.height)), (0, 0))
            self.surfaces[7]["title_screen_flashing_mask"][0].fill(color=(255, 0, 0))
            self.surfaces[7]["title_screen_flashing_mask"][0].set_alpha(85)
        elif flashing_index % 4 == 1:
            self.surfaces[7]["title_screen_flashing_mask"] = (
                pygame.Surface(size=(self.width, self.height)), (0, 0))
            self.surfaces[7]["title_screen_flashing_mask"][0].fill(color=(0, 255, 0))
            self.surfaces[7]["title_screen_flashing_mask"][0].set_alpha(85)
        elif flashing_index % 4 == 2:
            self.surfaces[7]["title_screen_flashing_mask"] = (
                pygame.Surface(size=(self.width, self.height)), (0, 0))
            self.surfaces[7]["title_screen_flashing_mask"][0].fill(color=(0, 0, 255))
            self.surfaces[7]["title_screen_flashing_mask"][0].set_alpha(85)
        else:
            self.surfaces[7]["title_screen_flashing_mask"][0].set_alpha(0)

        if flashing_index > 60:
            del self.surfaces[7]["title_screen_flashing_mask"]

            self.allowed_events.remove(Events.TITLE_SCREEN_SHOW_FLASHING_EFFECT_EVENT)
            self.allowed_events.add(Events.TITLE_SCREEN_SHOW_BACKGROUND_EVENT)
            pygame.event.set_allowed(list(self.allowed_events))

            pygame.event.post(pygame.event.Event(Events.TITLE_SCREEN_SHOW_BACKGROUND_EVENT))
        else:
            pygame.event.post(pygame.event.Event(Events.TITLE_SCREEN_SHOW_FLASHING_EFFECT_EVENT))

    def show_title_screen_shiny_effect(self, frame_index: int):
        shiny_effect_delay: int = 3
        delay: int = 2
        if int(frame_index / (shiny_effect_delay * len(self.title_screen_shine_frames))) % delay == 0:
            coord_index: int = int(frame_index / (shiny_effect_delay * len(self.title_screen_shine_frames) * delay)) % len(self.title_screen_shine_coordinates)
            self.surfaces[6]["title_screen_shiny_effect"] = (
                self.title_screen_shine_frames[
                    int(frame_index / shiny_effect_delay) % len(self.title_screen_shine_frames)],
                (self.title_screen_shine_coordinates[coord_index][0] - (self.title_screen_shine_frames[
                                                                            int(frame_index / shiny_effect_delay) % len(
                                                                                self.title_screen_shine_frames)].get_width() / 2),
                 (self.title_screen_shine_coordinates[coord_index][1] - (self.title_screen_shine_frames[
                                                                             int(frame_index / shiny_effect_delay) % len(
                                                                                 self.title_screen_shine_frames)].get_height() / 2))))
            self.surfaces[6]["title_screen_shiny_effect"][0].set_alpha(255)
        else:
            self.surfaces[6]["title_screen_shiny_effect"][0].set_alpha(0)

        if frame_index > 60 * 8:
            del self.surfaces[6]["title_screen_shiny_effect"]
            self.allowed_events.remove(Events.TITLE_SCREEN_SHOW_SHINY_EFFECT_EVENT)
            self.allowed_events.add(Events.TITLE_SCREEN_FADE_OUT_EVENT)

            pygame.event.set_allowed(list(self.allowed_events))

            pygame.event.post(pygame.event.Event(Events.TITLE_SCREEN_FADE_OUT_EVENT))
        else:
            pygame.event.post(pygame.event.Event(Events.TITLE_SCREEN_SHOW_SHINY_EFFECT_EVENT))

    def show_title_screen_sword(self, alpha: float):
        self.surfaces[4]["title_screen_sword"] = (
            self.title_screen_sword,
            Math.lerp_tuples((56, -self.title_screen_sword.get_height()), (56, 38), alpha=min(alpha, 1.0)))
        if alpha >= 1.0:
            self.allowed_events.remove(Events.TITLE_SCREEN_SHOW_SWORD_EVENT)
            self.allowed_events.add(Events.TITLE_SCREEN_SHOW_FLASHING_EFFECT_EVENT)
            pygame.event.set_allowed(list(self.allowed_events))

            pygame.event.post(pygame.event.Event(Events.TITLE_SCREEN_SHOW_FLASHING_EFFECT_EVENT))
        else:
            pygame.event.post(pygame.event.Event(Events.TITLE_SCREEN_SHOW_SWORD_EVENT))

    def show_title_screen_title(self):
        self.surfaces[5]["title_screen_over_sword_title"] = (self.title_screen_over_sword_title, (52, 89))
        self.surfaces[3]["title_screen_behind_sword_title_upper"] = (
            self.title_screen_behind_sword_title_upper, (53, 64))
        self.surfaces[3]["title_screen_behind_sword_title_lower"] = (
            self.title_screen_behind_sword_title_lower, (50, 133))
        self.title_screen_behind_sword_title_upper.set_alpha(
            self.title_screen_behind_sword_title_upper.get_alpha() + int(256.0 * (1.0 / self.clock.get_fps())))
        self.title_screen_over_sword_title.set_alpha(
            self.title_screen_over_sword_title.get_alpha() + int(256.0 * (1.0 / self.clock.get_fps())))
        self.title_screen_behind_sword_title_lower.set_alpha(
            self.title_screen_behind_sword_title_lower.get_alpha() + int(256.0 * (1.0 / self.clock.get_fps())))

        if self.title_screen_behind_sword_title_lower.get_alpha() >= 255:
            self.allowed_events.remove(Events.TITLE_SCREEN_SHOW_TITLE_EVENT)
            self.allowed_events.add(Events.TITLE_SCREEN_SHOW_SWORD_EVENT)
            pygame.event.set_allowed(list(self.allowed_events))

            pygame.event.post(pygame.event.Event(Events.TITLE_SCREEN_SHOW_SWORD_EVENT))
        else:
            pygame.event.post(pygame.event.Event(Events.TITLE_SCREEN_SHOW_TITLE_EVENT))

    def show_title_screen_triforce(self, frame_index: int):
        if Events.TITLE_SCREEN_TRIFORCE_START_EVENT not in self.allowed_events:
            return

        if frame_index >= len(self.title_screen_triforce_frames):
            self.allowed_events.remove(Events.TITLE_SCREEN_TRIFORCE_START_EVENT)
            self.allowed_events.add(Events.TITLE_SCREEN_SHOW_TITLE_EVENT)
            pygame.event.set_allowed(list(self.allowed_events))
            pygame.event.post(pygame.event.Event(Events.TITLE_SCREEN_SHOW_TITLE_EVENT))
            self.surfaces[2]["title_screen_triforce"] = (self.title_screen_triforce, (87, 60))

            del self.surfaces[4]["title_screen_power_triforce"]
            del self.surfaces[4]["title_screen_wisdom_triforce"]
            del self.surfaces[4]["title_screen_courage_triforce"]

            return

        if frame_index == 10:
            self.title_screen_title_music.set_volume(0.4)
            self.title_screen_title_music.play()

        self.surfaces[4]["title_screen_power_triforce"] = (
            pygame.transform.flip(surface=self.title_screen_triforce_frames[frame_index], flip_x=True, flip_y=False),
            Math.lerp_tuples(((self.width / 2) - (
                    self.title_screen_triforce_frames[
                        0].get_width() / 2),
                              -self.title_screen_triforce_frames[0].get_height()),
                             (107.0, 60.0),
                             min(frame_index / self.triforce_floating_frames, 1.0)))
        self.surfaces[4]["title_screen_wisdom_triforce"] = (
            pygame.transform.flip(surface=self.title_screen_triforce_frames[frame_index], flip_x=True, flip_y=False),
            Math.lerp_tuples((self.width / 6, self.height), (87.0, 100.0),
                             min(frame_index / self.triforce_floating_frames, 1.0)))
        self.surfaces[4]["title_screen_courage_triforce"] = (
            self.title_screen_triforce_frames[frame_index],
            Math.lerp_tuples((self.width * (5.0 / 6.0), self.height), (128.0, 100.0),
                             min(frame_index / self.triforce_floating_frames, 1.0)))
        pygame.event.post(pygame.event.Event(Events.TITLE_SCREEN_TRIFORCE_START_EVENT))
