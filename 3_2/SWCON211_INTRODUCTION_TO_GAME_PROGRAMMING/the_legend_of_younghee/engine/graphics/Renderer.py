import pygame

from engine.core.Math import Vector2f
from engine.graphics.Renderable import Renderable


class Depth:
    BACKGROUND_DEPTH: int = 0
    MAP_DEPTH: int = 1
    NORMAL0_DEPTH: int = 2
    NORMAL1_DEPTH: int = 3
    VFX_DEPTH: int = 4
    HUD_DEPTH: int = 5
    UI_DEPTH: int = 6
    DEBUG_DEPTH: int = 7


class Renderer:
    __slots__ = ["__scale_rate",
                 "__flags",
                 "__size",
                 "__front_buffer",
                 "__back_buffer",
                 "__renderables",
                 "__renderables_key_to_depth",
                 "__should_flash",
                 "__flashing_index",
                 "__flashing_counter",
                 "__flashing_duration",
                 "__player_offset",
                 "__offset_limit_top_left",
                 "__offset_limit_bottom_right"]

    def __init__(self, size: Vector2f, scale_rate: float = 1.0, flags: int = 0) -> None:
        assert isinstance(size, Vector2f) and isinstance(scale_rate, float) and isinstance(flags, int)
        self.__scale_rate: float = scale_rate
        self.__flags: int = flags
        self.__size: Vector2f = size
        self.__front_buffer: pygame.Surface = pygame.display.set_mode(
            size=(self.__size.x * self.__scale_rate, self.__size.y * self.__scale_rate),
            flags=self.__flags, depth=16)
        self.__back_buffer: pygame.Surface = pygame.Surface(size=Vector2f.to_tuple(vector=self.__size))

        self.__renderables: list[dict[str, Renderable]] = [dict(),
                                                           dict(),
                                                           dict(),
                                                           dict(),
                                                           dict(),
                                                           dict(),
                                                           dict(),
                                                           dict()]
        self.__renderables_key_to_depth: dict[str, int] = dict()

        self.__renderables_key_to_depth["title_screen_flashing_mask"] = Depth.DEBUG_DEPTH
        self.__renderables[Depth.DEBUG_DEPTH]["title_screen_flashing_mask"] = Renderable(
            surface=pygame.Surface(size=self.__back_buffer.get_size()),
            coordinate=Vector2f(x=0.0, y=0.0),
            depth=Depth.DEBUG_DEPTH,
            name="title_screen_flashing_mask"
        )
        self.__renderables[Depth.DEBUG_DEPTH]["title_screen_flashing_mask"].surface.set_alpha(0)

        self.__renderables_key_to_depth["fade_screen"] = Depth.DEBUG_DEPTH
        self.__renderables[Depth.DEBUG_DEPTH]["fade_screen"] = Renderable(
            surface=pygame.Surface(size=self.__back_buffer.get_size()),
            coordinate=Vector2f(x=0, y=0),
            depth=Depth.DEBUG_DEPTH,
            name="fade_screen"
        )
        self.__renderables[Depth.DEBUG_DEPTH]["fade_screen"].surface.set_alpha(0)

        self.__should_flash: bool = False
        self.__flashing_index: int = 0
        self.__flashing_counter: int = 0
        self.__flashing_duration: int = 0

        self.__player_offset: Vector2f = Vector2f(x=self.__size.x / 2.0, y=self.__size.y / 2.0)
        self.__offset_limit_top_left: Vector2f = Vector2f(x=0.0, y=0.0)
        self.__offset_limit_bottom_right: Vector2f = Vector2f(x=0.0, y=0.0)

    @property
    def player_offset(self) -> Vector2f:
        return self.__player_offset

    @player_offset.setter
    def player_offset(self, player_offset: Vector2f) -> None:
        self.__player_offset.x = player_offset.x
        self.__player_offset.y = player_offset.y

    @property
    def unscaled_size(self) -> Vector2f:
        return self.__size

    @property
    def scaled_size(self) -> Vector2f:
        return self.__size * self.__scale_rate

    def add_renderable(self, renderable: Renderable) -> bool:
        if renderable.name in self.__renderables[renderable.depth] or \
                renderable.name in self.__renderables_key_to_depth:
            return False
        self.__renderables[renderable.depth][renderable.name] = renderable
        self.__renderables_key_to_depth[renderable.name] = renderable.depth

        return True

    def get_renderable(self, key: str) -> Renderable:
        if key in self.__renderables_key_to_depth:
            return self.__renderables[self.__renderables_key_to_depth[key]][key]

        return None

    def has_renderable(self, key: str) -> bool:
        if key not in self.__renderables_key_to_depth:
            return False

        return key in self.__renderables[self.__renderables_key_to_depth[key]]

    def set_offset_limit(self, top_left: Vector2f, bottom_right: Vector2f):
        self.__offset_limit_top_left.copy(other=top_left)
        self.__offset_limit_bottom_right.copy(other=bottom_right)

    def set_renderable(self, key: str, renderable: Renderable) -> bool:
        assert key == renderable.name
        if key in self.__renderables[renderable.depth] and key in self.__renderables_key_to_depth:
            self.__renderables[renderable.depth][key] = renderable
            return True

        return False

    def remove_renderable(self, key: str) -> bool:
        # print(f"remove {key}")
        if key in self.__renderables_key_to_depth and key in self.__renderables[self.__renderables_key_to_depth[key]]:
            del self.__renderables[self.__renderables_key_to_depth[key]][key]
            del self.__renderables_key_to_depth[key]
            return True

        return False

    def start_fade_in(self, duration: int):
        print(f"renderer fade in")
        self.__renderables[Depth.DEBUG_DEPTH]["fade_screen"].start_fade_out(duration=duration)

    def start_fade_out(self, duration: int):
        print(f"renderer fade out")
        self.__renderables[Depth.DEBUG_DEPTH]["fade_screen"].start_fade_in(duration=duration)

    def start_flashing(self, duration: int):
        self.__should_flash = True
        self.__flashing_index = 0
        self.__flashing_counter = 0
        self.__flashing_duration = duration
        self.__renderables[Depth.DEBUG_DEPTH]["title_screen_flashing_mask"].surface.set_alpha(85)

    def stop_flashing(self):
        self.__should_flash = False
        self.__renderables[Depth.DEBUG_DEPTH]["title_screen_flashing_mask"].surface.set_alpha(0)

    def update(self, delta_time: float) -> None:
        if self.__should_flash:
            self.__flashing_counter += delta_time

            toggle_next_flash: bool = self.__flashing_counter > self.__flashing_duration
            if toggle_next_flash:
                self.__flashing_index += 1
                self.__flashing_counter = self.__flashing_counter - self.__flashing_duration

            if self.__flashing_index % 4 == 0:
                self.__renderables[Depth.DEBUG_DEPTH]["title_screen_flashing_mask"].surface.fill(color=(255, 0, 0))
            elif self.__flashing_index % 4 == 1:
                self.__renderables[Depth.DEBUG_DEPTH]["title_screen_flashing_mask"].surface.fill(color=(0, 255, 0))
            elif self.__flashing_index % 4 == 2:
                self.__renderables[Depth.DEBUG_DEPTH]["title_screen_flashing_mask"].surface.fill(color=(0, 0, 255))

        for renderables in self.__renderables:
            # print(f"renderables: {renderables}")
            for renderable in renderables.values():
                # print(f"\trenderable: {renderable}")
                renderable.update(delta_time=delta_time)

    def render(self) -> None:
        self.__back_buffer: pygame.Surface = pygame.Surface(size=Vector2f.to_tuple(vector=self.__size))

        for renderables in self.__renderables:
            for renderable in renderables.values():
                coordinate: Vector2f = Vector2f(x=renderable.coordinate.x - min(max(self.__player_offset.x, self.__offset_limit_top_left.x + self.__size.x / 2.0), self.__offset_limit_bottom_right.x - self.__size.x / 2.0) + self.__size.x / 2.0,
                                                y=renderable.coordinate.y - min(max(self.__player_offset.y, self.__offset_limit_top_left.y + self.__size.y / 2.0), self.__offset_limit_bottom_right.y - self.__size.y / 2.0) + self.__size.y / 2.0)
                self.__back_buffer.blit(source=renderable.surface,
                                        dest=Vector2f.to_tuple(vector=coordinate))

        self.__back_buffer = pygame.transform.scale(surface=self.__back_buffer, size=(
            self.__back_buffer.get_width() * self.__scale_rate, self.__back_buffer.get_height() * self.__scale_rate))
        self.__front_buffer.blit(source=self.__back_buffer, dest=(0, 0))
        pygame.display.flip()
