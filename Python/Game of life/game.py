from copy import deepcopy

from board import Board


class Game:
    def __init__(self,board):
        self.board=board
        self.pattern=[]

    def load_pattern(self,pattern):
        f=open('patterns.txt','rt')
        line=f.readline()
        while line:
            tokens=line.split('=')
            if tokens[0]==pattern:
                matrix=tokens[1].strip()
                self.pattern=self.compute_matrix(matrix)
                break
            line=f.readline()
        f.close()

    @staticmethod
    def compute_matrix(param):
        final_matrix=[]
        row=[]
        for char in param:
            if char=='[':
                row=[]
            elif char==']':
                final_matrix.append(row)
            elif char==',':
                continue
            else:
                row.append(int(char))
        return final_matrix

    def place(self, pattern,x,y):
        self.load_pattern(pattern)
        self.board.place(self.pattern,x,y)

    def get_board(self):
        return self.board

    def tick(self, n):
        return self.board.tick(n)

    def load(self):
        board=[]
        f=open('game.txt','rt')
        line=f.readline()
        while line:
            row=[]
            tokens=line.strip().split(',')
            for char in tokens:
                if char=='0' or char=='1':
                    row.append(int(char))
            board.append(row)
            line=f.readline()
        self.board.set_board(board)
        f.close()

    def save(self):
        f=open('game.txt','wt')
        board=self.board.get_board()
        for i in range(len(board)):
            for j in range(len(board)):
                f.write(str(board[i][j])+',')
            f.write('\n')
        f.close()
