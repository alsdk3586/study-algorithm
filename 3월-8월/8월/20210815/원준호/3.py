V, E = map(int, input().split(" "))
matrix = [[float("inf") for _ in range(V+1)] for _ in range(V+1)]
for _ in range(E):
    a, b, c = map(int, input().split(" "))
    matrix[a][b] = c

# 플로이드 알고리즘을 거치면 i,j의 값은 i에서 j로 가는 최단거리가 된다.
for i in range(1,V+1):
    for j in range(1,V+1):
        for k in range(1,V+1):
            matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j])

answer = float("inf")
for i in range(1,V+1):
    answer = min(answer, matrix[i][i])

if answer == float("inf"):
    print(-1)
else:
    print(answer)
