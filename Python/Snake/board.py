from enum import Enum
from random import random, choice

from texttable import Texttable
class SnakeDirection(Enum):
    UP = 0
    DOWN = 1
    LEFT = 2
    RIGHT = 3

class Board:
    __move_rules={SnakeDirection.UP:(-1,0), SnakeDirection.DOWN:(1,0), SnakeDirection.LEFT:(0,-1), SnakeDirection.RIGHT:(0,1) }
    def __init__(self, size):
        self.size = size
        self.data=[]

        for i in range(size):
            self.data.append([0]*size)

        self.free_spaces=[]
        for i in range(size):
            for j in range(size):
                self.free_spaces.append([i, j])

        self._snake = []
        self.place_snake()
        self._snake_dir=SnakeDirection.UP

    @property
    def snake_dir(self):
        return self._snake_dir
    @snake_dir.setter
    def snake_dir(self,value):
        self._snake_dir=value

    @property
    def snake(self):
        return self._snake
    @snake.setter
    def snake(self, snake):
        self._snake=snake

    def free_spaces(self):
        return self.free_spaces

    def place_snake(self):
        self.data[(self.size-1)//2][(self.size-1)//2]=2
        self.data[(self.size-1)//2-1][(self.size-1)//2]=1
        self.data[(self.size-1)//2+1][(self.size-1)//2]=2
        self.free_spaces.remove([(self.size-1)//2,(self.size-1)//2])
        self.free_spaces.remove([(self.size-1)//2-1,(self.size-1)//2])
        self.free_spaces.remove([(self.size-1)//2+1,(self.size-1)//2])
        self.snake=[((self.size-1)//2-1,(self.size-1)//2),((self.size-1)//2,(self.size-1)//2), ((self.size-1)//2+1,(self.size-1)//2)]

    def update_board(self):
        for i in range(len(self.data)):
            for j in range(len(self.data)):
                if self.data[i][j]==2 or self.data[i][j]==1:
                    self.data[i][j]=0

        for elem in range(len(self.snake)):
            x,y=self.snake[elem]
            if elem==0:
                self.data[x][y]=1
            else:
                self.data[x][y]=2

    def place_apples(self, number):
        cnt=0
        while cnt<number:
            coord=choice(self.free_spaces)
            if self.check_for_apples(coord[0],coord[1]):
                self.data[coord[0]][coord[1]]=-1
                self.free_spaces.remove([coord[0],coord[1]])
                cnt+=1

    def check_coord(self,row,col):
        if not(0<=row<self.size and 0<=col<self.size):
            return False
        if self.data[row][col]==2 or self.data[row][col]==1:
            return False
        return True

    def check_for_apples(self, row, col):
        for i in [-1, 0, 1]:
            for j in [-1, 0, 1]:
                if 0<=row+i<self.size and 0<=col+j<self.size:
                    if self.data[row+i][col+j]==-1:
                        return False
        return True

    def board_state(self):
        spaces=[]
        for i in range(len(self.data)):
            for j in range(len(self.data)):
                if self.data[i][j]==0:
                    spaces.append((i,j))
        return spaces

    def add_apple(self):
        x,y=choice(self.board_state())
        self.data[x][y]=-1

    def get_board(self):
        return self.data

    def __str__(self):
        t=Texttable()
        for i in range(self.size):
            row=[]
            for j in range(self.size):
                if self.data[i][j]==1:
                    symbol='*'
                elif self.data[i][j]==2:
                    symbol='+'
                elif self.data[i][j]==-1:
                    symbol='a'
                else:
                    symbol=' '
                row.append(symbol)
            t.add_row(row)
        return t.draw()

if __name__ == '__main__':
    b=Board(7)
    print(b)
    b.place_apples(3)
    print(b)
