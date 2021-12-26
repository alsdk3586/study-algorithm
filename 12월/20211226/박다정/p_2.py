import sys
import collections

input = sys.stdin.readline

n, m = map(int, input().rstrip().split(' '))
basket = [list(map(int, input().rstrip().split(' '))) for _ in range(n)]
cases = collections.deque([list(map(int, input().rstrip().split(' '))) for _ in range(m)])
cloud = [[n, 1], [n, 2], [n - 1, 1], [n - 1, 2]]
increase_water_location = []
DIAGONAL = [[-1, -1], [1, 1], [-1, 1], [1, -1]]

def is_diagonal(x, y):
    if x == -1 or y == -1:
        return False
    if x == n or y == n:
        return False
    return True


def move(direction):
    if direction == 1:
        for c in cloud:
            c[1] -= 1

            if c[1] == 0:
                c[1] = n

    elif direction == 2:
        for c in cloud:
            c[0] -= 1
            c[1] -= 1

            if c[0] == 0:
                c[0] = n
            if c[1] == 0:
                c[1] = n
    elif direction == 3:
        for c in cloud:
            c[0] -= 1
            if c[0] == 0:
                c[0] = n

    elif direction == 4:
        for c in cloud:
            c[0] -= 1
            c[1] += 1

            if c[0] == 0:
                c[0] = n
            if c[1] == n + 1:
                c[1] = 1
    elif direction == 5:
        for c in cloud:
            c[1] += 1
            if c[1] == n + 1:
                c[1] = 1

    elif direction == 6:
        for c in cloud:
            c[0] += 1
            c[1] += 1

            if c[0] == n + 1:
                c[0] = 1
            if c[1] == n + 1:
                c[1] = 1
    elif direction == 7:
        for c in cloud:
            c[0] += 1
            if c[0] == n + 1:
                c[0] = 1
    else:
        for c in cloud:
            c[0] += 1
            c[1] -= 1

            if c[0] == n + 1:
                c[0] = 1
            if c[1] == 0:
                c[1] = n


while cases:
    direction, distance = cases.popleft()
    destroy_cloud_location = [[0 for _ in range(n)] for _ in range(n)]

    for _ in range(distance):
        move(direction)
    for c in cloud:
        x, y = c
        basket[x - 1][y - 1] += 1
        destroy_cloud_location[x - 1][y - 1] = 1
        increase_water_location.append([x - 1, y - 1])

    for location in cloud:
        x, y = location
        for delta in DIAGONAL:
            next_x = x - 1 + delta[0]
            next_y = y - 1 + delta[1]
            if is_diagonal(next_x, next_y) and basket[next_x][next_y] > 0:
                basket[x - 1][y - 1] += 1
    cloud = []
    for i in range(n):
        for j in range(n):

            if basket[i][j] >= 2 and destroy_cloud_location[i][j] == 0:
                cloud.append([i + 1, j + 1])
                basket[i][j] -= 2
result = 0

for b in basket:
    result += sum(b)
print(result)
