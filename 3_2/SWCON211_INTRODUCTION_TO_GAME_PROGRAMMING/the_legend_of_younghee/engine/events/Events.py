from __future__ import annotations
import pygame


class Events:
    TRANSITION_EVENT: int = 0
    TITLE_SCREEN_EVENT: int = 1
    INPUT_NAME_EVENT: int = 2
    MAIN_GAME_EVENT: int = 3


class InputNameScreenEvent:
    START: int = 0
    END: int = 1


class TitleScreenEvent:
    SHOW_DEVELOPER: int = 0  # 0
    FADE_OUT_DEVELOPER: int = SHOW_DEVELOPER + 1  # 1
    SHOW_COPYRIGHT: int = FADE_OUT_DEVELOPER + 1  # 2
    ANIMATE_TRIFORCE: int = SHOW_COPYRIGHT + 1  # 3
    PLAY_MUSIC: int = ANIMATE_TRIFORCE + 1  # 4
    SHOW_COMPLETE_TRIFORCE: int = PLAY_MUSIC + 1  # 5
    FADE_IN_TITLE: int = SHOW_COMPLETE_TRIFORCE + 1  # 6
    SHOW_SWORD: int = FADE_IN_TITLE + 1  # 7
    SHOW_FLASHING_EFFECT: int = SHOW_SWORD + 1  # 8
    FADE_IN_BACKGROUND: int = SHOW_FLASHING_EFFECT + 1  # 9
    SHOW_SHINY_EFFECT: int = FADE_IN_BACKGROUND + 1  # 10
    FADE_OUT: int = SHOW_SHINY_EFFECT + 1  # 11
    END: int = FADE_OUT + 1  # 12


class MainGameEvent:
    START: int = 0
    END: int = 1
