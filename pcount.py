#!/usr/bin/env python3
def partitions(s):
    "Generate all partitions of the given sequence"
    if len(s) == 0:
        yield []
    elif len(s) == 1:
        yield [ s ]
    elif len(s) > 1:
        yield [ s ]
        for i in range(1,len(s)):
            for p in partitions(s[i:]):
                yield [ s[:i] ] + p

import sys
for p in partitions(list(range(int(sys.argv[1])))):
    print(p)
