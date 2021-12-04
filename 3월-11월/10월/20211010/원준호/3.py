from collections import deque

N, M = map(int, input().split(" "))
matrix = []
for _ in range(M) :
    matrix.append(list(map(int, input().split(" "))))

def toBinary(num):
    binary = ""
    while num >= 1:
        binary = str(num%2) + binary
        num = num // 2
    binary = binary.zfill(4)
    return binary

for i in range(M):
    for j in range(N):
        matrix[i][j] = toBinary(matrix[i][j])

visited = [[-1] * N for _ in range(M)]

def bfs(start, color):

    def check(x, y, binary):
        can = []
        cant = []

        if binary[0] == "0":
            can.append((x+1,y))
        else:
            cant.append((x+1,y))

        if binary[1] == "0":
            can.append((x,y+1))
        else:
            cant.append((x,y+1))

        if binary[2] == "0":
            can.append((x-1,y))
        else:
            cant.append((x-1,y))

        if binary[3] == "0":
            can.append((x,y-1))
        else:
            cant.append((x,y-1))

        return can, cant

    queue = deque()
    queue.append(start)
    cants = []
    visited[start[0]][start[1]] = color
    area = 1
    while queue:
        x, y = queue.popleft()
        binary = matrix[x][y]

        can, cant = check(x,y,binary)

        for nx, ny in can:
            if 0 <= nx < M and 0 <= ny < N and visited[nx][ny] == -1:
                queue.append((nx, ny))
                visited[nx][ny] = color
                area += 1
        cants.extend(cant)

    return area, cants

color = -1
cantss = []
areas = []
for i in range(M):
    for j in range(N):
        if visited[i][j] == -1:
            color += 1
            area, cants = bfs((i,j), color)
            cantss.append(cants)
            areas.append(area)

answer = 0
for i in range(len(areas)):
    near_area = 0
    for x , y in cantss[i]:
        if 0 <= x < M and 0 <= y < N:
            if i != visited[x][y]:
                near_area = max(near_area, areas[visited[x][y]])

    answer = max(answer, areas[i] + near_area)

print(len(areas))
print(max(areas))
print(answer)
