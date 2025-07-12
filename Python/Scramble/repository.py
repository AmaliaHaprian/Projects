from random import choice


class Repository:
    def __init__(self):
        self.file='sentences.txt'
        self.sentences = []
        self.load()

    def load(self):
        f=open(self.file,'rt')
        line=f.readline()
        while line:
            self.sentences.append(line)
            line=f.readline()
        f.close()

    def select_sentence(self):
        return choice(self.sentences)

