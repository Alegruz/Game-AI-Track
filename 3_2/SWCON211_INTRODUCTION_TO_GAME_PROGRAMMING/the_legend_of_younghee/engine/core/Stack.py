from typing import Any


class Stack:
    __slots__ = ["__data"]

    def __init__(self):
        self.__data: list[Any] = []

    @property
    def data(self) -> list[Any]:
        return self.__data

    def push(self, element: Any) -> None:
        self.__data.append(element)

    def pop(self) -> Any:
        return self.__data.pop()
