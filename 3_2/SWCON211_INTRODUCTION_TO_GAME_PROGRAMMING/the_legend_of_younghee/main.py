from typing import Union

import pygame

from engine.Engine import Engine
from engine.core.Math import Vector2f
from engine.graphics.Renderable import Renderable
from engine.graphics.Renderer import Depth
from engine.player.Player import Player
from game.scenes.InputNameScreenScene import InputNameScreenScene
from game.scenes.MainGameScene import MainGameScene
from game.scenes.TitleScreenScene import TitleScreenScene


def main() -> None:
    game_engine: Engine = Engine(width=256.0, height=224.0)

    # title_screen_scene: TitleScreenScene = TitleScreenScene()
    # game_engine.add_scene(scene=title_screen_scene)

    # input_screen_scene: InputNameScreenScene = InputNameScreenScene()
    # game_engine.add_scene(scene=input_screen_scene)
    # game_engine.add_transition(from_scene=title_screen_scene, to_scene=input_screen_scene)

    main_game_scene: MainGameScene = MainGameScene()
    game_engine.add_scene(scene=main_game_scene)
    # game_engine.add_transition(from_scene=input_screen_scene, to_scene=main_game_scene)

    # game_engine.set_current_scene(name=title_screen_scene.name)
    # game_engine.set_current_scene(name=input_screen_scene.name)
    game_engine.set_current_scene(name=main_game_scene.name)

    game_engine.start_current_scene(millis=1000)

    game_engine.run()


if __name__ == "__main__":
    main()
