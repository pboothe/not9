#!/usr/bin/env python3
def partitions(s, n):
    "Generate all partitions of the given sequence"
    if n == 0:
        yield [ s ]
    elif len(s) == 0:
        yield []
    elif len(s) == 1:
        yield [ s ]
    elif len(s) > 1:
        yield [ s ]
        for i in range(1,len(s)):
            for p in partitions(s[i:], n-1):
                yield [ s[:i] ] + p

def alphabetpartition(n=8):
    return partitions("abcdefghijklmnopqrstuvwxyz", 8)

if __name__ == '__main__':
    import sys
    for p in alphabetpartition():
        print(p)
