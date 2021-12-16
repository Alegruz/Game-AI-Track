from typing import Any


class GlobalConstants:
    __constants: dict[str, Any] = dict()

    @staticmethod
    def add_constant(key: str, value: Any) -> bool:
        if key in GlobalConstants.__constants:
            return False

        GlobalConstants.__constants[key] = value

    @staticmethod
    def add_or_set_constant(key: str, value: Any) -> None:
        GlobalConstants.__constants[key] = value

    @staticmethod
    def contains_constant(key: str) -> bool:
        return key in GlobalConstants.__constants

    @staticmethod
    def get_constant_or_none(key: str) -> Any:
        try:
            return GlobalConstants.__constants[key]
        except KeyError:
            return None

    @staticmethod
    def remove_constant(key: str) -> bool:
        if key not in GlobalConstants.__constants:
            return False

        del GlobalConstants.__constants[key]

    @staticmethod
    def set_constant(key: str, value: Any) -> bool:
        if key not in GlobalConstants.__constants:
            return False

        GlobalConstants.__constants[key] = value
