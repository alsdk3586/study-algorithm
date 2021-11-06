import sys

input = sys.stdin.readline
N, M, x, y, K = map(int, input().split())
dx = [0, 0, -1, 1]
dy = [1, -1, 0, 0]
dice = [0 for _ in range(7)]
arr = [list(map(int, input().split())) for _ in range(N)]
order = list(map(int, input().split()))


def move(direction):
    if direction == 1:
        dice[1], dice[3], dice[4], dice[6] = dice[3], dice[6], dice[1], dice[4]
    elif direction == 2:
        dice[1], dice[3], dice[4], dice[6] = dice[4], dice[1], dice[6], dice[3]
    elif direction == 3:
        dice[1], dice[2], dice[5], dice[6] = dice[2], dice[6], dice[1], dice[5]
    elif direction == 4:
        dice[1], dice[2], dice[5], dice[6] = dice[5], dice[1], dice[6], dice[2]


for i in order:
    nx = x+dx[i-1]
    ny = y+dy[i-1]
    if not 0 <= nx < N or not 0 <= ny < M:
        continue

    x, y = nx, ny
    move(i)

    if arr[x][y]:
        dice[1] = arr[x][y]
        arr[x][y] = 0
    else:
        arr[x][y] = dice[1]

    print(dice[6])
