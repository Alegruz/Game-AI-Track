import pygame

from engine.components.Component import Component


class BaseObject:
    __slots__ = ["__components"]

    def __init__(self):
        self.__components: dict[int, Component] = dict()

    def __del__(self):
        print(f"i am being deleted!! {self}, {id(self)}")
