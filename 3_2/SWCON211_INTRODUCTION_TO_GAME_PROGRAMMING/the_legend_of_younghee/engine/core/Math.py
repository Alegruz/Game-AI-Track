from __future__ import annotations
import math
import typing

from engine.graphics.Orientation import Orientation


class Math:
    @staticmethod
    def lerp_float(x: float, y: float, alpha: float) -> float:
        return (1.0 - alpha) * x + alpha * y

    @staticmethod
    def lerp_tuples(coord0: tuple[float, float], coord1: tuple[float, float], alpha: float) -> tuple[float, float]:
        return (1.0 - alpha) * coord0[0] + alpha * coord1[0], (1.0 - alpha) * coord0[1] + alpha * coord1[1]

    @staticmethod
    def lerp_vectors(coord0: Vector2f, coord1: Vector2f, alpha: float) -> Vector2f:
        return Vector2f(x=(1.0 - alpha) * coord0.x + alpha * coord1.x, y=(1.0 - alpha) * coord0.y + alpha * coord1.y)


class Vector2i:
    __slots__ = ["__x", "__y"]

    def __init__(self, x: int, y: int):
        if isinstance(x, float):
            x = int(x)
        if isinstance(y, float):
            y = int(y)
        assert isinstance(x, int)
        assert isinstance(y, int)

        self.__x = x
        self.__y = y

        # print(f"init: {id(self)}")

    def __del__(self):
        # print(f"i am being deleted, {self} {id(self)}")
        pass

    def __abs__(self):
        return Vector2i(x=abs(self.__x), y=abs(self.__y))

    @typing.overload
    def __add__(self, other: Vector2i) -> Vector2i:
        ...

    @typing.overload
    def __add__(self, other: int) -> Vector2i:
        ...

    def __add__(self, other: typing.Union[int, Vector2i]) -> Vector2i:
        if isinstance(other, Vector2i):
            return Vector2i(x=self.__x + other.__x, y=self.__y + other.__y)
        elif isinstance(other, int):
            return Vector2i(x=self.__x + other, y=self.__y + other)

        assert False

    def __eq__(self, other: Vector2i) -> bool:
        assert isinstance(other, Vector2i)
        return self.__x == other.x and self.__y == other.y

    def __ge__(self, other: Vector2i) -> bool:
        assert isinstance(other, Vector2i)
        return self.__x >= other.x and self.__y >= other.y

    def __gt__(self, other: Vector2i) -> bool:
        assert isinstance(other, Vector2i)
        return self.__x > other.x and self.__y > other.y

    def __len__(self) -> int:
        return 2

    @typing.overload
    def __mul__(self, other: Vector2i) -> int:
        ...

    @typing.overload
    def __mul__(self, other: int) -> Vector2i:
        ...

    @typing.overload
    def __mul__(self, other: int) -> Vector2i:
        ...

    def __mul__(self, other: typing.Union[Vector2i, float, int]) -> typing.Union[int, Vector2i]:
        if isinstance(other, Vector2i):
            return self.__x * other.__x + self.__y * other.__y
        elif isinstance(other, float) or isinstance(other, int):
            return Vector2i(x=int(self.__x * other), y=int(self.__y * other))

        assert False

    def __ne__(self, other: Vector2i) -> bool:
        assert isinstance(other, Vector2i)
        return self.__x != other.__x or self.__y != other.__y

    def __neg__(self) -> Vector2i:
        return Vector2i(x=-self.__x, y=-self.__y)

    def __str__(self) -> str:
        try:
            return f"({self.__x}, {self.__y})"
        except AttributeError:
            print(f"str: {id(self)}")
            assert False

    def __sub__(self, other: Vector2i) -> Vector2i:
        assert isinstance(other, Vector2i)
        return Vector2i(x=self.__x - other.__x, y=self.__y - other.__y)

    @property
    def x(self) -> int:
        try:
            return self.__x
        except AttributeError:
            print(f"id: {id(self)}")
            assert False

    @property
    def y(self) -> int:
        return self.__y

    @x.setter
    def x(self, x: int) -> None:
        self.__x = x

    @y.setter
    def y(self, y: int) -> None:
        self.__y = y

    def __copy__(self):
        class_type = self.__class__
        print(f"cls: {type(class_type)}")
        result = class_type.__new__(class_type)
        print(f"result: {type(result)}")
        result.__dict__.update(self.__dict__)
        return result

    def copy(self, other: Vector2i) -> None:
        assert isinstance(other, Vector2i)
        self.__x = other.x
        self.__y = other.y

    def get_length(self) -> float:
        return math.sqrt(self.__x * self.__x + self.__y * self.__y)

    def get_length_squared(self) -> int:
        return self.__x * self.__x + self.__y * self.__y

    def lerp(self, coord0: Vector2i, coord1: Vector2i, alpha: float):
        assert isinstance(coord0, Vector2i)
        assert isinstance(coord1, Vector2i)
        assert isinstance(alpha, float)

        self.__x = int((1.0 - alpha) * coord0.x + alpha * coord1.x)
        self.__y = int((1.0 - alpha) * coord0.y + alpha * coord1.y)

    def set_coordinate(self, x: int, y: int):
        self.x = x
        self.y = y

    @staticmethod
    def to_tuple(vector: Vector2i) -> tuple[int, int]:
        return vector.x, vector.y


class Vector2f:
    __slots__ = ["__x", "__y"]

    def __init__(self, x: float, y: float):
        if isinstance(x, int):
            x = float(x)
        if isinstance(y, int):
            y = float(y)
        assert isinstance(x, float)
        assert isinstance(y, float)

        self.__x = x
        self.__y = y

        # print(f"init: {id(self)}")

    def __del__(self):
        # print(f"i am being deleted, {self} {id(self)}")
        pass

    def __abs__(self):
        return Vector2f(x=abs(self.__x), y=abs(self.__y))

    @typing.overload
    def __add__(self, other: Vector2f) -> Vector2f:
        ...

    @typing.overload
    def __add__(self, other: float) -> Vector2f:
        ...

    def __add__(self, other: typing.Union[float, Vector2f]) -> Vector2f:
        if isinstance(other, Vector2f):
            return Vector2f(x=self.__x + other.x, y=self.__y + other.y)
        elif isinstance(other, float):
            return Vector2f(x=self.__x + other, y=self.__y + other)

        assert False

    def __ceil__(self) -> Vector2f:
        return Vector2f(x=math.ceil(self.__x), y=math.ceil(self.__y))

    def __eq__(self, other: Vector2f) -> bool:
        assert isinstance(other, Vector2f)
        return self.__x == other.x and self.__y == other.y

    def __floor__(self) -> Vector2f:
        return Vector2f(x=math.floor(self.__x), y=math.floor(self.__y))

    def __ge__(self, other: Vector2f) -> bool:
        assert isinstance(other, Vector2f)
        return self.__x >= other.x and self.__y >= other.y

    def __gt__(self, other: Vector2f) -> bool:
        assert isinstance(other, Vector2f)
        return self.__x > other.x and self.__y > other.y

    def __len__(self) -> int:
        return 2

    @typing.overload
    def __mul__(self, other: Vector2f) -> float:
        ...

    @typing.overload
    def __mul__(self, other: float) -> Vector2f:
        ...

    @typing.overload
    def __mul__(self, other: int) -> Vector2f:
        ...

    def __mul__(self, other: typing.Union[Vector2f, float, int]) -> typing.Union[float, Vector2f]:
        if isinstance(other, Vector2f):
            return self.__x * other.x + self.__y * other.y
        elif isinstance(other, float) or isinstance(other, int):
            return Vector2f(x=self.__x * other, y=self.__y * other)

        assert False

    def __ne__(self, other: Vector2f) -> bool:
        assert isinstance(other, Vector2f)
        return self.__x != other.x or self.__y != other.y

    def __neg__(self) -> Vector2f:
        return Vector2f(x=-self.__x, y=-self.__y)

    def __str__(self) -> str:
        try:
            return f"({self.__x}, {self.__y})"
        except AttributeError:
            print(f"str: {id(self)}")
            assert False

    def __sub__(self, other: Vector2f) -> Vector2f:
        assert isinstance(other, Vector2f)
        return Vector2f(x=self.__x - other.x, y=self.__y - other.y)

    @property
    def x(self) -> float:
        try:
            return self.__x
        except AttributeError:
            print(f"id: {id(self)}")
            assert False

    @property
    def y(self) -> float:
        return self.__y

    @x.setter
    def x(self, x: float) -> None:
        self.__x = x

    @y.setter
    def y(self, y: float) -> None:
        self.__y = y

    def __copy__(self):
        class_type = self.__class__
        print(f"cls: {type(class_type)}")
        result = class_type.__new__(class_type)
        print(f"result: {type(result)}")
        result.__dict__.update(self.__dict__)
        return result

    def copy(self, other: Vector2f) -> None:
        self.x = other.x
        self.y = other.y

    def get_distance_from(self, other: Vector2f):
        return (self - other).get_length()

    def get_distance_squared_from(self, other: Vector2f):
        return (self - other).get_length_squared()

    def get_length(self):
        return math.sqrt(self.__x * self.__x + self.__y * self.__y)

    def get_length_squared(self):
        return self.__x * self.__x + self.__y * self.__y

    @staticmethod
    def get_oriented_vector(top_left: Vector2f, size: Vector2f, orientation: int) -> Vector2f:
        center_x: float = top_left.x + size.x / 2.0
        center_y: float = top_left.y + size.y / 2.0
        right_x: float = top_left.x + size.x
        right_y: float = top_left.y + size.y
        if orientation == Orientation.TOP_LEFT:
            return top_left
        elif orientation == Orientation.TOP_CENTER:
            return Vector2f(x=center_x, y=top_left.y)
        elif orientation == Orientation.TOP_RIGHT:
            return Vector2f(x=right_x, y=top_left.y)
        elif orientation == Orientation.LEFT:
            return Vector2f(x=top_left.x, y=center_y)
        elif orientation == Orientation.CENTER:
            return Vector2f(x=center_x, y=center_y)
        elif orientation == Orientation.RIGHT:
            return Vector2f(x=right_x, y=center_y)
        elif orientation == Orientation.BOTTOM_LEFT:
            return Vector2f(x=top_left.x, y=right_y)
        elif orientation == Orientation.BOTTOM:
            return Vector2f(x=center_x, y=right_y)
        elif orientation == Orientation.BOTTOM_RIGHT:
            return Vector2f(x=right_x, y=right_y)

        assert False

    @staticmethod
    def elementwise_multiply(lhs: Vector2f, rhs: Vector2f) -> Vector2f:
        return Vector2f(x=lhs.__x * rhs.__x,
                        y=lhs.__y * rhs.__y)

    def lerp(self, coord0: Vector2f, coord1: Vector2f, alpha: float):
        assert isinstance(coord0, Vector2f)
        assert isinstance(coord1, Vector2f)
        assert isinstance(alpha, float)

        self.x = (1.0 - alpha) * coord0.x + alpha * coord1.x
        self.y = (1.0 - alpha) * coord0.y + alpha * coord1.y

    def normalize(self) -> bool:
        length: float = self.get_length()
        if length > 0.0:
            self.__x = self.__x / length
            self.__y = self.__y / length
            return True

        return False

    def set_coordinate(self, x: float, y: float):
        self.x = x
        self.y = y

    @staticmethod
    def to_tuple(vector: Vector2f) -> tuple[float, float]:
        return vector.x, vector.y


class Box:
    __slots__ = ["top_left", "width", "height"]

    def __init__(self, top_left: Vector2f, width: float, height: float):
        self.top_left: Vector2f = top_left
        self.width: float = width
        self.height: float = height

    def __str__(self) -> str:
        return f"box: {{ top_left: {self.top_left}, width: {self.width}, height: {self.height} }}"

    def has_collided_with(self, box: Box):
        return self.top_left.x < box.top_left.x + box.width and \
               self.top_left.x + self.width > box.top_left.x and \
               self.top_left.y < box.top_left.y + box.height and \
               self.top_left.y + self.height > box.top_left.y
