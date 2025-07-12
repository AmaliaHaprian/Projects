from random import choice

class LetterError(Exception):
    pass
class WordError(Exception):
    pass
class UndoError(Exception):
    pass
class Sentence:
    def __init__(self,sentence:str):
        self._sentence = sentence
        self._scrambled=self.scramble()
        self.score = self.get_score()
        self.history=[]
    @property
    def sentence(self):
        return self._sentence

    @property
    def scrambled(self):
        return self._scrambled
    @scrambled.setter
    def scrambled(self,scrambled):
        self._scrambled=scrambled

    def __len__(self):
        return len(self._sentence)

    def swap(self, word1,letter1,word2,letter2):

        words=self.scrambled.split()
        if len(words)<word1 or len(words)<word2:
            raise WordError("Not enough words")
        w1=words[word1]
        w2=words[word2]
        l1=w1[letter1]
        l2=w2[letter2]
        if len(w1)<letter1 or len(w2)<letter2:
            raise LetterError("Not enough letters")

        self.history.append(self.scrambled)
        if word1!=word2:
            new_1=''
            new_2=''
            for i in range(len(w1)):
                if i==letter1:
                    new_1=new_1+l2
                else:
                    new_1=new_1+w1[i]
            for i in range(len(w2)):
                if i==letter2:
                    new_2=new_2+l1
                else:
                    new_2=new_2+w2[i]
            for i in range(len(words)):
                if i==word1:
                    words[i]=new_1
                elif i==word2:
                    words[i]=new_2
        else:
            new=''
            for i in range(len(w1)):
                if i==letter1:
                    new=new+l2
                elif i==letter2:
                    new=new+l1
                else:
                    new=new+w1[i]
            for i in range(len(words)):
                if i==word1:
                    words[i]=new

        self.scrambled=' '.join(words)
        self.score-=1
        return self.score


    def scramble(self):
        copy=[]
        l=len(self._sentence)
        for i in range(l):
            copy.append('0')
        letters=[]
        list_of_words=self._sentence.split()
        cnt=0
        for i in range(len(list_of_words)):

            word=list_of_words[i]
            for j in range(len(word)):
                if j==0 or j==len(word)-1:
                    copy[cnt+j]=word[j]
                else:
                    letters.append(word[j])
            cnt += len(word)
            if cnt<len(self._sentence):
                copy[cnt]=' '
                cnt+=1

        for i in range(len(copy)):
            if copy[i]=='0':
                copy[i]=choice(letters)
                letters.remove(copy[i])
        return ''.join(copy)

    def get_score(self):
        score=0
        for letter in self.sentence:
            if letter!=' ':
                score+=1
        return score

    def undo(self):
        if len(self.history)==1:
            self.scrambled=self.history[0]
            self.history.pop()
        elif len(self.history)>1:
            self.history.pop()
            self.scrambled=self.history[-1]
        else:
            raise UndoError("Nothing to undo")

    def is_won(self):
        if self.score==0:
            return -1
        if self.scrambled==self.sentence:
            return 1
        else:
            return 0

    def __str__(self):
        return self.scrambled

if __name__=='__main__':
    s=Sentence('The quick brown fox jumps over the lazy dog')
    print(s.scramble())


