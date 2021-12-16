import math
import random
from typing import IO, Union

import pygame

from engine.core.GlobalConstants import GlobalConstants
from engine.core.Math import Vector2f, Vector2i
from engine.core.NavigationBox import NavigationBox
from engine.events.Events import Events, MainGameEvent
from engine.graphics.Renderable import Renderable
from engine.graphics.Renderer import Renderer, Depth
from engine.object.CollidableObject import CollidableObject
from engine.object.DestructibleObject import DestructibleObject
from engine.object.Enemy import Enemy, eEnemyState
from engine.object.Tile import Tile, eGroundType
from engine.physics.CollisionManager import CollisionManager
from engine.player.Player import Player
from engine.resources.RenderableStorage import RenderableStorage
from engine.resources.Scene import Scene


class MainGameScene(Scene):
    __slots__ = ["__main_game_keys", "__main_game_resource", "__player", "__map_data", "__map_tiles",
                 "__maps", "__map_tilesets", "__collision_manager", "__destructibles", "__enemies", "__attack_timer",
                 "__strong_attack_time_threshold", "__ganon_appear_timer", "__is_fighting_ganon", "__fanfare_timer"]

    def __init__(self, player: Player = None, renderer: Renderer = None):
        super().__init__(name="main_game", event_class_type=Events.MAIN_GAME_EVENT, renderer=renderer)

        self.__player: Player = player

        self.__main_game_keys: list[str] = []
        self.__main_game_resource: pygame.Surface = None

        self.__map_data: dict[
            str, dict[str, Union[pygame.Color, dict[str, dict[str, Union[str, int, list[int]]]]]]] = dict()
        self.__map_tiles: dict[str, dict[str, Tile]] = dict()
        # self.__map_resources: dict[str, pygame.Surface] = dict()
        self.__maps: dict[str, Renderable] = dict()
        self.__map_tilesets: list[list[Tile]] = []
        self.__destructibles: dict[str, DestructibleObject] = dict()

        self.__collision_manager: CollisionManager = None
        self.__enemies: dict[str, Enemy] = dict()

        self.__attack_timer: int = -1
        self.__strong_attack_time_threshold: int = 30

        self.__ganon_appear_timer: int = -1
        self.__is_fighting_ganon: bool = False
        self.__fanfare_timer: int = -1

    @property
    def player(self) -> Player:
        return self.__player

    @player.setter
    def player(self, player: Player) -> None:
        self.__player = player

    def initialize(self):
        print(f"MainGameScene::initialize")
        super().initialize()

        GlobalConstants.add_constant(key="cell_size", value=128)

        self.__player.initialize()

        self.initialize_kakariko_village()

        self.__collision_manager.add_collidable(key="player", collidable_object=self.__player)
        # self._background_musics["overworld"] = pygame.mixer.Sound("resources/musics/overworld.mp3")

    def initialize_kakariko_village(self):
        self.parse_map_data(data_file_name="resources/maps/examples/light_world/kakariko_village.dat",
                            name="kakariko_village")

        self._background_musics["kakariko_village"].play(loops=-1)
        self.__enemies["ganon"] = Enemy(
            coordinate=Vector2f(x=self.__player.coordinate.x + 100.0,
                                y=self.__player.coordinate.y),
            width=24.0,
            height=28.0,
            name="ganon",
            sprite_data_file="enemies/ganon"
        )
        self.__collision_manager.add_collidable(key="ganon",
                                                collidable_object=self.__enemies["ganon"])
        GlobalConstants.add_constant(key="ganon", value=self.__enemies["ganon"])
        self.__enemies["ganon"].initialize()
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
        tile_tileset: str = ""
        pattern: str = ""

        destructible_layer: int = -1
        destructible_x: int = -1
        destructible_y: int = -1
        destructible_sprite: str = ""
        destructible_sound: str = ""
        destructible_can_be_cut: bool = False

        is_properties: bool = False
        is_tile: bool = False
        is_destructible: bool = False
        is_npc: bool = False
        for line in data_file:
            splitted_line: list[str] = line.split()
            if len(splitted_line) <= 0:
                continue
            if not is_properties:
                if not is_tile and not is_destructible and not is_npc:
                    if splitted_line[0][:-1] == "properties":
                        is_properties = True
                    elif splitted_line[0][:-1] == "tile":
                        is_tile = True
                        is_destructible = False
                        is_npc = False
                        tile_tileset = tileset_name
                    elif splitted_line[0][:-1] == "destructible":
                        is_tile = False
                        is_destructible = True
                        is_npc = False
                    elif splitted_line[0][:-1] == "npc":
                        is_tile = False
                        is_destructible = False
                        is_npc = True
                elif is_tile:
                    if splitted_line[0] == "}":
                        is_tile = False
                        try:
                            least_tile_width: int = int(math.ceil(tile_width / GlobalConstants.get_constant_or_none(
                                key="cell_size")))
                            least_tile_height: int = int(
                                math.ceil(tile_height / GlobalConstants.get_constant_or_none(
                                    key="cell_size")))
                            if not eGroundType.is_walkable(ground_type=self.__map_tiles[tile_tileset][pattern].ground):
                                # print(least_tile_height, least_tile_width)
                                for y in range(0, least_tile_height):
                                    for x in range(0, least_tile_width):
                                        collidable_tile: CollidableObject = CollidableObject(
                                            coordinate=Vector2f(x=tile_x + x * GlobalConstants.get_constant_or_none(
                                                key="cell_size"),
                                                                y=tile_y + y * GlobalConstants.get_constant_or_none(
                                                                    key="cell_size")),
                                            width=tile_width - x * GlobalConstants.get_constant_or_none(key="cell_size"),
                                            height=tile_height - y * GlobalConstants.get_constant_or_none(
                                                key="cell_size")
                                        )
                                        index: int = 0
                                        while self.__collision_manager.contains_collidable_by_key(
                                                key=f"{pattern}_{index}"):
                                            index += 1
                                        self.__collision_manager.add_collidable(key=f"{pattern}_{index}",
                                                                                collidable_object=collidable_tile)
                            else:
                                # print(least_tile_height, least_tile_width)
                                for y in range(0, least_tile_height):
                                    for x in range(0, least_tile_width):
                                        navigation_box: NavigationBox = NavigationBox(
                                            top_left=Vector2f(x=tile_x + x * GlobalConstants.get_constant_or_none(
                                                key="cell_size"),
                                                              y=tile_y + y * GlobalConstants.get_constant_or_none(
                                                                  key="cell_size")),
                                            width=tile_width - x * GlobalConstants.get_constant_or_none(
                                                key="cell_size"),
                                            height=tile_height - y * GlobalConstants.get_constant_or_none(
                                                key="cell_size"),
                                        )
                                        index: int = 0
                                        while self.__collision_manager.contains_navigation_box_by_key(
                                                key=f"{pattern}_{index}"):
                                            index += 1
                                        self.__collision_manager.add_navigation_box(key=f"{pattern}_{index}",
                                                                                    navigation_box=navigation_box)
                        except KeyError:
                            # print(f"tileset: {tileset}, pattern: {pattern}, {self.__map_tiles[tile_tileset]}")
                            pattern = f"{pattern}_0"
                            least_tile_width: int = int(math.ceil(tile_width / GlobalConstants.get_constant_or_none(
                                key="cell_size")))
                            least_tile_height: int = int(
                                math.ceil(tile_height / GlobalConstants.get_constant_or_none(
                                    key="cell_size")))
                            if not eGroundType.is_walkable(ground_type=self.__map_tiles[tile_tileset][pattern].ground):
                                for y in range(0, least_tile_height):
                                    for x in range(0, least_tile_width):
                                        collidable_tile: CollidableObject = CollidableObject(
                                            coordinate=Vector2f(
                                                x=tile_x + x * GlobalConstants.get_constant_or_none(key="cell_size"),
                                                y=tile_y + y * GlobalConstants.get_constant_or_none(key="cell_size")),
                                            width=tile_width - x * GlobalConstants.get_constant_or_none(key="cell_size"),
                                            height=tile_height - y * GlobalConstants.get_constant_or_none(
                                                key="cell_size")
                                        )
                                        index: int = 0
                                        while self.__collision_manager.contains_collidable_by_key(
                                                key=f"{pattern}_{index}"):
                                            index += 1
                                        self.__collision_manager.add_collidable(key=f"{pattern}_{index}",
                                                                                collidable_object=collidable_tile)
                            else:
                                for y in range(0, least_tile_height):
                                    for x in range(0, least_tile_width):
                                        navigation_box: NavigationBox = NavigationBox(
                                            top_left=Vector2f(
                                                x=tile_x + x * GlobalConstants.get_constant_or_none(key="cell_size"),
                                                y=tile_y + y * GlobalConstants.get_constant_or_none(key="cell_size")),
                                            width=tile_width - x * GlobalConstants.get_constant_or_none(key="cell_size"),
                                            height=tile_height - y * GlobalConstants.get_constant_or_none(
                                                key="cell_size")
                                        )
                                        index: int = 0
                                        while self.__collision_manager.contains_navigation_box_by_key(
                                                key=f"{pattern}_{index}"):
                                            index += 1
                                        self.__collision_manager.add_navigation_box(key=f"{pattern}_{index}",
                                                                                    navigation_box=navigation_box)
                        num_columns = tile_width // self.__map_tiles[tile_tileset][
                            pattern].renderable.surface.get_width()
                        num_rows = tile_height // self.__map_tiles[tile_tileset][
                            pattern].renderable.surface.get_height()
                        for row_index in range(0, num_rows):
                            for column_index in range(0, num_columns):
                                dest_x = tile_x + column_index * self.__map_tiles[tile_tileset][
                                    pattern].renderable.surface.get_width()
                                dest_y = tile_y + row_index * self.__map_tiles[tile_tileset][
                                    pattern].renderable.surface.get_height()
                                map_surface.blit(source=self.__map_tiles[tile_tileset][pattern].renderable.surface,
                                                 dest=(dest_x, dest_y))
                                # for y_index in range(tile_y + row_index * self.__map_tiles[tile_tileset][
                                #     pattern].renderable.surface.get_height(),
                                #                      min(tile_y + (row_index + 1) * self.__map_tiles[tile_tileset][
                                #                          pattern].renderable.surface.get_height(),
                                #                          int(self._renderer.unscaled_size.y))):
                                #     for x_index in range(
                                #             tile_x + column_index * self.__map_tiles[tile_tileset][
                                #                 pattern].renderable.surface.get_width(),
                                #             min(tile_x + (column_index + 1) * self.__map_tiles[tile_tileset][
                                #                 pattern].renderable.surface.get_width(),
                                #                 int(self._renderer.unscaled_size.x))):
                                #         self.__map_tilesets[x_index][y_index] = self.__map_tiles[tile_tileset][pattern]
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
                    elif splitted_line[0] == "tileset":
                        tile_tileset = splitted_line[-1][1:-2]
                        self.parse_tileset_data(data_file_name=f"resources/tilesets/{tile_tileset}.dat",
                                                name=tile_tileset)
                elif is_destructible:
                    if splitted_line[0] == "layer":
                        destructible_layer = int(splitted_line[-1][:-1])
                    elif splitted_line[0] == "x":
                        destructible_x = int(splitted_line[-1][:-1])
                    elif splitted_line[0] == "y":
                        destructible_y = int(splitted_line[-1][:-1])
                    elif splitted_line[0] == "sprite":
                        destructible_sprite = splitted_line[-1][1:-2]
                    elif splitted_line[0] == "destruction_sound":
                        destructible_sound = splitted_line[-1][1:-2]
                        if destructible_sound != "":
                            self._sound_effects[destructible_sound] = pygame.mixer.Sound(
                                file=f"resources/sounds/{destructible_sound}.ogg")
                    elif splitted_line[0] == "can_be_cut":
                        destructible_can_be_cut = bool(splitted_line[-1][:-1])
                    elif splitted_line[0] == "}":
                        is_destructible = False
                        destructible_name: str = destructible_sprite.split("/")[-1]
                        name_counter: int = 0
                        original_name: str = destructible_name
                        prev_name: str = ""
                        while destructible_name in self.__destructibles:
                            prev_name = destructible_name
                            destructible_name = f"{original_name}_{name_counter}"
                            name_counter += 1
                        self.__destructibles[destructible_name] = \
                            DestructibleObject(coordinate=Vector2f(x=destructible_x,
                                                                   y=destructible_y),
                                               width=16.0,
                                               height=16.0,
                                               can_be_cut=destructible_can_be_cut,
                                               sprite_data_file=destructible_sprite,
                                               depth=destructible_layer + Depth.MAP_DEPTH,
                                               name=destructible_name,
                                               destruction_sound=self._sound_effects[destructible_sound] if destructible_sound != "" else None)
                        self.__destructibles[destructible_name].initialize()
                        self.__collision_manager.add_collidable(key=destructible_name,
                                                                collidable_object=self.__destructibles[
                                                                    destructible_name])
            else:
                if splitted_line[0] == "x":
                    map_x = int(splitted_line[-1][:-1])
                elif splitted_line[0] == "y":
                    map_y = int(splitted_line[-1][:-1])
                elif splitted_line[0] == "width":
                    map_width = int(splitted_line[-1][:-1])
                    GlobalConstants.add_constant(key="map_width", value=map_width)
                elif splitted_line[0] == "height":
                    map_height = int(splitted_line[-1][:-1])
                    GlobalConstants.add_constant(key="map_height", value=map_width)
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
                    if self.__collision_manager is None:
                        self.__collision_manager = CollisionManager(
                            grid_size=Vector2i(
                                x=int(math.ceil(map_width / GlobalConstants.get_constant_or_none(key="cell_size"))),
                                y=int(math.ceil(map_height / GlobalConstants.get_constant_or_none(key="cell_size")))),
                            cell_size=Vector2f(x=GlobalConstants.get_constant_or_none(key="cell_size"),
                                               y=GlobalConstants.get_constant_or_none(key="cell_size"))
                        )
                        GlobalConstants.add_constant(key="collision_manager", value=self.__collision_manager)
        self.__maps[name] = Renderable(surface=map_surface,
                                       coordinate=Vector2f(x=map_x, y=map_y),
                                       depth=Depth.BACKGROUND_DEPTH,
                                       name=name)
        self._renderer.add_renderable(renderable=self.__maps[name])
        self._renderer.set_offset_limit(top_left=Vector2f(x=map_x, y=map_y),
                                        bottom_right=Vector2f(x=map_x + map_width,
                                                              y=map_y + map_height))
        self._background_musics["kakariko_village"] = pygame.mixer.Sound("resources/musics/kakariko_village.mp3")
        self._background_musics["ganon_appears"] = pygame.mixer.Sound("resources/musics/ganon_appears.it")
        self._background_musics["ganon_battle"] = pygame.mixer.Sound("resources/musics/ganon_battle.it")
        self._background_musics["ganon_theme"] = pygame.mixer.Sound("resources/musics/ganon_theme.it")
        self._background_musics["fanfare"] = pygame.mixer.Sound("resources/musics/fanfare.it")

    def parse_tileset_data(self, data_file_name: str, name: str):
        if name in self.__map_data:
            return
        data_file: IO = open(file=data_file_name, mode="r")
        print(f"parsing tileset {data_file_name}")

        self.__map_data[name] = dict()
        self.__map_tiles[name] = dict()
        RenderableStorage.add_surface(key=name, surface=pygame.image.load(f"{data_file_name[:-4]}.tiles.png"))
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
                        if splitted_line[-1][:-1] == "true" or splitted_line[-1][:-1] == "false":
                            self.__map_data[name]["tile_pattern"][id][splitted_line[0]] = bool(splitted_line[-1][:-1])
                        else:
                            self.__map_data[name]["tile_pattern"][id][splitted_line[0]] = int(splitted_line[-1][:-1])
                        # print(f"\t\t{splitted_line[0]}: {int(splitted_line[-1][:-1])}")

        for tile_id in self.__map_data[name]["tile_pattern"]:
            if isinstance(self.__map_data[name]["tile_pattern"][tile_id]["x"], int):
                self.__map_tiles[name][tile_id] = Tile.create_tile_from_data(
                    id=tile_id,
                    data=self.__map_data[name]["tile_pattern"][tile_id],
                    resource=RenderableStorage.get_surface_or_none(key=name)
                )
            else:
                tiles = Tile.create_tiles_from_data(
                    id=tile_id,
                    data=self.__map_data[name]["tile_pattern"][tile_id],
                    resource=RenderableStorage.get_surface_or_none(key=name))
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
        # print(f"event: {event}")
        if self.__player is not None:
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT or event.key == pygame.K_RIGHT or event.key == pygame.K_UP or event.key == pygame.K_DOWN:
                    self.__player.movement_input_pressed(key=event.key)
                elif event.key == pygame.K_r:
                    self.__player.shield_pressed_action()
                elif event.key == pygame.K_f:
                    self.__attack_timer = 0
                    self.__player.sword_pressed_action()
                elif event.key == pygame.K_a:
                    self.__player.on_print_coord()
                elif event.key == pygame.K_d:
                    self.__player.flash_pressed_action()
                elif event.key == pygame.K_s:
                    self.__player.teleport_to_ganon_pressed_action()
            elif event.type == pygame.KEYUP:
                if event.key == pygame.K_LEFT or event.key == pygame.K_RIGHT or event.key == pygame.K_UP or event.key == pygame.K_DOWN:
                    self.__player.movement_input_released(key=event.key)
                elif event.key == pygame.K_f:
                    if self.__attack_timer > self.__strong_attack_time_threshold:
                        self.__player.sword_pressed_action(is_strong_attack=True)
                    self.__attack_timer = -1
        if event.type == pygame.USEREVENT:
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
        if self.__player.health <= 0 and GlobalConstants.contains_constant(key="player"):
            # self.__player.destroy()
            GlobalConstants.remove_constant(key="player")
            self._background_musics["kakariko_village"].stop()
            self._background_musics["ganon_appears"].stop()
            self._background_musics["ganon_battle"].stop()
            self._background_musics["ganon_theme"].stop()
            self._background_musics["fanfare"].stop()
            self._background_musics["game_over"] = pygame.mixer.Sound("resources/musics/game_over.it")
            self._background_musics["game_over"].play()

        if self.__fanfare_timer >= 0:
            self.__fanfare_timer += int(delta_time)
            if self.__fanfare_timer >= self._background_musics["fanfare"].get_length() * 333:
                self.__fanfare_timer = -1
                self._background_musics["kakariko_village"].play()
                self._background_musics["ganon_appears"].stop()
                self._background_musics["ganon_battle"].stop()
                self._background_musics["ganon_theme"].stop()
                self._background_musics["fanfare"].stop()

        if "ganon" in self.__enemies:
            if self.__fanfare_timer == -1 and \
                    self.__ganon_appear_timer == -1 and \
                    self.__enemies["ganon"].current_state == eEnemyState.FOLLOWING_PLAYER and \
                    not self.__is_fighting_ganon:
                self._background_musics["kakariko_village"].stop()
                self._background_musics["ganon_battle"].stop()
                self._background_musics["ganon_theme"].stop()
                self._background_musics["fanfare"].stop()
                self._background_musics["ganon_appears"].play()
                self.__ganon_appear_timer = 0
            elif self.__ganon_appear_timer >= 0:
                self.__ganon_appear_timer += int(delta_time)
                # print(f"timer: {self.__ganon_appear_timer} ~ {self._background_musics['ganon_appears'].get_length()}")
                if self.__ganon_appear_timer >= self._background_musics["ganon_appears"].get_length() * 333:
                    self._background_musics["kakariko_village"].stop()
                    self._background_musics["ganon_appears"].stop()
                    self._background_musics["ganon_theme"].stop()
                    self._background_musics["fanfare"].stop()
                    self._background_musics["ganon_battle"].play()
                    self.__ganon_appear_timer = -1
                    self.__is_fighting_ganon = True
            if self.__fanfare_timer == -1 and \
                    self.__is_fighting_ganon and \
                    (self.__enemies["ganon"].current_state == eEnemyState.IDLE or
                     self.__enemies["ganon"].current_state == eEnemyState.MOVING):
                self._background_musics["kakariko_village"].stop()
                self._background_musics["ganon_appears"].stop()
                self._background_musics["ganon_battle"].stop()
                self._background_musics["fanfare"].stop()
                self._background_musics["ganon_theme"].play()
                self.__is_fighting_ganon = False
            elif self.__enemies["ganon"].health <= 0:
                # self.__collision_manager.remove_collidable(key="ganon")
                # GlobalConstants.remove_constant(key="ganon")
                # self.__enemies["ganon"].destroy()
                # del self.__enemies["ganon"]
                self._background_musics["kakariko_village"].stop()
                self._background_musics["ganon_appears"].stop()
                self._background_musics["ganon_battle"].stop()
                self._background_musics["ganon_theme"].stop()
                self._background_musics["fanfare"].stop()
                self._background_musics["fanfare"].play()
                self.__is_fighting_ganon = False
                self.__fanfare_timer = 0
                self.__enemies["ganon"].health = 100.0
                self.__enemies["ganon"].coordinate = Vector2f(x=random.randint(0, GlobalConstants.get_constant_or_none(key="map_width")),
                                                              y=random.randint(0, GlobalConstants.get_constant_or_none(key="map_height")))
        if self.__attack_timer != -1:
            self.__attack_timer += int(delta_time)
        if self.__player is not None:
            self.__player.update(delta_time=delta_time)
        for destructible in self.__destructibles.values():
            destructible.update(delta_time=delta_time)
        for enemy in self.__enemies.values():
            enemy.update(delta_time=delta_time)

        self.__collision_manager.update(player=self.__player, delta_time=delta_time)

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
        # print(f"ground: {self.__map_tilesets[int(self.__player.coordinate.x)][int(self.__player.coordinate.y)]}")
