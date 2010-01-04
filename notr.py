#!/usr/bin/env python3

from alphabetpartitions import alphabetpartition
from collections import defaultdict


wfile = open("words/wordlist")
total, _ = wfile.readline().split()
total = int(total)
words = [ (int(freq), word) for (freq, word) in (line.split() for line in wfile) ]
for partition in alphabetpartition():
    rdict = {}
    for i in range(len(partition)):
        for c in partition[i]:
            rdict[c] = str(i)

    typings = defaultdict(list)
    for freq, word in words:
        typed = "".join(rdict[c] for c in word)
        typings[typed].append((freq, word))

    keyshit = 0
    for typed in typings:
        typings[typed].sort()
        typings[typed].reverse()

        for i in range(len(typings[typed])):
            freq, word = typings[typed][i]
            keyshit += (len(typed) + i) * freq

    print(partition, keyshit/total)
    
