N, M = map(int, input().split(" "))
x, y, d = map(int, input().split(" "))

matrix = []
for _ in range(N):
    matrix.append(list(map(int, input().split(" "))))

if d == 3:
    d = 1
elif d == 1:
    d = 3

# 0:북, 1:동, 2:남, 3:서  =>  0:북, 1:서, 2:남, 3:동
direction = {0: (-1, 0), 1: (0, -1), 2: (1, 0), 3: (0, 1)}

cleaning = 1
matrix[x][y] = 2
while True:
    # a,b
    for _ in range(4):
        d = (d+1)%4
        dx, dy = direction[d]
        nx = x + dx
        ny = y + dy
        if 0 <= nx < N and 0 <= ny < M and matrix[x + dx][y + dy] == 0:
            x, y = nx, ny
            cleaning += 1
            matrix[x][y] = 2
            break
    else:
        # c
        back_d = (d+2)%4
        dx, dy = direction[back_d]
        nx = x + dx
        ny = y + dy

        # d
        if not (0 <= nx < N and 0 <= ny < M) or matrix[nx][ny] == 1:
            break

        x, y = nx, ny

print(cleaning)
