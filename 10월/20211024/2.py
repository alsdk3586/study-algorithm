N, M = map(int, input().split(" "))

matrix = []

for _ in range(N):
    matrix.append(list(input()))

def move(idx, r_x, r_y, b_x, b_y):
    direction = {0:(-1,0), 1:(0,1), 2:(1,0), 3:(0,-1)}

    r_goal = False
    b_goal = False
    for _ in range(10):
        dx, dy = direction[idx]
        r_move, b_move = False, False
        if matrix[r_x+dx][r_y+dy] != "#":
            r_x, r_y = r_x + dx, r_y + dy
            r_move = True

        if matrix[b_x+dx][b_y+dy] != "#":
            b_x, b_y = b_x + dx, b_y + dy
            b_move = True

        if matrix[r_x][r_y] == "O":
            r_goal = True
            goal_idx = r_x, r_y
        if matrix[b_x][b_y] == "O":
            b_goal = True
            goal_idx = b_x, b_y

        # 두 공이 한번에 겹쳐지는 경우는 X
        if (r_x,r_y) == (b_x,b_y):
            if r_move:
                r_x, r_y = r_x - dx, r_y - dy
            if b_move:
                b_x, b_y = b_x - dx, b_y - dy

    if r_goal:
        r_x, r_y = goal_idx
    if b_goal:
        b_x, b_y = goal_idx

    return r_x,r_y,b_x,b_y

from collections import deque

def bfs():


    for i in range(N):
        for j in range(M):
            if matrix[i][j] == "R":
                r_x = i
                r_y = j
            elif matrix[i][j] == "B":
                b_x = i
                b_y = j
            elif matrix[i][j] == "O":
                goal = (i,j)

    queue = deque()
    queue.append([r_x, r_y, b_x, b_y, 0])

    visited = {}
    while queue:
        r_x, r_y, b_x, b_y, lvl = queue.popleft()

        if lvl > 10:
            continue

        if (b_x, b_y) == goal:
            continue

        if (r_x,r_y) == goal:
            return lvl

        # print(r_x,r_y,b_x,b_y)
        for i in range(4):
            nr_x, nr_y, nb_x, nb_y = move(i, r_x, r_y, b_x, b_y)
            #print("=>", r_x,r_y,b_x,b_y)
            if not visited.get((nr_x,nr_y,nb_x,nb_y)):
                visited[(nr_x,nr_y,nb_x,nb_y)] = True
                queue.append([nr_x,nr_y,nb_x,nb_y,lvl+1])

    return -1

print(bfs())
