N, M = map(int, input().split(" "))

matrix = [[float("inf") for _ in range(N+1)] for _ in range(N+1)]

for _ in range(M):
	a,b = map(int, input().split(" "))
	matrix[a][b] = 1
	matrix[b][a] = 1

for i in range(1, N+1):
    matrix[i][i] = 0

for k in range(1,N+1):
	for i in range(1, N+1):
		for j in range(1, N+1):
			matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j])

result_val = float("inf")
result_xy = [0,0]
for i in range(1,N):
    for j in range(i+1, N+1):
        answer_val = 0
        for k in range(1, N+1):
            answer_val += min(matrix[k][i], matrix[k][j])*2
        if result_val > answer_val:
            result_val = answer_val
            result_xy = [i,j]
print(result_xy[0], result_xy[1], result_val)
