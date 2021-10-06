from math import cos, radians, sin, sqrt
import random

from collections import defaultdict

from pyglet.image import load, ImageGrid, Animation
from pyglet.window import key

import cocos.layer
import cocos.sprite
import cocos.collision_model as cm
import cocos.euclid as eu


class Actor(cocos.sprite.Sprite):
    def __init__(self, image, x, y):
        super(Actor, self).__init__(image)
        self.position = eu.Vector2(x, y)
        self.cshape = cm.AARectShape(self.position,
                                     self.width * 0.5,
                                     self.height * 0.5)

    def move(self, offset, is_player: bool = False):
        self.position += offset
        self.cshape.center += offset

        if is_player:
            if self.position[0] < self.width / 2:
                self.position = (self.width / 2, self.position[1])
                self.cshape.center[0] = self.position[0]

            if self.parent.width - self.width / 2 < self.position[0]:
                self.position = (self.parent.width - self.width / 2, self.position[1])
                self.cshape.center[0] = self.position[0]

    def update(self, elapsed):
        pass

    def collide(self, other):
        pass

class PlayerCannonEffect(Actor):
    def __init__(self, x, y, opacity):
        super(PlayerCannonEffect, self).__init__(image="img/cannon.png", x=x, y=y)
        self.opacity = opacity
        self.cshape = cm.AARectShape((-1, -1),
                                     self.width * 0.5,
                                     self.height * 0.5)
    def update(self, elapsed):
        self.opacity -= 255 * elapsed

        if self.opacity <= 0:
            self.kill()

class PlayerCannon(Actor):
    KEYS_PRESSED = defaultdict(int)
    SHOOT_RATE: float = 0.5
    FLASH_RATE: float = 3.0

    def __init__(self, x, y):
        super(PlayerCannon, self).__init__('img/cannon.png', x, y)
        self.speed = eu.Vector2(200, 0)
        self.shoot_timer: float = 0.0
        self.flash_timer: float = 0.0
        self.shoot_mode: int = 1
        self.current_score: int = None

    def update(self, elapsed):
        if self.current_score is None:
            self.current_score: int = self.parent.score
        self.shoot_timer = max(0.0, self.shoot_timer - elapsed)
        self.flash_timer = max(0.0, self.flash_timer - elapsed)
        pressed = PlayerCannon.KEYS_PRESSED
        space_pressed = pressed[key.SPACE] == 1
        if space_pressed and self.shoot_timer == 0.0:
            self.shoot_timer = self.SHOOT_RATE
            self.parent.shoot_laser(x=self.x, y=self.y + 50, shoot_mode=self.shoot_mode)

        movement = pressed[key.RIGHT] - pressed[key.LEFT]
        w = self.width * 0.5
        if movement != 0 and w <= self.x <= self.parent.width - w:
            if pressed[key.F] and self.flash_timer == 0.0:
                self.flash_timer = self.FLASH_RATE
                previous_position = self.position
                self.move(self.speed * 40 * movement * elapsed, is_player=True)
                flash_size: int = 4
                for i in range(0, flash_size):
                    self.parent.add(PlayerCannonEffect(x=((self.position[0] - previous_position[0]) * (i + 1) / flash_size) + previous_position[0],
                                                   y=((self.position[1] - previous_position[1]) * (i + 1) / flash_size) + previous_position[1],
                                                   opacity=(255 * (i + 1)) / flash_size))
            else:
                self.move(self.speed * movement * elapsed, is_player=True)

    def collide(self, other):
        if isinstance(other, PlayerCannonEffect):
            return
        other.kill()
        self.kill()

class GameLayer(cocos.layer.Layer):
    is_event_handler = True

    def on_key_press(self, k, _):
        PlayerCannon.KEYS_PRESSED[k] = 1

    def on_key_release(self, k, _):
        PlayerCannon.KEYS_PRESSED[k] = 0
    
    def __init__(self, hud):
        super(GameLayer, self).__init__()
        w, h = cocos.director.director.get_window_size()
        self.hud = hud
        self.width = w
        self.height = h
        self.lives = 3
        self.score = 0
        self.laser_pool: list[PlayerShoot] = []
        self.update_score()
        self.create_player()
        self.create_alien_group(100, 300)
        cell = 1.25 * 50
        self.collman = cm.CollisionManagerGrid(0, w, 0, h, 
                                               cell, cell)
        self.schedule(self.update)

    def create_player(self):
        self.player = PlayerCannon(self.width * 0.5, 50)
        self.add(self.player)
        self.hud.update_lives(self.lives)

    def shoot_laser(self, x: float, y: float, shoot_mode: int = 1):
        offset: float = self.player.width / (self.player.shoot_mode + 1)
        for i in range(0, shoot_mode):
            if shoot_mode % 2 == 1:
                if i == shoot_mode // 2:
                    laser: PlayerShoot = PlayerShoot(x=x - self.player.width / 2 + offset * (i + 1),
                                                     y=y)
                else:
                    index: int = i
                    if i > shoot_mode // 2:
                        index = (shoot_mode // 2) - (i - shoot_mode // 2)
                    angle: float = radians((((shoot_mode - 2 * index) * 180 / ((shoot_mode - 2 * index) + 2)) / 3) + 60)
                    laser: PlayerShoot = PlayerShoot(x=x - self.player.width / 2 + offset * (i + 1),
                                                     y=y,
                                                     x_direction=(-1 if i < shoot_mode // 2 else 1) * cos(angle),
                                                     y_direction=-sin(angle))
            else:
                if i == shoot_mode // 2 - 1 or i == shoot_mode // 2:
                    laser: PlayerShoot = PlayerShoot(x=x - self.player.width / 2 + offset * (i + 1),
                                                     y=y)
                else:
                    index: int = i
                    if i > shoot_mode // 2:
                        index = ((shoot_mode // 2) - 1) - (i - (shoot_mode // 2))
                    angle: float = radians((((shoot_mode - 2 * index) * 180 / ((shoot_mode - 2 * index) + 2)) / 3) + 60)
                    laser: PlayerShoot = PlayerShoot(x=x - self.player.width / 2 + offset * (i + 1),
                                                     y=y,
                                                     x_direction=(-1 if i < shoot_mode // 2 else 1) * cos(angle),
                                                     y_direction=-sin(angle))
            self.add(laser)
            self.laser_pool.append(laser)

    def update_score(self, score=0):
        self.score += score
        self.hud.update_score(self.score)

    def create_alien_group(self, x, y):
        self.alien_group = AlienGroup(x, y)
        for alien in self.alien_group:
            self.add(alien)

    def update(self, dt):
        self.collman.clear()
        for _, node in self.children:
            self.collman.add(node)
            if not self.collman.knows(node):
                self.remove(node)
        # self.collide(PlayerShoot.INSTANCE)
        for laser in self.laser_pool:
            self.collide(laser)
        if self.collide(self.player):
            self.respawn_player()

        for column in self.alien_group.columns:
            shoot = column.shoot()
            if shoot is not None:
                self.add(shoot)

        for _, node in self.children:
            node.update(dt)
        self.alien_group.update(dt)
        if random.random() < 0.001:
            self.add(MysteryShip(50, self.height - 50))

        if self.score - self.player.current_score >= self.player.shoot_mode * 300:
            self.player.shoot_mode += 1

        is_alien_all_dead: bool = True
        for column in self.alien_group.columns:
            if len(column.aliens) != 0:
                is_alien_all_dead = False
                break

        if is_alien_all_dead:
            self.create_alien_group(100, 300)


    def collide(self, node):
        if node is not None:
            for other in self.collman.iter_colliding(node):
                node.collide(other)
                return True
        return False
    
    def respawn_player(self):
        self.lives -= 1
        if self.lives < 0:
            self.unschedule(self.update)
            self.hud.show_game_over()
        else:
            self.create_player()

class Alien(Actor):
    def load_animation(imgage):
        seq = ImageGrid(load(imgage), 2, 1)
        return Animation.from_image_sequence(seq, 0.5)
    
    TYPES = {
        '1': (load_animation('img/alien1.png'), 40),
        '2': (load_animation('img/alien2.png'), 20),
        '3': (load_animation('img/alien3.png'), 10)
    }

    def from_type(x, y, alien_type, column):
        animation, score = Alien.TYPES[alien_type]
        return Alien(animation, x, y, score, column)
    
    def __init__(self, img, x, y, score, column=None):
        super(Alien, self).__init__(img, x, y)
        self.score = score
        self.column = column

    def on_exit(self):
        super(Alien, self).on_exit()
        if self.column:
            self.column.remove(self)

class AlienColumn(object):
    def __init__(self, x, y):
        alien_types = enumerate(['3', '3', '2', '2', '1'])
        self.aliens = [Alien.from_type(x, y+i*60, alien, self) 
                       for i, alien in alien_types]

    def should_turn(self, d):
        if len(self.aliens) == 0:
            return False
        alien = self.aliens[0]
        x, width = alien.x, alien.parent.width
        return x >= width - 50 and d == 1 or x <= 50 and d == -1
    
    def remove(self, alien):
        self.aliens.remove(alien)

    def shoot(self):
        if random.random() < 0.001 and len(self.aliens) > 0:
            pos = self.aliens[0].position
            return Shoot(pos[0], pos[1] - 50)
        return None


class AlienGroup(object):
    def __init__(self, x, y):
        self.columns = [AlienColumn(x + i * 60, y)
                        for i in range(10)]
        self.speed = eu.Vector2(10, 0)
        self.direction = 1
        self.elapsed = 0.0
        self.period = 1.0

    def update(self, elapsed):
        self.elapsed += elapsed
        while self.elapsed >= self.period:
            self.elapsed -= self.period
            offset = self.direction * self.speed
            if self.side_reached():
                self.direction *= -1
                offset = eu.Vector2(0, -10)
            for alien in self:
                alien.move(offset)

    def side_reached(self):
        return any(map(lambda c: c.should_turn(self.direction), 
                       self.columns))

    def __iter__(self):
        for column in self.columns:
            for alien in column.aliens:
                yield alien

class Shoot(Actor):
    def __init__(self, x, y, img='img/shoot.png'):
        super(Shoot, self).__init__(img, x, y)
        self.speed = eu.Vector2(0, -400)

    def update(self, elapsed):
        self.move(offset=self.speed * elapsed)

class PlayerShoot(Shoot):
    INSTANCE = None

    def __init__(self, x: float, y: float, x_direction: float = 0, y_direction: float = -1, is_hidden: bool = True):
        super(PlayerShoot, self).__init__(x, y, 'img/laser.png')
        # self.speed *= -1
        self.velocity: float = self.speed[1]
        self.speed[0] = x_direction / sqrt(x_direction ** 2 + y_direction ** 2) * self.velocity
        self.speed[1] = y_direction / sqrt(x_direction ** 2 + y_direction ** 2) * self.velocity
        print(f"speed: {self.speed}")
        # PlayerShoot.INSTANCE = self

    def collide(self, other):
        if isinstance(other, Alien):
            self.parent.update_score(other.score)
            self.parent.laser_pool.remove(self)
            try:
                other.kill()
            except Exception as e:
                print(f"Exception: {e}")

            self.kill()

    def on_exit(self):
        super(PlayerShoot, self).on_exit()
        # PlayerShoot.INSTANCE = None

class HUD(cocos.layer.Layer):
    def __init__(self):
        super(HUD, self).__init__()
        w, h = cocos.director.director.get_window_size()
        self.score_text = cocos.text.Label('', font_size=18)
        self.score_text.position = (20, h - 40)
        self.lives_text = cocos.text.Label('', font_size=18)
        self.lives_text.position = (w - 100, h - 40)
        self.add(self.score_text)
        self.add(self.lives_text)

    def update_score(self, score):
        self.score_text.element.text = 'Score: %s' % score

    def update_lives(self, lives):
        self.lives_text.element.text = 'Lives: %s' % lives

    def show_game_over(self):
        w, h = cocos.director.director.get_window_size()
        game_over = cocos.text.Label('Game Over', font_size=50,
                                     anchor_x='center',
                                     anchor_y='center')
        game_over.position = w * 0.5, h * 0.5
        self.add(game_over)

class MysteryShip(Alien):
    SCORES = [10, 50, 100, 200]

    def __init__(self, x, y):
        score = random.choice(MysteryShip.SCORES)
        super(MysteryShip, self).__init__('img/alien4.png', x, y, 
                                          score)
        self.speed = eu.Vector2(150, 0)

    def update(self, elapsed):
        self.move(self.speed * elapsed)


if __name__ == '__main__':
    cocos.director.director.init(caption='Cocos Invaders', 
                                 width=800, height=650)
    main_scene = cocos.scene.Scene()
    hud_layer = HUD()
    main_scene.add(hud_layer, z=1)
    game_layer = GameLayer(hud_layer)
    main_scene.add(game_layer, z=0)
    cocos.director.director.run(main_scene)
