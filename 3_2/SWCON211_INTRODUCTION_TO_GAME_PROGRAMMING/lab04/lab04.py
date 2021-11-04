import cocos
import cocos.collision_model as cm
import cocos.euclid as eu
from random import randint
from math import sqrt

from collections import defaultdict
from pyglet.window import key

class Actor(cocos.sprite.Sprite):
    def __init__(self, x, y, color, width: int, height: int):
        super(Actor, self).__init__('ball.png', color=color)
        self.position = pos = eu.Vector2(x, y)
        self.cshape = cm.CircleShape(pos, self.width/2)
        self.speed: int = 1
        self.direction: list[int] = [0, 0]
        self.screen_width: int = width
        self.screen_height: int = height
        self.is_dead: bool = False

    def randomize_position(self, avoid_x1: int, avoid_y1: int, avoid_x2: int, avoid_y2: int):
        new_x: int = avoid_x1
        new_y: int = avoid_y1

        while avoid_x1 - self.width / 2 <= new_x <= avoid_x2 + self.width / 2:
            new_x = randint(0, self.screen_width - 1)

        while avoid_y1 - self.height / 2 <= new_y <= avoid_y2 + self.height / 2:
            new_y = randint(0, self.screen_height - 1)

        self.position = eu.Vector2(new_x, new_y)
        self.cshape.center = eu.Vector2(self.position[0], self.position[1])
        self.is_dead = True

    def update(self, is_player: bool):
        if self.position[0] < 0:
            self.position = eu.Vector2(self.screen_width - 1, self.position[1])
        if self.position[0] >= self.screen_width:
            self.position = eu.Vector2(0, self.position[1])
        if self.position[1] < 0:
            self.position = eu.Vector2(self.position[0], self.screen_height - 1)
        if self.position[1] >= self.screen_height:
            self.position = eu.Vector2(self.position[0], 0)
        if not is_player:
            if self.is_dead or (self.direction[0] == 0 and self.direction[1] == 0) or randint(0, 60) == 0:
                self.is_dead = False
                self.direction[0] = 0
                self.direction[1] = 0
                while self.direction[0] == 0:
                    self.direction[0] = randint(-16, 16)
                while self.direction[1] == 0:
                    self.direction[1] = randint(-16, 16)
            self.position = eu.Vector2(self.position[0] + (self.direction[0] / sqrt(self.direction[0] ** 2 + self.direction[1] ** 2)) * self.speed,
                                       self.position[1] + (self.direction[1] / sqrt(self.direction[0] ** 2 + self.direction[1] ** 2)) * self.speed)
            self.cshape.center = eu.Vector2(self.position[0], self.position[1])

class MainLayer(cocos.layer.Layer):
    is_event_handler = True

    def __init__(self):
        super(MainLayer, self).__init__()
        self.player = Actor(320, 240, (0, 0, 255), width=640, height=480)
        self.add(self.player)
        for pos in [(100,100), (540,380), (540,100), (100,380)]:
            self.add(Actor(pos[0], pos[1], (255, 0, 0), width=640, height=480))

        cell = self.player.width * 1.25
        self.collman = cm.CollisionManagerGrid(0, 640, 0, 480,
                                               cell, cell)
        self.speed = 100.0
        self.pressed = defaultdict(int)
        self.schedule(self.update)

    def on_key_press(self, k, m):
        self.pressed[k] = 1

    def on_key_release(self, k, m):
        self.pressed[k] = 0
        
    def update(self, dt):
        self.collman.clear()
        for _, node in self.children:
            self.collman.add(node)
            node.update(node is self.player)
        for other in self.collman.iter_colliding(self.player):
            # self.remove(other)
            other.randomize_position(avoid_x1=self.player.position[0] - self.player.width / 2,
                                     avoid_y1=self.player.position[1] - self.player.height / 2,
                                     avoid_x2=self.player.position[0] + self.player.width / 2,
                                     avoid_y2=self.player.position[1] + self.player.height / 2)

        x = self.pressed[key.RIGHT] - self.pressed[key.LEFT]
        y = self.pressed[key.UP] - self.pressed[key.DOWN]
        if x != 0 or y != 0:
            pos = self.player.position
            new_x = pos[0] + self.speed * x * dt
            new_y = pos[1] + self.speed * y * dt
            self.player.position = eu.Vector2(new_x, new_y)
            self.player.cshape.center = self.player.position

if __name__ == '__main__':
    cocos.director.director.init(caption='Hello, Cocos')
    layer = MainLayer()
    scene = cocos.scene.Scene(layer)
    cocos.director.director.run(scene)
