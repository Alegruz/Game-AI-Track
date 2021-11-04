from enum import Enum
from random import randint
import tkinter as tk
from tkinter import messagebox as mb
from typing import Set, Tuple

MINE: int = -1

class eGameMode(Enum):
	NINE_BY_NINE: int = 10
	SIXTEEN_BY_SIXTEEN: int = 40
	SIXTEEN_BY_THIRTY: int = 99

class eTileDirection(Enum):
	NW: int = 0
	N: int = 1
	NE: int = 2
	W: int = 3
	E: int = 4
	SW: int = 5
	S: int = 6
	SE: int = 7

class TileNode:
	def __init__(self, x: int, y: int, width: int, height: int, value: int) -> None:
		self.neighbor: list[TileNode] = [None, None, None, None, None, None, None, None]
		self.value: int = value
		self.x: int = x
		self.y: int = y
		self.is_flagged: bool = False
		self.is_opened: bool = False
		self.drawn_item_index: int = -1
	
	def add_neighbor(self, direction: eTileDirection, node):
		self.neighbor[direction.value] = node

class Board:
	def __init__(self, width: int, height: int, mine_count: int) -> None:
		assert width > 0 and height > 0 and mine_count > 0

		self.width: int = width
		self.height: int = height
		self.board: list[list[TileNode]] = []
		for y in range(0, height):
			self.board.append([])
			for x in range(0, width):
				self.board[y].append(TileNode(x=x, y=y, width=self.width, height=self.height, value=0))
		discovered: set[TileNode] = set()
		self.__add_node_recursive__(node=self.board[0][0], discovered=discovered)

		self.mine_positions: list[list[int, int]] = []
		for i in range(0, mine_count):
			self.mine_positions.append([0, 0])

		self.found_mine_count: int = 0
		self.mines: set[TileNode] = set()
		
		self.reset()

	def reset(self):
		self.__init_board__()
		
		for mine_position in self.mine_positions:
			while True:
				candidate_position = [randint(0, self.width - 1), randint(0, self.height - 1)]
				if self.board[candidate_position[1]][candidate_position[0]] not in self.mines:
					break
			mine_position[0] = candidate_position[0]
			mine_position[1] = candidate_position[1]
			self.board[candidate_position[1]][candidate_position[0]].value = MINE
			self.mines.add(self.board[candidate_position[1]][candidate_position[0]])
			has_left_cell: bool = candidate_position[0] > 0
			has_right_cell: bool = candidate_position[0] < self.width - 1
			has_top_cell: bool = candidate_position[1] > 0
			has_bottom_cell: bool = candidate_position[1] < self.height - 1
			if has_top_cell:
				if has_left_cell:
					if self.board[mine_position[1] - 1][mine_position[0] - 1].value != MINE:
						self.board[mine_position[1] - 1][mine_position[0] - 1].value += 1
				if has_right_cell:
					if self.board[mine_position[1] - 1][mine_position[0] + 1].value != MINE:
						self.board[mine_position[1] - 1][mine_position[0] + 1].value += 1
				if self.board[mine_position[1] - 1][mine_position[0]].value != MINE:
					self.board[mine_position[1] - 1][mine_position[0]].value += 1
			if has_bottom_cell:
				if has_left_cell:
					if self.board[mine_position[1] + 1][mine_position[0] - 1].value != MINE:
						self.board[mine_position[1] + 1][mine_position[0] - 1].value += 1
				if has_right_cell:
					if self.board[mine_position[1] + 1][mine_position[0] + 1].value != MINE:
						self.board[mine_position[1] + 1][mine_position[0] + 1].value += 1
				if self.board[mine_position[1] + 1][mine_position[0]].value != MINE:
					self.board[mine_position[1] + 1][mine_position[0]].value += 1
			if has_left_cell:
				if self.board[mine_position[1]][mine_position[0] - 1].value != MINE:
					self.board[mine_position[1]][mine_position[0] - 1].value += 1
			if has_right_cell:
				if self.board[mine_position[1]][mine_position[0] + 1].value != MINE:
					self.board[mine_position[1]][mine_position[0] + 1].value += 1
	
	def get_value(self, x: int, y: int) -> int:
		return self.board[y][x].value
	
	def open(self, x: int, y: int, item: int):
		self.board[y][x].is_opened = True
		self.board[y][x].drawn_item_index = item
	
	def mark(self, x: int, y: int, item: int):
		self.board[y][x].is_flagged = True
		self.board[y][x].drawn_item_index = item
		if self.board[y][x] in self.mines:
			self.found_mine_count += 1
	
	def unmark(self, x: int, y: int) -> int:
		self.board[y][x].is_flagged = False
		item: int = self.board[y][x].drawn_item_index
		self.board[y][x].drawn_item_index = -1
		if self.board[y][x] in self.mines:
			self.found_mine_count -= 1
		return item

	def __add_node_recursive__(self, node: TileNode, discovered: Set[TileNode]):
		if node not in discovered:
			discovered.add(node)
			has_left_cell: bool = node.x > 0
			has_right_cell: bool = node.x < self.width - 1
			has_top_cell: bool = node.y > 0
			has_bottom_cell: bool = node.y < self.height - 1

			if has_top_cell:
				if has_left_cell:
					node.add_neighbor(direction=eTileDirection.NW, node=self.board[node.y - 1][node.x - 1])
					self.__add_node_recursive__(node=self.board[node.y - 1][node.x - 1], discovered=discovered)
				if has_right_cell:
					node.add_neighbor(direction=eTileDirection.NE, node=self.board[node.y - 1][node.x + 1])
					self.__add_node_recursive__(node=self.board[node.y - 1][node.x + 1], discovered=discovered)
				node.add_neighbor(direction=eTileDirection.N, node=self.board[node.y - 1][node.x])
				self.__add_node_recursive__(node=self.board[node.y - 1][node.x], discovered=discovered)
			if has_bottom_cell:
				if has_left_cell:
					node.add_neighbor(direction=eTileDirection.SW, node=self.board[node.y + 1][node.x - 1])
					self.__add_node_recursive__(node=self.board[node.y + 1][node.x - 1], discovered=discovered)
				if has_right_cell:
					node.add_neighbor(direction=eTileDirection.SE, node=self.board[node.y + 1][node.x + 1])
					self.__add_node_recursive__(node=self.board[node.y + 1][node.x + 1], discovered=discovered)
				node.add_neighbor(direction=eTileDirection.N, node=self.board[node.y - 1][node.x])
				self.__add_node_recursive__(node=self.board[node.y - 1][node.x], discovered=discovered)
			if has_left_cell:
				node.add_neighbor(direction=eTileDirection.W, node=self.board[node.y][node.x - 1])
				self.__add_node_recursive__(node=self.board[node.y][node.x - 1], discovered=discovered)
			if has_right_cell:
				node.add_neighbor(direction=eTileDirection.E, node=self.board[node.y][node.x + 1])
				self.__add_node_recursive__(node=self.board[node.y][node.x + 1], discovered=discovered)

	def __init_board__(self):
		for y in range(0, self.height):
			for x in range(0, self.width):
				self.board[y][x].value = 0
		self.found_mine_count = 0


class MineSweeperGame(tk.Frame):
	TILE_SIZE: int = 32
	def __init__(self, master: tk.Tk):
		super(MineSweeperGame, self).__init__(master)
		
		self.canvas: tk.Canvas = None
		self.__init_menu__()
		self.__init_data__(mode=eGameMode.NINE_BY_NINE)

	def main(self):
		self.mainloop()

	def quit(self):
		self.__destroy_canvas__()
		self.destroy()
		self.master.destroy()
		
	def on_mine_detected(self):
		if self.__show_restart_game_dialog__(message="You Lost! Restart Game?"):
			self.__init_data__(mode=self.game_mode)
		else:
			self.quit()

	def on_mouse_left_click(self, event: tk.Event):
		x: int = event.x // self.TILE_SIZE
		y: int = event.y // self.TILE_SIZE

		# print(x, y, event, self.board.get_value(x, y))

		if self.board.board[y][x].is_flagged:
			self.canvas.delete(self.board.unmark(x, y))
		if self.board.get_value(x=x, y=y) != MINE:
			if self.board.get_value(x, y) > 0:
				self.canvas.create_rectangle(x * self.TILE_SIZE, y * self.TILE_SIZE, (x + 1) * self.TILE_SIZE, (y + 1) * self.TILE_SIZE, fill="orange")
				self.board.open(x, y, self.canvas.create_text(x * self.TILE_SIZE + self.TILE_SIZE / 2, y * self.TILE_SIZE + self.TILE_SIZE / 2, anchor=tk.CENTER, font=("Arial", (self.TILE_SIZE * 2) // 3), text=str(self.board.get_value(x=x, y=y))))
			else:
				discovered: set[TileNode] = set()
				self.open_empty_tile_recursive(node=self.board.board[y][x], discovered=discovered)
		else:
			self.canvas.create_text(x * self.TILE_SIZE + self.TILE_SIZE / 2, y * self.TILE_SIZE + self.TILE_SIZE / 2, anchor=tk.CENTER, font=("Arial", (self.TILE_SIZE * 2) // 3), text="X", fill="red")
			self.on_mine_detected()
		
		if self.board.found_mine_count == len(self.board.mines):
			self.on_victory()

	def on_mouse_right_click(self, event: tk.Event):
		x: int = event.x // self.TILE_SIZE
		y: int = event.y // self.TILE_SIZE
		# print(event, self.board.board[y][x])
		if not self.board.board[y][x].is_flagged and not self.board.board[y][x].is_opened:
			self.board.mark(x, y, self.canvas.create_text(x * self.TILE_SIZE + self.TILE_SIZE / 2, y * self.TILE_SIZE + self.TILE_SIZE / 2, anchor=tk.CENTER, font=("Arial", (self.TILE_SIZE * 2) // 3), text="?"))
		elif self.board.board[y][x].is_flagged:
			self.canvas.delete(self.board.unmark(x, y))
		# print(self.board.found_mine_count)
		if self.board.found_mine_count == len(self.board.mines):
			self.on_victory()

	def on_mouse_wheel_click(self, event: tk.Event):
		x: int = event.x // self.TILE_SIZE
		y: int = event.y // self.TILE_SIZE
		print(f"(x, y): ({x}, {y}) = {self.board.board[y][x].value}")

	def on_victory(self):
		if self.__show_restart_game_dialog__(message="You Won! Restart Game?"):
			self.__init_data__(mode=self.game_mode)
		else:
			self.quit()

	def open_empty_tile_recursive(self, node: TileNode, discovered: Set[TileNode]):
		if node not in discovered and (node.value != MINE):
			if self.board.board[node.y][node.x].is_flagged:
				self.canvas.delete(self.board.unmark(node.x, node.y))
			if node.value == 0:
				self.board.open(node.x, node.y, self.canvas.create_rectangle(node.x * self.TILE_SIZE, node.y * self.TILE_SIZE, (node.x + 1) * self.TILE_SIZE, (node.y + 1) * self.TILE_SIZE, fill="blue"))
			elif node.value > 0:
				self.canvas.create_rectangle(node.x * self.TILE_SIZE, node.y * self.TILE_SIZE, (node.x + 1) * self.TILE_SIZE, (node.y + 1) * self.TILE_SIZE, fill="orange")
				self.board.open(node.x, node.y, self.canvas.create_text(node.x * self.TILE_SIZE + self.TILE_SIZE / 2, node.y * self.TILE_SIZE + self.TILE_SIZE / 2, anchor=tk.CENTER, font=("Arial", (self.TILE_SIZE * 2) // 3), text=str(self.board.get_value(x=node.x, y=node.y))))
			discovered.add(node)

			if node.value == 0:
				has_left_cell: bool = node.x > 0
				has_right_cell: bool = node.x < self.width - 1
				has_top_cell: bool = node.y > 0
				has_bottom_cell: bool = node.y < self.height - 1

				if has_top_cell:
					self.open_empty_tile_recursive(node=self.board.board[node.y - 1][node.x], discovered=discovered)
					if has_left_cell:
						self.open_empty_tile_recursive(node=self.board.board[node.y - 1][node.x - 1], discovered=discovered)
					if has_right_cell:
						self.open_empty_tile_recursive(node=self.board.board[node.y - 1][node.x + 1], discovered=discovered)
				if has_bottom_cell:
					self.open_empty_tile_recursive(node=self.board.board[node.y + 1][node.x], discovered=discovered)
					if has_left_cell:
						self.open_empty_tile_recursive(node=self.board.board[node.y + 1][node.x - 1], discovered=discovered)
					if has_right_cell:
						self.open_empty_tile_recursive(node=self.board.board[node.y + 1][node.x + 1], discovered=discovered)
				if has_left_cell:
					self.open_empty_tile_recursive(node=self.board.board[node.y][node.x - 1], discovered=discovered)
				if has_right_cell:
					self.open_empty_tile_recursive(node=self.board.board[node.y][node.x + 1], discovered=discovered)

	def __destroy_canvas__(self):
		if self.canvas is not None:
			self.canvas.destroy()

	def __draw_lines__(self):
		for y in range(0, self.height):
			self.canvas.create_line(0, y * self.TILE_SIZE, self.width * self.TILE_SIZE, y * self.TILE_SIZE)

		for x in range(0, self.width):
			self.canvas.create_line(x * self.TILE_SIZE, 0, x * self.TILE_SIZE, self.height * self.TILE_SIZE)

	def __init_data__(self, mode: eGameMode):
		self.__destroy_canvas__()
		self.game_mode: eGameMode = mode
		self.width: int = -1
		self.height: int = -1
		self.mine_count: int = -1

		if self.game_mode == eGameMode.NINE_BY_NINE:
			self.width = 9
			self.height = 9
			self.mine_count = eGameMode.NINE_BY_NINE.value
		elif self.game_mode == eGameMode.SIXTEEN_BY_SIXTEEN:
			self.width = 16
			self.height = 16
			self.mine_count = eGameMode.SIXTEEN_BY_SIXTEEN.value
		elif self.game_mode == eGameMode.SIXTEEN_BY_THIRTY:
			self.width = 30
			self.height = 16
			self.mine_count = eGameMode.SIXTEEN_BY_THIRTY.value
		else:
			assert False

		self.board: Board = Board(width=self.width, height=self.height, mine_count=self.mine_count)
		self.canvas: tk.Canvas = tk.Canvas(self, bg='#aaaaff',
											width=self.width * self.TILE_SIZE,
											height=self.height * self.TILE_SIZE, )
		self.canvas.pack()
		self.pack()
		self.canvas.focus_set()

		self.canvas.bind(sequence="<Button-1>", func=self.on_mouse_left_click)
		self.canvas.bind(sequence="<Button-2>", func=self.on_mouse_wheel_click)
		self.canvas.bind(sequence="<Button-3>", func=self.on_mouse_right_click)

		self.__draw_lines__()

	def __init_menu__(self):
		self.menu_bar: tk.Menu = tk.Menu(master=self)
		self.file_menu: tk.Menu = tk.Menu(master=self.menu_bar, tearoff=0)
		self.file_menu.add_command(label="9 X 9", command=lambda: self.__init_data__(mode=eGameMode.NINE_BY_NINE), )
		self.file_menu.add_command(label="16 X 16", command=lambda: self.__init_data__(mode=eGameMode.SIXTEEN_BY_SIXTEEN))
		self.file_menu.add_command(label="16 X 30", command=lambda: self.__init_data__(mode=eGameMode.SIXTEEN_BY_THIRTY))
		self.file_menu.add_separator()
		self.file_menu.add_command(label="Exit", command=self.quit)
		self.menu_bar.add_cascade(label="Game Mode", menu=self.file_menu)
		self.master.config(menu=self.menu_bar)

	def __show_restart_game_dialog__(self, message: str) -> bool:
		return mb.askyesno(title="Restart Game?", message=message)		
		

if __name__ == "__main__":
	root: tk.Tk = tk.Tk()
	root.title("Hello, MineSweeper!")
	game: MineSweeperGame = MineSweeperGame(master=root)
	game.main()