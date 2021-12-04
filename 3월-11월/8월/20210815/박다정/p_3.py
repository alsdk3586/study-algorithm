import sys

input = sys.stdin.readline
INF = sys.maxsize

v, e = map(int, input().rstrip().split(' '))
roads = [[INF for _ in range(v)] for _ in range(v)]
result = INF

for _ in range(e):
    start, end, cost = map(int, input().rstrip().split(' '))
    roads[start - 1][end - 1] = cost

# 모든 경로의 최소 비용 구하기
for k in range(v):
    for i in range(v):
        for j in range(v):
            if roads[i][k] + roads[k][j] < roads[i][j]:
                roads[i][j] = roads[i][k] + roads[k][j]

# i -> j 가 존재하고 j -> i가 존재하면 싸이클이 존재
for i in range(v):
    for j in range(v):
        if roads[i][j] == INF:
            continue
        # 싸이클이 존재하는 모든 값 비교
        if roads[i][j] > 0 and roads[j][i] > 0:
            result = min(result, roads[i][j] + roads[j][i])

if result == INF:
    print(-1)
else:
    print(result)
