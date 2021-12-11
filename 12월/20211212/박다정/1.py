import sys

input = sys.stdin.readline

n = int(input().rstrip())

cities = [list(map(int, input().rstrip().split(' '))) for _ in range(n)]
answer = sys.maxsize


def dfs(start, current, accumulate, visited):
    global answer
    if len(visited) == n:
        if cities[current][start] > 0:
            answer = min(answer, accumulate + cities[current][start])
        return
    for i in range(len(cities[current])):
        if cities[current][i] == 0 or i == start or i in visited:
            continue
        visited.append(i)
        dfs(start, i, accumulate + cities[current][i], visited)
        visited.pop()


for i in range(len(cities)):
    dfs(i, i, 0, [i])

print(answer)
