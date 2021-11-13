H, W = map(int, input().split(" "))

matrix = []
for _ in range(H):
    matrix.append(list(input()))

N = int(input())
actions = []
for _ in range(N):
    actions.append(input().split(" "))

dao = 0
diz = 0
for i in range(H):
    for j in range(W):
        if matrix[i][j] == "D":
            dao = (i,j)
        if matrix[i][j] == "Z":
            diz = (i,j)

move = {"W":(-1,0), "S":(1,0), "D":(0,1), "A":(0,-1)}

answer = None
def go(now, path):
    global answer
    x,y = now
    idx = len(path)
    if matrix[x][y] == "Z":
        answer = path
        return

    if len(path) >= len(actions):
        return

    for key in actions[idx]:
        dx, dy = move[key]
        nx = x+dx
        ny = y+dy
        if 0 <= nx < H and 0 <= ny < W:
            if matrix[nx][ny] != "@":
                go((nx,ny), path+key)

go(dao, "")
if answer :
    print("YES")
    print(answer)
else:
    print("NO")
