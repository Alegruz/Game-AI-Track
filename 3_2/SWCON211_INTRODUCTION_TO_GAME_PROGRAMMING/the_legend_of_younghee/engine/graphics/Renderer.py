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
                 "__flashing_duration"]

    def __init__(self, size: tuple[float, float], scale_rate: float = 1.0, flags: int = 0) -> None:
        self.__scale_rate: float = scale_rate
        self.__flags: int = flags
        self.__size: tuple[float, float] = size
        self.__front_buffer: pygame.Surface = pygame.display.set_mode(
            size=(self.__size[0] * self.__scale_rate, self.__size[1] * self.__scale_rate),
            flags=self.__flags, depth=16)
        self.__back_buffer: pygame.Surface = pygame.Surface(size=self.__size)

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

    def set_renderable(self, key: str, renderable: Renderable) -> bool:
        assert key == renderable.name
        if key in self.__renderables[renderable.depth] and key in self.__renderables_key_to_depth:
            self.__renderables[renderable.depth][key] = renderable
            return True

        return False

    def remove_renderable(self, key: str) -> bool:
        print(f"remove {key}")
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
        self.__back_buffer: pygame.Surface = pygame.Surface(size=self.__size)

        for renderables in self.__renderables:
            for renderable in renderables.values():
                self.__back_buffer.blit(source=renderable.surface,
                                        dest=Vector2f.to_tuple(vector=renderable.coordinate))

        self.__back_buffer = pygame.transform.scale(surface=self.__back_buffer, size=(
            self.__back_buffer.get_width() * self.__scale_rate, self.__back_buffer.get_height() * self.__scale_rate))
        self.__front_buffer.blit(source=self.__back_buffer, dest=(0, 0))
        pygame.display.flip()
