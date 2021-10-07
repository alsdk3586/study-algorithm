from collections import deque
import sys

input = sys.stdin.readline
N, M = map(int, input().split(" "))

matrix = []
for _ in range(N):
    matrix.append(list(input()))


def bfs():
    queue = deque()
    visited = [[0] * M for _ in range(N)]
    for i in range(N):
        for j in range(M):
            if matrix[i][j] == "2":
                queue.append((i,j))
                visited[i][j] = 0

    while queue:
        x, y = queue.popleft()

        if "3" <= matrix[x][y]  <= "5":
            return visited[x][y]

        for dx, dy in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
            nx = x + dx
            ny = y + dy
            if 0 <= nx < N and 0 <= ny < M and visited[nx][ny] == 0 and matrix[nx][ny] != "1":
                queue.append((nx, ny))
                visited[nx][ny] = visited[x][y] + 1

    return 0

answer = bfs()
if answer == 0:
    print("NIE")
else:
    print("TAK")
    print(answer)
