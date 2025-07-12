from board import Board
from game import Game
from ui import UI


class Settings:
    __instance = None
    @staticmethod
    def get_instance():
        if Settings.__instance is not None:
            return Settings.__instance

        fin=open('settings.properties','rt')
        lines=fin.readlines()
        fin.close()

        settings={}
        for line in lines:
            tokens=line.strip().split('=')
            settings[tokens[0].strip()]=tokens[1].strip()
        size=settings['N']
        size=int(size)
        apples=settings['apples']
        apples=int(apples)
        Settings.__instance = Settings(size,apples)
        return Settings.__instance

    def __init__(self,size,apples):
        self._size=size
        self._apples=apples

    @property
    def size(self):
        return self._size
    @property
    def apples(self):
        return self._apples
if __name__=='__main__':
    s=Settings.get_instance().size
    b=Board(s)
    a=Settings.get_instance().apples
    b.place_apples(a)
    g=Game(b)
    ui=UI(g)
    ui.play()