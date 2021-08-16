import sys

input = sys.stdin.readline

n, m, k = map(int, input().rstrip().split(' '))
양분 = [list(map(int, input().rstrip().split(' '))) for _ in range(n)]
trees = [[{} for _ in range(n)] for _ in range(n)]

for _ in range(m):
    x, y, age = map(int, input().rstrip().split(' '))
    trees[x-1][y-1][age] = 1

land = [[5 for _ in range(n)] for _ in range(n)]
deltas = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]


for _ in range(k):
    # 봄
    # 나무가 자신의 나이만큼 양분을 먹고 나이가 1증가
    # 나무는 자신의 칸에 있는 양분 만큼만 먹을 수 있다
    # 여러개의 나무가 있을 때 나이가 어린 나무먼저 양분을 먹는다
    # 땅에 양분이 부족할 경우 그 나무는 즉시 죽는다

    for i in range(n):
        for j in range(n):
            tmp = {}
            영양소 = 0

            for age in sorted(trees[i][j].keys()):

                if land[i][j] >= age * trees[i][j][age]:
                    tmp[age+1] = trees[i][j][age]
                    land[i][j] -= age * trees[i][j][age]
                else:
                    tree = land[i][j] // age

                    if not tree:
                        영양소 += (age // 2) * trees[i][j][age]
                        continue
                    land[i][j] -= tree * age
                    tmp[age + 1] = tree
                    영양소 += (age // 2) * (trees[i][j][age] - tree)

            trees[i][j] = tmp
            land[i][j] += 영양소

    # 가을
    # 5의 배수의 나이를 가진 나무 주위에 나이가 1인 나무가 생긴다
    for i in range(n):
        for j in range(n):
            current_tree_count = 0
            for age in sorted(trees[i][j].keys()):
                if age % 5 == 0:
                    current_tree_count += trees[i][j][age]

            if not current_tree_count:
                continue

            for delta in deltas:
                dx, dy = delta
                next_x = i + dx
                next_y = j + dy

                if -1 < next_x < n and -1 < next_y < n:
                    if 1 not in trees[next_x][next_y]:
                        trees[next_x][next_y][1] = current_tree_count
                    else:
                        trees[next_x][next_y][1] += current_tree_count
            # 겨울
            # 문제에 주어진 양분을 땅에 공급한다.
    for i in range(n):
        for j in range(n):
            land[i][j] += 양분[i][j]

result = 0
for i in range(n):
    for j in range(n):
        result += sum(trees[i][j].values())

print(result)
