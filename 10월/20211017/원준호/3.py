matrix = []
for _ in range(9):
    matrix.append(list(map(int, input().split(" "))))

def check_num(x,y):


    # 세로
    all_num = set([1, 2, 3, 4, 5, 6, 7, 8, 9])
    for i in range(9):
        if matrix[i][y] != 0:
            all_num.remove(matrix[i][y])
    if len(all_num) == 1:
        return list(all_num)[0]

    # 가로
    all_num = set([1, 2, 3, 4, 5, 6, 7, 8, 9])
    for j in range(9):
        if matrix[x][j] != 0:
            all_num.remove(matrix[x][j])
    if len(all_num) == 1:
        return list(all_num)[0]

    # 사각형
    all_num = set([1, 2, 3, 4, 5, 6, 7, 8, 9])
    s_x = x // 3
    s_y = y // 3
    for i in range(s_x*3, s_x*3+3):
        for j in range(s_y*3, s_y*3+3):
            if matrix[i][j] != 0:
                all_num.remove(matrix[i][j])

    if len(all_num) == 1:
        return list(all_num)[0]
    else:
        return None

N = 0
for i in range(9):
    for j in range(9):
        if matrix[i][j] == 0:
            N += 1

def go(n):
    if n >= N:
        for row in matrix:
            print(*row)
        exit()

    for i in range(9):
        for j in range(9):
            if matrix[i][j] == 0:
                ret = check_num(i,j)
                if ret:
                    matrix[i][j] = ret
                    go(n+1)
                    matrix[i][j] = 0

go(0)
