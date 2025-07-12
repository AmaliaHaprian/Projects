from board import OccupiedCellError, BoardError, Board
from game import Game

class PatternError(Exception):
    pass
class UI:
    def __init__(self,game):
        self.game=game

    def place_ui(self,command):
        command = command.split(' ')
        f=open('patterns.txt','rt')
        line=f.readline()
        while len(line)>0:
            if command[1].strip() in line:
                coord=command[2].split(',')
                return command[1],int(coord[0]),int(coord[1])
            line=f.readline()
        f.close()
        raise PatternError("Pattern not found")

    def play(self):
        ipt=input("Load existing game or play a new one?(load/new):")
        if ipt=='load':
            self.game.load()
        else:
            pass

        print(self.game.get_board())
        while True:
            command=input('Commands: place PATTERN X,Y /tick /save\n'
                          'Patterns: block/tub/blinker/beacon/spaceship\n'
                          'Enter command: '
                          )
            if 'place' in command:
                try:
                    pattern,x,y=self.place_ui(command.strip())
                    self.game.place(pattern,x-1,y-1)
                    print(self.game.get_board())
                except PatternError as e:
                    print(e)
                except OccupiedCellError as e:
                    print(e)
                except BoardError as e:
                    print(e)

            if 'tick' in command:
                command=command.split(' ')
                self.game.tick(int(command[1]))
                print(self.game.get_board())

            if 'save' in command:
                self.game.save()


if __name__=='__main__':
    board=Board()
    game=Game(board)
    ui=UI(game)
    ui.play()