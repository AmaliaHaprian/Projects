from copy import deepcopy

from texttable import Texttable

class OccupiedCellError(Exception):
    pass
class BoardError(Exception):
    pass

class Board:
    def __init__(self):
        self.size=8
        self.data=[]
        for i in range(self.size):
            self.data.append([0]*self.size)
        self.free_spaces=[]
        for i in range(self.size):
            for j in range(self.size):
                self.free_spaces.append([i,j])

    def set_board(self,board):
        self.data=board

    def place(self, pattern,x,y):
        for i in range(len(pattern)):
            for j in range(len(pattern)):
                if pattern[i][j] == 1 and (x + i  > 7 or j + y > 7):
                    raise BoardError("Live cell outside of board.")
                elif pattern[i][j] == 0 and (x + i  > 7 or j + y > 7):
                    continue
                elif self.data[x + i ][j + y] == 1 and pattern[i][j] == 0:
                    continue
                elif self.data[x + i ][j + y ] == 1 and pattern[i][j] == 1:
                    raise OccupiedCellError("You cannot overlap a live cell.")
        for i in range(len(pattern)):
            for j in range(len(pattern)):
                if pattern[i][j] == 1 and (x + i  > 7 or j + y  > 7 or x + i - 1 < 0 or y + j - 1 < 0):
                    raise BoardError("Live cell outside of board.")
                elif pattern[i][j] == 0 and (x + i > 7 or j + y > 7):
                    continue
                elif self.data[x + i ][j + y ] == 1 and pattern[i][j] == 0:
                    continue
                elif self.data[x + i ][j + y ] == 1 and pattern[i][j] == 1:
                    raise BoardError("You cannot overlap a live cell.")
                else:
                    self.data[x + i ][j + y ] = pattern[i][j]

    def get_board(self):
        return self.data

    def __str__(self):
        t=Texttable()
        for i in range(self.size):
            row=[]
            for j in range(self.size):
                if self.data[i][j]==1:
                    row.append("X")
                else:
                    row.append(" ")
            t.add_row(row)
        return t.draw()

    def check_surrounding(self,x,y):
        cnt=0
        for i in [-1, 0, 1]:
            for j in [-1, 0, 1]:
                if 0<=x+i<8 and 0<=y+j<8:
                    if self.data[x+i][y+j] == 1 and not(i==0 and j==0):
                        cnt+=1
        return cnt

    def tick(self, n):
        for _ in range(n):

            copy=deepcopy(self.data)
            temp=deepcopy(self.free_spaces)
            for i in range(8):
                for j in range(8):
                    #cop2=deepcopy(copy)
                    if self.data[i][j]==1:
                        nbh=self.check_surrounding(i,j)
                        if nbh<2 or nbh>3:
                            copy[i][j]=0
                            #self.free_spaces.append([i,j])
                            temp.append([i,j])
                    else:
                        nbh=self.check_surrounding(i,j)
                        if nbh==3:
                            copy[i][j]=1
                            #self.free_spaces.remove([i,j])
                            if [i,j] in temp:
                                temp.remove([i,j])
            self.data=copy
            self.free_spaces=temp

        return self.data, self.free_spaces