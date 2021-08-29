import sys
from itertools import combinations

input = sys.stdin.readline
INF = sys.maxsize

n, m = map(int, input().rstrip().split(' '))
min_costs = [[INF for _ in range(n)] for _ in range(n)]

for _ in range(m):
    x, y = map(int, input().rstrip().split(' '))
    min_costs[x - 1][y - 1] = 1
    min_costs[y - 1][x - 1] = 1

results = []
# 모든 최소 비용 구하기
for k in range(n):
    for i in range(n):
        for j in range(n):
            if i == j:
                min_costs[i][j] = 0
                continue
            if min_costs[i][j] > min_costs[i][k] + min_costs[k][j]:
                min_costs[i][j] = min_costs[i][k] + min_costs[k][j]
# 모든 건물의 쌍을 구하기
cases = list(combinations([i for i in range(n)], 2))

for case in cases:
    one, two = case
    result = 0

    for i in range(n):
        if i == one or i == two:
            continue
        # 두 건물 가운데 가장 왕복이 최소인 비용을 선택
        result += min(min_costs[one][i] + min_costs[i][one], min_costs[two][i] + min_costs[i][two])
    results.append([one + 1, two + 1, result])
# 최소 비용, 첫번째 건물, 두번째 건물 순으로 정렬
results.sort(key=lambda x: (x[2], x[0], x[1]))

print(*results[0])
