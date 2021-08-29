N, M, K = map(int, input().split(" "))

food = []
for _ in range(N):
    food.append( list(map(int, input().split(" "))))

#matrix = [[{"food":5, "tree":[]} for _ in range(N)] for _ in range(N)]
matrix_tree = [[[] for _ in range(N)] for _ in range(N)]
matrix_food = [[5 for _ in range(N)] for _ in range(N)]
for _ in range(M):
    x, y, age = map(int, input().split(" "))
    matrix_tree[x-1][y-1].append(age)

for _ in range(K):
    for x in range(N):
        for y in range(N):
            if matrix_tree[x][y]:
                #     봄 : 자신의 나이만큼 양분을 먹고 나이 1 증가
                #     여러 나무 있으면 나이가 젤 어린 나무 부터 먹는다:
                #     나이 만큼 먹지 못하면 즉시 죽는다
                for idx in range(len(matrix_tree[x][y])-1, -1, -1):
                    # 어린 나무부터 먹어
                    if matrix_tree[x][y][idx] <= matrix_food[x][y]:
                        matrix_food[x][y] -= matrix_tree[x][y][idx]
                        matrix_tree[x][y][idx] += 1
                    # 양분 없으면 죽어
                    else:
                        # 여름 : 죽은 나무 양분으로
                        for died in matrix_tree[x][y][:idx+1]:
                            matrix_food[x][y] += died//2
                        matrix_tree[x][y] = matrix_tree[x][y][idx+1:]
                        break

    for x in range(N):
        for y in range(N):
            cnt = 0
            #       가을 : 나이가 5배수이면 인접한 8칸에 나이 1인 나무가 생김
            for tree in matrix_tree[x][y]:
                if tree % 5 == 0:
                    cnt += 1
            if cnt:
                for dx, dy in [(-1,-1),(-1,0),(-1,1),(0,-1),(0,1),(1,-1),(1,0),(1,1)]:
                    nx = x+dx
                    ny = y+dy
                    if 0 <= nx < N and 0 <= ny < N:
                        matrix_tree[nx][ny] += [1]*cnt

            # 겨울 : 양분 주입
            matrix_food[x][y] += food[x][y]

answer = 0
for x in range(N):
    for y in range(N):
        answer += len(matrix_tree[x][y])
print(answer)
# 양분은 5로 시작
# 나무는 M개
#
# 봄 : 자신의 나이만큼 양분을 먹고 나이 1 증가
#     여러 나무 있으면 나이가 젤 어린 나무 부터 먹는다:
#     나이 만큼 먹지 못하면 즉시 죽는다
#
# 여름 : 죽은 나무가 양분으로 변한다.
#         죽은 나무 나이의 반이 양분으로 추가된다 (int)
#
# 가을 : 나이가 5배수이면 번식.
#         인접한 8칸에 나이 1인 나무가 생김
#
#
# 겨울 : 양분을 주입 (A)
