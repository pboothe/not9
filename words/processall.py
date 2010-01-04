import sys
count,word,_,_ = input().split()
print(count,word)

oldcount = count
oldword = word
for line in sys.stdin:
    count,word,_,_ = line.split()
    count = int(count)

    if oldword == word:
        oldcount += count
    else:
        if oldword.isalpha():
            print(oldcount,oldword)
        oldcount = count
        oldword = word
print(oldcount,oldword)
