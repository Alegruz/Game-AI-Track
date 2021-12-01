from typing import IO, Union

import pygame

from engine.core.Math import Vector2f
from engine.events.Events import Events, MainGameEvent
from engine.graphics.Orientation import Orientation
from engine.graphics.Renderable import Renderable
from engine.graphics.Renderer import Renderer, Depth
from engine.object.CollidableObject import CollidableObject
from engine.object.Tile import Tile, eGroundType
from engine.physics.CollisionManager import CollisionManager
from engine.player.Player import Player, eFacingDirection
from engine.resources.Scene import Scene


class MainGameScene(Scene):
    __slots__ = ["__main_game_keys", "__main_game_resource", "__player", "__map_data", "__map_tiles", "__map_resources",
                 "__maps", "__map_tilesets", "__collision_manager"]

    def __init__(self, player: Player = None, renderer: Renderer = None):
        super().__init__(name="main_game", event_class_type=Events.MAIN_GAME_EVENT, renderer=renderer)

        self.__player: Player = player

        self.__main_game_keys: list[str] = []
        self.__main_game_resource: pygame.Surface = None

        self.__map_data: dict[
            str, dict[str, Union[pygame.Color, dict[str, dict[str, Union[str, int, list[int]]]]]]] = dict()
        self.__map_tiles: dict[str, dict[str, Tile]] = dict()
        self.__map_resources: dict[str, pygame.Surface] = dict()
        self.__maps: dict[str, Renderable] = dict()
        self.__map_tilesets: list[list[Tile]] = []

        self.__collision_manager: CollisionManager = CollisionManager()

    @property
    def player(self) -> Player:
        return self.__player

    @player.setter
    def player(self, player: Player) -> None:
        self.__player = player

    def initialize(self):
        print(f"MainGameScene::initialize")
        super().initialize()

        self.__player.initialize()

        self.initialize_kakario_village()

        self.__collision_manager.add_collidable(key="player", collidable_object=self.__player)
        # self._background_musics["overworld"] = pygame.mixer.Sound("resources/musics/overworld.mp3")

    def initialize_kakario_village(self):
        self.parse_map_data(data_file_name="resources/maps/first_map.dat", name="first_map")
        self._background_musics["kakariko_village"].play(loops=-1)
        # self.parse_tileset_data(data_file_name="resources/tilesets/house.dat", name="house")

        # house_surface: pygame.Surface = pygame.Surface(
        #     size=(self._renderer.unscaled_size.x, self._renderer.unscaled_size.y))
        # house_surface.fill(color=self.__map_data["house"]["background_color"])
        #
        # house_surface.blit(source=self.__map_tiles["house"]["wall.corner.1"].renderable.surface,
        #                    dest=(0, 0))
        # house_surface.blit(source=self.__map_tiles["house"]["wall.corner.2"].renderable.surface,
        #                    dest=())
        #
        # self.__maps["house"] = Renderable(surface=house_surface,
        #                                   coordinate=Vector2f(x=0.0, y=0.0),
        #                                   depth=Depth.BACKGROUND_DEPTH,
        #                                   name="house")
        # self._renderer.add_renderable(renderable=self.__maps["house"])

    def parse_map_data(self, data_file_name: str, name: str):
        data_file: IO = open(file=data_file_name, mode="r")

        map_surface: pygame.Surface = None
        map_x: int = -1
        map_y: int = -1
        map_width: int = -1
        map_height: int = -1
        tileset: str = ""
        tileset_name: str = ""

        tile_layer: int = -1
        tile_x: int = -1
        tile_y: int = -1
        tile_width: int = -1
        tile_height: int = -1
        pattern: str = ""

        is_properties: bool = False
        is_tile: bool = False
        for line in data_file:
            splitted_line: list[str] = line.split()
            if len(splitted_line) <= 0:
                continue
            if not is_properties:
                if not is_tile:
                    if splitted_line[0][:-1] == "properties":
                        is_properties = True
                    elif splitted_line[0][:-1] == "tile":
                        is_tile = True
                else:
                    if splitted_line[0] == "}":
                        is_tile = False
                        if not eGroundType.is_walkable(ground_type=self.__map_tiles[tileset_name][pattern].ground):
                            collidable_tile: CollidableObject = CollidableObject(coordinate=Vector2f(x=tile_x, y=tile_y),
                                                                                 width=tile_width,
                                                                                 height=tile_height)
                            index: int = 0
                            while self.__collision_manager.contains_collidable_by_key(key=f"{pattern}_{index}"):
                                index += 1
                            self.__collision_manager.add_collidable(key=f"{pattern}_{index}",
                                                                    collidable_object=collidable_tile)
                        num_columns = tile_width // self.__map_tiles[tileset_name][
                            pattern].renderable.surface.get_width()
                        num_rows = tile_height // self.__map_tiles[tileset_name][
                            pattern].renderable.surface.get_height()
                        for row_index in range(0, num_rows):
                            for column_index in range(0, num_columns):
                                dest_x = tile_x + column_index * self.__map_tiles[tileset_name][
                                    pattern].renderable.surface.get_width()
                                dest_y = tile_y + row_index * self.__map_tiles[tileset_name][
                                    pattern].renderable.surface.get_height()
                                map_surface.blit(source=self.__map_tiles[tileset_name][pattern].renderable.surface,
                                                 dest=(dest_x, dest_y))
                                # for y_index in range(tile_y + row_index * self.__map_tiles[tileset_name][
                                #     pattern].renderable.surface.get_height(),
                                #                      min(tile_y + (row_index + 1) * self.__map_tiles[tileset_name][
                                #                          pattern].renderable.surface.get_height(),
                                #                          int(self._renderer.unscaled_size.y))):
                                #     for x_index in range(
                                #             tile_x + column_index * self.__map_tiles[tileset_name][
                                #                 pattern].renderable.surface.get_width(),
                                #             min(tile_x + (column_index + 1) * self.__map_tiles[tileset_name][
                                #                 pattern].renderable.surface.get_width(),
                                #                 int(self._renderer.unscaled_size.x))):
                                #         self.__map_tilesets[x_index][y_index] = self.__map_tiles[tileset_name][pattern]

                    elif splitted_line[0] == "layer":
                        tile_layer = int(splitted_line[-1][:-1])
                    elif splitted_line[0] == "x":
                        tile_x = int(splitted_line[-1][:-1])
                    elif splitted_line[0] == "y":
                        tile_y = int(splitted_line[-1][:-1])
                    elif splitted_line[0] == "width":
                        tile_width = int(splitted_line[-1][:-1])
                    elif splitted_line[0] == "height":
                        tile_height = int(splitted_line[-1][:-1])
                    elif splitted_line[0] == "pattern":
                        pattern = splitted_line[-1][1:-2]
            else:
                if splitted_line[0] == "x":
                    map_x = int(splitted_line[-1][:-1])
                elif splitted_line[0] == "y":
                    map_y = int(splitted_line[-1][:-1])
                elif splitted_line[0] == "width":
                    map_width = int(splitted_line[-1][:-1])
                elif splitted_line[0] == "height":
                    map_height = int(splitted_line[-1][:-1])
                elif splitted_line[0] == "tileset":
                    tileset = splitted_line[-1][1:-2]
                    tileset_name = tileset.split(sep="/")[-1]
                    self.parse_tileset_data(data_file_name=f"resources/tilesets/{tileset}.dat", name=tileset_name)
                elif splitted_line[0] == "music":
                    if splitted_line[-1][1:-2] == "village":
                        self._background_musics["kakariko_village"] = pygame.mixer.Sound(
                            "resources/musics/kakariko_village.mp3")
                    else:
                        self._background_musics[splitted_line[-1][1:-2]] = pygame.mixer.Sound(
                            f"resources/musics/{splitted_line[-1][1:-2]}.mp3")
                elif splitted_line[0] == "}":
                    is_properties = False
                    self.__map_tilesets = [[None for j in range(0, map_height)] for i in range(0, map_width)]
                    map_surface = pygame.Surface(size=(map_width, map_height))
        self.__maps[name] = Renderable(surface=map_surface,
                                       coordinate=Vector2f(x=map_x, y=map_y),
                                       depth=Depth.MAP_DEPTH,
                                       name=name)
        self._renderer.add_renderable(renderable=self.__maps[name])
        self._renderer.set_offset_limit(top_left=Vector2f(x=map_x, y=map_y),
                                        bottom_right=Vector2f(x=map_x + map_width,
                                                              y=map_y + map_height))

    def parse_tileset_data(self, data_file_name: str, name: str):
        assert name not in self.__map_data
        data_file: IO = open(file=data_file_name, mode="r")

        self.__map_data[name] = dict()
        self.__map_tiles[name] = dict()
        self.__map_resources[name] = pygame.image.load(f"{data_file_name[:-4]}.tiles.png")
        is_tile_pattern: bool = False
        id: str = "None"
        # print(f"data: {name}")
        for line in data_file:
            splitted_line: list[str] = line.split()

            if not is_tile_pattern:
                if len(splitted_line) > 0:
                    if splitted_line[0][:-1] == "background_color":
                        self.__map_data[name]["background_color"] = pygame.Color(int(splitted_line[1][:-1]),
                                                                                 int(splitted_line[2][:-1]),
                                                                                 int(splitted_line[3]))
                        # print(
                        #     f"\tbackground_color: {int(splitted_line[1][:-1])}, {int(splitted_line[2][:-1])}, {int(splitted_line[3])}")
                    elif splitted_line[0][:-1] == "tile_pattern":
                        if "tile_pattern" not in self.__map_data[name]:
                            self.__map_data[name]["tile_pattern"] = dict()
                        is_tile_pattern = True
                        # print(f"\ttile_pattern: ", end="")
            else:
                if len(splitted_line) == 1 and splitted_line[0] == "}":
                    is_tile_pattern = False
                elif splitted_line[0] == "id":
                    id = splitted_line[-1][1:-2]
                    self.__map_data[name]["tile_pattern"][id] = dict()
                    # print(f"{id}")
                else:
                    if splitted_line[-1][-2] == "\"":
                        self.__map_data[name]["tile_pattern"][id][splitted_line[0]] = splitted_line[-1][1:-2]
                        # print(f"\t\t{splitted_line[0]}: {splitted_line[-1][1:-2]}")
                    elif splitted_line[-1][:-1] == "}":
                        # print(f"\t\t{splitted_line[0]}: {{ ", end="")
                        self.__map_data[name]["tile_pattern"][id][splitted_line[0]] = []
                        for i in range(3, len(splitted_line) - 1):
                            if splitted_line[i][-1] == ",":
                                self.__map_data[name]["tile_pattern"][id][splitted_line[0]].append(
                                    int(splitted_line[i][:-1]))
                            else:
                                self.__map_data[name]["tile_pattern"][id][splitted_line[0]].append(
                                    int(splitted_line[i]))
                            # print(f'{self.__map_data[name]["tile_pattern"][id][splitted_line[0]][-1]} ', end="")
                        # print("}")
                    else:
                        self.__map_data[name]["tile_pattern"][id][splitted_line[0]] = int(splitted_line[-1][:-1])
                        # print(f"\t\t{splitted_line[0]}: {int(splitted_line[-1][:-1])}")

        for tile_id in self.__map_data[name]["tile_pattern"]:
            if isinstance(self.__map_data[name]["tile_pattern"][tile_id]["x"], int):
                self.__map_tiles[name][tile_id] = Tile.create_tile_from_data(
                    id=tile_id,
                    data=self.__map_data[name]["tile_pattern"][tile_id],
                    resource=self.__map_resources[name]
                )
            else:
                tiles = Tile.create_tiles_from_data(
                    id=tile_id,
                    data=self.__map_data[name]["tile_pattern"][tile_id],
                    resource=self.__map_resources[name])
                for i, tile in enumerate(tiles):
                    self.__map_tiles[name][f"{tile_id}_{i}"] = tile

    def destroy(self):
        super().destroy()
        for key in self.__main_game_keys:
            del self._renderables[key]
            if self._renderer.remove_renderable(key=key):
                print(f"removed {key} successfully")
            else:
                print(f"unable to remove {key}")
        del self.__main_game_keys

        for music in self._background_musics.values():
            music.stop()
            del music

    def start(self, millis: int = 0):
        super().start(millis=millis)
        print(f"MainGameScene::start")
        if millis == 0:
            pygame.event.post(pygame.event.Event(pygame.USEREVENT,
                                                 class_type=Events.MAIN_GAME_EVENT,
                                                 event_type=MainGameEvent.START))
        else:
            pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                           class_type=Events.MAIN_GAME_EVENT,
                                                           event_type=MainGameEvent.START),
                                  millis=millis)
            self._is_start_timer_enabled = True

    def on_event(self, event: pygame.event.Event):
        super().on_event(event=event)

        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_LEFT or event.key == pygame.K_RIGHT or event.key == pygame.K_UP or event.key == pygame.K_DOWN:
                self.__player.movement_input_pressed(key=event.key)
            elif event.key == pygame.K_r:
                self.__player.shield_pressed_action()
            elif event.key == pygame.K_f:
                self.__player.sword_pressed_action()
        elif event.type == pygame.KEYUP:
            if event.key == pygame.K_LEFT or event.key == pygame.K_RIGHT or event.key == pygame.K_UP or event.key == pygame.K_DOWN:
                self.__player.movement_input_released(key=event.key)
        elif event.type == pygame.USEREVENT:
            if "class_type" in event.__dict__:
                print(f"main_game_event: {event.event_type}")
                if event.event_type == MainGameEvent.START:
                    self._renderer.start_fade_in(duration=1)
                    if self._is_start_timer_enabled:
                        pygame.time.set_timer(event=pygame.event.Event(pygame.USEREVENT,
                                                                       class_type=Events.MAIN_GAME_EVENT,
                                                                       event_type=MainGameEvent.START),
                                              millis=0)
                        self._is_start_timer_enabled = False
                else:
                    assert False

    def update(self, delta_time: float):
        self.__player.update(delta_time=delta_time)
        self.__collision_manager.update(delta_time=delta_time)

        # if self.__player.facing_direction == eFacingDirection.NORTH:
        #     facing_tile.x = self.__player.coordinate.x + self.__player.width / 2.0
        #     facing_tile.y = self.__player.coordinate.y - 1.0
        # elif self.__player.facing_direction == eFacingDirection.SOUTH:
        #     facing_tile.x = self.__player.coordinate.x + self.__player.width / 2.0
        #     facing_tile.y = self.__player.coordinate.y + self.__player.height + 1.0
        # elif self.__player.facing_direction == eFacingDirection.WEST:
        #     facing_tile.x = self.__player.coordinate.x - 1.0
        #     facing_tile.y = self.__player.coordinate.y + self.__player.height / 2.0
        # elif self.__player.facing_direction == eFacingDirection.EAST:
        #     facing_tile.x = self.__player.coordinate.x + self.__player.width + 1.0
        #     facing_tile.y = self.__player.coordinate.y + self.__player.height / 2.0

        # if not eGroundType.is_walkable(ground_type=self.__map_tilesets[int(facing_tile.x)][int(facing_tile.y)].ground):
        # print(f"ground: {self.__map_tilesets[int(facing_tile.x)][int(facing_tile.y)].ground}")
