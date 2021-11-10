import pygame
import pygame.locals


class Tile:
    @staticmethod
    def load_tile_table(filename: str, width: float, height: float):
        image: pygame.Surface = pygame.image.load(filename).convert_alpha()
        image_width, image_height = image.get_size()
        tile_table: list = []

        for x in range(0, int(image_width / width)):
            line: list = []
            tile_table.append(line)
            for y in range(0, int(image_height / height)):
                rect = (x * width, y * height, width, height)
                line.append(image.subsurface(rect=rect))

        return tile_table

