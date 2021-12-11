import sys

input = sys.stdin.readline

board = [list(map(int, input().rstrip().split(' '))) for _ in range(9)]
locations = []

for i in range(9):
    for j in range(9):
        if board[i][j] == 0:
            locations.append([i, j])


def print_answer():
    for row in board:
        print(*row)


def is_duplicated(x, y, target):
    for i in range(9):
        if board[x][i] == target:
            return True
        if board[i][y] == target:
            return True

    row = (x // 3) * 3
    column = (y // 3) * 3

    for i in range(row, row + 3):
        for j in range(column, column + 3):
            if board[i][j] == target:
                return True
    return False


def dfs(current):
    if current == len(locations):
        print_answer()
        exit(0)

    x, y = locations[current]

    for i in range(1, 10):
        if not is_duplicated(x, y, i):
            board[x][y] = i
            dfs(current + 1)
            board[x][y] = 0


dfs(0)
