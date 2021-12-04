def dfs(depth):
      if depth == blank_num:
          for v in board:
              print(' '.join(map(str, v)))
          exit(0)

      y, x = pos[depth]
      for n in range(1, 10):
          if not row_arr[y][n] and not col_arr[x][n] and not box_arr[y//3*3+x//3][n]:
              row_arr[y][n] = col_arr[x][n] = box_arr[y//3*3+x//3][n] = True
              board[y][x] = n
              dfs(depth+1)
              row_arr[y][n] = col_arr[x][n] = box_arr[y//3*3+x//3][n] = False
              board[y][x] = 0

board = [list(map(int, input().split())) for _ in range(9)]
row_arr = [[False]*10 for _ in range(10)]
col_arr = [[False]*10 for _ in range(10)]
box_arr = [[False]*10 for _ in range(10)]
pos = []

for r in range(9):
    for c in range(9):
        if not board[r][c]: 
            pos.append([r, c])
        else:
            row_arr[r][board[r][c]] = True
            col_arr[c][board[r][c]] = True
            box_arr[r//3*3+c//3][board[r][c]] = True

blank_num = len(pos)
dfs(0)