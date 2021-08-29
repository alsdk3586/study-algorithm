R, C, M = map(int, input().split(" "))
matrix = [[None for _ in range(C)] for _ in range(R)]

for _ in range(M):
    r,c,s,d,z = map(int, input().split(" "))
    if d == 2:
        d = 3
    elif d == 3:
        d = 2
    matrix[r-1][c-1] = (z,s,d-1)

# 1:상, 2:하, 3:우, 4:좌  =>  0:상, 1:우, 2:하, 3:좌2
direction = [(-1,0),(0,1),(1,0),(0,-1)]

def move(i,j,s,d):
    while s >= 1:

        if d%2 == 0 and i == 0:
            d = 2
        elif d%2 == 0 and i == R-1:
            d = 0
        elif d%2 == 1 and j == 0:
            d = 1
        elif d%2 == 1 and j == C-1:
            d = 3

        di, dj = direction[d]
        i = i + di
        j = j + dj

        s -= 1

    return i,j,d

sharks = []
answer = 0
for y in range(C):
    # 사람 낚시
    for i in range(R):
        if matrix[i][y]:
            answer += matrix[i][y][0]
            matrix[i][y] = None
            break

    sharks = []
    for i in range(R):
        for j in range(C):
            # 상어가 있으면
            if matrix[i][j]:
                z,s,d = matrix[i][j]
                ni,nj,d = move(i,j,s,d)
                matrix[i][j] = None
                sharks.append([ni,nj,z,s,d])

    for i,j,z,s,d in sharks:
        if matrix[i][j] == None:
            matrix[i][j] = (z,s,d)
        else:
            if matrix[i][j][0] < z:
                matrix[i][j] = (z,s,d)

print(answer)
