import sys

input = sys.stdin.readline
E, S, M = map(int, input().split())
x, y, z = 1, 1, 1
result = 1

while not (E == x and S == y and M == z):
    x += 1
    y += 1
    z += 1
    result += 1
    if x == 16:
        x = 1
    if y == 29:
        y = 1
    if z == 20:
        z = 1

print(result)
