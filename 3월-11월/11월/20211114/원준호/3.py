import sys

input = sys.stdin.readline
T = int(input())


for _ in range(T):
    N = int(input())

    ranks = []
    for _ in range(N):
        ranks.append(list(map(int, input().split(" "))))
    ranks.sort()

    answer = 0
    minRank = float("inf")
    for i in range(N):
        if minRank > ranks[i][1]:
            answer += 1

        minRank = min(minRank, ranks[i][1])

    print(answer)
