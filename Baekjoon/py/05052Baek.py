import sys
sys.setrecursionlimit(200000)
class Trie :
    def __init__(self) :
        self.count = 0
        self.child = {}
    def insert(self, s, pos) :
        self.count = self.count + 1
        if pos == len(s) :
            return
        if s[pos] not in self.child:
            self.child[s[pos]] = Trie()
        self.child[s[pos]].insert(s, pos + 1)
    def find(self, s, pos) :
        if len(s) == pos :
            return pos
        if self.count == 1 :
            return pos
        return self.child[s[pos]].find(s, pos + 1)
def solution(words):
    answer = 0
    trie = Trie()
    for s in words :
        trie.insert(s, 0)
    for s in words :
        answer = answer + trie.find(s, 0)
    return answer
