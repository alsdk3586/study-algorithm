import sys

input = sys.stdin.readline

n, m = map(int, input().rstrip().split(' '))
numbers = list(map(int, input().rstrip().split(' ')))
answer = []


def dfs(result):
    global answer
    if len(result) == m:
        answer.append(result[:])
        return

    for i in range(len(numbers)):
        result.append(numbers[i])
        dfs(result[:])
        result.pop()


numbers.sort()

dfs([])

for a in answer:
    print(*a)
