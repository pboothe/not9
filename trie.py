#!/usr/bin/env python3

from alphabetpartitions import alphabetpartition
from collections import defaultdict

class Trie:
    def __init__(self, partition):
        self.partition = partition
        self.children = {}
        self.words = []

    def __str__(self):
        s = ""
        for i in range(len(self.partition)):
            if i in self.children:
                s += "(" + str(i) + ", " + str(self.partition[i]) + ": " + str(self.children[i]) + ")"
        return "(" + str(self.words) + " " + s + ")"

    def insert(self, word, freq, index=0):
        if index == len(word):
            self.words.append((freq, word))
        else:
            c = word[index]
            for i in range(len(self.partition)):
                if c in self.partition[i]:
                    if i not in self.children:
                        self.children[i] = Trie(self.partition)
                    self.children[i].insert(word, freq, index+1)
                    break
            else:
                assert False, ("Missing character '%s'" % c)

    def totaldepth(self):
        self.words.sort()
        self.words.reverse()

        total = 0
        for i in range(len(self.words)):
            f,w = self.words[i]
            total += (len(w) + i) * f

        for c in self.children.values():
            total += c.totaldepth()
        return total

wfile = open("words/wordlist")
total, _ = wfile.readline().split()
total = int(total)
words = [ (int(freq), word) for (freq, word) in [line.split() for line in wfile] ]
for partition in [["abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"]]:
    t = Trie(partition)
    for f, w in words:
        t.insert(w, f)
    print(partition, t.totaldepth() / total)

if __name__ == '__main__':
    words = [ (5, "hi"), (6, "go"), (1, "hh") ]
    t = Trie(["hg", "io"])
    c = 0
    for f,w in words:
        print(str(t))
        t.insert(w,f)
        print(str(t))
        c += f
    print(t.totaldepth() / c)
