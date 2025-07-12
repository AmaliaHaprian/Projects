from game import Game, OutOfBoundsError

class UI:
    def __init__(self,game):
        self.game=game

    def play(self):
        while True:
            print(self.game.get_board())
            command=input("Enter command: move N/ right/left/up/down: ")
            if 'move' in command:
                command=command.split()
                n=int(command[1])
                try:
                    self.game.move(n)
                except OutOfBoundsError as e:
                    print(e)
                    break
            else:
                self.game.move_direction(command)