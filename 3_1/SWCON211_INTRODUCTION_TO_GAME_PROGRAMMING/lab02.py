from random import randint
from math import sqrt, fabs
import tkinter as tk


class GameObject(object):
    def __init__(self, canvas, item):
        self.canvas = canvas
        self.item = item

    def get_position(self):
        return self.canvas.coords(self.item)

    def move(self, x, y):
        self.canvas.move(self.item, x, y)

    def delete(self):
        self.canvas.delete(self.item)


class Ball(GameObject):
    def __init__(self, canvas: tk.Canvas, x: int, y: int):
        self.radius: int = 10
        self.direction: list[int] = [1, -1]
        self.speed: int = 10
        self.image: tk.PhotoImage = tk.PhotoImage(file="3_1/SWCON211_INTRODUCTION_TO_GAME_PROGRAMMING/ball2.png")
        self.x: int = x
        self.y: int = y
        item: int = canvas.create_image(x, y, anchor=tk.CENTER, image=self.image)
        super(Ball, self).__init__(canvas=canvas, item=item)

    def update(self):
        coords = self.get_position()
        width = self.canvas.winfo_width()
        if coords[0] <= 0 or coords[2] >= width:
            self.direction[0] *= -1
        if coords[1] <= 0:
            self.direction[1] *= -1
        x = self.direction[0] * self.speed
        y = self.direction[1] * self.speed
        self.move(x, y)

    def collide(self, game_objects: list):
        coords = self.get_position()
        x = (coords[0] + coords[2]) * 0.5
        if len(game_objects) > 1:
            self.direction[1] *= -1
        elif len(game_objects) == 1:
            game_object = game_objects[0]
            game_object_coords = game_object.get_position()

            intersection_0: tuple[int, int] = None
            intersection_1: tuple[int, int] = None
            is_vertical_middle: bool = (game_object_coords[1] + 1) < coords[1] and coords[3] < (game_object_coords[3] + 1)
            is_horizontal_middle: bool = (game_object_coords[0] + 1) < coords[0] and coords[2] < (game_object_coords[2] + 1)
            is_top: bool = coords[1] < (game_object_coords[1] + 1) < coords[3] < (game_object_coords[3] + 1)
            is_bottom: bool = (game_object_coords[1] + 1) < coords[1] < (game_object_coords[3] + 1) < coords[3]
            is_left: bool = coords[0] < (game_object_coords[0] + 1) < coords[2] < (game_object_coords[2] + 1)
            is_right: bool = (game_object_coords[0] + 1) < coords[0] < (game_object_coords[2] + 1) < coords[2]
            if is_left:
                if is_top:
                    intersection_0 = ((game_object_coords[0] + 1), coords[3])
                    intersection_1 = (coords[2], (game_object_coords[1] + 1))
                elif is_bottom:
                    intersection_0 = ((game_object_coords[0] + 1), coords[1])
                    intersection_1 = (coords[2], (game_object_coords[3] + 1))
                elif is_vertical_middle:
                    intersection_0 = ((game_object_coords[0] + 1), coords[1])
                    intersection_1 = ((game_object_coords[0] + 1), coords[3])
            elif is_right:
                if is_bottom:
                    intersection_0 = (coords[0], (game_object_coords[3] + 1))
                    intersection_1 = ((game_object_coords[2] + 1), coords[1])
                elif is_top:
                    intersection_0 = (coords[0], (game_object_coords[1] + 1))
                    intersection_1 = ((game_object_coords[2] + 1), coords[3])
                elif is_vertical_middle:
                    intersection_0 = ((game_object_coords[2] + 1), coords[1])
                    intersection_1 = ((game_object_coords[2] + 1), coords[3])
            elif is_horizontal_middle:
                if is_top:
                    intersection_0 = (coords[0], (game_object_coords[1] + 1))
                    intersection_1 = (coords[1], (game_object_coords[1] + 1))
                elif is_bottom:
                    intersection_0 = (coords[0], (game_object_coords[3] + 1))
                    intersection_1 = (coords[1], (game_object_coords[3] + 1))
            else:
                if x > coords[2]:
                    self.direction[0] = 1
                elif x < coords[0]:
                    self.direction[0] = -1
                else:
                    self.direction[1] *= -1

            if intersection_0 is not None and intersection_1 is not None:
                dx: int = intersection_1[0] - intersection_0[0]
                dy: int = intersection_1[1] - intersection_0[1]
                length: float = sqrt(fabs(dx) ** 2 + fabs(dy) ** 2)

                if is_horizontal_middle or is_vertical_middle:
                    if is_horizontal_middle:
                        normal_0: tuple[int, int] = (0, 1)
                        normal_1: tuple[int, int] = (0, -1)
                    else:
                        normal_0: tuple[int, int] = (1, 0)
                        normal_1: tuple[int, int] = (-1, 0)
                else:
                    normal_0: tuple[int, int] = (-dy, dx)
                    normal_1: tuple[int, int] = (dy, -dx)

                center_vector: tuple[int, int] = (
                    (((game_object_coords[0] + 1) + (game_object_coords[2] + 1)) / 2 - ((intersection_0[0] + intersection_1[0]) / 2)),
                    (((game_object_coords[1] + 1) + (game_object_coords[3] + 1)) / 2 - ((intersection_0[1] + intersection_1[1]) / 2)))

                cos_0: int = normal_0[0] * center_vector[0] + normal_0[1] * center_vector[1]
                cos_1: int = normal_1[0] * center_vector[0] + normal_1[1] * center_vector[1]

                if cos_0 < cos_1:
                    normal: tuple[float, float] = (length * normal_0[0] / sqrt(normal_0[0] ** 2 + normal_0[1] ** 2),
                                                   length * normal_0[1] / sqrt(normal_0[0] ** 2 + normal_0[1] ** 2))
                else:
                    normal: tuple[float, float] = (length * normal_1[0] / sqrt(normal_1[0] ** 2 + normal_1[1] ** 2),
                                                   length * normal_1[1] / sqrt(normal_1[0] ** 2 + normal_1[1] ** 2))

                cos: float = normal[0] * self.direction[0] + normal[1] * self.direction[1]
                if cos < 0.0:
                    if is_horizontal_middle or is_vertical_middle:
                        if is_horizontal_middle:
                            self.direction[1] *= -1
                        else:
                            self.direction[0] *= -1
                    else:
                        vx: float = 2 * (-self.direction[0] * normal[0] - self.direction[1] * normal[1]) * normal[0] + \
                                    self.direction[0]
                        vy: float = 2 * (-self.direction[0] * normal[0] - self.direction[1] * normal[1]) * normal[1] + \
                                    self.direction[1]
                        self.direction[0] = sqrt(2) * (vx / sqrt(vx ** 2 + vy ** 2))
                        self.direction[1] = sqrt(2) * (vy / sqrt(vx ** 2 + vy ** 2))

        for game_object in game_objects:
            if isinstance(game_object, Brick):
                game_object.hit()

    def get_position(self):
        return self.canvas.coords(self.item)[0], \
               self.canvas.coords(self.item)[1], \
               self.canvas.coords(self.item)[0] + 2 * self.radius, \
               self.canvas.coords(self.item)[1] + 2 * self.radius


class Paddle(GameObject):
    def __init__(self, canvas, x, y):
        self.width = 80
        self.height = 10
        self.ball = None
        item = canvas.create_rectangle(x - self.width / 2,
                                       y - self.height / 2,
                                       x + self.width / 2,
                                       y + self.height / 2,
                                       fill='blue')
        super(Paddle, self).__init__(canvas, item)

    def set_ball(self, ball):
        self.ball = ball

    def move(self, offset):
        coords = self.get_position()
        width = self.canvas.winfo_width()
        if coords[0] + offset >= 0 and coords[2] + offset <= width:
            super(Paddle, self).move(offset, 0)
            if self.ball is not None:
                self.ball.move(offset, 0)


class Brick(GameObject):
    COLORS = {1: '#999999', 2: '#555555', 3: '#222222'}

    def __init__(self, canvas, x, y, hits):
        self.width = 75
        self.height = 20
        self.hits = hits
        color = Brick.COLORS[hits]
        item = canvas.create_rectangle(x - self.width / 2,
                                       y - self.height / 2,
                                       x + self.width / 2,
                                       y + self.height / 2,
                                       fill=color, tags='brick')
        super(Brick, self).__init__(canvas, item)

    def hit(self):
        self.hits -= 1
        if self.hits == 0:
            self.delete()
        else:
            self.canvas.itemconfig(self.item,
                                   fill=Brick.COLORS[self.hits])


class Game(tk.Frame):
    def __init__(self, master: tk.Tk):
        super(Game, self).__init__(master)
        self.level: int = 1
        self.lives: int = 3
        self.width: int = 610
        self.height: int = 400
        self.canvas: tk.Canvas = tk.Canvas(self, bg='#aaaaff',
                                           width=self.width,
                                           height=self.height, )
        self.canvas.pack()
        self.pack()

        self.items: dict = {}
        self.ball: Ball = None
        self.paddle: Paddle = Paddle(self.canvas, self.width / 2, 326)
        self.items[self.paddle.item] = self.paddle

        self.you_win_text: int = None

        self.hud: int = None
        self.setup_game()
        self.canvas.focus_set()
        self.canvas.bind('<Left>',
                         lambda _: self.paddle.move(-10))
        self.canvas.bind('<Right>',
                         lambda _: self.paddle.move(10))

    def setup_game(self):
        if self.you_win_text is not None:
            self.canvas.unbind('<space>')
            self.canvas.delete(self.you_win_text)

        for y in range(0, self.level):
            for x in range(5, self.width - 5, 75):
                if randint(0, 1) == 0:
                    self.add_brick(x + 37.5, 50 + y * 20, randint(1, min(self.level - y, 3)))

        self.add_ball()
        self.update_lives_text()
        self.text: str = self.draw_text(300, 200,
                                        'Press Space to start')
        self.canvas.bind('<space>', lambda _: self.start_game())

    def add_ball(self):
        if self.ball is not None:
            self.ball.delete()
        paddle_coords = self.paddle.get_position()
        x = (paddle_coords[0] + paddle_coords[2]) * 0.5
        self.ball = Ball(self.canvas, x, 310)
        self.paddle.set_ball(self.ball)

    def add_brick(self, x, y, hits):
        brick = Brick(self.canvas, x, y, hits)
        self.items[brick.item] = brick

    def draw_text(self, x, y, text, size='40'):
        font = ('Helvetica', size)
        return self.canvas.create_text(x, y, text=text,
                                       font=font)

    def update_lives_text(self):
        text: str = f"Lives: {self.lives} Level: {self.level}"
        if self.hud is None:
            self.hud = self.draw_text(100, 20, text, 15)
        else:
            self.canvas.itemconfig(self.hud, text=text)

    def start_game(self):
        self.canvas.unbind('<space>')
        self.canvas.delete(self.text)
        self.paddle.ball = None
        self.game_loop()

    def game_loop(self):
        self.check_collisions()
        num_bricks = len(self.canvas.find_withtag('brick'))
        if num_bricks == 0:
            self.level += 1
            self.ball.speed = None
            self.you_win_text = self.draw_text(300, 200, 'You win! Press Space to Continue', size=25)
            self.canvas.bind('<space>', lambda _: self.setup_game())
        elif self.ball.get_position()[3] >= self.height:
            self.ball.speed = None
            self.lives -= 1
            if self.lives < 0:
                self.draw_text(300, 200, 'Game Over')
            else:
                self.after(1000, self.setup_game)
        else:
            self.ball.update()
            self.after(50, self.game_loop)

    def check_collisions(self):
        ball_coords = self.ball.get_position()
        items = self.canvas.find_overlapping(*ball_coords)
        objects = [self.items[x] for x in items if x in self.items]
        self.ball.collide(objects)


if __name__ == '__main__':
    root = tk.Tk()
    root.title('Hello, Pong!')
    game = Game(root)
    game.mainloop()
