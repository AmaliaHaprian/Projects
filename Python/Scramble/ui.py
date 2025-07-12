from random import choice

from game import Game
from repository import Repository
from sentence import Sentence, LetterError, WordError, UndoError


class UI:
    def __init__(self, sentence:Sentence):
        self.sentence = sentence

    def process_command(self, command:str):
        word1=command[5]
        letter1=command[7]
        word2=command[9]
        letter2=command[11]
        return word1,letter1,word2,letter2

    def play(self):
        print("Welcome to Scramble Game. Your score starts from the length of the sentence. Try to remake the sentence before you reach 0!")
        while True:
            print(self.sentence)
            if self.sentence.is_won()==1:
                print("You won!")
                break
            elif self.sentence.is_won()==-1:
                print("You lost!")
                break
            command=input("Commands: swap word1 letter1 word2 letter2(indexed from 0)\n "
                          "         undo\n"
                          "Enter command: ")
            if 'swap' in command:
                word1,letter1,word2,letter2 = self.process_command(command)
                try:
                    word1=int(word1)
                    letter1=int(letter1)
                    word2=int(word2)
                    letter2=int(letter2)
                    score=self.sentence.swap(word1,letter1,word2,letter2)
                    print("Your score is:",score)
                except ValueError:
                    print("Integers expected")
                except LetterError as e:
                    print(e)
                except WordError as e:
                    print(e)
            elif 'undo' in command:
                try:
                    self.sentence.undo()
                except UndoError as e:
                    print(e)



if __name__ == "__main__":
    repo=Repository()
    sentence=repo.select_sentence()
    s=Sentence(sentence)
    ui=UI(s)
    ui.play()
