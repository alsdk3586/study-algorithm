import sys

INF = sys.maxsize
input = sys.stdin.readline

n, k = map(int, input().rstrip().split(' '))
space = [list(map(int, input().rstrip().split(' '))) for _ in range(n)]
result = [INF]

# dfs로 주어진 위치에서 모든 경로를 탐색해서 최소 값을 갱신
def dfs(count, time, index, visited):
    if count == 0:
        result[0] = min(time, result[0])
        return
    for i in range(n):
        if not visited[i]:
            visited[i] = True
            dfs(count - 1, time + space[index][i], i, visited)
            visited[i] = False

# 플로이드 아샬로 최단 각 지점의 최단 거리를 갱신
for m in range(n):
    for i in range(n):
        for j in range(n):
            if i == j:
                continue
            space[i][j] = min(space[i][j], space[i][m] + space[m][j])

visited = [False for _ in range(n)]
visited[k] = True
dfs(n - 1, 0, k, visited)

print(result[0])
