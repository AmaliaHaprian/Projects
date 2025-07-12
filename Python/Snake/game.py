from board import Board
class OutOfBoundsError(Exception):
    pass

from enum import Enum
class SnakeDirection(Enum):
    UP = 0
    DOWN = 1
    LEFT = 2
    RIGHT = 3

class Game:
    __move_rules = {SnakeDirection.UP.name: (-1, 0), SnakeDirection.DOWN.name: (1, 0), SnakeDirection.LEFT.name: (0, -1), SnakeDirection.RIGHT.name: (0, 1)}
    def __init__(self,board):
        self._board = board

    def get_board(self):
        return self._board

    def move(self, n=1):
        snake_dir=self._board.snake_dir
        move_x,move_y=Game.__move_rules[snake_dir.name]
        for cnt in range(n):
            current_x, current_y = self._board.snake[0]
            new_x,new_y=current_x+move_x,current_y+move_y
            if self._board.check_coord(new_x,new_y):
                if self._board.get_board()[new_x][new_y]==-1:
                    last_x,last_y=self._board.snake[-1]
                    self._board.snake.append((last_x-move_x,last_y-move_y))
                    self._board.add_apple()
                for i in range(len(self._board.snake)-1,0,-1):
                    self._board.snake[i]=self._board.snake[i-1]
                self._board.snake[0] = (new_x, new_y)
            else:
                raise OutOfBoundsError("Invalid move.Game over")
        self._board.update_board()

    def move_direction(self, direction):
        if direction == 'right':
            self._board.snake_dir=SnakeDirection.RIGHT
        elif direction == 'left':
            self._board.snake_dir=SnakeDirection.LEFT
        elif direction == 'up':
            self._board.snake_dir=SnakeDirection.UP
        elif direction == 'down':
            self._board.snake_dir=SnakeDirection.DOWN
        self.move()






