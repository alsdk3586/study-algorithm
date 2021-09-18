import sys

sys.setrecursionlimit(10**6)

S = list(input())
T = list(input())

while len(T) != len(S):

    if T[-1] == "B":
        T.pop()
        T = T[::-1]
    else:
        T.pop()

if T == S:
    print(1)
else:
    print(0)
