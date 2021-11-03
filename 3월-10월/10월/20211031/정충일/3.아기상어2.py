import sys
from collections import deque

input = sys.stdin.readline

N, M = map(int, input().split())
arr = []
dx = [-1, -1, -1, 0, 1, 0, 1, 1]
dy = [-1, 0, 1, 1, 1, -1, 0, -1]

q = deque()
for i in range(N):
    temp = list(map(int, input().split()))
    for t in range(M):
        if temp[t] == 1:
            q.append((i, t))
    arr.append(temp)


def bfs():
    while q:
        x, y = q.popleft()
        for k in range(8):
            nx, ny = x + dx[k], y + dy[k]
            if nx < 0 or nx >= N or ny < 0 or ny >= M:
                continue
            if arr[nx][ny] == 0:
                q.append([nx, ny])
                arr[nx][ny] = arr[x][y] + 1


bfs()
dist = 0
for i in range(N):
    for j in range(M):
        dist = max(arr[i][j], dist)

print(dist-1)
