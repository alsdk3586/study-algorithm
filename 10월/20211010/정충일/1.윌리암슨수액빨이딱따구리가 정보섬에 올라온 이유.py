import sys
from collections import deque

input = sys.stdin.readline
N, M = map(int, input().split())
arr = [list(map(int, input().strip())) for _ in range(N)]
visited = [[0]*M for _ in range(N)]
q = deque()
dx = [0,0,-1,1]
dy = [1,-1,0,0]

def bfs(x,y):
    global ans
    q.append([x,y])
    visited[x][y]+=1
    while q:
        x, y = q.popleft()
        for i in range(4):
            nx = x + dx[i]
            ny = y + dy[i]
            if 0<=nx<N and 0<=ny<M and arr[nx][ny] != 1 and not visited[nx][ny]:
                    q.append([nx,ny])
                    visited[nx][ny]= visited[x][y] +1
                    if arr[nx][ny] in (3,4,5):
                        print('TAK')
                        print(visited[x][y])
                        exit()
    print('NIE')

for i in range(N):
    for j in range(M):
        if arr[i][j]==2:
            bfs(i,j)