import msvcrt
import os
import random
import sys
import time

from typing import Union


def convert_celsius_to_fahrenheit(celsius: float):
    return (9.0 / 5.0) * celsius + 32.0


def lab01():
    print("================LAB01================")
    input_celsius: float = None

    while input_celsius is None:
        input_data: str = input("Input celsius temperature: ")
        if input_data.isnumeric():
            input_celsius = float(input_data)

    print(f"Celsius degree {input_celsius} in fahrenheit is: {convert_celsius_to_fahrenheit(celsius=input_celsius)}")


def lab02(a: int, b: int):
    print("================LAB02================")
    print(f"{a} / {b}: quotient: {a // b}, remainder: {a % b}")


def lab03(working_hours: int, hourly_pay: float):
    print("================LAB03================")
    print(f"Worker worked for {working_hours} hours.", end='')

    total_pay: float = 0.0
    if working_hours > 40:
        total_pay = float(working_hours - 40) * 1.5 * hourly_pay + 40.0 * hourly_pay
        print(" Worker worked more than 40 hours")
    else:
        total_pay = float(working_hours) * hourly_pay
        print()

    print(f"Worker's hourly pay is {hourly_pay}")
    print(f"Worker's total pay is {total_pay}")


def lab04(score: float):
    print("================LAB04================")
    if not 0.0 <= score <= 1.0:
        raise IndexError("Score must be in-between 0.0 and 1.0")

    print(f"Your score {score} has been graded as: ", end='')
    if score >= 0.9:
        print("A.")
    elif score >= 0.8:
        print("B.")
    elif score >= 0.7:
        print("C.")
    elif score >= 0.6:
        print("D.")
    else:
        print("F.")


def lab05(number: Union[int, float]):
    print("================LAB05================")
    print(f"{number} is ", end='')

    if number > 0:
        print("positive.")
    elif number < 0:
        print("negative.")
    else:
        print("zero.")


def lab06(number: int):
    assert number >= 0
    print("================LAB06================")

    print(f"Input number: {number}")
    index: int = 1
    while number > 0:
        print(f"\tDigit {index}: {number % 10}")
        number = int(number / 10)
        index += 1


def lab07(number: int):
    assert number >= 0
    print("================LAB07================")

    print(f"Input number: {number}, ", end='')
    digits: int = 0
    while number > 0:
        number = int(number / 10)
        digits += 1
    print(f"number of digits: {digits}.")


def lab08(size: int):
    assert size % 2 == 1 and 3 <= size <= 15
    print("================LAB08================")

    matrix: list[list[int]] = []
    for row in range(0, size):
        matrix.append([])
        for column in range(0, size):
            matrix[row].append(0)
    number: int = 1

    current_x: int = int(size / 2)
    current_y: int = 0
    while number <= size * size:
        matrix[current_y][current_x] = number

        number += 1
        new_y = (current_y - 1) % size
        new_x = (current_x - 1) % size

        if matrix[new_y][new_x] != 0:
            new_y = (current_y + 1) % size
            new_x = current_x

        current_y = new_y
        current_x = new_x

    for row in range(0, size):
        for column in range(0, size):
            print(f"{matrix[row][column]} ", end='')
        print()


class Object:
    def __init__(self, x: float, y: float, color: str = "white"):
        self.x: float = x
        self.y: float = y
        self.color: str = color

    def __str__(self):
        return f"object(x:{self.x}, y:{self.y}, color:{self.color})"


class Ball(Object):
    def __init__(self, x: float, y: float, radius: float, color: str = "white"):
        super(Ball, self).__init__(x=x, y=y, color=color)
        self.radius: float = radius

    def __str__(self):
        return f"ball(({super(Ball, self).__str__()}), radius:{self.radius})"


def lab09():
    print("================LAB09================")
    white_object: Object = Object(x=0.0, y=0.0)
    print(white_object)
    black_small_ball: Ball = Ball(x= 1.0, y=1.0, radius=0.5, color="black")
    print(black_small_ball)
    red_large_ball: Ball = Ball(x=4.0, y=3.0, radius=2.5, color="red")
    print(red_large_ball)
    green_small_ball_over_white_object: Ball = Ball(x=white_object.x,
                                              y=white_object.y,
                                              radius=black_small_ball.radius,
                                              color="green")
    print(green_small_ball_over_white_object)


class Snake:
    def __init__(self, length: int):
        self.length: int = length
        self.head: list[int] = []
        self.tail: list[int] = []


class SnakeGame:
    DIRECTION_TO_TUPLE: dict = {"LEFT": (-1, 0), "DOWN": (0, 1), "NON_DIR": (0, 0), "UP": (0, -1), "RIGHT": (1, 0)}
    INT_TO_DIRECTION: list[str] = ["NON_DIR", "UP", "RIGHT", "LEFT", "DOWN"]
    DIRECTION: dict = {"LEFT": -2, "DOWN": -1, "NON_DIR": 0, "UP": 1, "RIGHT": 2}
    SPRITE: dict = {"EMPTY": 0, "BODY": 1, "HEAD": 2, "FOOD": 3}
    ELEMENT: dict = {"SPRITE": 0, "DIRECTION": 1}

    def __init__(self, width: int, height: int, length: int, delay: float):
        self.width: int = width
        self.height: int = height
        self.init_length: int = length
        self.snake: Snake = Snake(length)
        self.delay: float = delay
        self.board: list[list[int]] = [[[0] * 2 for x in range(self.width)] for y in range(self.height)]

        self.snake.head = [self.height // 2, self.snake.length - 1]
        self.snake.tail = [self.height // 2, 0]

        for i in range(0, self.snake.length):
            self.board[self.height // 2][i][SnakeGame.ELEMENT["SPRITE"]] \
                = SnakeGame.SPRITE["BODY"]
            self.board[self.height // 2][i][SnakeGame.ELEMENT["DIRECTION"]] \
                = SnakeGame.DIRECTION["RIGHT"]

        self.board[self.height // 2][self.snake.length - 1][SnakeGame.ELEMENT["SPRITE"]] \
            = SnakeGame.SPRITE["HEAD"]
        self.board[self.height // 2][self.snake.length - 1][SnakeGame.ELEMENT["DIRECTION"]] \
            = SnakeGame.DIRECTION["RIGHT"]

        x: int = random.randint(0, self.width - 1)
        y: int = random.randint(0, self.height - 1)
        while self.board[y][x][SnakeGame.ELEMENT["SPRITE"]] \
                != SnakeGame.SPRITE["EMPTY"]:
            x = random.randint(0, self.width - 1)
            y = random.randint(0, self.height - 1)

        self.board[y][x][SnakeGame.ELEMENT["SPRITE"]] = SnakeGame.SPRITE["FOOD"]

    def render(self):
        os.system('cls||clear')
        for x in range(0, self.width + 2):
            print("=", end="")
        print("")
        for y in range(0, self.height):
            print("|", end="")
            for x in range(0, self.width):
                if self.board[y][x][SnakeGame.ELEMENT["SPRITE"]] \
                        == SnakeGame.SPRITE["BODY"]:
                    print("+", end="")
                elif self.board[y][x][SnakeGame.ELEMENT["SPRITE"]] \
                        == SnakeGame.SPRITE["HEAD"]:
                    print("@", end="")
                elif self.board[y][x][SnakeGame.ELEMENT["SPRITE"]] \
                        == SnakeGame.SPRITE["FOOD"]:
                    print("*", end="")
                else:
                    print(" ", end="")
            print("|")

        for x in range(0, self.width + 2):
            print("=", end="")
        print("")

    @staticmethod
    def get_direction() -> str:
        direction: str = "NON_DIR"
        msvcrt.getch()
        ch: str = msvcrt.getch().decode()

        if ch == chr(72):
            print("UP")
            direction = "UP"
        elif ch == chr(75):
            print("LEFT")
            direction = "LEFT"
        elif ch == chr(77):
            print("RIGHT")
            direction = "RIGHT"
        elif ch == chr(80):
            print("DOWN")
            direction = "DOWN"
        elif ch == chr(113):
            print("QUIT")
            direction = "NULL"

        return direction

    def spawn_food(self):
        while True:
            food_x: int = random.randint(0, self.width)
            food_y: int = random.randint(0, self.height)

            if self.board[food_y][food_x][SnakeGame.ELEMENT["SPRITE"]] == SnakeGame.SPRITE["EMPTY"]:
                break

        self.board[food_y][food_x][SnakeGame.ELEMENT["SPRITE"]] = SnakeGame.SPRITE["FOOD"]
        self.board[food_y][food_x][SnakeGame.ELEMENT["DIRECTION"]] = SnakeGame.DIRECTION["NON_DIR"]

    def update_snake(self, direction_int: int) -> bool:
        self.board[self.snake.head[0]][self.snake.head[1]][SnakeGame.ELEMENT["SPRITE"]] \
            = SnakeGame.SPRITE["BODY"]

        direction: tuple[int, int] = self.DIRECTION_TO_TUPLE[self.INT_TO_DIRECTION[direction_int]]

        new_head_x = self.snake.head[0] + direction[1]
        new_head_y = self.snake.head[1] + direction[0]

        if new_head_x < 0 or new_head_x >= self.height:
            return False

        if new_head_y < 0 or new_head_y >= self.width:
            return False

        has_ate_food: bool = False
        if self.board[new_head_x][new_head_y][SnakeGame.ELEMENT["SPRITE"]] == SnakeGame.SPRITE["FOOD"]:
            has_ate_food = True
            self.board[new_head_x][new_head_y][SnakeGame.ELEMENT["SPRITE"]] = SnakeGame.SPRITE["EMPTY"]
            self.spawn_food()
        elif self.board[new_head_x][new_head_y][SnakeGame.ELEMENT["SPRITE"]] \
                != SnakeGame.SPRITE["EMPTY"]:
            return False

        if not has_ate_food:
            next_tail_x: int \
                = self.snake.tail[0] \
                  + self.DIRECTION_TO_TUPLE[
                      self.INT_TO_DIRECTION[
                          self.board[self.snake.tail[0]][self.snake.tail[1]][SnakeGame.ELEMENT["DIRECTION"]]
                      ]
                  ][1]
            next_tail_y: int \
                = self.snake.tail[1] \
                  + self.DIRECTION_TO_TUPLE[
                      self.INT_TO_DIRECTION[
                          self.board[self.snake.tail[0]][self.snake.tail[1]][SnakeGame.ELEMENT["DIRECTION"]]
                      ]
                  ][0]

            self.board[self.snake.tail[0]][self.snake.tail[1]][SnakeGame.ELEMENT["SPRITE"]] \
                = SnakeGame.SPRITE["EMPTY"]

            print(f"{next_tail_x}, {next_tail_y}, {self.snake.tail}, "
                  f'{self.board[self.snake.tail[0]][self.snake.tail[1]][SnakeGame.ELEMENT["SPRITE"]]}')

            self.snake.tail[0] = next_tail_x
            self.snake.tail[1] = next_tail_y

        self.board[new_head_x][new_head_y][SnakeGame.ELEMENT["SPRITE"]] \
            = SnakeGame.SPRITE["HEAD"]

        self.board[self.snake.head[0]][self.snake.head[1]][SnakeGame.ELEMENT["DIRECTION"]] \
            = direction_int

        self.snake.head[0] = new_head_x
        self.snake.head[1] = new_head_y

        return True

    def main(self):
        self.render()

        previous_direction: str = "RIGHT"
        while True:
            start = time.time()
            has_made_decision: bool = False
            while (time.time() - start) <= self.delay / 1000.0:
                if not has_made_decision:
                    current: str = previous_direction
                    if msvcrt.kbhit():
                        sys.stdout.flush()
                        current = self.get_direction()
                        if current == "NULL":
                            return
                        elif current != "NON_DIR":
                            previous_direction = current

                    if not self.update_snake(self.DIRECTION[current]):
                        return
                    else:
                        has_made_decision = True

            self.render()
            print("Score: {}".format(self.snake.length - self.init_length))


def main():
    # lab01()
    # lab02(a=random.randint(0, 100), b=random.randint(0, 100))
    # lab03(working_hours=random.randint(0, 80), hourly_pay=random.uniform(0, 10.0))
    # lab04(score=random.uniform(0.0, 1.0))
    # for i in range(0, 100):
    #     lab05(number=random.uniform(-10.0, 10.0))
    # for i in range(0, 100):
    #     lab06(number=random.randint(0, 1000000))
    # for i in range(0, 10):
    #     lab07(number=random.randint(0, pow(10, random.randint(0, 8))))
    # lab08(size=(random.randint(1, 7) * 2 + 1))
    # lab09()
    game = SnakeGame(60, 24, 4, 300)
    game.main()


if __name__ == "__main__":
    main()
