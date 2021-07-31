import sys

input = sys.stdin.readline

n = int(input().rstrip())
m = int(input().rstrip())

weights = [[0 for _ in range(n + 1)] for _ in range(n + 1)]

# 무게를 알 수 없는 경우는 서로 연결 되지 않은 경우
# 따라서 한 지점에서 다른 지점까지 방문하는 경우를 탐색

for _ in range(m):
    i, j = map(int, input().rstrip().split(' '))
    weights[i][j] = 1

# 한 지점에서 다른 지점까지 갈 수 있는 경우 확인
for i in range(1, n + 1):
    for j in range(1, n + 1):
        for k in range(1, n + 1):
            if weights[j][i] and weights[i][k]:
                weights[j][k] = 1

for i in range(1, n + 1):
    count = -1
    for j in range(1, n + 1):
        # i -> j 경우가 없고 j -> i 경우가 없으면 무게를 알 수 없는 경우
        if not weights[i][j] and not weights[j][i]:
            count += 1
    print(count)
