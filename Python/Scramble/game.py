from sentence import Sentence


class Game:
    def __init__(self,sentence:Sentence):
        self.sentence = sentence
        self.score=self.get_score()

    def get_score(self):
        score=0
        for letter in self.sentence.sentence:
            if letter!=' ':
                score+=1
        return score

    def __str__(self):
        return self.sentence.scrambled